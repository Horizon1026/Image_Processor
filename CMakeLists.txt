cmake_minimum_required( VERSION 3.10 )

project( image_processor )

set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++17 -O3 -Wall -lpthread" )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_STANDARD 17 )

# Add image processor.
if ( NOT TARGET lib_image_processor )
    add_subdirectory( src ${PROJECT_SOURCE_DIR}/build/lib_image_processor )
endif()

find_package( OpenCV REQUIRED )

add_executable( test_image_processor
    test/test_image_processor.cpp
)
target_link_libraries( test_image_processor
    ${OpenCV_LIBS}
    lib_image_processor
)
