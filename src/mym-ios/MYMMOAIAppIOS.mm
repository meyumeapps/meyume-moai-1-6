
#ifndef DISABLE_MYM_MOAI_APP

#include "pch.h"

#import <mym-ios/MYMMOAIAppIOS.h>
#include <sys/types.h>
#include <sys/sysctl.h>

// init the class
int MYMMOAIAppIOS::_init ( lua_State* L ) {
	MOAILuaState state ( L );
	
	return 0;
}

int MYMMOAIAppIOS::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );
	
	if ( idx < TOTAL ) {
		
		MYMMOAIAppIOS::Get ().mListeners [ idx ].SetRef ( state, 2 );
	}
	
	return 0;
}

// open an url
int MYMMOAIAppIOS::_openUrl(lua_State* L) {
	MOAILuaState state ( L );
	
	cc8* url = state.GetValue < cc8* >( 1, "" );
	
	bool ret = false;
	if ( url && url [ 0 ] != '\0' ) {
		ret = [[ UIApplication sharedApplication ] openURL:[ NSURL URLWithString:[ NSString stringWithFormat: @"%s", url ]]];
	}
	
	lua_pushboolean(state, ret);
	
	return 1;
}

// get user defaults prop
int MYMMOAIAppIOS::_getUserDefaultsProp(lua_State* L) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* >( 1, "" );
	cc8* type = state.GetValue < cc8* >( 2, "" );
	NSObject *tmp = [[NSUserDefaults standardUserDefaults] objectForKey:[NSString stringWithUTF8String:key]];
	
	if (strcmp(type, "boolean") == 0) {
		lua_pushboolean(state, [(NSNumber*)tmp boolValue]);
	} else {
		if ([tmp isKindOfClass:[NSNumber class]]) {
			lua_pushstring(state, [[(NSNumber*)tmp stringValue] UTF8String]);
		} else {
			lua_pushstring(state, [(NSString*)tmp UTF8String]);
		}
	}
	
	return 1;
}

int MYMMOAIAppIOS::_setUserDefaultsProp(lua_State* L) {
	MOAILuaState state ( L );
	
	cc8* key = state.GetValue < cc8* >( 1, "" );
	cc8* val = state.GetValue < cc8* >( 2, "" );
	
	[[NSUserDefaults standardUserDefaults] setObject:[NSString stringWithUTF8String:val] forKey:[NSString stringWithUTF8String:key]];
	
	return 0;
}

// get device version
int MYMMOAIAppIOS::_getDeviceVersion(lua_State* L) {
	MOAILuaState state ( L );
	
	size_t size;
	
    // Set 'oldp' parameter to NULL to get the size of the data
    // returned so we can allocate appropriate amount of space.
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
	
    // Allocate the space to store and return the name.
    char name[size];
	
    // Get the platform name.
    sysctlbyname("hw.machine", name, &size, NULL, 0);
	
	cc8* ret = (cc8*)name;
	lua_pushstring(state, ret);
	
	return 1;
}

int MYMMOAIAppIOS::_setAutoRender(lua_State* L) {
	MOAILuaState state ( L );
	
	bool val = lua_toboolean ( state, 1 );
	
	MYMMOAIAppIOS::Get().autoRender = val;
	
	return 0;
}

// constructor
MYMMOAIAppIOS::MYMMOAIAppIOS () {
	RTTI_SINGLE ( MOAILuaObject )
}

MYMMOAIAppIOS::~MYMMOAIAppIOS () {

}

// register class with LUA
void MYMMOAIAppIOS::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "APP_DID_BECOME_ACTIVATE", ( u32 )APP_DID_BECOME_ACTIVATE );
	state.SetField ( -1, "APP_WILL_RESIGN_ACTIVE", ( u32 )APP_WILL_RESIGN_ACTIVE );
	state.SetField ( -1, "APP_WILL_ENTER_FOREGROUND", ( u32 )APP_WILL_ENTER_FOREGROUND );
	state.SetField ( -1, "APP_DID_ENTER_BACKGROUND", ( u32 )APP_DID_ENTER_BACKGROUND );
	state.SetField ( -1, "APP_WILL_TERMINATE", ( u32 )APP_WILL_TERMINATE );
	state.SetField ( -1, "APP_OPENED_FROM_URL", ( u32 )APP_OPENED_FROM_URL );

	luaL_Reg regTable [] = {
		{ "init",					_init },
		{ "setListener",			_setListener },
		{ "openUrl",				_openUrl },
		{ "getUserDefaultsProp",	_getUserDefaultsProp },
		{ "setUserDefaultsProp",	_setUserDefaultsProp },
		{ "getDeviceVersion",		_getDeviceVersion },
		{ "setAutoRender",			_setAutoRender },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

// called from app delegate to notify that the app did become active
void MYMMOAIAppIOS::appDidBecomeActive() {
	MOAILuaRef& callback = this->mListeners [ APP_DID_BECOME_ACTIVATE ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

// called from app delegate to notify that the app will resign active
void MYMMOAIAppIOS::appWillResignActive() {
	MOAILuaRef& callback = this->mListeners [ APP_WILL_RESIGN_ACTIVE ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

// called from app delegate to notify that the app will enter foreground
void MYMMOAIAppIOS::appWillEnterForeground() {
	MOAILuaRef& callback = this->mListeners [ APP_WILL_ENTER_FOREGROUND ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

// called from app delegate to notify that the app did enter background
void MYMMOAIAppIOS::appDidEnterBackground() {
	MOAILuaRef& callback = this->mListeners [ APP_DID_ENTER_BACKGROUND ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

// called from app delegate to notify that the app will terminate
void MYMMOAIAppIOS::appWillTerminate() {
	MOAILuaRef& callback = this->mListeners [ APP_WILL_TERMINATE ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

// called from app delegate to notify that the app is opened from URL
bool MYMMOAIAppIOS::appOpenFromUrl(NSURL *url, NSString *sourceApp) {
	MOAILuaRef& callback = this->mListeners [ APP_OPENED_FROM_URL ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		lua_newtable ( state );
		
		lua_pushstring(state, "url");
		lua_pushstring(state, [[url absoluteString] UTF8String]);
		lua_settable ( state, -3 );
		
		if (sourceApp) {
			lua_pushstring(state, "sourceApp");
			lua_pushstring(state, [sourceApp UTF8String]);
			lua_settable ( state, -3 );
		}
		
		state.DebugCall ( 1, 0 );
	}
	
	return true;
}


#endif