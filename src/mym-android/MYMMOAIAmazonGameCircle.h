/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIAmazonGameCircle : 
	public MOAIGlobalClass < MYMMOAIAmazonGameCircle, MOAILuaObject > {

private:
	static int _setListener(lua_State* L);
	static int _showLogin(lua_State* L);
	static int _showLeaderboard(lua_State* L);
	static int _showLeaderboards(lua_State* L);
	static int _showAchievements(lua_State* L);
	static int _submitScore(lua_State* L);
	static int _unlockAchievement(lua_State* L);
	static int _resolveWhispersyncConflict(lua_State* L);
	static int _synchronize(lua_State* L);
	static int _saveGameString(lua_State* L);
	static int _getGameString(lua_State* L);
	static int _saveString(lua_State* L);
	static int _getString(lua_State* L);
	static int _saveLong(lua_State* L);
	static int _getLong(lua_State* L);
	static int _saveInt(lua_State* L);
	static int _getInt(lua_State* L);
	static int _saveDouble(lua_State* L);
	static int _getDouble(lua_State* L);

public:
	DECL_LUA_SINGLETON(MYMMOAIAmazonGameCircle);
	
	enum {
		ON_WHISPERSYNC_CONFLICTS,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAIAmazonGameCircle();
	~MYMMOAIAmazonGameCircle();
	void RegisterLuaClass(MOAILuaState& state);
	void notifyHandleWhispersyncConflicts(cc8* map, cc8* key, cc8* localValue, cc8* cloudValue);
};
