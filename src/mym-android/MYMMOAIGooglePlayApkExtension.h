/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIGooglePlayApkExtension : 
	public MOAIGlobalClass < MYMMOAIGooglePlayApkExtension, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _setListener(lua_State* L);
	static int _checkExpansionFile(lua_State* L);
	static int _getResourcesPath(lua_State* L);
	static int _deleteExpansionResources(lua_State* L);
public:
	DECL_LUA_SINGLETON(MYMMOAIGooglePlayApkExtension);
	
	enum {
		DONE_CHECKING,
		NOTIFY_DOWNLOAD_PROGRESS,
		NOTIFY_VALIDATE_PROGRESS,
		NOTIFY_VALIDATION_FAILED,
		NOTIFY_EXTRACTION_FAILED,
		NOTIFY_EXTRACTING,
		NOTIFY_DOWNLOAD_FAILED,
		NOTIFY_NETWORK_NOT_AVAILABLE,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAIGooglePlayApkExtension();
	~MYMMOAIGooglePlayApkExtension();
	void RegisterLuaClass(MOAILuaState& state);
	void notifyDoneChecking();
	void notifyDownloadProgress(long p);
	void notifyValidateProgress(long p);
	void notifyValidationFailed();
	void notifyExtractionFailed();
	void notifyExtracting();
	void notifyDownloadFailed();
	void notifyNetworkNotAvailable();
};
