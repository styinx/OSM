
# OSM

__TOC__:

- [Introduction](#introduction)
    - [Features](#features)
    - [Installation](#installation)
    - [Compilation](#compilation)
    - [Execution](#execution)
- [Approach](#approach)
- [Implementation](#implementation)
    - [Data Structures and Primitives](#data-structures-and-primitives)
    - [Adjacency Array](#adjacency-array)
    - [Grid](#grid)
    - [Route search](#route-search)
    - [Examples](#examples)
    - [Limitations](#limitations)
- [Conclusion](#conclusion)

## Introduction
<a id="introduction"/>

The idea of this project is to create a route between to points on a map and include a number of attractions along this route.


### Features
<a id="features"/>

__Major__:
- Route navigation from a start point to a target.
- Selectable tourism spots which can be added to a route.
- A possible configuration for automatic selection in a given range.
- Route navigation with different transportation types (car, bicycle, by foot).

__Minor__:
- The map coordinates of the UI are selected to the map bounds with an appropriate zoom.
- Distance and duration calculation for a route.
- Expandable UI (separated from leaflet map).
- Communication between backend and frontend through QTWebchannel.

## Installation
<a id="installation"/>

Github: [Project repository](https://github.com/styinx/OSM)  
Build status: [![Build Status](https://travis-ci.com/styinx/OSM.svg?branch=master)](https://travis-ci.com/styinx/OSM)
  
__Requirements__:
- inphos42/osmpbf  
- zlib  
- libprotobuf-dev  
- protobuf-compiler  
- libqt5webengine5  
- libqt5widgets5  
- qtwebengine5-dev

All required dependencies can be installed with the install script in the `scripts/` directory. The script creates a virtual python environment and install *conan* which will load available packages from conan-center. All other dependencies will be installed over *apt*. Lastly it will clone the dependencies that are available on github.

The script can be used from the command line with the following command. You have to chose the root directory of the repository.
```
$ ./scripts/install.sh
```

### Compilation
<a id="compilation"/>

The project can be compiled with the compile script int the `scripts/` directory which uses cmake. First, the script compiles the osmpbf library. After that the OSM poject is compiled. The executables are located at `build/bin/`.

The script can be used from the command line with the following command. You have to chose the root directory of the repository.
```  
./scripts/compile.sh  
```

### Execution
<a id="execution"/>

From repository root directory:
```
./build/bin/OSM <relative path to pbf file>
```

From bin directory:
```
./OSM <relative path to the pbf file>
```

__Additional Notes__:

On some occasions it happend that the program crashed during the reading of a *.pdf file. 
The error message is attached below. 
This error is caused by the protobuf or/and the osmpbf library and occurs ~once for every 10 executions.
It is not caused by the implementation of this project.
```
[libprotobuf FATAL /usr/include/google/protobuf/repeated_field.h:1078] CHECK failed: (index) < (current_size_): 
terminate called after throwing an instance of 'google::protobuf::FatalException'
  what():  CHECK failed: (index) < (current_size_): 
Aborted (core dumped)
```

## Approach
<a id="approach"/>

- attractions
- route concatenation
- pbf

## Implementation
<a id="implementation"/>

![Class diagram](https://github.com/styinx/OSM/blob/master/report/class_diagram.png)

### Data Structures and Primitives
<a id="data_structures"/>

In the following we introduce the most important data structures that were used to represent nodes and edges.

The `Node` structure occupies 24 Bytes in memory which is the smallest possible value.
Since we want to identify a node by its unique 64 bit id and we have to store the nodes location with the latitude and longitude (each 32 bits) we already occupy 16 bytes.
Furthermore, we need to store additional information for which we have 64/32 bit left which depends on the systems architecture.
We decided to not use double precision floating numbers for the latitude and longitude values since single precision is good enough for this use case.
The coordinates are accurate within a 10 centimeters range.

To reduce the size of the `Node` data structure even more we decided to use a bit mask to store additional tourist information.
How this bit mask is used is described later in this work.
 

```c++
struct Node
{
    Uint64 id   = 0;
    float lat   = 0;
    float lon   = 0;
    Uint16 town = 0;
    Byte mask   = 0;
    // 8 - 40 bits padding
}
```

The `Edge` data structure occupies also 24 bytes.
Firstly, we need to store the ids of the source and target nodes that are part of the edge which takes 16 bytes.
Secondly, the distance of the edge is stored which is used later in the route search for the weights.
This takes another 4 bytes.
In the last 32 bits the speed and the flag values are stored.
Like in the `Node` structure we use a bit mask to store the road types of the edge.
This uses the available space efficiently.

```c++
struct Edge
{
    Uint64 source  = 0;
    Uint64 target  = 0;
    float distance = 0;
    Byte speed     = 0;
    Byte mask      = 0;
    Byte tourism   = 0;
    bool oneway    = false;
    // 0 bits padding
}
```

In order to collect the available attractions that are connected to the street network we extracted the `tourism` [key](https://wiki.openstreetmap.org/wiki/Key:tourism) from the nodes and edges in the `*.pbf` files.


```c++
enum class NodeTypeMask : Byte
{
    HAS_EDGES           = 0x01,
    TOWN                = 0x02,
    TOURISM             = 0x04,
    TOURISM_ATTRACTION  = 0x08,
    TOURISM_INFORMATION = 0x0F,
    TOURISM_CULTURE     = 0x10,
    TOURISM_SLEEPING    = 0x20,
    TOURISM_UNKNOWN     = 0x40
};
```

Like the attraction flags, the street types are also read from the `*.pbf` files.
In this case the highway tag [key](https://wiki.openstreetmap.org/wiki/Key:highway) is selected.
For each type of transportation (by foot, bicycle, car) there exists a separate flag for the street.
Every different type of street from motorway to living street has its onw bit set in the bit mask.
Streets that do not match the existing road types such as walkways or smaller paths are given the type of a road that fits the best.
Also, the type of access is stored appropriately.
The tags that are checked for road types and attractions can be found [here](https://github.com/styinx/OSM/blob/master/code/include/structures/Primitives.hpp#L63-#L113).

Since there is no guarantee that all the given osm data is valid we created a default that sets every unknown tag to a default.
This default is the living street with a speed limit of 30.
This way pedestrians, bikers and cars can access this road.
A highway tag that does not contain any value is given the value of a residential street with a speed limit of 50.

```c++
enum class EdgeTypeMask : Byte  
{  
    // Access types  
    FOOT             = 0x01,  
    BICYCLE          = 0x02,  
    CAR              = 0x04,  
    PUBLIC_TRANSPORT = 0x08,   // unused
    
    // Street types 
    LIVING_STREET     = 0x17,  
    SERVICE_STREET    = 0x24,  
    PEDESTRIAN_STREET = 0x37,  
    TRACK_STREET      = 0x43,  
    BUS_STREET        = 0x5C,  
    ESCAPE_STREET     = 0x64,  
    RACEWAY_STREET    = 0x70,  
    
    // Street types  
    MOTORWAY     = 0x84,  
    TRUNK        = 0x94,  
    PRIMARY      = 0xA4,  
    SECONDARY    = 0xB6,  
    TERTIARY     = 0xC7,  
    UNCLASSIFIED = 0xD7,  
    RESIDENTIAL  = 0xE7,  
};
```

### Adjacency Array
<a id="adjacency_array"/>

To store nodes and edges efficiently we decided to go for an adjacency array.
It consists of 3 arrays (vectors) that store the nodes, edges and edge offsets respectively.
Since all three arrays have to be in a specific order they have to be process after initially load the `*.pbf` file.
Upon reading an openstreetmaps resource file for the first time the ids of the nodes that are part of an edge are extracted and stored in a map container.
Those edges are instantiated in this step and stored in the `m_edges` container, currently in no specific order.
When the resource file is read a second time we can then instantiate all those nodes that we part in the previous step.
A second read of the resource file is necessary because edges and nodes are not guaranteed to be in order.
So, we don't know if we need a node at a specific time during reading.
After the resource is read a second time the processing of the edges and nodes can begin.

The processing is done in the method [computeOffsets()](https://github.com/styinx/OSM/blob/master/code/source/structures/AdjacencyArray.cpp#L30) which sorts the nodes and edges by the unique id in ascending order.
When the containers are sorted the offsets are calculated for the outgoing edges of a node.
Since the two containers were sorted before we have a runtime of `O(n+m)` where n is the number nodes and m the number of edges.
In this function the distances of an edge are also computed, since we now have the coordinates of a node.

The implementation of the AdjacencyArray class can be found [here](https://github.com/styinx/OSM/blob/master/code/include/structures/AdjacencyArray.hpp).

```c++
class AdjacencyArray
{
    Vector<Node>   m_nodes;
    Vector<Edge>   m_edges;
    Vector<Uint64> m_o_offset;

    ...

    void           computeOffsets();
    void           addNode(const Node& node);
    void           addEdge(const Edge& edge);
    Vector<Edge> edges(const Uint64 node) const;
};
```

### Grid
<a id="grid"/>

The `Grid` structure helps to access nodes on the map in approximately `O(1)`. 
For this the loaded map is partitioned in a 100 by 100 grid.
Each cell in this grid holds a number of nodes which is determined by their latitude and longitude values.
The dimensions of the grid are set statically out of simplicity.
A approach for future improvements would be to set those dynamically by the number of nodes and the latitude/longitude range.

We provide two different approaches for the selection of a node in a cell.
On the one hand there is the option to find the [_first_](https://github.com/styinx/OSM/blob/master/code/source/structures/Grid.cpp#L91-112) closest node.
It will look for a node in the same cell as the specified location that is inside the specified range.
On the other hand there is the option to find the [_best_](https://github.com/styinx/OSM/blob/master/code/source/structures/Grid.cpp#L112-134) closest node.
This will look for the node that is exactly the closest in the cell.

The implementation of the Grid class can be found [here](https://github.com/styinx/OSM/blob/master/code/include/structures/Grid.hpp).

```c++
class Grid
{
    struct Cell
    {
        Vector<Uint64> children;
    };

    static const Uint16 m_x = 100;
    static const Uint16 m_y = 100;
    const MapBounds     m_bounds;
    Vector<Cell>        m_cells{m_x * m_y};

    ...

    void           set(const float lat, const float lon, const Uint64 index);
    Vector<Uint64> get(const Uint16 cell) const;
    Uint64         getFirstClosest(const float lat, const float lon, const float range = 500) const;
    Uint64         getBestClosest(const float lat, const float lon) const;
};
```

### Route Search
<a id="route_search"/>

### Examples
<a id="examples"/>

![ST](https://github.com/styinx/OSM/blob/master/report/stuttgart.png "Stuttgart")
![ST](https://github.com/styinx/OSM/blob/master/report/stuttgart2.png "Stuttgart")
![BW](https://github.com/styinx/OSM/blob/master/report/bawü.png "Baden-Württemberg")
![DE](https://github.com/styinx/OSM/blob/master/report/deutschland.png "Deutschland")
![DE](https://github.com/styinx/OSM/blob/master/report/deutschland2.png "Deutschland")
  

### Limitations
<a id="limitations"/>

__Accuracy of target selection__:

Some edges are not labeled with the correct highway tags. 
If a user chooses a node as a start or stops location that is part of that edge the Dijkstra algorithm might not find a valid route. 
This project provides a fallback mechanism, which looks for the _first_ closest node that is connected to the street network.
The mechanism utilizes the Grid of the map an selects the first Node that is in the same cell as the initial target node that the user did specify.
Since the first node in this cell might not always be the exact node that the user selected the calculated route will start with a gap between the start node and the actual route.
This is marked with red in the following image.
 
![Selection target](https://github.com/styinx/OSM/blob/master/report/limitation_selection.png)

A possible solution for this is to calculate the _best_ closest point in a cell to the initial user defined node.
This would degrade performance based on the number of nodes and the size of the Grid.
Testing showed that a Grid size of 100x100 is suitable.
Since we want to have a `O(1)` access to a node on the map we decided to keep prefer the _first_ closest node in the cell.
The missing offset between initial node and _first_ closest seems acceptable and do not degrade the quality of the calculated route.
As shown in the picture above the offset between initial node and the selected is ~200m which does not restrain a user by much.

Future improvements could organize the Grid in a different way and allocate the dimensions dynamically based on the range of the map data.
It might also be possible to use another data structure such as a quad tree that could also reduce the number of nodes in a cell.

__Missing/Wrong edge information__:

In some route calculations we identified that the search algorithm sometimes took false shortcuts to secondary or even tertiary roads instead of a motorway.
For some cases we could detect the problems but not for every case.
There exist edges that are not labeled with the motorway tag or have an appropriate maximum speed tag.

The fallback mechanism for this is to give a highway without a value a default of a living street with the maximum speed of 30.
This way, also pedestrians and bikers can take the route, although it might not always make sense like in the picture below.
The picture shows the route that the algorithm created (in blue) for a car.
It is obvious that the algorithm should have return the red marked route instead.

![Motorway](https://github.com/styinx/OSM/blob/master/report/limitation_tags.png)

__Number of attractions__:

The number of attractions is limited to 10 attractions.

## Conclusion
<a id="conclusion"/>
