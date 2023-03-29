# Define which version of CMake we need. This should be updated if target systems have a more modern version available
# because we can profit from newer features and policies. As of the time of this writing, CMake 3.25.2 is the most
# recent release.
cmake_minimum_required(VERSION "3.11.0")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project("oglcpplib"
  LANGUAGES CXX
  VERSION "0.1.20"
)
 
# Check if interprocedural optimization (IPO/LTO) is supported
include("CheckIPOSupported" ${GLFW_INCLUDE_DIRS})
check_ipo_supported(RESULT IPO_IS_SUPPORTED)

# Find shared system dependencies
find_package("OpenGL")


# Set the output directories for libraries and applications to be the "build" directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# Add the local "sub-projects"
add_subdirectory("lib")
add_subdirectory("application")
