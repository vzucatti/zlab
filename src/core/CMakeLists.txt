
add_library(zlab_core STATIC
  numeric_types.cpp
)

target_include_directories(zlab_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
