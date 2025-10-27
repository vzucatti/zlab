
add_executable( ode_demo ode_demo.cpp )
target_link_libraries( ode_demo PRIVATE zlab )

add_executable( linearLeastSquares_demo linearLeastSquares_demo.cpp )
target_link_libraries( linearLeastSquares_demo PRIVATE zlab )
