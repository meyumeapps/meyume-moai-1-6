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
#include <mym-android/MYMMOAIAmazonIAP.h>

extern JavaVM* jvm;

int MYMMOAIAmazonIAP::_init(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass amazonIAP = env->FindClass("com/meyume/moai/MYMAmazonIAP");
	if (amazonIAP == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find java class %s", "com/meyume/moai/MYMAmazonIAP");
	} else {
		jmethodID init = env->GetStaticMethodID (amazonIAP, "init", "()V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(amazonIAP, init);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonIAP::_requestProducts(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	int top = lua_tointeger(state, 1);
	jobjectArray array = (jobjectArray)env->NewObjectArray(top, env->FindClass("java/lang/String"), env->NewStringUTF(""));
	
	for (int i = 0; i < top; i++) {
		int index = i + 2;
		cc8* identifier = lua_tostring(state, index);
		env->SetObjectArrayElement(array, i, env->NewStringUTF(identifier));
	}
	
	jclass amazonIAP = env->FindClass("com/meyume/moai/MYMAmazonIAP");
	if (amazonIAP == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find java class %s", "com/meyume/moai/MYMAmazonIAP");
	} else {
		jmethodID requestProducts = env->GetStaticMethodID (amazonIAP, "requestProducts", "([Ljava/lang/String;)V");
		if (requestProducts == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find static java method %s", "requestProducts");
		} else {
			env->CallStaticVoidMethod(amazonIAP, requestProducts, array);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonIAP::_requestPurchase(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	JNI_GET_JSTRING (id, jid);
	
	jclass amazonIAP = env->FindClass("com/meyume/moai/MYMAmazonIAP");
	if (amazonIAP == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find java class %s", "com/meyume/moai/MYMAmazonIAP");
	} else {
		jmethodID requestPurchase = env->GetStaticMethodID (amazonIAP, "requestPurchase", "(Ljava/lang/String;)V");
		if (requestPurchase == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find static java method %s", "requestPurchase");
		} else {
			env->CallStaticVoidMethod(amazonIAP, requestPurchase, jid);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonIAP::_getPurchases(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass amazonIAP = env->FindClass("com/meyume/moai/MYMAmazonIAP");
	if (amazonIAP == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find java class %s", "com/meyume/moai/MYMAmazonIAP");
	} else {
		jmethodID getPurchases = env->GetStaticMethodID (amazonIAP, "getPurchases", "()V");
		if (getPurchases == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonIAP: Unable to find static java method %s", "getPurchases");
		} else {
			env->CallStaticVoidMethod(amazonIAP, getPurchases);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonIAP::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIAmazonIAP::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

MYMMOAIAmazonIAP::MYMMOAIAmazonIAP() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIAmazonIAP::~MYMMOAIAmazonIAP() {
}

void MYMMOAIAmazonIAP::RegisterLuaClass(MOAILuaState& state) {
	state.SetField(-1,"RETRIEVED_PRODUCTS", (u32)RETRIEVED_PRODUCTS);
	state.SetField(-1,"FAILED_TO_GET_PRODUCTS", (u32)FAILED_TO_GET_PRODUCTS);
	state.SetField(-1,"FAILED_TO_PURCHASE", (u32)FAILED_TO_PURCHASE);
	state.SetField(-1,"PURCHASED", (u32)PURCHASED);
	state.SetField(-1,"REQUEST_OWNED_PURCHASE", (u32)REQUEST_OWNED_PURCHASE);
	state.SetField(-1,"FAILED_TO_GET_PURCHASES", (u32)FAILED_TO_GET_PURCHASES);
	state.SetField(-1,"RETRIEVED_PURCHASES", (u32)RETRIEVED_PURCHASES);
	
	luaL_Reg regTable[] = {
		{"init", _init},
		{"setListener", _setListener},
		{"requestProducts", _requestProducts},
		{"requestPurchase", _requestPurchase},
		{"getPurchases", _getPurchases},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

void MYMMOAIAmazonIAP::notifyRetrievedProducts(cc8* array[], int length) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_PRODUCTS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_newtable ( state );
		
		for (int i = 0; i < length; i++) {
			lua_newtable ( state );
			
			lua_pushstring(state, array[i]);
			lua_setfield(state, -2, "product");
		
			lua_rawseti(state, -2, i + 1);
		}
		
		state.DebugCall(1, 0);
	}
}

void MYMMOAIAmazonIAP::notifyFailedToGetProducts(int errorCode) {
	MOAILuaRef& callback = this->mListeners[FAILED_TO_GET_PRODUCTS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushinteger(state, errorCode);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIAmazonIAP::notifyFailedToPurchase(int errorCode) {
	MOAILuaRef& callback = this->mListeners[FAILED_TO_PURCHASE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushinteger(state, errorCode);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIAmazonIAP::notifyPurchased(cc8* id) {
	MOAILuaRef& callback = this->mListeners[PURCHASED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushstring(state, id);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIAmazonIAP::notifyRequestOwnedPurchase() {
	MOAILuaRef& callback = this->mListeners[REQUEST_OWNED_PURCHASE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIAmazonIAP::notifyFailedToGetPurchases() {
	MOAILuaRef& callback = this->mListeners[FAILED_TO_GET_PURCHASES];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIAmazonIAP::notifyRetrievedPurchases(cc8* array[], int length) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_PURCHASES];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_newtable ( state );
		
		for (int i = 0; i < length; i++) {
			lua_pushstring( state, "id");
			lua_pushstring ( state, array[i]);
			lua_settable ( state, -3 );
		}
		
		state.DebugCall(1, 0);
	}
}

extern "C" void Java_com_meyume_moai_MYMAmazonIAP_AKUMYMNotifyAmazonIAPRetrievedProducts(JNIEnv* env, jclass obj, jobjectArray array, int length) {
	cc8* products[length];
	
	for (int i = 0; i < length; i++) {
		jstring data = (jstring)env->GetObjectArrayElement(array, i);
		products[i] = (cc8*)env->GetStringUTFChars(data, 0);
	}
	
	MYMMOAIAmazonIAP::Get().notifyRetrievedProducts(products, length);
}

extern "C" void Java_com_meyume_moai_MYMAmazonIAP_AKUMYMNotifyAmazonIAPFailedToRequestProducts(JNIEnv* env, jclass obj, int errorCode) {
	MYMMOAIAmazonIAP::Get().notifyFailedToGetProducts(errorCode);
}

extern "C" void Java_com_meyume_moai_MYMAmazonIAP_AKUMYMNotifyAmazonIAPFailedToRequestPurchase(JNIEnv* env, jclass obj, int errorCode) {
	MYMMOAIAmazonIAP::Get().notifyFailedToPurchase(errorCode);
}

extern "C" void Java_com_meyume_moai_MYMAmazonIAP_AKUMYMNotifyAmazonIAPPurchasedProduct(JNIEnv* env, jclass obj, jstring id) {
	MYMMOAIAmazonIAP::Get().notifyPurchased((cc8*)env->GetStringUTFChars(id, 0));
}

extern "C" void Java_com_meyume_moai_MYMAmazonIAP_AKUMYMNotifyAmazonIAPRequestOwnedPurchase(JNIEnv* env, jclass obj) {
	MYMMOAIAmazonIAP::Get().notifyRequestOwnedPurchase();
}

extern "C" void Java_com_meyume_moai_MYMAmazonIAP_AKUMYMNotifyAmazonIAPFailedToRetrievePurchases(JNIEnv* env, jclass obj) {
	MYMMOAIAmazonIAP::Get().notifyFailedToGetPurchases();
}

extern "C" void Java_com_meyume_moai_MYMAmazonIAP_AKUMYMNotifyAmazonIAPRetrievedPurchases(JNIEnv* env, jclass obj, jobjectArray array, int length) {
	cc8* ids[length];
	
	for (int i = 0; i < length; i++) {
		jstring id = (jstring)env->GetObjectArrayElement(array, i);
		ids[i] = (cc8*)env->GetStringUTFChars(id, 0);
	}
	
	MYMMOAIAmazonIAP::Get().notifyRetrievedPurchases(ids, length);
}
