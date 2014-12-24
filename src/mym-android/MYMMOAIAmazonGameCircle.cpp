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
#include <mym-android/MYMMOAIAmazonGameCircle.h>

extern JavaVM* jvm;

int MYMMOAIAmazonGameCircle::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIAmazonGameCircle::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_showLogin(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID showLogin = env->GetStaticMethodID (amazonGameCircle, "showLogin", "()V");
		if (showLogin == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "showLogin");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, showLogin);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_showLeaderboard(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	JNI_GET_JSTRING (id, jid);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID showLeaderboard = env->GetStaticMethodID (amazonGameCircle, "showLeaderboard", "(Ljava/lang/String;)V");
		if (showLeaderboard == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "showLeaderboard");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, showLeaderboard, jid);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_showLeaderboards(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID showLeaderboards = env->GetStaticMethodID (amazonGameCircle, "showLeaderboards", "()V");
		if (showLeaderboards == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "showLeaderboards");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, showLeaderboards);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_showAchievements(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID showAchievements = env->GetStaticMethodID (amazonGameCircle, "showAchievements", "()V");
		if (showAchievements == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "showAchievements");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, showAchievements);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_submitScore(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	long score = lua_tonumber(state, 2);
	
	// JNI bug that failed sending a long integer number to Java,
	// the work around is to use an array instead.
	jlongArray scoreArray = env->NewLongArray(1);
	jlong *arr = env->GetLongArrayElements(scoreArray, NULL);
	arr[0] = score;
	env->ReleaseLongArrayElements(scoreArray, arr, NULL);
	
	JNI_GET_JSTRING (id, jid);
	
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID submitScore = env->GetStaticMethodID (amazonGameCircle, "submitScore", "(Ljava/lang/String;[J)V");
		if (submitScore == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "submitScore");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, submitScore, jid, scoreArray);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_unlockAchievement(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* id = lua_tostring(state, 1);
	JNI_GET_JSTRING (id, jid);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID unlockAchievement = env->GetStaticMethodID (amazonGameCircle, "unlockAchievement", "(Ljava/lang/String;)V");
		if (unlockAchievement == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "unlockAchievement");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, unlockAchievement, jid);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_resolveWhispersyncConflict(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	bool useLocal = lua_toboolean(state, 3);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID resolveWhispersyncConflict = env->GetStaticMethodID (amazonGameCircle, "resolveWhispersyncConflict", "(Ljava/lang/String;Ljava/lang/String;Z)V");
		if (resolveWhispersyncConflict == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "resolveWhispersyncConflict");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, resolveWhispersyncConflict, jmap, jkey, useLocal);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_synchronize(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID synchronize = env->GetStaticMethodID (amazonGameCircle, "synchronize", "()V");
		if (synchronize == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "synchronize");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, synchronize);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_saveGameString(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	cc8* val = lua_tostring(state, 3);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	JNI_GET_JSTRING (val, jval);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID saveGameString = env->GetStaticMethodID (amazonGameCircle, "saveGameString", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (saveGameString == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "saveGameString");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, saveGameString, jmap, jkey, jval);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_getGameString(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jstring ret;
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID getGameString = env->GetStaticMethodID (amazonGameCircle, "getGameString", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
		if (getGameString == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "getGameString");
		} else {
			ret = (jstring)env->CallStaticObjectMethod(amazonGameCircle, getGameString, jmap, jkey);
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

int MYMMOAIAmazonGameCircle::_saveString(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	cc8* val = lua_tostring(state, 3);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	JNI_GET_JSTRING (val, jval);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID saveString = env->GetStaticMethodID (amazonGameCircle, "saveString", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (saveString == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "saveString");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, saveString, jmap, jkey, jval);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_getString(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jstring ret;
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID getString = env->GetStaticMethodID (amazonGameCircle, "getString", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
		if (getString == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "getString");
		} else {
			ret = (jstring)env->CallStaticObjectMethod(amazonGameCircle, getString, jmap, jkey);
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

int MYMMOAIAmazonGameCircle::_saveLong(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	long val = lua_tonumber(state, 3);
	
	// JNI bug that failed sending a long integer number to Java,
	// the work around is to use an array instead.
	jlongArray valArray = env->NewLongArray(1);
	jlong *arr = env->GetLongArrayElements(valArray, NULL);
	arr[0] = val;
	env->ReleaseLongArrayElements(valArray, arr, NULL);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID saveLong = env->GetStaticMethodID (amazonGameCircle, "saveLong", "(Ljava/lang/String;Ljava/lang/String;[J)V");
		if (saveLong == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "saveLong");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, saveLong, jmap, jkey, valArray);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_getLong(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jlong ret = 0;
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID getLong = env->GetStaticMethodID (amazonGameCircle, "getLong", "(Ljava/lang/String;Ljava/lang/String;)J");
		if (getLong == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "getLong");
		} else {
			ret = (jlong)env->CallStaticLongMethod(amazonGameCircle, getLong, jmap, jkey);
		}
	}
	
	lua_pushnumber(state, ret);
	
	return 1;
}

int MYMMOAIAmazonGameCircle::_saveInt(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	int val = lua_tonumber(state, 3);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID saveInt = env->GetStaticMethodID (amazonGameCircle, "saveInt", "(Ljava/lang/String;Ljava/lang/String;I)V");
		if (saveInt == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "saveInt");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, saveInt, jmap, jkey, val);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_getInt(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jint ret = 0;
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID getInt = env->GetStaticMethodID (amazonGameCircle, "getInt", "(Ljava/lang/String;Ljava/lang/String;)I");
		if (getInt == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "getInt");
		} else {
			ret = (jint)env->CallStaticIntMethod(amazonGameCircle, getInt, jmap, jkey);
		}
	}
	
	lua_pushnumber(state, ret);
	
	return 1;
}

int MYMMOAIAmazonGameCircle::_saveDouble(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	double val = lua_tonumber(state, 3);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID saveDouble = env->GetStaticMethodID (amazonGameCircle, "saveDouble", "(Ljava/lang/String;Ljava/lang/String;D)V");
		if (saveDouble == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "saveDouble");
		} else {
			env->CallStaticVoidMethod(amazonGameCircle, saveDouble, jmap, jkey, val);
		}
	}
	
	return 0;
}

int MYMMOAIAmazonGameCircle::_getDouble(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	cc8* map = lua_tostring(state, 1);
	cc8* key = lua_tostring(state, 2);
	JNI_GET_JSTRING (map, jmap);
	JNI_GET_JSTRING (key, jkey);
	
	jdouble ret = 0;
	
	jclass amazonGameCircle = env->FindClass("com/meyume/moai/MYMAmazonGameCircle");
	if (amazonGameCircle == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMAmazonGameCircle: Unable to find java class %s", "com/meyume/moai/MYMAmazonGameCircle");
	} else {
		jmethodID getDouble = env->GetStaticMethodID (amazonGameCircle, "getDouble", "(Ljava/lang/String;Ljava/lang/String;)D");
		if (getDouble == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAmazonGameCircle: Unable to find static java method %s", "getDouble");
		} else {
			ret = (jdouble)env->CallStaticDoubleMethod(amazonGameCircle, getDouble, jmap, jkey);
		}
	}
	
	lua_pushnumber(state, ret);
	
	return 1;
}

MYMMOAIAmazonGameCircle::MYMMOAIAmazonGameCircle() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIAmazonGameCircle::~MYMMOAIAmazonGameCircle() {
}

void MYMMOAIAmazonGameCircle::RegisterLuaClass(MOAILuaState& state) {
	state.SetField(-1,"ON_WHISPERSYNC_CONFLICTS", (u32)ON_WHISPERSYNC_CONFLICTS);
	
	luaL_Reg regTable[] = {
		{"setListener", _setListener},
		{"showLogin", _showLogin},
		{"showLeaderboard", _showLeaderboard},
		{"showLeaderboards", _showLeaderboards},
		{"showAchievements", _showAchievements},
		{"submitScore", _submitScore},
		{"unlockAchievement", _unlockAchievement},
		{"resolveWhispersyncConflict", _resolveWhispersyncConflict},
		{"synchronize", _synchronize},
		{"saveGameString", _saveGameString},
		{"getGameString", _getGameString},
		{"saveString", _saveString},
		{"getString", _getString},
		{"saveLong", _saveLong},
		{"getLong", _getLong},
		{"saveInt", _saveInt},
		{"getInt", _getInt},
		{"saveDouble", _saveDouble},
		{"getDouble", _getDouble},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

void MYMMOAIAmazonGameCircle::notifyHandleWhispersyncConflicts(cc8* map, cc8* key, cc8* localValue, cc8* cloudValue) {
	MOAILuaRef& callback = this->mListeners[ON_WHISPERSYNC_CONFLICTS];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		
		lua_pushstring(state, map);
		lua_pushstring(state, key);
		lua_pushstring(state, localValue);
		lua_pushstring(state, cloudValue);
		
		state.DebugCall(4, 0);
	}
}

extern "C" void Java_com_meyume_moai_MYMAmazonGameCircle_AKUNotifyHandleWhispersyncConflicts(JNIEnv* env, jclass obj, jstring map, jstring key, jstring localValue, jstring cloudValue) {
	MYMMOAIAmazonGameCircle::Get().notifyHandleWhispersyncConflicts((cc8*)env->GetStringUTFChars(map, 0), (cc8*)env->GetStringUTFChars(key, 0), (cc8*)env->GetStringUTFChars(localValue, 0), (cc8*)env->GetStringUTFChars(cloudValue, 0));
}
