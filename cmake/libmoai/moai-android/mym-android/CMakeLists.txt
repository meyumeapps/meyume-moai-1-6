cmake_minimum_required ( VERSION 2.8.5 )
project ( mym-android )

#tell our parent to dump our setting for ndk_build
list(APPEND MOAI_ANDROID_MODULES "mym-android")
set(MOAI_ANDROID_MODULES "${MOAI_ANDROID_MODULES}" PARENT_SCOPE)

set ( MOAI_ANDROID_INCLUDES 
  "${MOAI_ROOT}/src/"
  "${CMAKE_BINARY_DIR}/libmoai/config"
 )

include_directories ( 
  ${MOAI_ANDROID_INCLUDES} 
)

set ( CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/src/mym-android" )

# Use all cpp files in directory as source code but don't recurse, so that host-jni.cpp is excluded
file ( GLOB MOAI_ANDROID_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

add_library ( mym-android STATIC ${MOAI_ANDROID_SRC} )
target_link_libraries( mym-android moai-sim moai-util moai-core )

install(TARGETS mym-android EXPORT libmoai ARCHIVE DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ DESTINATION include/mym-android
          FILES_MATCHING PATTERN "*.h")

#jni
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/jni/host-jni.cpp DESTINATION ../modules/jni/mym-android)

#java
#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/MoaiTwitter.java DESTINATION ../modules/moai/moai-android-twitter)

#third-party
install(DIRECTORY ${MOAI_ROOT}/3rdparty-android-mym/chartsboot-5.1.0/ DESTINATION ../modules/external/mym-android)
install(DIRECTORY ${MOAI_ROOT}/3rdparty-android-mym/amazon-iap-2.0.1/ DESTINATION ../modules/external/mym-android)
install(DIRECTORY ${MOAI_ROOT}/3rdparty-android-mym/twitter4j-4.0.1/ DESTINATION ../modules/external/mym-android)
install(DIRECTORY ${MOAI_ROOT}/3rdparty-android-mym/commons-io-2.4/ DESTINATION ../modules/external/mym-android)
install(DIRECTORY ${MOAI_ROOT}/3rdparty-android-mym/google-play-services/ DESTINATION ../modules/external/mym-android)