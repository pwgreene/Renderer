PROJECT(KNN)
cmake_minimum_required(VERSION 3.5)
set(LIB_NAME KNN)

if(APPLE)
    add_definitions("-Wno-deprecated-declarations")
endif()

if(UNIX)
    # Enable C++11
    add_definitions("-std=c++11")
elseif(MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -WX")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

set(CPP_FILES
kdTree.cpp
main.cpp
stb.cpp
)

set(CPP_HEADERS
kdTree.h
)

# sway include directory
include_directories(sway/include/sway)

include_directories(vecmath/include)
add_subdirectory(vecmath)

set (STB_SRC
${SRC_DIR}stb_image.h
${SRC_DIR}stb_image_write.h)
SOURCE_GROUP(stb FILES ${STB_SRC})

add_library(${LIB_NAME} STATIC ${CPP_FILES} ${CPP_HEADERS})
add_executable(kdTree ${CPP_FILES} ${CPP_HEADERS} ${STB_SRC})
target_link_libraries(kdTree vecmath2)