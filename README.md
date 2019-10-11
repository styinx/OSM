# OSM

## Install dependencies

### libosmscout

- Install the library into your preferred path.

```
sudo apt install qt5-default
git clone https://github.com/Framstag/libosmscout
cd libosmscout
mkdir build 
cd build
cmake ..
make
```

### conan

```
pip install conan
```

## Install application

- install the application into your preferred path.

```
git clone https://github.com/styinx/OSM
cd OSM
mkdir build
conan install . -if build
cd
cd build
cmake ..
make
```

- choose the base path of the OSM application to run it

```
cd ../build/bin
./OSM
```
