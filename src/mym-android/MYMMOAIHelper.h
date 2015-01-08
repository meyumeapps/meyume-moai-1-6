/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIHelper : 
	public MOAIGlobalClass < MYMMOAIHelper, MOAILuaObject > {

private:
	static int	_openURL			( lua_State* L );
	static int	_getSharedProp		( lua_State* L );
	static int	_setSharedProp		( lua_State* L );
	static int	_setListener 	( lua_State* L );
	static int	_setAutoRender		( lua_State* L );

public:
	DECL_LUA_SINGLETON(MYMMOAIHelper);
	
	enum {
		BACK_BUTTON_PRESSED,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAIHelper();
	~MYMMOAIHelper();
	void RegisterLuaClass(MOAILuaState& state);
	bool	notifyBackButtonPressed		();
};
