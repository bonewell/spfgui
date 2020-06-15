find_package(Qt5QuickTest REQUIRED)

# no need to copy around qml test files for shadow builds - just set the respective define
add_definitions(-DQUICK_TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(qmltests main.cpp qml.qrc)
add_test(NAME qmltests COMMAND qmltests)

target_link_libraries(qmltests PRIVATE Qt5::QuickTest)
