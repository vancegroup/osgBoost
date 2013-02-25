project(osgBoost)
cmake_minimum_required(VERSION 2.8)

find_package(OpenSceneGraph REQUIRED)
find_package(Boost REQUIRED)

if(MSVC)
	option(BUILD_WITH_PROJECT_FOLDERS
		"Use project folders in build system - not compatible with Visual C++ Express editions!"
		ON)
else()
	set(BUILD_WITH_PROJECT_FOLDERS ON)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ${BUILD_WITH_PROJECT_FOLDERS})


include(CTest)

add_subdirectory(osgTraits)
add_subdirectory(tests)

