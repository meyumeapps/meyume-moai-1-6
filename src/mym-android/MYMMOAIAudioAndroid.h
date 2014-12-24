/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIAudioAndroid : 
	public MOAIGlobalClass < MYMMOAIAudioAndroid, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _setListener(lua_State* L);
	static int _enablePlaySoundInstantly(lua_State* L);
	static int _loadSound(lua_State* L);
	static int _unloadSound(lua_State* L);
	static int _playSound(lua_State* L);
	static int _pauseSound(lua_State* L);
	static int _resumeSound(lua_State* L);
	static int _stopSound(lua_State* L);
	static int _pauseAllSounds(lua_State* L);
	static int _resumeAllSounds(lua_State* L);
	static int _setSoundVolume(lua_State* L);
	static int _loadMusic(lua_State* L);
	static int _unloadMusic(lua_State* L);
	static int _playMusic(lua_State* L);
	static int _stopMusic(lua_State* L);
	static int _pauseMusic(lua_State* L);
	static int _setMusicLoop(lua_State* L);
	static int _setMusicVolume(lua_State* L);
	static int _updateMusicVolume(lua_State* L);
	static int _pauseAllMusics(lua_State* L);
	static int _resumeAllMusics(lua_State* L);
	static int _isMusicLooping(lua_State* L);
	static int _isMusicPlaying(lua_State* L);
	static int _isMusicPlayerExist(lua_State* L);

public:
	DECL_LUA_SINGLETON(MYMMOAIAudioAndroid);
	
	enum {
		MUSIC_PLAYER_READY,
		MUSIC_PLAYER_COMPLETED,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAIAudioAndroid();
	~MYMMOAIAudioAndroid();
	void RegisterLuaClass(MOAILuaState& state);
	void notifyMusicPlayerReady(cc8* name);
	void notifyMusicPlayerCompleted(cc8* name);
};
