cmake_minimum_required(VERSION 2.8.5)

project(host-sdl)
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake-modules")

set (LUA_LIB_DIR  "")
set (MOAI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")


#set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMOAI_OS_LINUX " )

if (LIB_PATH)
  get_filename_component(LIB_PATH ${LIB_PATH} ABSOLUTE)
endif(LIB_PATH)

if (HOST_ROOT)
  get_filename_component(HOST_ROOT ${HOST_ROOT} ABSOLUTE)
else (HOST_ROOT)
  set (HOST_ROOT ${MOAI_ROOT}/src)
endif(HOST_ROOT)

  

include(../../cmake-modules/platform-linux.cmake)
include(../../cmake-modules/platform-common.cmake)
include(../../cmake-modules/module-setup.cmake)
include(../../cmake-modules/libmoai-setup.cmake)
install(EXPORT libmoai DESTINATION cmake )

add_subdirectory(../host-modules host-modules)


find_package ( OpenGL REQUIRED )

include_directories ( ${OPENGL_INCLUDE_DIRS} ${HOST_ROOT} )

#fix lua lib path
if (NOT LIB_PATH)
  link_directories(${LUA_LIB_DIR})
endif (NOT LIB_PATH)

# Use all cpp files in directory as source code
file ( GLOB HOST_SDL_SRC "${HOST_ROOT}/host-sdl/*.cpp" "${HOST_ROOT}/host-sdl/*.h" )

add_executable ( moai ${HOST_SDL_SRC} )
install(TARGETS moai DESTINATION bin)

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
  ${OPENGL_LIBRARIES}
  Xxf86vm
  xcb
  xcb-randr
  xcb-util
  
)


