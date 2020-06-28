[![Build Status](https://travis-ci.com/bonewell/spfgui.svg?branch=master)](https://travis-ci.com/bonewell/spfgui)

# spfgui
GUI client for SPF microservice

## Build
```Shell
$ mkdir build
$ cd build
$ conan install ../libspfclient
$ export Qt5_DIR=<path-to-qt>/lib/cmake/Qt5
$ export Qt5QuickTest_DIR=<path-to-qt>/lib/cmake/Qt5QuickTest
$ cmake ..
$ cmake --build .
```

## Run tests
```Shell
$ ./qmltests/qmltests
```

## Run
```Shell
$ ./spfgui
```

## Using
- Click on empty place to create a vertex.
- Double click on the vertex to remove it.
- Click one vertex and then other vertex to set the edge between them. Set weight in the popup.
- Double click on the weight label to remove the edge.
- Click one vertex and then long press on other vertex to calculate the shortest path.
