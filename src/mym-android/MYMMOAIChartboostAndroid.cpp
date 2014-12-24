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
#include <mym-android/MYMMOAIChartboostAndroid.h>

extern JavaVM* jvm;

int MYMMOAIChartboostAndroid::_init(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* appId = lua_tostring(state, 1);
	cc8* appSignature = lua_tostring(state, 2);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (appId, jappId);
	JNI_GET_JSTRING (appSignature, jappSignature);
	
	jclass chartboost = env->FindClass("com/meyume/moai/MYMChartboost");
	if (chartboost == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find java class %s", "com/meyume/moai/MYMChartboost");
	} else {
		jmethodID init = env->GetStaticMethodID (chartboost, "init", "(Ljava/lang/String;Ljava/lang/String;)V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(chartboost, init, jappId, jappSignature);
		}
	}
	
	return 0;
}

int MYMMOAIChartboostAndroid::_cacheAd(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* location = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (location, jlocation);
	
	jclass chartboost = env->FindClass("com/meyume/moai/MYMChartboost");
	if (chartboost == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find java class %s", "com/meyume/moai/MYMChartboost");
	} else {
		jmethodID cacheAd = env->GetStaticMethodID (chartboost, "cacheAd", "(Ljava/lang/String;)V");
		if (cacheAd == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find static java method %s", "cacheAd");
		} else {
			env->CallStaticVoidMethod(chartboost, cacheAd, jlocation);
		}
	}
	
	return 0;
}

int MYMMOAIChartboostAndroid::_showAd(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* location = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (location, jlocation);
	
	jclass chartboost = env->FindClass("com/meyume/moai/MYMChartboost");
	if (chartboost == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find java class %s", "com/meyume/moai/MYMChartboost");
	} else {
		jmethodID showAd = env->GetStaticMethodID (chartboost, "showAd", "(Ljava/lang/String;)V");
		if (showAd == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find static java method %s", "showAd");
		} else {
			env->CallStaticVoidMethod(chartboost, showAd, jlocation);
		}
	}
	
	return 0;
}

int MYMMOAIChartboostAndroid::_cacheMoreApps(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass chartboost = env->FindClass("com/meyume/moai/MYMChartboost");
	if (chartboost == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find java class %s", "com/meyume/moai/MYMChartboost");
	} else {
		jmethodID cacheMoreApps = env->GetStaticMethodID (chartboost, "cacheMoreApps", "()V");
		if (cacheMoreApps == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find static java method %s", "cacheMoreApps");
		} else {
			env->CallStaticVoidMethod(chartboost, cacheMoreApps);
		}
	}
	
	return 0;
}

int MYMMOAIChartboostAndroid::_showMoreApps(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass chartboost = env->FindClass("com/meyume/moai/MYMChartboost");
	if (chartboost == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find java class %s", "com/meyume/moai/MYMChartboost");
	} else {
		jmethodID showMoreApps = env->GetStaticMethodID (chartboost, "showMoreApps", "()V");
		if (showMoreApps == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find static java method %s", "showMoreApps");
		} else {
			env->CallStaticVoidMethod(chartboost, showMoreApps);
		}
	}
	
	return 0;
}

int MYMMOAIChartboostAndroid::_cancelAds(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass chartboost = env->FindClass("com/meyume/moai/MYMChartboost");
	if (chartboost == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find java class %s", "com/meyume/moai/MYMChartboost");
	} else {
		jmethodID cancelAds = env->GetStaticMethodID (chartboost, "cancelAds", "()V");
		if (cancelAds == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIChartboostAndroid: Unable to find static java method %s", "cancelAds");
		} else {
			env->CallStaticVoidMethod(chartboost, cancelAds);
		}
	}
	
	return 0;
}

MYMMOAIChartboostAndroid::MYMMOAIChartboostAndroid() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIChartboostAndroid::~MYMMOAIChartboostAndroid() {
}

void MYMMOAIChartboostAndroid::RegisterLuaClass(MOAILuaState& state) {
	luaL_Reg regTable[] = {
		{"init", _init},
		{"loadInterstitial", _cacheAd},
		{"showInterstitial", _showAd},
		{"loadMoreApps", _cacheMoreApps},
		{"showMoreApps", _showMoreApps},
		{"cancelAds", _cancelAds},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}
