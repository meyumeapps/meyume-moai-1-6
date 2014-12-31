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
#include <mym-android/MYMMOAIGoogleBillingAndroid.h>

extern JavaVM* jvm;

int MYMMOAIGoogleBillingAndroid::_init(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass googleBilling = env->FindClass("com/meyume/moai/gp/MYMGoogleBilling");
	if (googleBilling == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find java class %s", "com/meyume/moai/gp/MYMGoogleBilling");
	} else {
		jmethodID init = env->GetStaticMethodID (googleBilling, "init", "()V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(googleBilling, init);
		}
	}
	
	return 0;
}

int MYMMOAIGoogleBillingAndroid::_requestProducts(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	int top = lua_tointeger(state, 1);
	jobjectArray array = (jobjectArray)env->NewObjectArray(top, env->FindClass("java/lang/String"), env->NewStringUTF(""));
	
	for (int i = 0; i < top; i++) {
		int index = i + 2;
		cc8* identifier = lua_tostring(state, index);
		env->SetObjectArrayElement(array, i, env->NewStringUTF(identifier));
	}
	
	jclass googleBilling = env->FindClass("com/meyume/moai/gp/MYMGoogleBilling");
	if (googleBilling == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find java class %s", "com/meyume/moai/gp/MYMGoogleBilling");
	} else {
		jmethodID requestProducts = env->GetStaticMethodID (googleBilling, "requestProducts", "([Ljava/lang/String;)V");
		if (requestProducts == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find static java method %s", "requestProducts");
		} else {
			env->CallStaticVoidMethod(googleBilling, requestProducts, array);
		}
	}
	
	return 0;
}

int MYMMOAIGoogleBillingAndroid::_requestPurchase(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	bool consumable = lua_toboolean(state, 2);
	JNI_GET_JSTRING (id, jid);
	
	jclass googleBilling = env->FindClass("com/meyume/moai/gp/MYMGoogleBilling");
	if (googleBilling == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find java class %s", "com/meyume/moai/gp/MYMGoogleBilling");
	} else {
		jmethodID requestPurchase = env->GetStaticMethodID (googleBilling, "requestPurchase", "(Ljava/lang/String;Z)V");
		if (requestPurchase == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find static java method %s", "requestPurchase");
		} else {
			env->CallStaticVoidMethod(googleBilling, requestPurchase, jid, consumable);
		}
	}
	
	return 0;
}

int MYMMOAIGoogleBillingAndroid::_consumePurchase(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	JNI_GET_JSTRING (id, jid);
	
	jclass googleBilling = env->FindClass("com/meyume/moai/gp/MYMGoogleBilling");
	if (googleBilling == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find java class %s", "com/meyume/moai/gp/MYMGoogleBilling");
	} else {
		jmethodID consumePurchase = env->GetStaticMethodID (googleBilling, "consumePurchase", "(Ljava/lang/String;)V");
		if (consumePurchase == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find static java method %s", "consumePurchase");
		} else {
			env->CallStaticVoidMethod(googleBilling, consumePurchase, jid);
		}
	}
	
	return 0;
}

int MYMMOAIGoogleBillingAndroid::_checkPurchased(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	JNI_GET_JSTRING (id, jid);
	
	jclass googleBilling = env->FindClass("com/meyume/moai/gp/MYMGoogleBilling");
	if (googleBilling == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find java class %s", "com/meyume/moai/gp/MYMGoogleBilling");
	} else {
		jmethodID checkPurchased = env->GetStaticMethodID (googleBilling, "checkPurchased", "(Ljava/lang/String;)Z");
		if (checkPurchased == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIGoogleBillingAndroid: Unable to find static java method %s", "checkPurchased");
		} else {
			jboolean ret = (jboolean)env->CallStaticBooleanMethod(googleBilling, checkPurchased, jid);
			lua_pushboolean(state, ret);
			return 1;
		}
	}
	
	lua_pushboolean(state, false);
	return 1;
}

int MYMMOAIGoogleBillingAndroid::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIGoogleBillingAndroid::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

MYMMOAIGoogleBillingAndroid::MYMMOAIGoogleBillingAndroid() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIGoogleBillingAndroid::~MYMMOAIGoogleBillingAndroid() {
}

void MYMMOAIGoogleBillingAndroid::RegisterLuaClass(MOAILuaState& state) {
	state.SetField(-1,"DID_INIT", (u32)DID_INIT);
	state.SetField(-1,"RETRIEVED_PRODUCTS", (u32)RETRIEVED_PRODUCTS);
	state.SetField(-1,"FAILED_TO_GET_PRODUCTS", (u32)FAILED_TO_GET_PRODUCTS);
	state.SetField(-1,"FAILED_TO_PURCHASE", (u32)FAILED_TO_PURCHASE);
	state.SetField(-1,"PURCHASED", (u32)PURCHASED);
	state.SetField(-1,"REQUEST_OWNED_PURCHASE", (u32)REQUEST_OWNED_PURCHASE);
	state.SetField(-1,"FAILED_TO_GET_PURCHASES", (u32)FAILED_TO_GET_PURCHASES);
	state.SetField(-1,"RETRIEVED_PURCHASES", (u32)RETRIEVED_PURCHASES);
	state.SetField(-1,"FAILED_TO_CONSUME_PURCHASE", (u32)FAILED_TO_CONSUME_PURCHASE);
	state.SetField(-1,"DID_CONSUME_PURCHASE", (u32)DID_CONSUME_PURCHASE);
	
	luaL_Reg regTable[] = {
		{"init", _init},
		{"setListener", _setListener},
		{"requestProducts", _requestProducts},
		{"requestPurchase", _requestPurchase},
		{"consumePurchase", _consumePurchase},
		{"checkPurchased", _checkPurchased},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

void MYMMOAIGoogleBillingAndroid::notifyDidInit() {
	MOAILuaRef& callback = this->mListeners[DID_INIT];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGoogleBillingAndroid::notifyRetrievedProducts(cc8* array[], int length) {
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

void MYMMOAIGoogleBillingAndroid::notifyFailedToGetProducts(int errorCode) {
	MOAILuaRef& callback = this->mListeners[FAILED_TO_GET_PRODUCTS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushinteger(state, errorCode);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGoogleBillingAndroid::notifyFailedToPurchase(int errorCode) {
	MOAILuaRef& callback = this->mListeners[FAILED_TO_PURCHASE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushinteger(state, errorCode);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGoogleBillingAndroid::notifyPurchased(cc8* id) {
	MOAILuaRef& callback = this->mListeners[PURCHASED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushstring(state, id);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGoogleBillingAndroid::notifyRequestOwnedPurchase(cc8* id) {
	MOAILuaRef& callback = this->mListeners[REQUEST_OWNED_PURCHASE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushstring(state, id);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGoogleBillingAndroid::notifyFailedToGetPurchases() {
	MOAILuaRef& callback = this->mListeners[FAILED_TO_GET_PURCHASES];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIGoogleBillingAndroid::notifyRetrievedPurchases(cc8* array[], int length) {
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

void MYMMOAIGoogleBillingAndroid::notifyFailedToConsumePurchase(int errorCode) {
	MOAILuaRef& callback = this->mListeners[FAILED_TO_CONSUME_PURCHASE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushinteger(state, errorCode);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIGoogleBillingAndroid::notifyDidConsumePurchase(cc8* id) {
	MOAILuaRef& callback = this->mListeners[DID_CONSUME_PURCHASE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushstring(state, id);
		state.DebugCall(1, 0);
	}
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingDidInit(JNIEnv* env, jclass obj) {
	MYMMOAIGoogleBillingAndroid::Get().notifyDidInit();
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingRetrievedProducts(JNIEnv* env, jclass obj, jobjectArray array, int length) {
	cc8* products[length];
	
	for (int i = 0; i < length; i++) {
		jstring data = (jstring)env->GetObjectArrayElement(array, i);
		products[i] = (cc8*)env->GetStringUTFChars(data, 0);
	}
	
	MYMMOAIGoogleBillingAndroid::Get().notifyRetrievedProducts(products, length);
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingFailedToRequestProducts(JNIEnv* env, jclass obj, int errorCode) {
	MYMMOAIGoogleBillingAndroid::Get().notifyFailedToGetProducts(errorCode);
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingFailedToRequestPurchase(JNIEnv* env, jclass obj, int errorCode) {
	MYMMOAIGoogleBillingAndroid::Get().notifyFailedToPurchase(errorCode);
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingPurchasedProduct(JNIEnv* env, jclass obj, jstring id) {
	MYMMOAIGoogleBillingAndroid::Get().notifyPurchased((cc8*)env->GetStringUTFChars(id, 0));
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingRequestOwnedPurchase(JNIEnv* env, jclass obj, jstring id) {
	MYMMOAIGoogleBillingAndroid::Get().notifyRequestOwnedPurchase((cc8*)env->GetStringUTFChars(id, 0));
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingFailedToGetPurchases(JNIEnv* env, jclass obj) {
	MYMMOAIGoogleBillingAndroid::Get().notifyFailedToGetPurchases();
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingRetrievedPurchases(JNIEnv* env, jclass obj, jobjectArray array, int length) {
	cc8* ids[length];
	
	for (int i = 0; i < length; i++) {
		jstring id = (jstring)env->GetObjectArrayElement(array, i);
		ids[i] = (cc8*)env->GetStringUTFChars(id, 0);
	}
	
	MYMMOAIGoogleBillingAndroid::Get().notifyRetrievedPurchases(ids, length);
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingFailedToConsumePurchase(JNIEnv* env, jclass obj, int errorCode) {
	MYMMOAIGoogleBillingAndroid::Get().notifyFailedToConsumePurchase(errorCode);
}

extern "C" void Java_com_meyume_moai_gp_MYMGoogleBilling_AKUMYMNotifyGoogleBillingDidConsumePurchase(JNIEnv* env, jclass obj, jstring id) {
	MYMMOAIGoogleBillingAndroid::Get().notifyDidConsumePurchase((cc8*)env->GetStringUTFChars(id, 0));
}
