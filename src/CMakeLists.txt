

add_subdirectory( core )
add_subdirectory( math )

add_library( zlab INTERFACE )
target_link_libraries( zlab INTERFACE zlab_core zlab_math )

