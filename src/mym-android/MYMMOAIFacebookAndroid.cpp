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
#include <mym-android/MYMMOAIFacebookAndroid.h>

extern JavaVM* jvm;

int MYMMOAIFacebookAndroid::_init(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID init = env->GetStaticMethodID (facebook, "init", "()V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(facebook, init);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_login( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID login = env->GetStaticMethodID (facebook, "login", "()V");
		if (login == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "login");
		} else {
			env->CallStaticVoidMethod(facebook, login);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_logout( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID logout = env->GetStaticMethodID (facebook, "logout", "()V");
		if (logout == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "logout");
		} else {
			env->CallStaticVoidMethod(facebook, logout);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_getPermissions( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jstring ret;
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID getPermissions = env->GetStaticMethodID (facebook, "getPermissions", "()Ljava/lang/String;");
		if (getPermissions == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "getPermissions");
		} else {
			ret = (jstring)env->CallStaticObjectMethod(facebook, getPermissions);
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

int MYMMOAIFacebookAndroid::_requestPermissions( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	int length = lua_tointeger(state, 1);
	jobjectArray array = (jobjectArray)env->NewObjectArray(length, env->FindClass("java/lang/String"), env->NewStringUTF(""));
	
	for (int i = 0; i < length; i++) {
		cc8* p = lua_tostring(state, i + 2);
		env->SetObjectArrayElement(array, i, env->NewStringUTF(p));
	}
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID requestPermissions = env->GetStaticMethodID (facebook, "requestPermissions", "([Ljava/lang/String;)V");
		if (requestPermissions == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "requestPermissions");
		} else {
			env->CallStaticVoidMethod(facebook, requestPermissions, array);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_publish( lua_State* L ) {
	MOAILuaState state(L);
	JNI_GET_ENV (jvm, env);
	
	cc8* title = lua_tostring(state, 1);
	cc8* message = lua_tostring(state, 2);
	cc8* url = lua_tostring(state, 3);
	cc8* pictureUrl = lua_tostring(state, 4);
	
	JNI_GET_JSTRING (title, jtitle);
	JNI_GET_JSTRING (message, jmessage);
	JNI_GET_JSTRING (url, jurl);
	JNI_GET_JSTRING (pictureUrl, jpictureUrl);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID publish = env->GetStaticMethodID (facebook, "publish", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (publish == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "publish");
		} else {
			env->CallStaticVoidMethod(facebook, publish, jtitle, jmessage, jurl, jpictureUrl);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_postPhoto( lua_State* L ) {
	MOAILuaState state(L);
	JNI_GET_ENV (jvm, env);
	
	cc8* message = lua_tostring(state, 1);
	cc8* url = lua_tostring(state, 2);
	cc8* pictureUrl = lua_tostring(state, 3);
	
	JNI_GET_JSTRING (message, jmessage);
	JNI_GET_JSTRING (url, jurl);
	JNI_GET_JSTRING (pictureUrl, jpictureUrl);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID postPhoto = env->GetStaticMethodID (facebook, "postPhoto", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (postPhoto == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "postPhoto");
		} else {
			env->CallStaticVoidMethod(facebook, postPhoto, jmessage, jurl, jpictureUrl);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_openRequestDialog( lua_State* L ) {
	MOAILuaState state(L);
	JNI_GET_ENV (jvm, env);
	
	cc8* title = lua_tostring(state, 1);
	cc8* message = lua_tostring(state, 2);
	
	JNI_GET_JSTRING (title, jtitle);
	JNI_GET_JSTRING (message, jmessage);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID openRequestDialog = env->GetStaticMethodID (facebook, "openRequestDialog", "(Ljava/lang/String;Ljava/lang/String;)V");
		if (openRequestDialog == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "openRequestDialog");
		} else {
			env->CallStaticVoidMethod(facebook, openRequestDialog, jtitle, jmessage);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_sendRequest( lua_State* L ) {
	MOAILuaState state(L);
	JNI_GET_ENV (jvm, env);
	
	cc8* title = lua_tostring(state, 1);
	cc8* message = lua_tostring(state, 2);
	cc8* item = lua_tostring(state, 3);
	int qty = lua_tointeger(state, 4);
	
	JNI_GET_JSTRING (title, jtitle);
	JNI_GET_JSTRING (message, jmessage);
	JNI_GET_JSTRING (item, jitem);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID sendRequest = env->GetStaticMethodID (facebook, "sendRequest", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V");
		if (sendRequest == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "sendRequest");
		} else {
			env->CallStaticVoidMethod(facebook, sendRequest, jtitle, jmessage, jitem, qty);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_getAppRequests( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID getAppRequests = env->GetStaticMethodID (facebook, "getAppRequests", "()V");
		if (getAppRequests == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "getAppRequests");
		} else {
			env->CallStaticVoidMethod(facebook, getAppRequests);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_deleteRequest( lua_State* L ) {
	MOAILuaState state(L);
	
	cc8* requestId = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (requestId, jrequestId);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID deleteRequest = env->GetStaticMethodID (facebook, "deleteRequest", "(Ljava/lang/String;)V");
		if (deleteRequest == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "deleteRequest");
		} else {
			env->CallStaticVoidMethod(facebook, deleteRequest, jrequestId);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_getUserDetails( lua_State* L ) {
	MOAILuaState state(L);
	
	cc8* userId = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (userId, juserId);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID getUserDetails = env->GetStaticMethodID (facebook, "getUserDetails", "(Ljava/lang/String;)V");
		if (getUserDetails == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "getUserDetails");
		} else {
			env->CallStaticVoidMethod(facebook, getUserDetails, juserId);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_loadProfilePicture( lua_State* L ) {
	MOAILuaState state(L);
	
	cc8* userId = lua_tostring(state, 1);
	cc8* url = lua_tostring(state, 2);
	bool fromCacheOnly = lua_toboolean(state, 3);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (userId, juserId);
	JNI_GET_JSTRING (url, jurl);
	
	jstring ret;
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID loadProfilePicture = env->GetStaticMethodID (facebook, "loadProfilePicture", "(Ljava/lang/String;Ljava/lang/String;Z)Ljava/lang/String;");
		if (loadProfilePicture == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "loadProfilePicture");
		} else {
			ret = (jstring)env->CallStaticObjectMethod(facebook, loadProfilePicture, juserId, jurl, fromCacheOnly);
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

int MYMMOAIFacebookAndroid::_getFriends( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID getFriends = env->GetStaticMethodID (facebook, "getFriends", "()V");
		if (getFriends == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "getFriends");
		} else {
			env->CallStaticVoidMethod(facebook, getFriends);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_sendScore( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	long score = lua_tonumber(state, 1);
	// JNI bug that failed sending a long integer number to Java,
	// the work around is to use an array instead.
	jlongArray scoreArray = env->NewLongArray(1);
	jlong *arr = env->GetLongArrayElements(scoreArray, NULL);
	arr[0] = score;
	env->ReleaseLongArrayElements(scoreArray, arr, NULL);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID sendScore = env->GetStaticMethodID (facebook, "sendScore", "([J)V");
		if (sendScore == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "sendScore");
		} else {
			env->CallStaticVoidMethod(facebook, sendScore, scoreArray);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_getScores( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID getScores = env->GetStaticMethodID (facebook, "getScores", "()V");
		if (getScores == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "getScores");
		} else {
			env->CallStaticVoidMethod(facebook, getScores);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_graphRequest( lua_State* L ) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* path = lua_tostring(state, 1);
	cc8* method = lua_tostring(state, 2);
	int count = lua_tointeger(state, 3);
	
	int top = state.GetTop ();
	jobjectArray array = (jobjectArray)env->NewObjectArray(top, env->FindClass("java/lang/String"), env->NewStringUTF(""));
	
	for ( int i = 4; i <= top; ++i ) {
		if ( state.IsType ( i, LUA_TSTRING )) {
			
			cc8* p = state.GetValue < cc8* >( i, "" );
			env->SetObjectArrayElement(array, i - 4, env->NewStringUTF(p));
		}
	}
	
	JNI_GET_JSTRING (path, jpath);
	JNI_GET_JSTRING (method, jmethod);
	
	jclass facebook = env->FindClass("com/meyume/moai/MYMFacebook");
	if (facebook == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find java class %s", "com/meyume/moai/MYMFacebook");
	} else {
		jmethodID graphRequest = env->GetStaticMethodID (facebook, "graphRequest", "(Ljava/lang/String;Ljava/lang/String;I[Ljava/lang/String;)V");
		if (graphRequest == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIFacebookAndroid: Unable to find static java method %s", "graphRequest");
		} else {
			env->CallStaticVoidMethod(facebook, graphRequest, jpath, jmethod, count, array);
		}
	}
	
	return 0;
}

int MYMMOAIFacebookAndroid::_setListener( lua_State* L ) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIFacebookAndroid::Get().mListeners[idx].SetStrongRef(state, 2);
	}
	
	return 0;
}

MYMMOAIFacebookAndroid::MYMMOAIFacebookAndroid() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIFacebookAndroid::~MYMMOAIFacebookAndroid() {
}

void MYMMOAIFacebookAndroid::RegisterLuaClass(MOAILuaState& state) {
	state.SetField ( -1, "DID_LOGIN",		( u32 )DID_LOGIN );
	state.SetField ( -1, "DID_LOGOUT",		( u32 )DID_LOGOUT );
	state.SetField ( -1, "RETRIEVED_USER_DETAILS",	( u32 )RETRIEVED_USER_DETAILS );
	state.SetField ( -1, "REQUEST_DIALOG_CLOSED",	( u32 )REQUEST_DIALOG_CLOSED );
	state.SetField ( -1, "PUBLISH_DIALOG_CLOSED",	( u32 )PUBLISH_DIALOG_CLOSED );
	state.SetField ( -1, "RETRIEVED_SCORES",	( u32 )RETRIEVED_SCORES );
	state.SetField ( -1, "RETRIEVED_APP_REQUESTS",	( u32 )RETRIEVED_APP_REQUESTS );
	state.SetField ( -1, "RETRIEVED_FRIENDS",	( u32 )RETRIEVED_FRIENDS );
	state.SetField ( -1, "RETRIEVED_PERMISSIONS",	( u32 )RETRIEVED_PERMISSIONS );
	state.SetField ( -1, "REQUESTED_PERMISSIONS",	( u32 )REQUESTED_PERMISSIONS );
	state.SetField ( -1, "RETRIEVED_PROFILE_PICTURE",	( u32 )RETRIEVED_PROFILE_PICTURE );
	state.SetField ( -1, "RETRIEVED_GRAPH_REQUEST_DATA",	( u32 )RETRIEVED_GRAPH_REQUEST_DATA );
	state.SetField ( -1, "DID_POST_PHOTO",	( u32 )DID_POST_PHOTO );
	
	luaL_Reg regTable[] = {
		{ "init", _init},
		{ "login",					_login },
		{ "logout",					_logout },
		{ "getPermissions",			_getPermissions },
		{ "requestPermissions",		_requestPermissions },
		{ "publish",				_publish },
		{ "postPhoto",				_postPhoto },
		{ "openRequestDialog",		_openRequestDialog },
		{ "sendRequest",			_sendRequest },
		{ "getAppRequests",			_getAppRequests },
		{ "deleteRequest",			_deleteRequest },
		{ "getUserDetails",			_getUserDetails },
		{ "loadProfilePicture",		_loadProfilePicture },
		{ "getFriends",				_getFriends },
		{ "setListener",			_setListener },
		{ "sendScore",				_sendScore },
		{ "getScores",				_getScores },
		{ "graphRequest",			_graphRequest },
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}


void MYMMOAIFacebookAndroid::notifyFBDidLogin() {
	MOAILuaRef& callback = this->mListeners[DID_LOGIN];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidLogout() {
	MOAILuaRef& callback = this->mListeners[DID_LOGOUT];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		state.DebugCall(0, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidRetrieveUserDetails(cc8* jsonResult) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_USER_DETAILS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, jsonResult);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidRetrieveFriends(cc8* jsonResult) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_FRIENDS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, jsonResult);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidClosePublishDialog(bool success) {
	MOAILuaRef& callback = this->mListeners[PUBLISH_DIALOG_CLOSED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushboolean(state, success);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidCloseRequestDialog(bool success) {
	MOAILuaRef& callback = this->mListeners[REQUEST_DIALOG_CLOSED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushboolean(state, success);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidRetrieveScores(cc8* jsonResult) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_SCORES];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, jsonResult);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidRetrieveAppRequests(cc8* jsonResult) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_APP_REQUESTS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, jsonResult);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidRetrievePermissions(cc8* jsonResult) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_PERMISSIONS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, jsonResult);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidRequestPermissions() {
	MOAILuaRef& callback = this->mListeners[REQUESTED_PERMISSIONS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		state.DebugCall(0, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidLoadProfilePicture(cc8* userId, cc8* picturePath) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_PROFILE_PICTURE];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, userId);
		lua_pushstring(state, picturePath);
		state.DebugCall(2, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidReceiveGraphRequestData(cc8* jsonResult) {
	MOAILuaRef& callback = this->mListeners[RETRIEVED_GRAPH_REQUEST_DATA];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, jsonResult);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIFacebookAndroid::notifyFBDidPostPhoto(bool success) {
	MOAILuaRef& callback = this->mListeners[DID_POST_PHOTO];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushboolean(state, success);
		state.DebugCall(1, 0);
	}
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidLogin ( JNIEnv* env, jclass obj ) {
	MYMMOAIFacebookAndroid::Get().notifyFBDidLogin();
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidLogout ( JNIEnv* env, jclass obj ) {
	MYMMOAIFacebookAndroid::Get().notifyFBDidLogout();
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRetrieveUserDetails ( JNIEnv* env, jclass obj, jstring jsonResult ) {
	if (jsonResult == NULL) {
		return;
	}
	MYMMOAIFacebookAndroid::Get().notifyFBDidRetrieveUserDetails((cc8*)env->GetStringUTFChars(jsonResult, 0));
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRetrieveFriends ( JNIEnv* env, jclass obj, jstring jsonResult ) {
	if (jsonResult == NULL) {
		return;
	}
	MYMMOAIFacebookAndroid::Get().notifyFBDidRetrieveFriends((cc8*)env->GetStringUTFChars(jsonResult, 0));
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidClosePublishDialog ( JNIEnv* env, jclass obj, jboolean success ) {
	MYMMOAIFacebookAndroid::Get().notifyFBDidClosePublishDialog(success);
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidCloseRequestDialog ( JNIEnv* env, jclass obj, jboolean success ) {
	MYMMOAIFacebookAndroid::Get().notifyFBDidCloseRequestDialog(success);
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRetrieveScores ( JNIEnv* env, jclass obj, jstring jsonResult ) {
	if (jsonResult == NULL) {
		return;
	}
	const char *result = env->GetStringUTFChars(jsonResult, 0);
	cc8* scores = (cc8*)result;
	MYMMOAIFacebookAndroid::Get().notifyFBDidRetrieveScores(scores);
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRetrieveAppRequests ( JNIEnv* env, jclass obj, jstring jsonResult ) {
	if (jsonResult == NULL) {
		return;
	}
	MYMMOAIFacebookAndroid::Get().notifyFBDidRetrieveAppRequests((cc8*)env->GetStringUTFChars(jsonResult, 0));
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRetrievePermissions ( JNIEnv* env, jclass obj, jstring jsonResult ) {
	if (jsonResult == NULL) {
		return;
	}
	MYMMOAIFacebookAndroid::Get().notifyFBDidRetrievePermissions((cc8*)env->GetStringUTFChars(jsonResult, 0));
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRequestPermissions ( JNIEnv* env, jclass obj ) {
	MYMMOAIFacebookAndroid::Get().notifyFBDidRequestPermissions();
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRetrieveProfilePicture ( JNIEnv* env, jclass obj, jstring userId, jstring picturePath ) {
	if (userId == NULL) {
		return;
	}
	if (picturePath == NULL) {
		return;
	}
	MYMMOAIFacebookAndroid::Get().notifyFBDidLoadProfilePicture((cc8*)env->GetStringUTFChars(userId, 0), (cc8*)env->GetStringUTFChars(picturePath, 0));
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidRetrieveGraphRequestData ( JNIEnv* env, jclass obj, jstring jsonResult ) {
	if (jsonResult == NULL) {
		return;
	}
	MYMMOAIFacebookAndroid::Get().notifyFBDidReceiveGraphRequestData((cc8*)env->GetStringUTFChars(jsonResult, 0));
}

extern "C" void Java_com_meyume_moai_MYMFacebook_AKUMYMNotifyFBDidPostPhoto ( JNIEnv* env, jclass obj, jboolean success ) {
	MYMMOAIFacebookAndroid::Get().notifyFBDidPostPhoto(success);
}
