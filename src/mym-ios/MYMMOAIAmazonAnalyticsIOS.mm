
#include "pch.h"

#import <mym-ios/MYMMOAIAmazonAnalyticsIOS.h>


//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//

int MYMMOAIAmazonAnalyticsIOS::_init(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* appKey = lua_tostring(state, 1);
	cc8* privateKey = lua_tostring(state, 2);
	if (appKey == NULL) {
		appKey = "";
	}
	if (privateKey == NULL) {
		privateKey = "";
	}
	id<AIInsightsCredentials> credentials = [AIAmazonInsights credentialsWithApplicationKey:[NSString stringWithUTF8String:appKey] withPrivateKey:[NSString stringWithUTF8String:privateKey]];
	MYMMOAIAmazonAnalyticsIOS::Get().insights = [[AIAmazonInsights insightsWithCredentials:credentials] retain];
	
	return 0;
}

int MYMMOAIAmazonAnalyticsIOS::_recordEvent(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* eventName = lua_tostring(state, 1);
	int count = lua_tointeger(state, 2);
	
	id<AIEventClient> eventClient = MYMMOAIAmazonAnalyticsIOS::Get().insights.eventClient;
	id<AIEvent> event = [eventClient createEventWithEventType:[NSString stringWithUTF8String:eventName]];
	
	for (int i = 1; i <= count * 2; i += 2) {
		cc8* key = lua_tostring(state, i + 2);
		cc8* val = lua_tostring(state, i + 3);
		if (key == NULL) {
			key = "";
		}
		if (val == NULL) {
			val = "";
		}
		[event addAttribute:[NSString stringWithUTF8String:val] forKey:[NSString stringWithUTF8String:key]];
	}

	[eventClient recordEvent:event];

	return 0;
}


//================================================================//
// MYMMOAIAmazonAnalyticsIOS
//================================================================//

//----------------------------------------------------------------//
MYMMOAIAmazonAnalyticsIOS::MYMMOAIAmazonAnalyticsIOS () {
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MYMMOAIAmazonAnalyticsIOS::~MYMMOAIAmazonAnalyticsIOS () {
	
}

//----------------------------------------------------------------//
void MYMMOAIAmazonAnalyticsIOS::RegisterLuaClass ( MOAILuaState& state ) {
	luaL_Reg regTable [] = {
		{"init", _init},
		{"recordEvent", _recordEvent},
		{NULL, NULL}
	};

	luaL_register ( state, 0, regTable );
}

