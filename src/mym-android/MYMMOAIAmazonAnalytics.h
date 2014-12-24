/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIAmazonAnalytics : 
	public MOAIGlobalClass < MYMMOAIAmazonAnalytics, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _recordEvent(lua_State* L);

public:
	DECL_LUA_SINGLETON(MYMMOAIAmazonAnalytics);
	
	MYMMOAIAmazonAnalytics();
	~MYMMOAIAmazonAnalytics();
	void RegisterLuaClass(MOAILuaState& state);

};
