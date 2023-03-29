# Define a library named like our project (relative paths are resolved relative to the current directory!)
add_library("${PROJECT_NAME}"
  "source/3DBox.cpp"
# "source/3DCamera.cpp"
 "source/3DColor.cpp"
# "source/3DCone.cpp"
# "source/3DCube.cpp"
# "source/3DCylinder.cpp"
# "source/3DLight.cpp"
"source/3DMaterial.cpp"
# "source/3DPoint.cpp"
# "source/3DPyramid.cpp"
# "source/3DScene.cpp"
# "source/3DShape.cpp"
# "source/3DSphere.cpp"
"source/3DTexture.cpp"
# "source/3DFont.cpp"
# "source/3DText.cpp"
# "source/3DTorus.cpp"
# "source/3DPartialDisk.cpp"
)

# Define the include paths (relative paths are resolved relative to the current directory!)
target_include_directories("${PROJECT_NAME}" PUBLIC
  "include"
  "/usr/include/"
)

# Set the default compiler "features" (CMake determines the flags based on the abstract features)
target_compile_features("${PROJECT_NAME}" PUBLIC
  "cxx_std_17" # Use C++17 => generates the correct flag based on the compiler
)

# Set some compiler specific flags that CMake doesn't know about (yet?)
target_compile_options("${PROJECT_NAME}" PUBLIC
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall>
  $<$<CXX_COMPILER_ID:GNU,Clang>:-Wextra>
  # $<$<CXX_COMPILER_ID:GNU,Clang>:-Werror> # Disabled for now, because there are a lot of warning due to non-standard C++, etc!
  # $<$<CXX_COMPILER_ID:GNU,Clang>:-pedantic-errors> # Disabled for now, because there are a lot of warning due to non-standard C++ ,etc!
)

# Link against the required libraries (since we are linking "public", all consumers inherit the dependencies)
target_link_libraries("${PROJECT_NAME}" PUBLIC
  "OpenGL::GL"
  "OpenGL::GLU"
#  "GLFW"
  "${GLFW_STATIC_LIBRARIES}"
  )


# Set some more specific properties (those are never(!!) inherited)
set_target_properties("${PROJECT_NAME}" PROPERTIES
  CXX_STANDARD_REQUIRED YES # Require at least the desired standard
  CXX_EXTENSIONS OFF # No GNU extensions for C++, thank you very much
  INTERPROCEDURAL_OPTIMIZATION ${IPO_IS_SUPPORTED} # If we can do IPO, we should
)
