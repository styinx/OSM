# OSM

[![Build Status](https://travis-ci.com/styinx/OSM.svg?token=MRNvDQResksrdNAQddri&branch=master)](https://travis-ci.com/styinx/OSM)
[![Build Status](https://travis-ci.com/styinx/OSM.svg?token=MRNvDQResksrdNAQddri&branch=dev)](https://travis-ci.com/styinx/OSM)

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

### Efficient data sctructure (Task 3)

```
sh ./build/bin/OSM_Task_3 <pbf file path>
```

## Notes

Hardware:
  - 16 GB RAM
  - Intel(R) Core(TM) i5-4690K CPU @ 3.50GHz

Execution times:
  - Task 2:
    - BW: ~ 30sec
    - DE: ~ 3min
  - Task 3:
    - BW: ~ 2min 30sec
    - DE: ~ 
