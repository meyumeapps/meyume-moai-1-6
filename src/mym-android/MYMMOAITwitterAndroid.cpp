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
#include <mym-android/MYMMOAITwitterAndroid.h>

extern JavaVM* jvm;

int MYMMOAITwitterAndroid::_init(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* apiKey = lua_tostring(state, 1);
	cc8* apiSecret = lua_tostring(state, 2);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (apiKey, japiKey);
	JNI_GET_JSTRING (apiSecret, japiSecret);
	
	jclass mymTwitter = env->FindClass("com/meyume/moai/MYMTwitter");
	if (mymTwitter == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAITwitterAndroid: Unable to find java class %s", "com/meyume/moai/MYMTwitter");
	} else {
		jmethodID init = env->GetStaticMethodID (mymTwitter, "init", "(Ljava/lang/String;Ljava/lang/String;)V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAITwitterAndroid: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(mymTwitter, init, japiKey, japiSecret);
		}
	}
	
	return 0;
}

int MYMMOAITwitterAndroid::_login(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass mymTwitter = env->FindClass("com/meyume/moai/MYMTwitter");
	if (mymTwitter == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAITwitterAndroid: Unable to find java class %s", "com/meyume/moai/MYMTwitter");
	} else {
		jmethodID login = env->GetStaticMethodID (mymTwitter, "login", "()V");
		if (login == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAITwitterAndroid: Unable to find static java method %s", "login");
		} else {
			env->CallStaticVoidMethod(mymTwitter, login);
		}
	}
	
	return 0;
}

int MYMMOAITwitterAndroid::_tweetPhoto(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* message = lua_tostring(state, 1);
	cc8* url = lua_tostring(state, 2);
	cc8* pictureUrl = lua_tostring(state, 3);
	
	JNI_GET_JSTRING (message, jmessage);
	JNI_GET_JSTRING (url, jurl);
	JNI_GET_JSTRING (pictureUrl, jpictureUrl);
	
	jclass mymTwitter = env->FindClass("com/meyume/moai/MYMTwitter");
	if (mymTwitter == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAITwitterAndroid: Unable to find java class %s", "com/meyume/moai/MYMTwitter");
	} else {
		jmethodID tweetPhoto = env->GetStaticMethodID (mymTwitter, "tweetPhoto", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (tweetPhoto == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAITwitterAndroid: Unable to find static java method %s", "tweetPhoto");
		} else {
			env->CallStaticVoidMethod(mymTwitter, tweetPhoto, jmessage, jurl, jpictureUrl);
		}
	}
	
	return 0;
}

int MYMMOAITwitterAndroid::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAITwitterAndroid::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

MYMMOAITwitterAndroid::MYMMOAITwitterAndroid() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAITwitterAndroid::~MYMMOAITwitterAndroid() {
}

void MYMMOAITwitterAndroid::RegisterLuaClass(MOAILuaState& state) {
	state.SetField ( -1, "DID_LOGIN",		( u32 )DID_LOGIN );
	state.SetField ( -1, "FAILED_LOGIN",		( u32 )FAILED_LOGIN );
	state.SetField ( -1, "DID_TWEET_PHOTO",		( u32 )DID_TWEET_PHOTO );
	
	luaL_Reg regTable[] = {
		{"init", _init},
		{"login", _login},
		{"tweetPhoto", _tweetPhoto},
		{"setListener", _setListener},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

void MYMMOAITwitterAndroid::notifyDidLogin() {
	MOAILuaRef& callback = this->mListeners[DID_LOGIN];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAITwitterAndroid::notifyFailedLogin() {
	MOAILuaRef& callback = this->mListeners[FAILED_LOGIN];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAITwitterAndroid::notifyDidTweetPhoto(bool success) {
	MOAILuaRef& callback = this->mListeners[DID_TWEET_PHOTO];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushboolean(state, success);
		state.DebugCall(1, 0);
	}
}

extern "C" void Java_com_meyume_moai_MYMTwitter_AKUMYMNotifyTwitterDidLogin ( JNIEnv* env, jclass obj ) {
	MYMMOAITwitterAndroid::Get().notifyDidLogin();
}

extern "C" void Java_com_meyume_moai_MYMTwitter_AKUMYMNotifyTwitterFailedLogin ( JNIEnv* env, jclass obj ) {
	MYMMOAITwitterAndroid::Get().notifyFailedLogin();
}

extern "C" void Java_com_meyume_moai_MYMTwitter_AKUMYMNotifyDidTweetPhoto ( JNIEnv* env, jclass obj, jboolean success ) {
	MYMMOAITwitterAndroid::Get().notifyDidTweetPhoto(success);
}
