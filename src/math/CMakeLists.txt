
add_library(zlab_math STATIC
    rbf.cpp
    utilities.cpp
    matrix.cpp
    ode.cpp    
)

target_include_directories(zlab_math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(zlab_math PUBLIC zlab_core)
