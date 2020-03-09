
# OSM

**TOC**:

- [Introduction](#introduction)
    - [Features](#features)
    - [Installation](#installation)
    - [Compilation](#compilation)
    - [Execution](#execution)
- [Approach](#approach)
- [Implementation](#implementation)
    - [Data Structures and Primitives](#data-structures-and-primitives)
    - [Examples](#examples)
    - [Limitations](#limitations)
- [Implementation](#implementation)

## Introduction
<a id="introduction"/>

### Features
<a id="features"/>

**Major**:
- Route navigation from a start point to a target.
- Selectable tourism spots which can be added to a route.
- A possible configuration for automatic selection in a given range.
- Route navigation with different transportation types (car, bicycle, by foot).

**Minor**:
- The map coordinates of the UI are selected to the map bounds with an appropriate zoom.
- Distance and duration calculation for a route.
- Expandable UI (separated from leaflet map).
- Fast communication between backend and frontend through QTWebchannel.

## Installation
<a id="installation"/>

Github: [Project repository](https://github.com/styinx/OSM)  
Build status: [![Build Status](https://travis-ci.com/styinx/OSM.svg?branch=master)](https://travis-ci.com/styinx/OSM)
  
**Requirements**:
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

**Additional Notes**:

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

## Implementation
<a id="implementation"/>

![Class diagram](https://github.com/styinx/OSM/blob/master/report/class_diagram.pdf)

### Data Structures and Primitives
<a id="data_structures"/>  

```c++
struct Node
{
	Uint64 id   = 0;
	float lat   = 0;
	float lon   = 0;
	Uint16 town = 0;
	Byte mask   = 0;
	Byte speed  = 0;
}
```

```c++
struct Edge
{
	Uint64 source  = 0;
	Uint64 target  = 0;
	float distance = 0;
	Byte speed     = 0;
	Byte mask      = 0;
	bool oneway    = false;
}
```

```c++
enum class EdgeTypeMask : Byte  
{  
  // Access types  
  FOOT             = 0x01,  
  BICYCLE          = 0x02,  
  CAR              = 0x04,  
  PUBLIC_TRANSPORT = 0x08,  
  
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

### Examples
<a id="examples"/>

![ST](https://github.com/styinx/OSM/blob/master/report/stuttgart.png "Stuttgart")
![ST](https://github.com/styinx/OSM/blob/master/report/stuttgart2.png "Stuttgart")
![BW](https://github.com/styinx/OSM/blob/master/report/bawü.png "Baden-Württemberg")
![DE](https://github.com/styinx/OSM/blob/master/report/deutschland.png "Deutschland")
![DE](https://github.com/styinx/OSM/blob/master/report/deutschland2.png "Deutschland")
  

### Limitations
<a id="limitations"/>

**Accuracy of target selection**:

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

**Missing/Wrong edge information**:

In some route calculations we identified that the search algorithm sometimes took false shortcuts to secondary or even tertiary roads instead of a motorway.
For some cases we could detect the problems but not for every case.
There exist edges that are not labeled with the motorway tag or have an appropriate maximum speed tag.

The fallback mechanism for this is to give a highway without a value a default of a living street with the maximum speed of 30.
This way, also pedestrians and bikers can take the route, although it might not always make sense like in the picture below.
The picture shows the route that the algorithm created (in blue) for a car.
It is obvious that the algorithm should have return the red marked route instead.

![Motorway](https://github.com/styinx/OSM/blob/master/report/limitation_tags.png)

**Number of attractions**:

The number of attractions is limited to 10 attractions.
