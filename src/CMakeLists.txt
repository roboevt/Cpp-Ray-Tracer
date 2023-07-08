#cmake -B build -S ./src/ -DCMAKE_TOOLCHAIN_FILE=/home/roboevt/dev/c++/Cpp-Ray-Tracer/vcpkg/scripts/buildsystems/vcpkg.cmake
#cmake --build ./build

cmake_minimum_required( VERSION 3.12 )

project( CPPRayTracer)

include(/home/roboevt/dev/c++/Cpp-Ray-Tracer/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package( OpenGL REQUIRED )
find_package( glfw3 REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} )

file(GLOB SOURCES *.cpp)

add_compile_options(-msse4.1 -std=c++20 -O3)

add_executable( CPPRayTracer ${SOURCES} )

target_link_libraries( CPPRayTracer ${OPENGL_LIBRARIES} glfw )