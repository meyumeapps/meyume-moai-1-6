//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef DISABLE_CHARTBOOST

#include "pch.h"

#import <mym-ios/MYMMOAIChartBoostIOS.h>
#import <Chartboost/Chartboost.h>
#import <Chartboost/CBNewsfeed.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
//----------------------------------------------------------------//
/**	@name	hasCachedInterstitial
 @text	returns whether a cached ad is available
 
 @out 	bool	True, if an ad is cached.
 */
int MYMMOAIChartBoostIOS::_hasCachedInterstitial ( lua_State* L ) {
	MOAILuaState state ( L );
	
	bool isAdAvailable = [ Chartboost hasInterstitial:CBLocationDefault ];
	
	lua_pushboolean ( state, isAdAvailable );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	init
	@text	Initialize ChartBoost.
	
	@in		string	appId			Available in ChartBoost dashboard settings.
	@in 	string	appSignature	Available in ChartBoost dashboard settings.
	@out 	nil
*/
int MYMMOAIChartBoostIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* identifier = lua_tostring ( state, 1 );
	cc8* signature = lua_tostring ( state, 2 );
	
	[Chartboost startWithAppId:[ NSString stringWithUTF8String:identifier ] appSignature:[ NSString stringWithUTF8String:signature ] delegate:nil];
	[Chartboost setShouldRequestInterstitialsInFirstSession:YES];
	[Chartboost setShouldDisplayLoadingViewForMoreApps:YES];
	[Chartboost setAutoCacheAds:YES];
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	loadInterstitial
	@text	Request that an interstitial ad be cached for later display.
	
	@opt	string	locationId		Optional location ID.
	@out 	nil
*/
int MYMMOAIChartBoostIOS::_loadInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );

	// At the moment, to keep parity with Android, don't allow locations.
	cc8* location = lua_tostring ( state, 1 );
	
	if ( location != nil ) {
		
		[Chartboost cacheInterstitial:[ NSString stringWithUTF8String:location ]];
	} else {
		
		[Chartboost cacheInterstitial:CBLocationDefault ];
	}
			
	return 0;
}

//----------------------------------------------------------------//
int MYMMOAIChartBoostIOS::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );
	
	if ( idx < TOTAL ) {
		
		MYMMOAIChartBoostIOS::Get ().mListeners [ idx ].SetRef ( state, 2 );
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	showInterstitial
	@text	Request an interstitial ad display if a cached ad is available.
	
	@opt	string	locationId		Optional location ID.
	@out 	bool					True, if an ad is cached and will be displayed.
*/
int MYMMOAIChartBoostIOS::_showInterstitial ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	MYMMOAIChartBoostIOS::Get().shouldCancelAds = false;

	// At the moment, to keep parity with Android, don't allow locations.
	cc8* location = lua_tostring ( state, 1 );
	
	if ( location != nil ) {
		[Chartboost showInterstitial:[ NSString stringWithUTF8String:location ]];
	} else {
		
		[Chartboost showInterstitial:CBLocationDefault ];
	}
			
	lua_pushboolean ( state, false );

	return 1;
}

int MYMMOAIChartBoostIOS::_cacheMoreApps ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	[Chartboost cacheMoreApps:CBLocationDefault];
	
	return 0;
}

int MYMMOAIChartBoostIOS::_showMoreApps ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	[Chartboost showMoreApps:CBLocationDefault];
	
	return 0;
}

int MYMMOAIChartBoostIOS::_cancelAds ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	MYMMOAIChartBoostIOS::Get().shouldCancelAds = true;
	
	return 0;
}

int MYMMOAIChartBoostIOS::_startNewsfeed ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	[CBNewsfeed startWithDelegate:nil];
	
	return 0;
}

int MYMMOAIChartBoostIOS::_showNewsfeed ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	NSInteger msgCount = 0;//[newsfeed messageCount];
	// only show newsfeed UI when have at least 1 message
	//if ([CBNewsfeed messageCount] > 0) {
		[CBNewsfeed showNewsfeedUI];
	//}
	
	lua_pushinteger(state, msgCount);
	
	return 1;
}


//================================================================//
// MYMMOAIChartBoostIOS
//================================================================//

//----------------------------------------------------------------//
MYMMOAIChartBoostIOS::MYMMOAIChartBoostIOS () {

	RTTI_SINGLE ( MOAILuaObject )	

	//mDelegate = [[ MoaiChartBoostDelegate alloc ] init ];
}

//----------------------------------------------------------------//
MYMMOAIChartBoostIOS::~MYMMOAIChartBoostIOS () {

	//[ mDelegate release ];
}

//----------------------------------------------------------------//
void MYMMOAIChartBoostIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "INTERSTITIAL_LOAD_FAILED",	( u32 )INTERSTITIAL_LOAD_FAILED );
	state.SetField ( -1, "INTERSTITIAL_DISMISSED", 		( u32 )INTERSTITIAL_DISMISSED );

	luaL_Reg regTable [] = {
		{ "hasCachedInterstitial",	_hasCachedInterstitial },
		{ "init",					_init },
		{ "loadInterstitial",		_loadInterstitial },
		{ "setListener",			_setListener },
		{ "showInterstitial",		_showInterstitial },
		{ "loadMoreApps",			_cacheMoreApps },
		{ "showMoreApps",			_showMoreApps },
		{ "cancelAds",				_cancelAds },
		{ "startNewsfeed",			_startNewsfeed },
		{ "showNewsfeed",			_showNewsfeed },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MYMMOAIChartBoostIOS::NotifyInterstitialDismissed () {	
	
	MOAILuaRef& callback = this->mListeners [ INTERSTITIAL_DISMISSED ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

//----------------------------------------------------------------//
void MYMMOAIChartBoostIOS::NotifyInterstitialLoadFailed () {	
	
	MOAILuaRef& callback = this->mListeners [ INTERSTITIAL_LOAD_FAILED ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}
//================================================================//
// MoaiChartBoostDelegate
//================================================================//
@implementation MoaiChartBoostDelegate

/// Called before requesting an interestitial from the back-end
- (BOOL)shouldRequestInterstitial:(NSString *)location {
	return YES;
}

/// Called when an interstitial has been received, before it is presented on screen
/// Return NO if showing an interstitial is currently innapropriate, for example if the user has entered the main game mode.
- (BOOL)shouldDisplayInterstitial:(NSString *)location {
	if (MYMMOAIChartBoostIOS::Get().shouldCancelAds) {
		return NO;
	}
	return YES;
}

/// Called when an interstitial has been received and cached.
- (void)didCacheInterstitial:(NSString *)location {
	
}

/// Called when an interstitial has failed to come back from the server
- (void)didFailToLoadInterstitial:(NSString *)location {
	MYMMOAIChartBoostIOS::Get ().NotifyInterstitialLoadFailed ();
}

/// Called when the user dismisses the interstitial
/// If you are displaying the add yourself, dismiss it now.
- (void)didDismissInterstitial:(NSString *)location {
	[Chartboost cacheInterstitial:location];
	
	MYMMOAIChartBoostIOS::Get ().NotifyInterstitialDismissed ();
}

/// Same as above, but only called when dismissed for a close
- (void)didCloseInterstitial:(NSString *)location {
	
}

/// Same as above, but only called when dismissed for a click
- (void)didClickInterstitial:(NSString *)location {
	
}

/// Called when an more apps page has been received, before it is presented on screen
/// Return NO if showing the more apps page is currently innapropriate
- (BOOL)shouldDisplayMoreApps {
	return YES;
}

/// Called when the More Apps page has been received and cached
- (void)didCacheMoreApps {
	
}

/// Called when a more apps page has failed to come back from the server
- (void)didFailToLoadMoreApps {
	
}

/// Called when the user dismisses the more apps view
/// If you are displaying the add yourself, dismiss it now.
- (void)didDismissMoreApps {
	
}

/// Same as above, but only called when dismissed for a close
- (void)didCloseMoreApps {
	
}

/// Same as above, but only called when dismissed for a click
- (void)didClickMoreApps {
	
}


@end

#endif