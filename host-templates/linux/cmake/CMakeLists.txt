cmake_minimum_required(VERSION 2.8.5)

project(host-sdl)

set (HOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../")

if (LIB_PATH)
  get_filename_component(LIB_PATH ${LIB_PATH} ABSOLUTE)
else(LIB_PATH)
   message(fatal "Must provide a library path via -DLIB_PATH=<path to moai libs and includes>")
endif(LIB_PATH)

find_package ( OpenGL REQUIRED )
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPOSIX -std=gnu99 -DNDEBUG -DHAVE_MEMMOVE" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPOSIX " )
set ( VFS_INCLUDE "-I${LIB_PATH}/include -include ${LIB_PATH}/include/zl-vfs/zl_replace.h")
set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${VFS_INCLUDE}" )
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${VFS_INCLUDE}" )

#link lib moai
include(${LIB_PATH}/cmake/libmoai.cmake)
link_directories(${LIB_PATH}/lib)

add_subdirectory(host-modules)

include_directories ( ${OPENGL_INCLUDE_DIRS} ${HOST_ROOT} )

# Use all cpp files in directory as source code
file ( GLOB HOST_SDL_SRC "${HOST_ROOT}/host-sdl/*.cpp" "${HOST_ROOT}/host-sdl/*.h" )

add_executable ( moai ${HOST_SDL_SRC} )

target_link_libraries ( moai 
  host-modules
  moai-sim
  moai-util
  moai-core
  zlcore
  SDL2-static
  pthread 
  rt
  Xi
)