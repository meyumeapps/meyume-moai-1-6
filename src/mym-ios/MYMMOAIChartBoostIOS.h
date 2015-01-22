//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef	MOAICHARTBOOSTIOS_H
#define	MOAICHARTBOOSTIOS_H

#ifndef DISABLE_CHARTBOOST

#import <moai-core/headers.h>
//#import <Chartboost/Chartboost.h>
//#import <Chartboost/CBNewsfeed.h>
#import <UIKit/UIKit.h>

@class MoaiChartBoostDelegate;

//================================================================//
// #import <ChartBoost.h>
//================================================================//
class MYMMOAIChartBoostIOS :
	public MOAIGlobalClass < MYMMOAIChartBoostIOS, MOAILuaObject > {
private:

	MoaiChartBoostDelegate*	mDelegate;

	//----------------------------------------------------------------//
	static int	_hasCachedInterstitial	( lua_State* L );
	static int	_init					( lua_State* L );
	static int	_loadInterstitial		( lua_State* L );
	static int	_setListener			( lua_State* L );
	static int	_showInterstitial		( lua_State* L );
		static int _cacheMoreApps(lua_State* L);
		static int _showMoreApps(lua_State* L);
		static int _cancelAds(lua_State* L);
		static int _startNewsfeed(lua_State* L);
		static int _showNewsfeed(lua_State* L);
	
public:

	DECL_LUA_SINGLETON ( MYMMOAIChartBoostIOS );

	enum {
		INTERSTITIAL_LOAD_FAILED,
		INTERSTITIAL_DISMISSED,
		TOTAL
	};
	
	MOAILuaStrongRef		mListeners [ TOTAL ];
		
		BOOL shouldCancelAds;
	
					MYMMOAIChartBoostIOS				();
					~MYMMOAIChartBoostIOS				();
	void 			NotifyInterstitialDismissed		();
	void 			NotifyInterstitialLoadFailed	();
	void			RegisterLuaClass				( MOAILuaState& state );
};

//================================================================//
// MoaiChartBoostDelegate
//================================================================//
@interface MoaiChartBoostDelegate : NSObject /*< ChartboostDelegate >*/ {
@private
}
@end

#endif  //DISABLE_CHARTBOOST

#endif  //MOAICHARTBOOSTIOS_H
