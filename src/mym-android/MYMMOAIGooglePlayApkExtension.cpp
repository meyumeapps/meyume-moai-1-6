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
#include <mym-android/MYMMOAIGooglePlayApkExtension.h>

extern JavaVM* jvm;


int MYMMOAIGooglePlayApkExtension::_init(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass apkExpansionHandler = env->FindClass("com/meyume/moai/gp/MYMApkExpansionHandler");
	if (apkExpansionHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find java class %s", "com/meyume/moai/gp/MYMApkExpansionHandler");
	} else {
		jmethodID init = env->GetStaticMethodID (apkExpansionHandler, "init", "()V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(apkExpansionHandler, init);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayApkExtension::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIGooglePlayApkExtension::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

int MYMMOAIGooglePlayApkExtension::_checkExpansionFile(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass apkExpansionHandler = env->FindClass("com/meyume/moai/gp/MYMApkExpansionHandler");
	if (apkExpansionHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find java class %s", "com/meyume/moai/gp/MYMApkExpansionHandler");
	} else {
		jmethodID checkExpansionFile = env->GetStaticMethodID (apkExpansionHandler, "checkExpansionFile", "()V");
		if (checkExpansionFile == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find static java method %s", "checkExpansionFile");
		} else {
			env->CallStaticVoidMethod(apkExpansionHandler, checkExpansionFile);
		}
	}
	
	return 0;
}

int MYMMOAIGooglePlayApkExtension::_getResourcesPath(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jstring ret;
	
	jclass apkExpansionHandler = env->FindClass("com/meyume/moai/gp/MYMApkExpansionHandler");
	if (apkExpansionHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find java class %s", "com/meyume/moai/gp/MYMApkExpansionHandler");
	} else {
		jmethodID getResourcesPath = env->GetStaticMethodID (apkExpansionHandler, "getResourcesPath", "()Ljava/lang/String;");
		if (getResourcesPath == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find static java method %s", "getResourcesPath");
		} else {
			ret = (jstring)env->CallStaticObjectMethod(apkExpansionHandler, getResourcesPath);
		}
	}
	
	if (ret == NULL) {
		lua_pushstring(state, "");
	} else {
		cc8* retString = (cc8*)env->GetStringUTFChars(ret, 0);
		lua_pushstring(state, retString);
	}
	
	return 1;
}

int MYMMOAIGooglePlayApkExtension::_deleteExpansionResources(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass apkExpansionHandler = env->FindClass("com/meyume/moai/gp/MYMApkExpansionHandler");
	if (apkExpansionHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find java class %s", "com/meyume/moai/gp/MYMApkExpansionHandler");
	} else {
		jmethodID deleteExpansionResources = env->GetStaticMethodID (apkExpansionHandler, "deleteExpansionResources", "()V");
		if (deleteExpansionResources == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGooglePlayApkExtension: Unable to find static java method %s", "deleteExpansionResources");
		} else {
			env->CallStaticVoidMethod(apkExpansionHandler, deleteExpansionResources);
		}
	}
	
	return 0;
}

MYMMOAIGooglePlayApkExtension::MYMMOAIGooglePlayApkExtension() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIGooglePlayApkExtension::~MYMMOAIGooglePlayApkExtension() {
}

void MYMMOAIGooglePlayApkExtension::RegisterLuaClass(MOAILuaState& state) {
	state.SetField(-1,"DONE_CHECKING", (u32)DONE_CHECKING);
	state.SetField(-1,"NOTIFY_DOWNLOAD_PROGRESS", (u32)NOTIFY_DOWNLOAD_PROGRESS);
	state.SetField(-1,"NOTIFY_VALIDATE_PROGRESS", (u32)NOTIFY_VALIDATE_PROGRESS);
	state.SetField(-1,"NOTIFY_VALIDATION_FAILED", (u32)NOTIFY_VALIDATION_FAILED);
	state.SetField(-1,"NOTIFY_EXTRACTION_FAILED", (u32)NOTIFY_EXTRACTION_FAILED);
	state.SetField(-1,"NOTIFY_EXTRACTING", (u32)NOTIFY_EXTRACTING);
	state.SetField(-1,"NOTIFY_DOWNLOAD_FAILED", (u32)NOTIFY_DOWNLOAD_FAILED);
	state.SetField(-1,"NOTIFY_NETWORK_NOT_AVAILABLE", (u32)NOTIFY_NETWORK_NOT_AVAILABLE);
	
	luaL_Reg regTable[] = {
		{"setListener", _setListener},
		{"init", _init},
		{"checkExpansionFile", _checkExpansionFile},
		{"getResourcesPath", _getResourcesPath},
		{"deleteExpansionResources", _deleteExpansionResources},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

void MYMMOAIGooglePlayApkExtension::notifyDoneChecking() {
	MOAILuaRef& callback = this->mListeners[DONE_CHECKING];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayApkExtension::notifyDownloadProgress(long p) {
	MOAILuaRef& callback = this->mListeners[NOTIFY_DOWNLOAD_PROGRESS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushnumber(state, p);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGooglePlayApkExtension::notifyValidateProgress(long p) {
	MOAILuaRef& callback = this->mListeners[NOTIFY_VALIDATE_PROGRESS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushnumber(state, p);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGooglePlayApkExtension::notifyValidationFailed() {
	MOAILuaRef& callback = this->mListeners[NOTIFY_VALIDATION_FAILED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayApkExtension::notifyExtractionFailed() {
	MOAILuaRef& callback = this->mListeners[NOTIFY_EXTRACTION_FAILED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayApkExtension::notifyExtracting() {
	MOAILuaRef& callback = this->mListeners[NOTIFY_EXTRACTING];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayApkExtension::notifyDownloadFailed() {
	MOAILuaRef& callback = this->mListeners[NOTIFY_DOWNLOAD_FAILED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGooglePlayApkExtension::notifyNetworkNotAvailable() {
	MOAILuaRef& callback = this->mListeners[NOTIFY_NETWORK_NOT_AVAILABLE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKUMYMNotifyDoneChecking(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayApkExtension::Get().notifyDoneChecking();
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKUMYMNotifyDownloadProgress(JNIEnv* env, jclass obj, long p) {
	MYMMOAIGooglePlayApkExtension::Get().notifyDownloadProgress(p);
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKUMYMNotifyValidateProgress(JNIEnv* env, jclass obj, long p) {
	MYMMOAIGooglePlayApkExtension::Get().notifyValidateProgress(p);
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKUMYMNotifyValidationFailed(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayApkExtension::Get().notifyValidationFailed();
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKUMYMNotifyExtractionFailed(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayApkExtension::Get().notifyExtractionFailed();
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKUMYMNotifyExtracting(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayApkExtension::Get().notifyExtracting();
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKUMYMNotifyDownloadFailed(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayApkExtension::Get().notifyDownloadFailed();
}

extern "C" void Java_com_meyume_moai_gp_MYMApkExpansionHandler_AKYMYMNotifyNetworkNotAvailable(JNIEnv* env, jclass obj) {
	MYMMOAIGooglePlayApkExtension::Get().notifyNetworkNotAvailable();
}
