/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIChartboostAndroid : 
	public MOAIGlobalClass < MYMMOAIChartboostAndroid, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _cacheAd(lua_State* L);
	static int _showAd(lua_State* L);
	static int _cacheMoreApps(lua_State* L);
	static int _showMoreApps(lua_State* L);
	static int _cancelAds(lua_State* L);

public:
	DECL_LUA_SINGLETON(MYMMOAIChartboostAndroid);
	
	MYMMOAIChartboostAndroid();
	~MYMMOAIChartboostAndroid();
	void RegisterLuaClass(MOAILuaState& state);

};
