# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (
	"raytracing-in-a-weekend"
	VERSION 1.0
	DESCRIPTION "this project follows the 'raytracing-in-a-weekend' tutorial"
	LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "/Ox")
# Include sub-projects.
add_subdirectory ("raytracing-in-a-weekend")
