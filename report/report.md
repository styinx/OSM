
# OSM

  

## Introduction

### Features

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

The project can be compiled with the compile script int the `scripts/` directory which uses cmake. First, the script compiles the osmpbf library. After that the OSM poject is compiled. The executables are located at `build/bin/`.

The script can be used from the command line with the following command. You have to chose the root directory of the repository.
```  
./scripts/compile.sh  
```

### Execution

From repository root directory:
```
./build/bin/OSM <relative path to pbf file>
```

From bin directory:
```
./OSM <relative path to the pbf file>
```

**Additional Notes**:
On some occasions it happend that the program crashed during the reading of a *.pdf file. The error message is attached below. This error is caused by the osmpbf library and occurs ~ once for every 10 executions.
```
[libprotobuf FATAL /usr/include/google/protobuf/repeated_field.h:1078] CHECK failed: (index) < (current_size_): 
terminate called after throwing an instance of 'google::protobuf::FatalException'
  what():  CHECK failed: (index) < (current_size_): 
Aborted (core dumped)
```

## Implementation

![Class diagram](https://github.com/styinx/OSM/blob/master/report/class_diagram.pdf)

### Data Structures and Primitives

  

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

![ST](https://github.com/styinx/OSM/blob/master/report/stuttgart.png)
![ST](https://github.com/styinx/OSM/blob/master/report/stuttgart2.png)
![BW](https://github.com/styinx/OSM/blob/master/report/bawü.png)
![DE](https://github.com/styinx/OSM/blob/master/report/stuttgart.png)
![DE](https://github.com/styinx/OSM/blob/master/report/stuttgart2.png)

### Edges

![Motorway](https://github.com/styinx/OSM/blob/master/report/network.png)
  

### Limitations

- Some edges are not labeled with the correct highway tags. If a user chooses such an edge as a start or stops location the Dijkstra algorithm might not find a valid route. This project provides a fallback mechanism, which looks for closest nodes that are connected to valid edges.

- The number of attractions is limited to 10 attractions with a range of 0 to 10 kilometers.
