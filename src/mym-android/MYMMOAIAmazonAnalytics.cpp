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
#include <mym-android/MYMMOAIAmazonAnalytics.h>

extern JavaVM* jvm;

int MYMMOAIAmazonAnalytics::_init(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* appKey = lua_tostring(state, 1);
	cc8* privateKey = lua_tostring(state, 2);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (appKey, jappKey);
	JNI_GET_JSTRING (privateKey, jprivateKey);
	
	jclass analytics = env->FindClass("com/meyume/moai/MYMAmazonAnalytics");
	if (analytics == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonAnalytics: Unable to find java class %s", "com/meyume/moai/MYMAmazonAnalytics");
	} else {
		jmethodID init = env->GetStaticMethodID (analytics, "init", "(Ljava/lang/String;Ljava/lang/String;)V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonAnalytics: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(analytics, init, jappKey, jprivateKey);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonAnalytics::_recordEvent(lua_State* L) {
	MOAILuaState state(L);
	JNI_GET_ENV (jvm, env);
	
	cc8* event = lua_tostring(state, 1);
	int count = lua_tointeger(state, 2);
	
	int top = state.GetTop ();
	jobjectArray array = (jobjectArray)env->NewObjectArray(top, env->FindClass("java/lang/String"), env->NewStringUTF(""));
	
	for ( int i = 3; i <= top; ++i ) {
		if ( state.IsType ( i, LUA_TSTRING )) {
			
			cc8* p = state.GetValue < cc8* >( i, "" );
			env->SetObjectArrayElement(array, i - 3, env->NewStringUTF(p));
		}
	}
	
	JNI_GET_JSTRING (event, jevent);
	
	jclass analytics = env->FindClass("com/meyume/moai/MYMAmazonAnalytics");
	if (analytics == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonAnalytics: Unable to find java class %s", "com/meyume/moai/MYMAmazonAnalytics");
	} else {
		jmethodID recordEvent = env->GetStaticMethodID (analytics, "recordEvent", "(Ljava/lang/String;I[Ljava/lang/String;)V");
		if (recordEvent == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonAnalytics: Unable to find static java method %s", "recordEvent");
		} else {
			env->CallStaticVoidMethod(analytics, recordEvent, jevent, count, array);
		}
	}
	
	return 0;
}

MYMMOAIAmazonAnalytics::MYMMOAIAmazonAnalytics() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIAmazonAnalytics::~MYMMOAIAmazonAnalytics() {
}

void MYMMOAIAmazonAnalytics::RegisterLuaClass(MOAILuaState& state) {
	luaL_Reg regTable[] = {
		{"init", _init},
		{"recordEvent", _recordEvent},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}
