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
#include <mym-android/MYMMOAIGooglePlayServices.h>

extern JavaVM* jvm;


int MYMMOAIGooglePlayServices::_init(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID init = env->GetStaticMethodID (googlePlayServices, "init", "()V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, init);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIGooglePlayServices::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_login(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID connect = env->GetStaticMethodID (googlePlayServices, "connect", "()V");
		if (connect == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "connect");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, connect);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_logout(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID logout = env->GetStaticMethodID (googlePlayServices, "logout", "()V");
		if (logout == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "logout");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, logout);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_isLoggedIn(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID isLoggedIn = env->GetStaticMethodID (googlePlayServices, "isLoggedIn", "()Z");
		if (isLoggedIn == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "isLoggedIn");
		} else {
			jboolean ret = (jboolean)env->CallStaticBooleanMethod(googlePlayServices, isLoggedIn);
			
			lua_pushboolean(state, ret);
			return 1;
		}
	}
	
	lua_pushboolean(state, false);
	return 1;
}

int MYMMOAIGooglePlayServices::_showLeaderboard(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	JNI_GET_JSTRING (id, jid);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID showLeaderboard = env->GetStaticMethodID (googlePlayServices, "showLeaderboard", "(Ljava/lang/String;)V");
		if (showLeaderboard == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "showLeaderboard");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, showLeaderboard, jid);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_showLeaderboards(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID showLeaderboards = env->GetStaticMethodID (googlePlayServices, "showLeaderboards", "()V");
		if (showLeaderboards == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "showLeaderboards");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, showLeaderboards);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_showAchievements(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID showAchievements = env->GetStaticMethodID (googlePlayServices, "showAchievements", "()V");
		if (showAchievements == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "showAchievements");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, showAchievements);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_submitScore(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	long score = lua_tonumber(state, 2);
	bool immediate = lua_toboolean(state, 3);
	
	// JNI bug that failed sending a long integer number to Java,
	// the work around is to use an array instead.
	jlongArray scoreArray = env->NewLongArray(1);
	jlong *arr = env->GetLongArrayElements(scoreArray, NULL);
	arr[0] = score;
	env->ReleaseLongArrayElements(scoreArray, arr, NULL);
	
	JNI_GET_JSTRING (id, jid);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID submitScore = env->GetStaticMethodID (googlePlayServices, "submitScore", "(Ljava/lang/String;[JZ)V");
		if (submitScore == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "submitScore");
		} else {
			//env->CallStaticVoidMethod(googlePlayServices, submitScore, jid, score, immediate);
			env->CallStaticVoidMethod(googlePlayServices, submitScore, jid, scoreArray, immediate);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_unlockAchievement(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	JNI_GET_JSTRING (id, jid);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID unlockAchievement = env->GetStaticMethodID (googlePlayServices, "unlockAchievement", "(Ljava/lang/String;)V");
		if (unlockAchievement == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "unlockAchievement");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, unlockAchievement, jid);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_incrementAchievement(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	int numSteps = lua_tointeger(state, 2);
	JNI_GET_JSTRING (id, jid);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID incrementAchievement = env->GetStaticMethodID (googlePlayServices, "incrementAchievement", "(Ljava/lang/String;I)V");
		if (incrementAchievement == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "incrementAchievement");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, incrementAchievement, jid, numSteps);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_loadPlayerRank(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	bool forceReload = lua_toboolean(state, 2);
	JNI_GET_JSTRING (id, jid);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID loadPlayerRank = env->GetStaticMethodID (googlePlayServices, "loadPlayerRank", "(Ljava/lang/String;Z)V");
		if (loadPlayerRank == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "loadPlayerRank");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, loadPlayerRank, jid, forceReload);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_loadAchievements(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID loadAchievements = env->GetStaticMethodID (googlePlayServices, "loadAchievements", "()V");
		if (loadAchievements == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "loadAchievements");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, loadAchievements);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayServices::_isServiceAvailable(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID isServiceAvailable = env->GetStaticMethodID (googlePlayServices, "isServiceAvailable", "()Z");
		if (isServiceAvailable == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "isServiceAvailable");
		} else {
			jboolean ret = (jboolean)env->CallStaticBooleanMethod(googlePlayServices, isServiceAvailable);
			
			lua_pushboolean(state, ret);
			return 1;
		}
	}
	
	lua_pushboolean(state, false);
	return 1;
}

int MYMMOAIGooglePlayServices::_showShareDialog(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* text = lua_tostring(state, 1);
	cc8* url = lua_tostring(state, 2);
	JNI_GET_JSTRING (text, jtext);
	JNI_GET_JSTRING (url, jurl);
	
	jclass googlePlayServices = env->FindClass("com/meyume/moai/gp/MYMGooglePlayServices");
	if (googlePlayServices == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find java class %s", "com/meyume/moai/gp/MYMGooglePlayServices");
	} else {
		jmethodID showShareDialog = env->GetStaticMethodID (googlePlayServices, "showShareDialog", "(Ljava/lang/String;Ljava/lang/String;)V");
		if (showShareDialog == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayServices: Unable to find static java method %s", "showShareDialog");
		} else {
			env->CallStaticVoidMethod(googlePlayServices, showShareDialog, jtext, jurl);
		}
	}
	
	return 0;
}

MYMMOAIGooglePlayServices::MYMMOAIGooglePlayServices() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIGooglePlayServices::~MYMMOAIGooglePlayServices() {
}

void MYMMOAIGooglePlayServices::RegisterLuaClass(MOAILuaState& state) {
	state.SetField(-1,"LOGGED_IN", (u32)LOGGED_IN);
	state.SetField(-1,"LOGGED_OUT", (u32)LOGGED_OUT);
	state.SetField(-1,"LOADED_PLAYER_RANK", (u32)LOADED_PLAYER_RANK);
	state.SetField(-1,"DID_SUBMIT_SCORE", (u32)DID_SUBMIT_SCORE);
	state.SetField(-1,"LOADED_ACHIEVEMENTS", (u32)LOADED_ACHIEVEMENTS);
	
	luaL_Reg regTable[] = {
		{"setListener", _setListener},
		{"init", _init},
		{"login", _login},
		{"logout", _logout},
		{"isLoggedIn", _isLoggedIn},
		{"showLeaderboard", _showLeaderboard},
		{"showLeaderboards", _showLeaderboards},
		{"showAchievements", _showAchievements},
		{"submitScore", _submitScore},
		{"unlockAchievement", _unlockAchievement},
		{"incrementAchievement", _incrementAchievement},
		{"loadPlayerRank", _loadPlayerRank},
		{"loadAchievements", _loadAchievements},
		{"isServiceAvailable", _isServiceAvailable},
		{"showShareDialog", _showShareDialog},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

void MYMMOAIGooglePlayServices::notifyLoggedIn() {
	MOAILuaRef& callback = this->mListeners[LOGGED_IN];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayServices::notifyLoggedOut() {
	MOAILuaRef& callback = this->mListeners[LOGGED_OUT];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayServices::notifyLoadedPlayerRank(long rank) {
	MOAILuaRef& callback = this->mListeners[LOADED_PLAYER_RANK];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushnumber(state, rank);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGooglePlayServices::notifyDidSubmitScore() {
	MOAILuaRef& callback = this->mListeners[DID_SUBMIT_SCORE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayServices::notifyLoadedAchievements(cc8* array[], int length) {
	MOAILuaRef& callback = this->mListeners[LOADED_ACHIEVEMENTS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_newtable ( state );
		
		for (int i = 0; i < length; i++) {
			lua_newtable ( state );
			
			lua_pushstring(state, array[i]);
			lua_setfield(state, -2, "achievement");
		
			lua_rawseti(state, -2, i + 1);
		}
		
		state.DebugCall(1, 0);
	}
}


extern "C" void Java_com_meyume_moai_gp_MYMGooglePlayServices_AKUMYMNotifyGPSOnConnected(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayServices::Get().notifyLoggedIn();
}

extern "C" void Java_com_meyume_moai_gp_MYMGooglePlayServices_AKUMYMNotifyGPSFailedToConnect(JNIEnv* env, jclass obj, int code) {
	
}

extern "C" void Java_com_meyume_moai_gp_MYMGooglePlayServices_AKUMYMNotifyGPSOnDisconnected(JNIEnv* env, jclass obj) {
	
}

extern "C" void Java_com_meyume_moai_gp_MYMGooglePlayServices_AKUMYMNotifyGPSOnSignedOut(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayServices::Get().notifyLoggedOut();
}

extern "C" void Java_com_meyume_moai_gp_MYMGooglePlayServices_AKUMYMNotifyGPSLoadedPlayerRank(JNIEnv* env, jclass obj, long rank) {
	MYMMOAIGooglePlayServices::Get().notifyLoadedPlayerRank(rank);
}

extern "C" void Java_com_meyume_moai_gp_MYMGooglePlayServices_AKUMYMNotifyGPSDidSubmitScore(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayServices::Get().notifyDidSubmitScore();
}

extern "C" void Java_com_meyume_moai_gp_MYMGooglePlayServices_AKUMYMNotifyGPSLoadedAchievements(JNIEnv* env, jclass obj, jobjectArray array, int length) {
	cc8* achievements[length];
	
	for (int i = 0; i < length; i++) {
		jstring entry = (jstring)env->GetObjectArrayElement(array, i);
		achievements[i] = (cc8*)env->GetStringUTFChars(entry, 0);
	}
	
	MYMMOAIGooglePlayServices::Get().notifyLoadedAchievements(achievements, length);
}
