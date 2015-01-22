cmake_minimum_required ( VERSION 2.8.11 )
project ( mym-ios )

# lib Chartboost
set(CHARTBOOST_ROOT ${MOAI_ROOT}/3rdparty-ios-mym/Chartboost-5.1.3/Chartboost.framework)
set(CHARTBOOST_LIB ${CHARTBOOST_ROOT}/Chartboost)
add_library(Chartboost SHARED IMPORTED)
set_property(TARGET Chartboost PROPERTY IMPORTED_LOCATION ${CHARTBOOST_LIB})
set_property(TARGET Chartboost PROPERTY FRAMEWORK 1)

install(DIRECTORY ${CHARTBOOST_ROOT} DESTINATION lib)

# lib AmazonInsights
set(AMZN_INSIGHTS_ROOT ${MOAI_ROOT}/3rdparty-ios-mym/AmazonInsightsSDK/AmazonInsightsSDK.framework)
set(AMZN_INSIGHTS_LIB ${AMZN_INSIGHTS_ROOT}/AmazonInsightsSDK)
add_library(AmazonInsights SHARED IMPORTED)
set_property(TARGET AmazonInsights PROPERTY IMPORTED_LOCATION ${AMZN_INSIGHTS_LIB})
set_property(TARGET AmazonInsights PROPERTY FRAMEWORK 1)

install(DIRECTORY ${AMZN_INSIGHTS_ROOT} DESTINATION lib)

# lib FacebookSDK
set(FACEBOOK_ROOT ${MOAI_ROOT}/3rdparty-ios-mym/FacebookSDK-3.22/FacebookSDK.framework)
set(FACEBOOK_LIB ${FACEBOOK_ROOT}/FacebookSDK)
add_library(FacebookSDK SHARED IMPORTED)
set_property(TARGET FacebookSDK PROPERTY IMPORTED_LOCATION ${FACEBOOK_LIB})
set_property(TARGET FacebookSDK PROPERTY FRAMEWORK 1)

install(DIRECTORY ${FACEBOOK_ROOT} DESTINATION lib)

#glue
set (CMAKE_CURRENT_SOURCE_DIR "${MOAI_ROOT}/src/mym-ios")
file ( GLOB SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.mm" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )


add_library(mym-ios STATIC  ${SRC})

target_include_directories(mym-ios PUBLIC 
		"$<BUILD_INTERFACE:${MOAI_ROOT}/src>"
		"$<BUILD_INTERFACE:${CHARTBOOST_ROOT}>"
		"$<BUILD_INTERFACE:${AMZN_INSIGHTS_ROOT}>"
		"$<BUILD_INTERFACE:${FACEBOOK_ROOT}>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
	)

target_link_libraries( mym-ios moai-sim moai-util moai-core Chartboost AmazonInsights FacebookSDK)
set_target_properties( mym-ios PROPERTIES FOLDER Modules)
install(TARGETS mym-ios EXPORT libmoai ARCHIVE DESTINATION lib)
install(FILES ${MOAI_ROOT}/src/mym-ios/host.h DESTINATION include/mym-ios)
