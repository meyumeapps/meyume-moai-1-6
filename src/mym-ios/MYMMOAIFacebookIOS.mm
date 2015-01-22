
#ifndef DISABLE_FACEBOOK

#include "pch.h"

#import <mym-ios/MYMMOAIFacebookIOS.h>
#import <Social/Social.h>
#include <string.h>

#define FBC_SAVE_FILEPATH @"Documents/fbc/"
#define FBC_PROFILE_PICTURE_URL @"http://graph.facebook.com/%@/picture?type=large"


struct LoadAndSaveProfilePictureArgs {
	cc8* userId;
	bool notifyCallback;
};

@implementation MYMFBURLConnection
@synthesize userIdString;
@synthesize responseData;
@end


//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	init
	@text	Initialize Facebook.
	
	@in		string	appId			Facebook app id.
 @in		string	appSecret		Facebook app secret.
	@in 	string	appSchemeSuffix	Facebook app suffix.
	@out 	nil
*/
int MYMMOAIFacebookIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );

	cc8* appId = lua_tostring ( state, 1 );
	cc8* appSecret = lua_tostring ( state, 2 );
	cc8* appSchemeSuffix = lua_tostring ( state, 3 );
	
	MYMMOAIFacebookIOS::Get()._appId = [NSString stringWithUTF8String:appId];
	MYMMOAIFacebookIOS::Get()._appSecret = [[NSString stringWithUTF8String:appSecret] retain];
	MYMMOAIFacebookIOS::Get()._appSchemeSuffix = [NSString stringWithUTF8String:appSchemeSuffix];
	
	[FBSettings setDefaultAppID:MYMMOAIFacebookIOS::Get()._appId];
	[FBSettings setDefaultUrlSchemeSuffix:MYMMOAIFacebookIOS::Get()._appSchemeSuffix];
	
	//[FBSettings enableBetaFeature:FBBetaFeaturesOpenGraphShareDialog];
	//[FBSettings enableBetaFeature:FBBetaFeaturesShareDialog];
	
	MYMMOAIFacebookIOS::Get().fbSession = [[FBSession alloc] init];
	[FBSession setActiveSession:MYMMOAIFacebookIOS::Get().fbSession];
	
	bool ret = false;
	if (MYMMOAIFacebookIOS::Get().fbSession.state == FBSessionStateCreatedTokenLoaded) {
		ret = true;
		[FBSession openActiveSessionWithReadPermissions:nil allowLoginUI:YES completionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
			MYMMOAIFacebookIOS::Get()._sessionStateChanged(session, status, error);
		}];
	}
	
	lua_pushboolean(state, ret);
	
	return 1;
}

// login
int MYMMOAIFacebookIOS::_login ( lua_State* L ) {
	if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 6.0) {
		[FBSession openActiveSessionWithReadPermissions:[NSArray arrayWithObjects:@"email", nil] allowLoginUI:YES completionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
			/*if (status == FBSessionStateOpen) {
				[FBSession.activeSession requestNewPublishPermissions:[NSArray arrayWithObjects:@"publish_actions", nil] defaultAudience:FBSessionDefaultAudienceFriends completionHandler:^(FBSession *session, NSError *error) {
					MYMMOAIFacebookIOS::Get()._sessionStateChanged(session, status, error);
				}];
			} else {
				MYMMOAIFacebookIOS::Get()._sessionStateChanged(session, status, error);
			}
			*/
			dispatch_async(dispatch_get_current_queue(), ^{
				MYMMOAIFacebookIOS::Get()._sessionStateChanged(session, status, error);
			});
		}];
	} else {
		[FBSession openActiveSessionWithPublishPermissions:[NSArray arrayWithObjects:@"publish_actions", nil] defaultAudience:FBSessionDefaultAudienceFriends allowLoginUI:YES completionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
			MYMMOAIFacebookIOS::Get()._sessionStateChanged(session, status, error);
		}];
	}
	return 0;
}

// logout
int MYMMOAIFacebookIOS::_logout ( lua_State* L ) {
	[FBSession.activeSession closeAndClearTokenInformation];
	[FBSession.activeSession close];
	[FBSession setActiveSession:nil];
	
	[MYMMOAIFacebookIOS::Get().fbSession closeAndClearTokenInformation];
	[MYMMOAIFacebookIOS::Get().fbSession close];
	
	if (MYMMOAIFacebookIOS::Get().fbSession.state == FBSessionStateClosed) {
		MYMMOAIFacebookIOS::Get().notifyDidLogout();
	}
	
	return 0;
}

// get user's granted permissions
int MYMMOAIFacebookIOS::_getPermissions( lua_State* L ) {
	[FBRequestConnection startWithGraphPath:@"me/permissions" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		MYMMOAIFacebookIOS::Get().notifyDidReceivePermissions(result);
	}];
}

// request additional permissions
int MYMMOAIFacebookIOS::_requestPermissions( lua_State* L ) {
	MOAILuaState state ( L );
	
	NSMutableArray *permissions = [NSMutableArray arrayWithCapacity:0];
	int count = lua_tointeger ( state, 1 );
	for (int i = 1; i <= count; i++) {
		cc8* p = lua_tostring(state, i + 1);
		[permissions addObject:[NSString stringWithUTF8String:p]];
	}
	
	[FBSession.activeSession requestNewPublishPermissions:permissions defaultAudience:FBSessionDefaultAudienceFriends completionHandler:^(FBSession *session, NSError *error) {
		// done
		MYMMOAIFacebookIOS::Get().notifyDidRequestPermissions();
	}];
}

// publish to user's wall
int MYMMOAIFacebookIOS::_publish ( lua_State* L ) {
	MOAILuaState state ( L );
	cc8* title = lua_tostring(state, 1);
	cc8* message = lua_tostring(state, 2);
	cc8* url = lua_tostring(state, 3);
	cc8* imgUrl = lua_tostring(state, 4);
	cc8* userId =lua_tostring(state, 5);
	
	/*
	NSURL *linkUrl = [[NSURL alloc] initWithString:[NSString stringWithUTF8String:url]];
	NSURL *imageUrl = [[NSURL alloc] initWithString:[NSString stringWithUTF8String:imgUrl]];
	FBAppCall *ret = [FBDialogs presentShareDialogWithLink:linkUrl name:[NSString stringWithUTF8String:message] caption:[NSString stringWithUTF8String:title] description:nil picture:imageUrl clientState:nil handler:^(FBAppCall *call, NSDictionary *results, NSError *error) {
	}];
	*/
	//if (ret == nil) {
	NSMutableDictionary *params = [NSMutableDictionary dictionaryWithObjectsAndKeys:
								   [NSString stringWithUTF8String:imgUrl], @"picture",
								   //[NSString stringWithUTF8String:message], @"message",
								   [NSString stringWithUTF8String:message], @"name",
								   [NSString stringWithUTF8String:url], @"link",
								   [NSString stringWithUTF8String:" "], @"caption",
								   [NSString stringWithUTF8String:title], @"description",
								   nil];
	if (userId != NULL) {
		[params setObject:[NSString stringWithUTF8String:userId] forKey:@"to"];
	}
	[FBWebDialogs presentFeedDialogModallyWithSession:nil parameters:params handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
		MYMMOAIFacebookIOS::Get().notifyDidClosePublishDialog(result == FBWebDialogResultDialogCompleted);
	}];
	//}
	
	return 0;
}

// post photo to user's wall
int MYMMOAIFacebookIOS::_postPhoto ( lua_State* L ) {
	MOAILuaState state ( L );
	cc8* message = lua_tostring(state, 1);
	cc8* url = lua_tostring(state, 2);
	cc8* imgUrl = lua_tostring(state, 3);
	cc8* userId = lua_tostring(state, 4);
	
	if (message == NULL) {
		message = "";
	}
	if (url == NULL) {
		url = "";
	}
	if (imgUrl == NULL) {
		imgUrl = "";
	}
	if (userId == NULL || userId == "") {
		userId = "me";
	}
	
	NSMutableDictionary *params = [NSMutableDictionary dictionaryWithCapacity:0];
	
	UIImage *img = [[UIImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:imgUrl]];
	if (img != nil) {
		NSData *imgData = UIImagePNGRepresentation(img);
		[params setObject:imgData forKey:@"source"];
	}
	[params setObject:[NSString stringWithUTF8String:message] forKey:@"message"];
	//[params setObject:[NSString stringWithUTF8String:url] forKey:@"link"];
	
	[FBRequestConnection startWithGraphPath:[NSString stringWithFormat:@"%s/photos", userId] parameters:params HTTPMethod:@"POST" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		if (error) {
			NSLog(@"---- failed to post photo, error: %@", error);
			MYMMOAIFacebookIOS::Get().notifyDidPostPhoto(NO);
		} else {
			MYMMOAIFacebookIOS::Get().notifyDidPostPhoto(YES);
		}
	}];
	
	return 0;
}

// open request dialog
// - this is a user generated request
int MYMMOAIFacebookIOS::_openRequestDialog( lua_State* L ) {
	MOAILuaState state ( L );
	cc8* title = lua_tostring(state, 1);
	cc8* message = lua_tostring(state, 2);
	
	[FBWebDialogs presentRequestsDialogModallyWithSession:nil message:[NSString stringWithUTF8String:message] title:[NSString stringWithUTF8String:title] parameters:nil handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
		// done
	}];
	
	return 0;
}

// send request (and additional data as a gift or something) to a specific user
// - this is an app generated request
int MYMMOAIFacebookIOS::_sendRequest ( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* userId = lua_tostring(state, 1);
	cc8* message = lua_tostring(state, 2);
	cc8* item = lua_tostring(state, 3);
	int qty = lua_tointeger(state, 4);
	
	NSMutableDictionary *params = [@{@"data" : [NSString stringWithFormat:@"%s;%d", item, qty], @"to" : [NSString stringWithUTF8String:userId]} mutableCopy];
	FBFrictionlessRecipientCache *friendCache = [[FBFrictionlessRecipientCache alloc] init];
	[friendCache prefetchAndCacheForSession:nil];
	
	[FBWebDialogs presentRequestsDialogModallyWithSession:nil message:[NSString stringWithUTF8String:message] title:nil parameters:params handler:^(FBWebDialogResult result, NSURL *resultURL, NSError *error) {
		// done
	} friendCache:friendCache];
	
	return 0;
}

// get the receiving app requests for gifts
int MYMMOAIFacebookIOS::_getAppRequests( lua_State* L ) {
	MOAILuaState state ( L );
	
	[FBRequestConnection startWithGraphPath:@"me/apprequests" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		MYMMOAIFacebookIOS::Get().notifyDidReceiveAppRequests(result);
	}];
	
	return 0;
}

// delete the request
int MYMMOAIFacebookIOS::_deleteRequest( lua_State* L ) {
	MOAILuaState state ( L );
	
	cc8* requestId = lua_tostring(state, 1);
	
	MYMMOAIFacebookIOS::Get().deleteRequest([NSString stringWithUTF8String:requestId]);
	
	return 0;
}

int MYMMOAIFacebookIOS::_getUserDetails(lua_State *L) {
	if (FBSession.activeSession.isOpen) {
		MOAILuaState state ( L );
		cc8* userId =lua_tostring(state, 1);
		NSString *userIdString = nil;
		if (userId == NULL || strcmp(userId, "") == 0) {
			userIdString = @"me";
		} else {
			userIdString = [NSString stringWithUTF8String:userId];
		}
		
		[FBRequestConnection startWithGraphPath:userIdString parameters:[NSDictionary dictionaryWithObject:@"picture,id,name,first_name,last_name,middle_name,gender,locale,link,username,age_range,installed,devices,email,birthday" forKey:@"fields"] HTTPMethod:@"GET" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
			if (!error) {
				//NSLog(@"--- user details result: %@", (NSString*)result);
				MYMMOAIFacebookIOS::Get().notifyDidRetrieveUserDetails(result);
			}
		}];
	}
	
	return 0;
}

int MYMMOAIFacebookIOS::_loadProfilePicture(lua_State *L) {
	MOAILuaState state ( L );
	cc8* userId = lua_tostring(state, 1);
	cc8* url = lua_tostring(state, 2);
	bool fromCacheOnly = lua_toboolean(state, 3);
	
	__block NSString *userIdString = [NSString stringWithUTF8String:userId];
	
	// check the picture saved on disk
	NSString *filepath = MYMMOAIFacebookIOS::Get().getProfilePictureFilepath(userIdString);
	BOOL isDir;
	if ([[NSFileManager defaultManager] fileExistsAtPath:filepath isDirectory:&isDir] && !isDir) {
		// found picture on disk
		lua_pushstring(state, [filepath UTF8String]);
	} else {
		if (!fromCacheOnly && FBSession.activeSession.isOpen) {
			__block NSData *imgData = nil;
			
			if (url != NULL && strcmp(url, "") != 0) {
				NSString *urlString = [NSString stringWithUTF8String:url];
				NSURL *url = [[NSURL alloc] initWithString:urlString];
				
				NSMutableURLRequest *req = [[NSMutableURLRequest alloc] initWithURL:url];
				[req setHTTPMethod:@"GET"];
				MYMFBURLConnection *con = [[MYMFBURLConnection alloc] initWithRequest:req delegate:MYMMOAIFacebookIOS::Get().fbUrlConnectionListner];
				con.userIdString = userIdString;
				[con start];
			} else {
				[FBRequestConnection startWithGraphPath:userIdString parameters:[NSDictionary dictionaryWithObject:@"picture" forKey:@"fields"] HTTPMethod:@"GET" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
					if (!error) {
						id picture = [(NSDictionary *)result objectForKey:@"picture"];
						id data = [(NSDictionary *)picture objectForKey:@"data"];
						NSString *urlString = [(NSDictionary *)data objectForKey:@"url"];
						NSURL *url = [[NSURL alloc] initWithString:urlString];
						
						NSMutableURLRequest *req = [[NSMutableURLRequest alloc] initWithURL:url];
						[req setHTTPMethod:@"GET"];
						MYMFBURLConnection *con = [[MYMFBURLConnection alloc] initWithRequest:req delegate:MYMMOAIFacebookIOS::Get().fbUrlConnectionListner];
						con.userIdString = userIdString;
						[con start];
					}
				}];
			}
		}
		
		lua_pushboolean(state, false);
	}
	
	return 1;
}

// open the friends selection dialog
int MYMMOAIFacebookIOS::_selectFriends(lua_State *L) {
	if (FBSession.activeSession.isOpen) {
		MOAILuaState state ( L );
		bool multiSelect = lua_toboolean(state, 1);
		
		MYMMOAIFacebookIOS::Get().friendPickerVC= [[FBFriendPickerViewController alloc] initWithNibName:nil bundle:nil];
		MYMMOAIFacebookIOS::Get().friendPickerVC.delegate = MYMMOAIFacebookIOS::Get().fbcListener;
		MYMMOAIFacebookIOS::Get().friendPickerVC.allowsMultipleSelection = multiSelect;
		
		UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
		[rootViewController presentModalViewController:MYMMOAIFacebookIOS::Get().friendPickerVC animated:YES];
		
		// search bar
		CGFloat searchBarHeight = 44.0;
		UISearchBar *searchBar = [[UISearchBar alloc] initWithFrame:CGRectMake(0, 0, rootViewController.view.bounds.size.width, searchBarHeight)];
		searchBar.autoresizingMask = searchBar.autoresizingMask | UIViewAutoresizingFlexibleWidth;
		searchBar.delegate = MYMMOAIFacebookIOS::Get().fbcListener;
		searchBar.showsCancelButton = YES;
		
		// attach search bar to FB friend picker VC
		[MYMMOAIFacebookIOS::Get().friendPickerVC.canvasView addSubview:searchBar];
		CGRect newFrame = MYMMOAIFacebookIOS::Get().friendPickerVC.view.bounds;
		newFrame.size.height -= searchBarHeight;
		newFrame.origin.y = searchBarHeight;
		MYMMOAIFacebookIOS::Get().friendPickerVC.tableView.frame = newFrame;
		
		// load FB friends
		[MYMMOAIFacebookIOS::Get().friendPickerVC loadData];
	}
	
	return 0;
}

// get the list of friends
int MYMMOAIFacebookIOS::_getFriends( lua_State* L ) {
	[FBRequestConnection startWithGraphPath:@"me/friends" parameters:[NSDictionary dictionaryWithObject:@"picture,id,name,installed" forKey:@"fields"] HTTPMethod:@"GET" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		if (!error) {
			MYMMOAIFacebookIOS::Get().notifyDidReceiveFriends(result);
		}
	}];
	
	return 0;
}

// publish score
int MYMMOAIFacebookIOS::_sendScore( lua_State* L ) {
	MOAILuaState state ( L );
	long score = lua_tonumber(state, 1);
	
	NSMutableDictionary *params = [NSMutableDictionary dictionaryWithObjectsAndKeys:[NSString stringWithFormat:@"%ld", score], @"score", nil];
	NSString *path = @"me/scores";
	[FBRequestConnection startWithGraphPath:path parameters:params HTTPMethod:@"POST" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		// do nothing
		if (error) {
			NSLog(@"---- failed to send score, error: %@", error.description);
		}
	}];
	
	return 0;
}

// retrieve scores for current player and friends
int MYMMOAIFacebookIOS::_getScores( lua_State* L ) {
	[FBRequestConnection startWithGraphPath:[NSString stringWithFormat:@"%@/scores", MYMMOAIFacebookIOS::Get()._appId] parameters:nil HTTPMethod:@"GET" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		if (error) {
			NSLog(@"---- failed to retrieve scores, error: %@", error.description);
		} else {
			//NSLog(@"---- retrieved scores: %@", result);
			MYMMOAIFacebookIOS::Get().notifyDidReceiveScores(result);
		}
	}];
	
	return 0;
}

int MYMMOAIFacebookIOS::_graphRequest( lua_State* L ) {
	MOAILuaState state ( L );
	cc8* path = lua_tostring(state, 1);
	cc8* method = lua_tostring(state, 2);
	int count = lua_tointeger(state, 3);
	
	NSMutableDictionary *params = [NSMutableDictionary dictionaryWithCapacity:count * 2];
	for (int i = 1; i <= count * 2; i += 2) {
		cc8* key = lua_tostring(state, i + 3);
		cc8* val = lua_tostring(state, i + 4);
		//NSLog(@"--- key: %s, val: %s", key, val);
		[params setObject:[NSString stringWithUTF8String:val] forKey:[NSString stringWithUTF8String:key]];
	}
	
	[FBRequestConnection startWithGraphPath:[NSString stringWithUTF8String:path] parameters:params HTTPMethod:[[NSString stringWithUTF8String:method] uppercaseString] completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		if (error) {
			NSLog(@"---- failed to send graph request, error: %@", error);
		} else {
			MYMMOAIFacebookIOS::Get().notifyDidReceiveGraphRequestData(result);
		}
	}];
	
	return 0;
}

void MYMMOAIFacebookIOS::_sessionStateChanged(FBSession *session, FBSessionState state, NSError *error) {
	switch (state) {
		case FBSessionStateOpen:
			if (!error) {
				MYMMOAIFacebookIOS::Get().fbSession = session;
				MYMMOAIFacebookIOS::Get().notifyDidLogin();
			}
			break;
		case FBSessionStateClosed:
			MYMMOAIFacebookIOS::Get().notifyDidLogout();
			
			break;
		case FBSessionStateClosedLoginFailed:
			[FBSession.activeSession closeAndClearTokenInformation];
			MYMMOAIFacebookIOS::Get().notifyDidLogout();
			
			break;
		default:
			break;
	}
}

// set listener for callback to LUA
int MYMMOAIFacebookIOS::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );
	
	if ( idx < TOTAL ) {
		
		MYMMOAIFacebookIOS::Get ().mListeners [ idx ].SetRef ( state, 2 );
	}
	
	return 0;
}

// push FBUser data into LUA table
MOAIScopedLuaState MYMMOAIFacebookIOS::pushFBUserToLuaState(MOAIScopedLuaState state, id<FBGraphUser> user) {
	lua_newtable ( state );
	
	if (user.id) {
		lua_pushstring(state, [user.id UTF8String]);
		lua_setfield(state, -2, "id");
	}
	
	if (user.name) {
		lua_pushstring(state, [user.name UTF8String]);
		lua_setfield(state, -2, "name");
	}
	
	if (user.first_name) {
		lua_pushstring(state, [user.first_name UTF8String]);
		lua_setfield(state, -2, "first_name");
	}
	
	if (user.last_name) {
		lua_pushstring(state, [user.last_name UTF8String]);
		lua_setfield(state, -2, "last_name");
	}
	
	if (user.middle_name) {
		lua_pushstring(state, [user.middle_name UTF8String]);
		lua_setfield(state, -2, "middle_name");
	}
	
	if (user.link) {
		lua_pushstring(state, [user.link UTF8String]);
		lua_setfield(state, -2, "link");
	}
	
	if (user.username) {
		lua_pushstring(state, [user.username UTF8String]);
		lua_setfield(state, -2, "username");
	}
	
	if (user.birthday) {
		lua_pushstring(state, [user.birthday UTF8String]);
		lua_setfield(state, -2, "birthday");
	}
	
	return state;
}

/*
 Parse json object data into LUA table
 */
MOAIScopedLuaState MYMMOAIFacebookIOS::jsonDicToLuaState(id jsonData, MOAIScopedLuaState state) {
	lua_newtable ( state );
	
	NSArray *keys = [(NSDictionary*)jsonData allKeys];
	for (NSString *key in keys) {
		id val = [(NSDictionary*)jsonData objectForKey:key];
		//NSLog(@"-- in jsonDicToLuaState, key: %@, val: %@", key, (NSString*)val);
		
		if ([val isKindOfClass:[NSString class]]) {
			lua_pushstring(state, [(NSString*)val UTF8String]);
		} else if ([val isKindOfClass:[NSDictionary class]]) {
			state = MYMMOAIFacebookIOS::Get().jsonDicToLuaState(val, state);
		} else if ([val isKindOfClass:[NSNumber class]]) {
			lua_pushnumber(state, [(NSNumber*)val intValue]);
		} else if ([val isKindOfClass:[NSArray class]]) {
			lua_newtable ( state );
			state = MYMMOAIFacebookIOS::Get().jsonArrayToLuaState(val, state);
		}
		lua_setfield(state, -2, [key UTF8String]);
	}
	
	return state;
}

/*
 Parse json array data into LUA table
 */
MOAIScopedLuaState MYMMOAIFacebookIOS::jsonArrayToLuaState(id jsonArray, MOAIScopedLuaState state) {
	NSArray *array = (NSArray*)jsonArray;
	for (int i = 0; i < [array count]; i++) {
		id val = [array objectAtIndex:i];
		//NSLog(@"-- in jsonArrayToLuaState, index: %d, val: %@", i, (NSString*)val);
		
		if ([val isKindOfClass:[NSDictionary class]]) {
			state = MYMMOAIFacebookIOS::Get().jsonDicToLuaState(val, state);
			lua_rawseti(state, -2, i + 1);
		}
	}
	
	return state;
}

void *loadAndSaveProfilePictureThread(void *threadargs) {
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	
	struct LoadAndSaveProfilePictureArgs *args;
	args = (struct LoadAndSaveProfilePictureArgs *)threadargs;
	
	cc8* tmp = (cc8*)args->userId;
	NSString *userId = [NSString stringWithUTF8String:tmp];
	bool notifyCallback = (bool)args->notifyCallback;
	
	// load from server
	NSURL *url = [[NSURL alloc] initWithString:[NSString stringWithFormat:FBC_PROFILE_PICTURE_URL, userId]];
	NSData *data = [NSData dataWithContentsOfURL:url];
	
	// save to disk
	NSString *filepath = MYMMOAIFacebookIOS::Get().getProfilePictureFilepath(userId);
	[data writeToFile:filepath atomically:YES];
	
	if (notifyCallback) {
		MYMMOAIFacebookIOS::Get().notifyDidLoadProfilePicture(userId, filepath);
	}
	
	[pool drain];
	pthread_exit(NULL);
}

void MYMMOAIFacebookIOS::loadAndSaveProfilePicture(NSString *userId, BOOL notifyCallback) {
	pthread_t thread;
	struct LoadAndSaveProfilePictureArgs args;
	//args.userId = [userId UTF8String];
	const char* tmp1 = [userId UTF8String];
	char tmp2[[userId length]];
	strcpy(tmp2, tmp1);
	args.userId = (cc8*)tmp2;
	
	args.notifyCallback = notifyCallback;
	pthread_create(&thread, NULL, loadAndSaveProfilePictureThread, &args);
}

//================================================================//
// MYMMOAIFacebookIOS
//================================================================//

//----------------------------------------------------------------//
MYMMOAIFacebookIOS::MYMMOAIFacebookIOS () {
	RTTI_SINGLE ( MOAILuaObject )
	
	fbcListener = [[MYMMOAIFacebookListener alloc] init];
	fbUrlConnectionListner = [[MYMFBURLConnectionListner alloc] init];
}

//----------------------------------------------------------------//
MYMMOAIFacebookIOS::~MYMMOAIFacebookIOS () {
	[fbcListener release];
	[fbUrlConnectionListner release];
}

void MYMMOAIFacebookIOS::notifyDidLogin() {
	MOAILuaRef& callback = this->mListeners [ DID_LOGIN ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidLogout() {
	MOAILuaRef& callback = this->mListeners [ DID_LOGOUT ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidRetrieveUserDetails(id jsonResult) {
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_USER_DETAILS ];
	
	if ( callback ) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state = MYMMOAIFacebookIOS::Get().jsonDicToLuaState(jsonResult, state);
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidLoadProfilePicture(NSString *userId, NSString *picturePath) {
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_PROFILE_PICTURE ];
	
	if ( callback ) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		lua_pushstring(state, [userId UTF8String]);
		lua_pushstring(state, [picturePath UTF8String]);
		
		state.DebugCall ( 2, 0 );
	}
}

void MYMMOAIFacebookIOS::nofityDidSelectFriend(NSArray *friends) {
	if (friends == nil) {
		return;
	}
	
	MOAILuaRef& callback = this->mListeners [ SELECTED_FRIENDS ];
	
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		// parent table
		lua_newtable ( state );
		
		for (int i = 0; i < [friends count]; i++) {
			id<FBGraphUser> user = (id<FBGraphUser>)[friends objectAtIndex:i];
			state = MYMMOAIFacebookIOS::Get().pushFBUserToLuaState(state, user);
			
			// end child table
			lua_rawseti(state, -2, i + 1);
		}
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidReceiveFriends(id jsonResult) {
	if (jsonResult == nil) {
		return;
	}
	
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_FRIENDS ];
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		// parent table
		lua_newtable ( state );
		
		NSArray *array = (NSArray*)[jsonResult objectForKey:@"data"];
		
		state = MYMMOAIFacebookIOS::Get().jsonArrayToLuaState(array, state);
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidClosePublishDialog(BOOL success) {
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_PROFILE_PICTURE ];
	
	if ( callback ) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		lua_pushboolean(state, success);
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidReceiveScores(id jsonResult) {
	if (jsonResult == nil) {
		return;
	}
	
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_SCORES ];
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		// parent table
		lua_newtable ( state );
		
		NSArray *array = (NSArray*)[jsonResult objectForKey:@"data"];
		
		state = MYMMOAIFacebookIOS::Get().jsonArrayToLuaState(array, state);
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidReceiveAppRequests(id jsonResult) {
	if (jsonResult == nil) {
		return;
	}
	
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_APP_REQUESTS ];
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		// parent table
		lua_newtable ( state );
		
		NSArray *array = (NSArray*)[jsonResult objectForKey:@"data"];
		
		state = MYMMOAIFacebookIOS::Get().jsonArrayToLuaState(array, state);
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidReceivePermissions(id jsonResult) {
	if (jsonResult == nil) {
		return;
	}
	
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_PERMISSIONS ];
	if (callback) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		// parent table
		lua_newtable ( state );
		
		NSArray *array = (NSArray*)[jsonResult objectForKey:@"data"];
		
		state = MYMMOAIFacebookIOS::Get().jsonArrayToLuaState(array, state);
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidRequestPermissions() {
	MOAILuaRef& callback = this->mListeners [ REQUESTED_PERMISSIONS ];
	
	if ( callback ) {
		
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidReceiveGraphRequestData(id jsonResult) {
	MOAILuaRef& callback = this->mListeners [ RETRIEVED_GRAPH_REQUEST_DATA ];
	
	if ( callback ) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state = MYMMOAIFacebookIOS::Get().jsonDicToLuaState(jsonResult, state);
		
		state.DebugCall ( 1, 0 );
	}
}

void MYMMOAIFacebookIOS::notifyDidPostPhoto(BOOL success) {
	MOAILuaRef& callback = this->mListeners [ DID_POST_PHOTO ];
	
	if ( callback ) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		lua_pushboolean(state, success);
		
		state.DebugCall ( 1, 0 );
	}
}

// Is called  when the app is open from a URL
void MYMMOAIFacebookIOS::handleOpenUrl(NSURL *url, NSString *sourceApp) {
	//[FBSession.activeSession handleOpenURL:url];
	
	// attempt to extract a token from the url
	[FBAppCall handleOpenURL:url sourceApplication:sourceApp fallbackHandler:^(FBAppCall *call) {
		// If there is an active session
		if (FBSession.activeSession.isOpen) {
			// Check the incoming link
			MYMMOAIFacebookIOS::Get().handleAppLinkData(call.appLinkData);
		} else if (call.accessTokenData) {
			// If token data is passed in and there's no active session.
			if (MYMMOAIFacebookIOS::Get().handleAppLinkToken(call.accessTokenData)) {
				// Attempt to open the session using the cached token and if successful then check the incoming link
				MYMMOAIFacebookIOS::Get().handleAppLinkData(call.appLinkData);
			}
		}
	}];
}

// handle the app link token
bool MYMMOAIFacebookIOS::handleAppLinkToken(FBAccessTokenData *appLinkToken) {
	// Initialize a new blank session instance...
	FBSession *appLinkSession = [[FBSession alloc] initWithAppID:nil permissions:nil defaultAudience:FBSessionDefaultAudienceNone urlSchemeSuffix:nil tokenCacheStrategy:[FBSessionTokenCachingStrategy nullCacheInstance]];
	[FBSession setActiveSession:appLinkSession];
	
	// ... and open it from the App Link's Token.
	return [appLinkSession openFromAccessTokenData:appLinkToken completionHandler:^(FBSession *session, FBSessionState status, NSError *error) {
		if (error) {
			NSLog(@"Error using cached token to open a session: %@", error.description);
		}
	}];
}

// handle the additional data attached in a request url
void MYMMOAIFacebookIOS::handleAppLinkData(FBAppLinkData *appLinkData) {
	NSString *targetURLString = appLinkData.originalQueryParameters[@"target_url"];
	if (targetURLString) {
		NSURL *targetURL = [NSURL URLWithString:targetURLString];
		
		// parse url params
		NSArray *pairs = [[targetURL query] componentsSeparatedByString:@"&"];
		NSMutableDictionary *targetParams = [[[NSMutableDictionary alloc] init] autorelease];
		for (NSString *pair in pairs) {
			NSArray *kv = [pair componentsSeparatedByString:@"="];
			NSString *val = [[kv objectAtIndex:1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
			
			[targetParams setObject:val forKey:[kv objectAtIndex:0]];
		}
		
		NSString *ref = [targetParams objectForKey:@"ref"];
		// Check for the ref parameter to check if this is one of
        // our incoming news feed link, otherwise it can be an
        // an attribution link
		if ([ref isEqualToString:@"notif"]) {
			// Get the request id
			NSString *requestIDParam = targetParams[@"request_ids"];
			NSArray *requestIDs = [requestIDParam componentsSeparatedByString:@","];
			
			// Get the request data from a Graph API call to the request id endpoint
			[FBRequestConnection startWithGraphPath:requestIDs[0] completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
				if (error) {
					NSLog(@"Error getting request data: %@", error.description);
				} else {
					NSString *jsonDataString = result[@"data"];
					if (jsonDataString) {
						// this is a gift sending request
					} else {
						// this is an app request
						
						// delete the request on FB
						MYMMOAIFacebookIOS::Get().deleteRequest(result[@"id"]);
					}
				}
			}];
		}
	}
}

// delete an FB request by its id
void MYMMOAIFacebookIOS::deleteRequest(NSString *requestId) {
	[FBRequestConnection startWithGraphPath:requestId parameters:nil HTTPMethod:@"DELETE" completionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
		// done
	}];
}

//----------------------------------------------------------------//
void MYMMOAIFacebookIOS::RegisterLuaClass ( MOAILuaState& state ) {
	state.SetField ( -1, "DID_LOGIN",		( u32 )DID_LOGIN );
	state.SetField ( -1, "DID_LOGOUT",		( u32 )DID_LOGOUT );
	state.SetField ( -1, "RETRIEVED_USER_DETAILS",	( u32 )RETRIEVED_USER_DETAILS );
	state.SetField ( -1, "RETRIEVED_PROFILE_PICTURE",	( u32 )RETRIEVED_PROFILE_PICTURE );
	state.SetField ( -1, "SELECTED_FRIENDS",	( u32 )SELECTED_FRIENDS );
	state.SetField ( -1, "PUBLISH_DIALOG_CLOSED",	( u32 )PUBLISH_DIALOG_CLOSED );
	state.SetField ( -1, "RETRIEVED_SCORES",	( u32 )RETRIEVED_SCORES );
	state.SetField ( -1, "RETRIEVED_APP_REQUESTS",	( u32 )RETRIEVED_APP_REQUESTS );
	state.SetField ( -1, "RETRIEVED_FRIENDS",	( u32 )RETRIEVED_FRIENDS );
	state.SetField ( -1, "RETRIEVED_PERMISSIONS",	( u32 )RETRIEVED_PERMISSIONS );
	state.SetField ( -1, "REQUESTED_PERMISSIONS",	( u32 )REQUESTED_PERMISSIONS );
	state.SetField ( -1, "RETRIEVED_GRAPH_REQUEST_DATA",	( u32 )RETRIEVED_GRAPH_REQUEST_DATA );
	state.SetField ( -1, "DID_POST_PHOTO",	( u32 )DID_POST_PHOTO );
	
	luaL_Reg regTable [] = {
		{ "init",					_init },
		{ "login",					_login },
		{ "logout",					_logout },
		{ "getPermissions",			_getPermissions },
		{ "requestPermissions",		_requestPermissions },
		{ "publish",				_publish },
		{ "postPhoto",				_postPhoto },
		{ "openRequestDialog",		_openRequestDialog },
		{ "sendRequest",			_sendRequest },
		{ "getAppRequests",			_getAppRequests },
		{ "deleteRequest",			_deleteRequest },
		{ "getUserDetails",			_getUserDetails },
		{ "loadProfilePicture",		_loadProfilePicture },
		{ "selectFriends",			_selectFriends },
		{ "getFriends",				_getFriends },
		{ "setListener",			_setListener },
		{ "sendScore",				_sendScore },
		{ "getScores",				_getScores },
		{ "graphRequest",			_graphRequest },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

// Return the filepath for a FB profile picture
NSString* MYMMOAIFacebookIOS::getProfilePictureFilepath(NSString *userId) {
	NSString  *dir = [NSHomeDirectory() stringByAppendingPathComponent:FBC_SAVE_FILEPATH];
	BOOL isDir;
	if (![[NSFileManager defaultManager] fileExistsAtPath:dir isDirectory:&isDir] or !isDir) {
		[[NSFileManager defaultManager] createDirectoryAtPath:dir withIntermediateDirectories:NO attributes:nil error:nil];
	}
	
	NSString *pngFilepath = [dir stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.png", userId]];
	
	if ([[NSFileManager defaultManager] fileExistsAtPath:pngFilepath isDirectory:&isDir] && !isDir) {
		return pngFilepath;
	}
	
	return @"";
}

void MYMMOAIFacebookIOS::downloadedProfilePicture(NSString *userIdString, NSData *imgData) {
	if (imgData != nil) {
		// save to disk
		NSString  *dir = [NSHomeDirectory() stringByAppendingPathComponent:FBC_SAVE_FILEPATH];
		
		// save as PNG
		NSString *filepath = [dir stringByAppendingFormat:@"/%@.png", userIdString];
		
		UIImage *image = [[UIImage alloc] initWithData:imgData];
		NSData *newImgData = [NSData dataWithData:UIImagePNGRepresentation(image)];
		
		[newImgData writeToFile:filepath atomically:YES];
		
		MYMMOAIFacebookIOS::Get().notifyDidLoadProfilePicture(userIdString, filepath);
	}
}


//================================================================//
// MYMMOAIFacebookListener
//================================================================//
@implementation MYMMOAIFacebookListener

- (void)friendPickerViewController:(FBFriendPickerViewController *)friendPicker handleError:(NSError *)error {
	NSLog(@"friend picker error: %@", error.description);
}

- (BOOL)friendPickerViewController:(FBFriendPickerViewController *)friendPicker shouldIncludeUser:(id <FBGraphUser>)user {
	if (MYMMOAIFacebookIOS::Get().searchText && ![MYMMOAIFacebookIOS::Get().searchText isEqualToString:@""]) {
		NSRange result = [user.name rangeOfString:MYMMOAIFacebookIOS::Get().searchText options:NSCaseInsensitiveSearch];
		return (result.location != NSNotFound);
	}
	
	return YES;
}

- (void)friendPickerViewControllerDataDidChange:(FBFriendPickerViewController *)friendPicker {
	//NSLog(@"friend picker data did change");
}

- (void)friendPickerViewControllerSelectionDidChange:(FBFriendPickerViewController *)friendPicker {
	//NSLog(@"--- friend picker selection did change: %d", [friendPicker.selection count]);
	//if (MYMMOAIFacebookIOS::Get().selectedFriends) {
	//	[MYMMOAIFacebookIOS::Get().selectedFriends release];
	//}
	MYMMOAIFacebookIOS::Get().selectedFriends = friendPicker.selection;
}

- (void)facebookViewControllerCancelWasPressed:(id)sender {
	UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
	[rootViewController dismissModalViewControllerAnimated:YES];
	
	[MYMMOAIFacebookIOS::Get().friendPickerVC release];
	MYMMOAIFacebookIOS::Get().friendPickerVC = nil;
}

- (void)facebookViewControllerDoneWasPressed:(id)sender {
	
	FBFriendPickerViewController *friendPickerVC = (FBFriendPickerViewController*)sender;
	
	//MYMMOAIFacebookIOS::Get().nofityDidSelectFriend(MYMMOAIFacebookIOS::Get().selectedFriends);
	MYMMOAIFacebookIOS::Get().nofityDidSelectFriend(friendPickerVC.selection);
	
	UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
	[rootViewController dismissModalViewControllerAnimated:YES];
	
	[MYMMOAIFacebookIOS::Get().friendPickerVC release];
	MYMMOAIFacebookIOS::Get().friendPickerVC = nil;
}

// UISearchBarDelegate

- (void)searchBarSearchButtonClicked:(UISearchBar*)searchBar {
	[searchBar resignFirstResponder];
	MYMMOAIFacebookIOS::Get().searchText = searchBar.text;
	[MYMMOAIFacebookIOS::Get().friendPickerVC updateView];
}

- (void)searchBarCancelButtonClicked:(UISearchBar *) searchBar {
	[searchBar resignFirstResponder];
	MYMMOAIFacebookIOS::Get().searchText = nil;
	[MYMMOAIFacebookIOS::Get().friendPickerVC updateView];
}

@end

@implementation MYMFBURLConnectionListner

// Callback when a connection failed to load its request successfully.
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
	NSLog(@"---- connection didFailWithError: %@", error);
}

// Callback when received response from server
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
	//NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse*)response;
	//NSLog(@"---- connection response: %d", [httpResponse statusCode]);
}

// Callback when received response data from server
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data {
	MYMFBURLConnection *con = (MYMFBURLConnection*)connection;
	if (con.responseData == nil) {
		con.responseData = [[NSMutableData alloc] initWithData:data];
	} else {
		[con.responseData appendData:data];
	}
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection {
	MYMFBURLConnection *con = (MYMFBURLConnection*)connection;
	MYMMOAIFacebookIOS::Get().downloadedProfilePicture(con.userIdString, con.responseData);
}

@end

#endif