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
#include <mym-android/MYMMOAIAudioAndroid.h>

extern JavaVM* jvm;

int MYMMOAIAudioAndroid::_init(lua_State* L) {
	MOAILuaState state(L);
	
	int maxStreams = lua_tointeger(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID init = env->GetStaticMethodID (audioHandler, "init", "(I)V");
		if (init == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "init");
		} else {
			env->CallStaticVoidMethod(audioHandler, init, maxStreams);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_setListener(lua_State* L) {
	MOAILuaState state(L);
	
	u32 idx = state.GetValue<u32>(1, TOTAL);
	
	if (idx < TOTAL) {
		MYMMOAIAudioAndroid::Get().mListeners[idx].SetRef(state, 2);
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_enablePlaySoundInstantly(lua_State* L) {
	MOAILuaState state(L);
	
	bool enable = lua_toboolean(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID enablePlaySoundInstantly = env->GetStaticMethodID (audioHandler, "enablePlaySoundInstantly", "(Z)V");
		if (enablePlaySoundInstantly == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "enablePlaySoundInstantly");
		} else {
			env->CallStaticVoidMethod(audioHandler, enablePlaySoundInstantly, enable);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_loadSound(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	bool fromAssets = lua_toboolean(state, 2);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID loadSound = env->GetStaticMethodID (audioHandler, "loadSound", "(Ljava/lang/String;Z)I");
		if (loadSound == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "loadSound");
		} else {
			int ret = env->CallStaticIntMethod(audioHandler, loadSound, jname, fromAssets);
			lua_pushinteger(state, ret);
			
			return 1;
		}
	}
	
	lua_pushinteger(state, 0);
	return 1;
}

int MYMMOAIAudioAndroid::_unloadSound(lua_State* L) {
	MOAILuaState state(L);
	
	int soundId = lua_tointeger(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID unloadSound = env->GetStaticMethodID (audioHandler, "unloadSound", "(I)V");
		if (unloadSound == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "unloadSound");
		} else {
			env->CallStaticVoidMethod(audioHandler, unloadSound, soundId);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_playSound(lua_State* L) {
	MOAILuaState state(L);
	
	int soundId = lua_tointeger(state, 1);
	int loop = lua_tointeger(state, 2);
	float volume = lua_tonumber(state, 3);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID playSound = env->GetStaticMethodID (audioHandler, "playSound", "(IIF)I");
		if (playSound == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "playSound");
		} else {
			int ret = env->CallStaticIntMethod(audioHandler, playSound, soundId, loop, volume);
			lua_pushinteger(state, ret);
			
			return 1;
		}
	}
	
	lua_pushinteger(state, 0);
	return 1;
}

int MYMMOAIAudioAndroid::_pauseSound(lua_State* L) {
	MOAILuaState state(L);
	
	int soundId = lua_tointeger(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID pauseSound = env->GetStaticMethodID (audioHandler, "pauseSound", "(I)V");
		if (pauseSound == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "pauseSound");
		} else {
			env->CallStaticVoidMethod(audioHandler, pauseSound, soundId);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_resumeSound(lua_State* L) {
	MOAILuaState state(L);
	
	int soundId = lua_tointeger(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID resumeSound = env->GetStaticMethodID (audioHandler, "resumeSound", "(I)V");
		if (resumeSound == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "resumeSound");
		} else {
			env->CallStaticVoidMethod(audioHandler, resumeSound, soundId);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_stopSound(lua_State* L) {
	MOAILuaState state(L);
	
	int soundId = lua_tointeger(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID stopSound = env->GetStaticMethodID (audioHandler, "stopSound", "(I)V");
		if (stopSound == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "stopSound");
		} else {
			env->CallStaticVoidMethod(audioHandler, stopSound, soundId);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_pauseAllSounds(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID pauseAllSounds = env->GetStaticMethodID (audioHandler, "pauseAllSounds", "()V");
		if (pauseAllSounds == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "pauseAllSounds");
		} else {
			env->CallStaticVoidMethod(audioHandler, pauseAllSounds);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_resumeAllSounds(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID resumeAllSounds = env->GetStaticMethodID (audioHandler, "resumeAllSounds", "()V");
		if (resumeAllSounds == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "resumeAllSounds");
		} else {
			env->CallStaticVoidMethod(audioHandler, resumeAllSounds);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_setSoundVolume(lua_State* L) {
	MOAILuaState state(L);
	
	int soundId = lua_tointeger(state, 1);
	float leftVolume = lua_tonumber(state, 2);
	float rightVolume = lua_tonumber(state, 3);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID setSoundVolume = env->GetStaticMethodID (audioHandler, "setSoundVolume", "(IFF)V");
		if (setSoundVolume == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "setSoundVolume");
		} else {
			env->CallStaticVoidMethod(audioHandler, setSoundVolume, soundId, leftVolume, rightVolume);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_loadMusic(lua_State* L) {
	MOAILuaState state(L);
	
	int channel = lua_tonumber(state, 1);
	cc8* name = lua_tostring(state, 2);
	bool loop = lua_toboolean(state, 3);
	float leftVolume = lua_tonumber(state, 4);
	float rightVolume = lua_tonumber(state, 5);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID loadMusic = env->GetStaticMethodID (audioHandler, "loadMusic", "(ILjava/lang/String;ZFF)V");
		if (loadMusic == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "loadMusic");
		} else {
			env->CallStaticVoidMethod(audioHandler, loadMusic, channel, jname, loop, leftVolume, rightVolume);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_unloadMusic(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID unloadMusic = env->GetStaticMethodID (audioHandler, "unloadMusic", "(Ljava/lang/String;)V");
		if (unloadMusic == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "unloadMusic");
		} else {
			env->CallStaticVoidMethod(audioHandler, unloadMusic, jname);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_playMusic(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID playMusic = env->GetStaticMethodID (audioHandler, "playMusic", "(Ljava/lang/String;)V");
		if (playMusic == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "playMusic");
		} else {
			env->CallStaticVoidMethod(audioHandler, playMusic, jname);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_stopMusic(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID stopMusic = env->GetStaticMethodID (audioHandler, "stopMusic", "(Ljava/lang/String;)V");
		if (stopMusic == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "stopMusic");
		} else {
			env->CallStaticVoidMethod(audioHandler, stopMusic, jname);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_pauseMusic(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID pauseMusic = env->GetStaticMethodID (audioHandler, "pauseMusic", "(Ljava/lang/String;)V");
		if (pauseMusic == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "pauseMusic");
		} else {
			env->CallStaticVoidMethod(audioHandler, pauseMusic, jname);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_setMusicLoop(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	bool loop = lua_toboolean(state, 2);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID setMusicLoop = env->GetStaticMethodID (audioHandler, "setMusicLoop", "(Ljava/lang/String;Z)V");
		if (setMusicLoop == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "setMusicLoop");
		} else {
			env->CallStaticVoidMethod(audioHandler, setMusicLoop, jname, loop);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_setMusicVolume(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	float leftVolume = lua_tonumber(state, 2);
	float rightVolume = lua_tonumber(state, 3);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID setMusicVolume = env->GetStaticMethodID (audioHandler, "setMusicVolume", "(Ljava/lang/String;FF)V");
		if (setMusicVolume == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "setMusicVolume");
		} else {
			env->CallStaticVoidMethod(audioHandler, setMusicVolume, jname, leftVolume, rightVolume);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_updateMusicVolume(lua_State* L) {
	MOAILuaState state(L);
	
	int channel = lua_tonumber(state, 1);
	float leftVolume = lua_tonumber(state, 2);
	float rightVolume = lua_tonumber(state, 3);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID updateMusicVolume = env->GetStaticMethodID (audioHandler, "updateMusicVolume", "(IFF)V");
		if (updateMusicVolume == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "updateMusicVolume");
		} else {
			env->CallStaticVoidMethod(audioHandler, updateMusicVolume, channel, leftVolume, rightVolume);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_pauseAllMusics(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID pauseAllMusics = env->GetStaticMethodID (audioHandler, "pauseAllMusics", "()V");
		if (pauseAllMusics == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "pauseAllMusics");
		} else {
			env->CallStaticVoidMethod(audioHandler, pauseAllMusics);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_resumeAllMusics(lua_State* L) {
	MOAILuaState state(L);
	
	JNI_GET_ENV (jvm, env);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID resumeAllMusics = env->GetStaticMethodID (audioHandler, "resumeAllMusics", "()V");
		if (resumeAllMusics == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "resumeAllMusics");
		} else {
			env->CallStaticVoidMethod(audioHandler, resumeAllMusics);
		}
	}
	
	return 0;
}

int MYMMOAIAudioAndroid::_isMusicLooping(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID isMusicLooping = env->GetStaticMethodID (audioHandler, "isMusicLooping", "(Ljava/lang/String;)Z");
		if (isMusicLooping == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "isMusicLooping");
		} else {
			jboolean jret = (jboolean)env->CallStaticBooleanMethod(audioHandler, isMusicLooping, jname);
			
			lua_pushboolean(state, jret);
			return 1;
		}
	}
	
	lua_pushboolean(state, false);
	return 1;
}

int MYMMOAIAudioAndroid::_isMusicPlaying(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID isMusicPlaying = env->GetStaticMethodID (audioHandler, "isMusicPlaying", "(Ljava/lang/String;)Z");
		if (isMusicPlaying == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "isMusicPlaying");
		} else {
			jboolean jret = (jboolean)env->CallStaticBooleanMethod(audioHandler, isMusicPlaying, jname);
			
			lua_pushboolean(state, jret);
			return 1;
		}
	}
	
	lua_pushboolean(state, false);
	return 1;
}

int MYMMOAIAudioAndroid::_isMusicPlayerExist(lua_State* L) {
	MOAILuaState state(L);
	
	cc8* name = lua_tostring(state, 1);
	
	JNI_GET_ENV (jvm, env);
	
	JNI_GET_JSTRING (name, jname);
	
	jclass audioHandler = env->FindClass("com/meyume/moai/MYMAudioHandler");
	if (audioHandler == NULL) {
		ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find java class %s", "com/meyume/moai/MYMAudioHandler");
	} else {
		jmethodID isMusicPlayerExist = env->GetStaticMethodID (audioHandler, "isMusicPlayerExist", "(Ljava/lang/String;)Z");
		if (isMusicPlayerExist == NULL) {
			ZLLog::LogF ( ZLLog::CONSOLE, "MYMMOAIAudioAndroid: Unable to find static java method %s", "isMusicPlayerExist");
		} else {
			jboolean jret = (jboolean)env->CallStaticBooleanMethod(audioHandler, isMusicPlayerExist, jname);
			
			lua_pushboolean(state, jret);
			return 1;
		}
	}
	
	lua_pushboolean(state, false);
	return 1;
}

MYMMOAIAudioAndroid::MYMMOAIAudioAndroid() {
	RTTI_SINGLE(MOAILuaObject)
}

MYMMOAIAudioAndroid::~MYMMOAIAudioAndroid() {
}

void MYMMOAIAudioAndroid::RegisterLuaClass(MOAILuaState& state) {
	state.SetField(-1,"MUSIC_PLAYER_READY", (u32)MUSIC_PLAYER_READY);
	state.SetField(-1,"MUSIC_PLAYER_COMPLETED", (u32)MUSIC_PLAYER_COMPLETED);
	
	luaL_Reg regTable[] = {
		{"init", _init},
		{"setListener", _setListener},
		{"enablePlaySoundInstantly", _enablePlaySoundInstantly},
		{"loadSound", _loadSound},
		{"unloadSound", _unloadSound},
		{"playSound", _playSound},
		{"pauseSound", _pauseSound},
		{"resumeSound", _resumeSound},
		{"stopSound", _stopSound},
		{"pauseAllSounds", _pauseAllSounds},
		{"resumeAllSounds", _resumeAllSounds},
		{"setSoundVolume", _setSoundVolume},
		{"loadMusic", _loadMusic},
		{"unloadMusic", _unloadMusic},
		{"playMusic", _playMusic},
		{"stopMusic", _stopMusic},
		{"pauseMusic", _pauseMusic},
		{"setMusicLoop", _setMusicLoop},
		{"setMusicVolume", _setMusicVolume},
		{"updateMusicVolume", _updateMusicVolume},
		{"pauseAllMusics", _pauseAllMusics},
		{"resumeAllMusics", _resumeAllMusics},
		{"isMusicLooping", _isMusicLooping},
		{"isMusicPlaying", _isMusicPlaying},
		{"isMusicPlayerExist", _isMusicPlayerExist},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

void MYMMOAIAudioAndroid::notifyMusicPlayerReady(cc8* name) {
	MOAILuaRef& callback = this->mListeners[MUSIC_PLAYER_READY];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushstring(state, name);
		state.DebugCall(1, 0);
	}
}

void MYMMOAIAudioAndroid::notifyMusicPlayerCompleted(cc8* name) {
	MOAILuaRef& callback = this->mListeners[MUSIC_PLAYER_COMPLETED];
		
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf();
		lua_pushstring(state, name);
		state.DebugCall(1, 0);
	}
}

extern "C" void Java_com_meyume_moai_MYMAudioHandler_AKUNotifyMYMMusicPlayerReady(JNIEnv* env, jclass obj, jstring jname) {
	cc8* name = env->GetStringUTFChars(jname, 0);
	
	MYMMOAIAudioAndroid::Get().notifyMusicPlayerReady(name);
}

extern "C" void Java_com_meyume_moai_MYMAudioHandler_AKUNotifyMYMMusicPlayerCompleted(JNIEnv* env, jclass obj, jstring jname) {
	cc8* name = env->GetStringUTFChars(jname, 0);
	
	MYMMOAIAudioAndroid::Get().notifyMusicPlayerCompleted(name);
}
