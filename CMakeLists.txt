cmake_minimum_required(VERSION 3.5)

project(spfgui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set(SRC
    main.cpp
    graph/client.cpp
    graph/edgemodel.cpp
    graph/graphmodel.cpp
    graph/vertexmodel.cpp
)

if(ANDROID)
    add_library(spfgui SHARED ${SRC} qml.qrc)
else()
    add_executable(spfgui ${SRC} qml.qrc)
endif()

target_compile_definitions(spfgui
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(spfgui
  PRIVATE Qt5::Core Qt5::Quick SPF::client)

add_subdirectory(libspfclient)

enable_testing()
add_subdirectory(qmltests)
