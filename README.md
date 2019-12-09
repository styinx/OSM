# OSM

[github repo](https://github.com/styinx/OSM)

Requires: (should be installed via the install script)
- inphos42/osmpbf
- zlib
- libprotobuf-dev
- protobuf-compiler
- libqt5webengine5
- libqt5widgets5
- qtwebengine5-dev


[![Build Status](https://travis-ci.com/styinx/OSM.svg?branch=master)](https://travis-ci.com/styinx/OSM)

# Instructions

```
git clone https://github.com/styinx/OSM
cd OSM
```

## Install

```
./scripts/install.sh
```

## Build 

```
./scripts/compile.sh
```

## Run

- navigate to the base dir of the OSM repository

```
sh ./build/bin/OSM
```

## Usage

### Read pbf file (Task 2)

```
sh ./build/bin/OSM_Task_2 <pbf file path> 
```

### Efficient data structure (Task 3)

```
sh ./build/bin/OSM_Task_3 <pbf file path>
```

### Visualize osm map (Task 4)

```
sh ./build/bin/OSM_Task_4 <pbf file path>
```

### Shortest-path algorithm (Task 5)

```
sh ./build/bin/OSM_Task_5 <pbf file path>
```

# Notes

**Hamburg** 53.5503410,10.0006540

**Stuttgart** 48.7784485,9.1800132

## Germany
- Nodes: 307793444
- Ways: 49974007
- Relations: 622452

## BW
- Nodes: 43693622
- Ways: 7245584
- Relations: 90278

## Stuttgart
- Nodes: 14660711
- Ways: 2546502
- Relations: 25540
