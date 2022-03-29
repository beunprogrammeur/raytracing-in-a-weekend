# CMakeList.txt : CMake project for raytracing-in-a-weekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (raytracing-in-a-weekend 
	"program.cpp"  
	"vec3.cpp"

	"vec3.h" 
	"color.h" 
	"ray.h"
	 "hittable.h" "sphere.h" "sphere.cpp" "hittable_list.h" "hittable_list.cpp" "program.h" "camera.h" "camera.cpp" "random.h" "io.h" "material.h")

# TODO: Add tests and install targets if needed.
