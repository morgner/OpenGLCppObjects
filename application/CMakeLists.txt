# Our application used GLU, so better find it
find_package("GLUT")
find_package("glfw3" REQUIRED)

# Define an executable for our test application (relative paths are resolved relative to the current directory!)
add_executable("simplest-test"
  "test/test.cpp"
)


# Define an executable for our test application (relative paths are resolved relative to the current directory!)
add_executable("simplest-text"
  "test/text.cpp"
)



# Link against the required libraries (we are linking "private" here, since nobody can reasonably link against an executable)
target_link_libraries("simplest-test" PRIVATE
  "${PROJECT_NAME}" # Link against the oglc.lib
  "GLUT::GLUT" 
#  "GLFW"
  "${GLFW_STATIC_LIBRARIES}"
)


# Link against the required libraries (we are linking "private" here, since nobody can reasonably link against an executable)
target_link_libraries("simplest-text" PRIVATE
  "${PROJECT_NAME}" # Link against the oglc.lib
  "GLUT::GLUT" 
#  "GLFW"
  "${GLFW_STATIC_LIBRARIES}"
)



#include_directories(/usr/include/GLFW/)

set_target_properties("simplest-test" PROPERTIES
  CXX_STANDARD_REQUIRED YES # Require at least the desired standard
  CXX_EXTENSIONS OFF # No GNU extensions for C++, thank you very much
  INTERPROCEDURAL_OPTIMIZATION ${IPO_IS_SUPPORTED} # If we can do IPO, we should
)

set_target_properties("simplest-text" PROPERTIES
  CXX_STANDARD_REQUIRED YES # Require at least the desired standard
  CXX_EXTENSIONS OFF # No GNU extensions for C++, thank you very much
  INTERPROCEDURAL_OPTIMIZATION ${IPO_IS_SUPPORTED} # If we can do IPO, we should
)

