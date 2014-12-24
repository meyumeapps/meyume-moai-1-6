/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIAmazonIAP : 
	public MOAIGlobalClass < MYMMOAIAmazonIAP, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _setListener(lua_State* L);
	static int _requestProducts(lua_State* L);
	static int _requestPurchase(lua_State* L);
	static int _getPurchases(lua_State* L);

public:
	DECL_LUA_SINGLETON(MYMMOAIAmazonIAP);
	
	enum {
		RETRIEVED_PRODUCTS,
		FAILED_TO_GET_PRODUCTS,
		FAILED_TO_PURCHASE,
		PURCHASED,
		REQUEST_OWNED_PURCHASE,
		FAILED_TO_GET_PURCHASES,
		RETRIEVED_PURCHASES,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAIAmazonIAP();
	~MYMMOAIAmazonIAP();
	void RegisterLuaClass(MOAILuaState& state);
	void notifyRetrievedProducts(cc8* array[], int length);
	void notifyFailedToGetProducts(int errorCode);
	void notifyFailedToPurchase(int errorCode);
	void notifyPurchased(cc8* id);
	void notifyRequestOwnedPurchase();
	void notifyFailedToGetPurchases();
	void notifyRetrievedPurchases(cc8* array[], int length);
};
