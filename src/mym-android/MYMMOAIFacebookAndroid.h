/*
 * Copyright (c) Xtremics Ltd All rights reserved.
 *
 * This software is the confidential and proprietary information of Xtremics
 * ("Confidential Information"). You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into with Xtremics.
 */
 
#include <moai-core/headers.h>

class MYMMOAIFacebookAndroid : 
	public MOAIGlobalClass < MYMMOAIFacebookAndroid, MOAILuaObject > {

private:
	static int _init(lua_State* L);
	static int _login( lua_State* L );
	static int _logout( lua_State* L );
	static int _getPermissions( lua_State* L );
	static int _requestPermissions( lua_State* L );
	static int _publish( lua_State* L );
	static int _postPhoto( lua_State* L );
	static int _openRequestDialog( lua_State* L );
	static int _sendRequest( lua_State* L );
	static int _getAppRequests( lua_State* L );
	static int _deleteRequest( lua_State* L );
	static int _getUserDetails( lua_State* L );
	static int _loadProfilePicture( lua_State* L );
	static int _getFriends( lua_State* L );
	static int _sendScore( lua_State* L );
	static int _getScores( lua_State* L );
	static int _graphRequest( lua_State* L );
	static int _setListener( lua_State* L );

public:
	DECL_LUA_SINGLETON(MYMMOAIFacebookAndroid);
	
	enum {
		DID_LOGIN,
		DID_LOGOUT,
		RETRIEVED_USER_DETAILS,
		REQUEST_DIALOG_CLOSED,
		PUBLISH_DIALOG_CLOSED,
		RETRIEVED_SCORES,
		RETRIEVED_APP_REQUESTS,
		RETRIEVED_FRIENDS,
		RETRIEVED_PERMISSIONS,
		REQUESTED_PERMISSIONS,
		RETRIEVED_PROFILE_PICTURE,
		RETRIEVED_GRAPH_REQUEST_DATA,
		DID_POST_PHOTO,
		TOTAL,
	};
	
	MOAILuaStrongRef mListeners[TOTAL];
	
	MYMMOAIFacebookAndroid();
	~MYMMOAIFacebookAndroid();
	void RegisterLuaClass(MOAILuaState& state);
	
	void notifyFBDidLogin();
	void notifyFBDidLogout();
	void notifyFBDidRetrieveUserDetails(cc8* jsonResult);
	void notifyFBDidRetrieveFriends(cc8* jsonResult);
	void notifyFBDidClosePublishDialog(bool success);
	void notifyFBDidCloseRequestDialog(bool success);
	void notifyFBDidRetrieveScores(cc8* jsonResult);
	void notifyFBDidRetrieveAppRequests(cc8* jsonResult);
	void notifyFBDidRetrievePermissions(cc8* jsonResult);
	void notifyFBDidRequestPermissions();
	void notifyFBDidLoadProfilePicture(cc8* userId, cc8* picturePath);
	void notifyFBDidReceiveGraphRequestData(cc8* jsonResult);
	void notifyFBDidPostPhoto(bool success);

};
