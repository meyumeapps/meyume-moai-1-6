/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */

#include "moai-core/pch.h"
#include "moai-sim/pch.h"

#include <jni.h>

#include <moai-android/moaiext-jni.h>
#include <mym-android/MYMMOAIHelper.h>

extern JavaVM* jvm;

int MYMMOAIHelper::_openURL(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* url = lua_tostring ( state, 1 );
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING ( url, jurl );
	
	jclass helper = env->FindClass("com/meyume/moai/MYMMoaiHelper");
	if (helper == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIHelper: Unable to find java class %s", "com/meyume/moai/MYMMoaiHelper");
	} else {
		jmethodID openURL = env->GetStaticMethodID (helper, "openURL", "(Ljava/lang/String;)Z");
		if (openURL == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIHelper: Unable to find static java method %s", "openURL");
		} else {
			jboolean ret = env->CallStaticBooleanMethod(helper, openURL, jurl);
			lua_pushboolean ( state, ret );
			
			return 1;
		}
	}
	
	lua_pushinteger ( state, false );
	return 1;
}

int MYMMOAIHelper::_getSharedProp(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* key = lua_tostring ( state, 1 );
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING ( key, jkey );
	
	jclass helper = env->FindClass("com/meyume/moai/MYMMoaiHelper");
	if (helper == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIHelper: Unable to find java class %s", "com/meyume/moai/MYMMoaiHelper");
	} else {
		jmethodID getSharedProp = env->GetStaticMethodID (helper, "getSharedProp", "(Ljava/lang/String;)I");
		if (getSharedProp == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIHelper: Unable to find static java method %s", "getSharedProp");
		} else {
			int ret = env->CallStaticIntMethod(helper, getSharedProp, jkey);
			lua_pushinteger ( state, ret );
			
			return 1;
		}
	}
	
	lua_pushinteger ( state, 0 );
	return 1;
}

int MYMMOAIHelper::_setSharedProp(lua_State* L) {
	MOAILuaState state(L);
	JNI_GET_ENV (jvm, env);
	
	cc8* key = lua_tostring ( state, 1 );
	int val = lua_tointeger ( state, 2 );
	
	JNI_GET_JSTRING ( key, jkey );
	
	jclass helper = env->FindClass("com/meyume/moai/MYMMoaiHelper");
	if (helper == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIHelper: Unable to find java class %s", "com/meyume/moai/MYMMoaiHelper");
	} else {
		jmethodID setSharedProp = env->GetStaticMethodID (helper, "setSharedProp", "(Ljava/lang/String;I)V");
		if (setSharedProp == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIHelper: Unable to find static java method %s", "setSharedProp");
		} else {
			env->CallStaticVoidMethod(helper, setSharedProp, jkey, val);
		}
	}
	
	return 0;
}

int MYMMOAIHelper::_setAutoRender ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	bool val = lua_toboolean ( state, 1 );
	
	JNI_GET_ENV ( jvm, env );
	
	jclass helper = env->FindClass ( "com/meyume/moai/MYMMoaiHelper" );
    if ( helper == NULL ) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMoaiHelper: Unable to find java class %s", "com/meyume/moai/MYMMoaiHelper" );
    } else {

    	jmethodID setAutoRender = env->GetStaticMethodID ( helper, "setAutoRender", "(Z)V" );
    	if ( setAutoRender == NULL ) {

			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMoaiHelper: Unable to find static java method %s", "setAutoRender" );
    	} else {

			env->CallStaticVoidMethod ( helper, setAutoRender, val);
		}
	}
	
	return 0;
}


int MYMMOAIHelper::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIHelper::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

MYMMOAIHelper::MYMMOAIHelper() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIHelper::~MYMMOAIHelper() {
}

void MYMMOAIHelper::RegisterLuaClass(MOAILuaState& state) {
	state.SetField ( -1, "BACK_BUTTON_PRESSED",		( u32 )BACK_BUTTON_PRESSED );
	
	luaL_Reg regTable[] = {
		{ "openURL",				_openURL },
		{ "getSharedProp",			_getSharedProp },
		{ "setSharedProp",			_setSharedProp },
		{ "setListener",			_setListener },
		{ "setAutoRender",			_setAutoRender },
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

bool MYMMOAIHelper::notifyBackButtonPressed () {
	
	MOAILuaRef& callback = this->mListeners [ BACK_BUTTON_PRESSED ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();

		state.DebugCall ( 0, 1 );

		return lua_toboolean ( state, -1 );
	} else {
		
		return false;
	}
}

extern "C" bool Java_com_meyume_moai_MYMMoaiHelper_AKUAppBackButtonPressed ( JNIEnv* env, jclass obj ) {

	return MYMMOAIHelper::Get ().notifyBackButtonPressed ();
}

