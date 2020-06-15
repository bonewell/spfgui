![CI](https://github.com/bonewell/spfgui/workflows/CI/badge.svg)

# spfgui
GUI client for SPF microservice

## Build
```Shell
$ mkdir build
$ cd build
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
- Click one vertex and then the other vertex to set the edge between them. Set weight in the popup.
- Double click on the weight label to remove the edge.
