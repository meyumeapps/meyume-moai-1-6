
#ifndef	MOAIFACEBOOKIOS_H
#define	MOAIFACEBOOKIOS_H

#ifndef DISABLE_FACEBOOK

#define FB_BUILD_ONLY

#import <moai-core/headers.h>
#import <FacebookSDK/FacebookSDK.h>
#import <Foundation/Foundation.h>

@class MYMMOAIFacebookListener;
@class MYMFBURLConnectionListner;

//================================================================//
// MYMMOAIFacebookIOS
//================================================================//
class MYMMOAIFacebookIOS :
	public MOAIGlobalClass < MYMMOAIFacebookIOS, MOAILuaObject > {
private:
		
		MYMMOAIFacebookListener *fbcListener;
		MYMFBURLConnectionListner *fbUrlConnectionListner;
		
		static int _init( lua_State* L );
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
		static int _selectFriends( lua_State* L );
		static int _getFriends( lua_State* L );
		static int _sendScore( lua_State* L );
		static int _getScores( lua_State* L );
		static int _graphRequest( lua_State* L );
		static int	_setListener( lua_State* L );
		static void _sessionStateChanged(FBSession *session, FBSessionState state, NSError *error);
		
		MOAIScopedLuaState pushFBUserToLuaState(MOAIScopedLuaState state, id<FBGraphUser> user);
		
		void loadAndSaveProfilePicture(NSString *userId, BOOL notifyCallback);
	
public:

	DECL_LUA_SINGLETON ( MYMMOAIFacebookIOS );
		
		enum {
			DID_LOGIN,
			DID_LOGOUT,
			RETRIEVED_USER_DETAILS,
			SELECTED_FRIENDS,
			RETRIEVED_PROFILE_PICTURE,
			PUBLISH_DIALOG_CLOSED,
			RETRIEVED_SCORES,
			RETRIEVED_APP_REQUESTS,
			RETRIEVED_FRIENDS,
			RETRIEVED_PERMISSIONS,
			REQUESTED_PERMISSIONS,
			RETRIEVED_GRAPH_REQUEST_DATA,
			DID_POST_PHOTO,
			TOTAL
		};
		
		MOAILuaStrongRef		mListeners [ TOTAL ];
	
		NSString *_appId;
		NSString *_appSecret;
		NSString *_appSchemeSuffix;
		FBSession *fbSession;
		NSArray *selectedFriends;
		NSString *searchText;
		FBFriendPickerViewController *friendPickerVC;

		MYMMOAIFacebookIOS();
		~MYMMOAIFacebookIOS();
		void notifyDidLogin();
		void notifyDidLogout();
		void notifyDidRetrieveUserDetails(id jsonResult);
		void notifyDidLoadProfilePicture(NSString *userId, NSString *picturePath);
		void nofityDidSelectFriend(NSArray *friends);
		void notifyDidReceiveFriends(id jsonResult);
		void notifyDidClosePublishDialog(BOOL success);
		void notifyDidReceiveScores(id jsonResult);
		void notifyDidReceiveAppRequests(id jsonResult);
		void notifyDidReceivePermissions(id jsonResult);
		void notifyDidRequestPermissions();
		void notifyDidReceiveGraphRequestData(id jsonResult);
		void notifyDidPostPhoto(BOOL success);
		void handleOpenUrl(NSURL *url, NSString *sourceApp);
		bool handleAppLinkToken(FBAccessTokenData *appLinkToken);
		void handleAppLinkData(FBAppLinkData *appLinkData);
		void deleteRequest(NSString *requestId);
		void RegisterLuaClass( MOAILuaState& state );
		NSString* getProfilePictureFilepath(NSString *userId);
		void downloadedProfilePicture(NSString *userId, NSData *imgData);
		MOAIScopedLuaState jsonDicToLuaState(id jsonData, MOAIScopedLuaState state);
		MOAIScopedLuaState jsonArrayToLuaState(id jsonArray, MOAIScopedLuaState state);
};


//================================================================//
// MYMMOAIFacebookListener
//================================================================//
@interface MYMMOAIFacebookListener : NSObject <FBFriendPickerDelegate, UISearchBarDelegate>

@end

@interface MYMFBURLConnection : NSURLConnection {
	NSString *userIdString;
	NSMutableData *responseData;
}
@property(nonatomic, retain) NSString *userIdString;
@property(nonatomic, retain) NSMutableData *responseData;
@end

@interface MYMFBURLConnectionListner : NSObject <NSURLConnectionDelegate, NSURLConnectionDataDelegate>

@end

#endif  //DISABLE_FACEBOOK

#endif  //MOAIFACEBOOKIOS_H
