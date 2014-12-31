/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIGooglePlayServices : 
	public MOAIGlobalClass < MYMMOAIGooglePlayServices, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _setListener(lua_State* L);
	static int _login(lua_State* L);
	static int _logout(lua_State* L);
	static int _isLoggedIn(lua_State* L);
	static int _showLeaderboard(lua_State* L);
	static int _showLeaderboards(lua_State* L);
	static int _showAchievements(lua_State* L);
	static int _submitScore(lua_State* L);
	static int _unlockAchievement(lua_State* L);
	static int _incrementAchievement(lua_State* L);
	static int _loadPlayerRank(lua_State* L);
	static int _loadAchievements(lua_State* L);
	static int _isServiceAvailable(lua_State* L);
	static int _showShareDialog(lua_State* L);
public:
	DECL_LUA_SINGLETON(MYMMOAIGooglePlayServices);
	
	enum {
		LOGGED_IN,
		LOGGED_OUT,
		LOADED_PLAYER_RANK,
		DID_SUBMIT_SCORE,
		LOADED_ACHIEVEMENTS,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAIGooglePlayServices();
	~MYMMOAIGooglePlayServices();
	void RegisterLuaClass(MOAILuaState& state);
	void notifyLoggedIn();
	void notifyLoggedOut();
	void notifyLoadedPlayerRank(long rank);
	void notifyDidSubmitScore();
	void notifyLoadedAchievements(cc8* array[], int length);

};
