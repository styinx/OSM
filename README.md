# OSM

## Install

### Clone github repo

```
git clone https://github.com/styinx/OSM
cd OSM
```

### Install dependencies

#### Install conan

- requires python and pip

```
pip install conan
```

#### Install protobuf compiler

```
sudo apt install protobuf-compiler
```

#### Install QT5

```
sudo apt install qt5-default
```

### libosmscout

#### Clone libosmscout

- navigate to the base dir of the OSM repository

```
git clone https://github.com/Framstag/libosmscout
cd libosmscout
```

#### Build libosmscout

- navigate to the base dir of the libosmscout repository

```
mkdir build 
cd build
cmake ..
make Import
```

### Build OSM

- navigate to the base dir of the OSM repository

```
mkdir build
conan install . -if build
cd build
cmake ..
make
```

### Run OSM

- navigate to the base dir of the OSM repository

```
cd build/bin
./OSM
```

## Usage

### Read pbf file (Task 2)

```
./OSM_Task2 -d <pbf file path> --destinationDirectory <temp file path> --typefile ../../libosmscout/stylesheets/map.ost
```

### Efficient data sctructure (Task 3)

```
./OSM_Task3 -d <pbf file path> --destinationDirectory <temp file path> --typefile ../../libosmscout/stylesheets/map.ost
```
