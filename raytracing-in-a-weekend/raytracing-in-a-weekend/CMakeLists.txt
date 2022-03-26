# CMakeList.txt : CMake project for raytracing-in-a-weekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (raytracing-in-a-weekend "program.cpp"  "vec3.h" "color.h" "ray.h")

# TODO: Add tests and install targets if needed.
