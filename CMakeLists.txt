project(osgBoost)
cmake_minimum_required(2.8)

find_package(OpenSceneGraph REQUIRED)
find_package(Boost REQUIRED)

include(CTest)

add_subdirectory(osgTraits)
add_subdirectory(tests)

