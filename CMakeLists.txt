cmake_minimum_required( VERSION 3.10 )

project( image_processor )

set( CMAKE_BUILD_TYPE "Debug" )
set( CMAKE_CXX_FLAGS "-std=c++17 -O3 -Wall -lpthread" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_STANDARD 20 )

# Add image processor.
if( NOT TARGET lib_image_processor )
    add_subdirectory( src ${PROJECT_SOURCE_DIR}/build/lib_image_processor )
endif()

# Add visualizor.
set( VISUALIZOR_PATH ${PROJECT_SOURCE_DIR}/../Visualizor2D )
if( NOT TARGET lib_2d_visualizor )
    add_subdirectory( ${VISUALIZOR_PATH}/src ${PROJECT_SOURCE_DIR}/build/lib_2d_visualizor )
endif()

# Add tick tock utility.
set( SLAM_UTILITY_PATH ${PROJECT_SOURCE_DIR}/../Slam_Utility )
if( NOT TARGET lib_slam_utility_tick_tock )
    add_subdirectory( ${SLAM_UTILITY_PATH}/src/tick_tock ${PROJECT_SOURCE_DIR}/build/lib_slam_utility_tick_tock )
endif()

add_executable( test_image_processor
    test/test_image_processor.cpp
)
target_link_libraries( test_image_processor
    lib_image_processor
    lib_2d_visualizor
    lib_slam_utility_tick_tock
)
target_include_directories( test_image_processor PRIVATE
    ${SLAM_UTILITY_PATH}/src/tick_tock
)
