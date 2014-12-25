/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAITwitterAndroid : 
	public MOAIGlobalClass < MYMMOAITwitterAndroid, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _login(lua_State* L);
	static int _tweetPhoto(lua_State* L);
	static int _setListener(lua_State* L);

public:
	DECL_LUA_SINGLETON(MYMMOAITwitterAndroid);
	
	enum {
		DID_LOGIN,
		FAILED_LOGIN,
		DID_TWEET_PHOTO,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAITwitterAndroid();
	~MYMMOAITwitterAndroid();
	void RegisterLuaClass(MOAILuaState& state);
	
	void notifyDidLogin();
	void notifyFailedLogin();
	void notifyDidTweetPhoto(bool success);

};
