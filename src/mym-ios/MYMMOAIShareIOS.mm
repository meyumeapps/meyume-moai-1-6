
#include "pch.h"

#import <mym-ios/MYMMOAIShareIOS.h>
#include <sys/types.h>
#include <sys/sysctl.h>

#import <UIKit/UIKit.h>
#import <Social/Social.h>

// init the class
int MYMMOAIShareIOS::_init ( lua_State* L ) {
	MOAILuaState state ( L );
	
	MYMMOAIShareIOS::Get()._accountStore = [[[ACAccountStore alloc] init] retain];
	
	return 0;
}

int MYMMOAIShareIOS::_share(lua_State* L) {
	MOAILuaState state ( L );
	
	cc8* target = state.GetValue < cc8* >( 1, "" );
	cc8* title = state.GetValue < cc8* >( 2, "" );
	cc8* msg = state.GetValue < cc8* >( 3, "" );
	cc8* url = state.GetValue < cc8* >( 4, "" );
	cc8* imgUrl = state.GetValue < cc8* >( 5, "" );
	
	if (target == NULL) {
		target = "";
	}
	if (title == NULL) {
		title = "";
	}
	if (msg == NULL) {
		msg = "";
	}
	if (url == NULL) {
		url = "";
	}
	if (imgUrl == NULL) {
		imgUrl = "";
	}
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	
	if (strcmp(target, "twitter") == 0) {
		// share Twitter
		if ([SLComposeViewController isAvailableForServiceType:SLServiceTypeTwitter]) {
			SLComposeViewController *tweet = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
			[tweet setInitialText:[NSString stringWithUTF8String:msg]];
			[tweet addURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
			//UIImage *img = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:imgUrl] ofType:@"png"]];
			UIImage *img = [UIImage imageNamed:[NSString stringWithUTF8String:imgUrl]];
			[tweet addImage:img];
			
			[rootVC presentViewController:tweet animated:YES completion:nil];
		} else {
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Twitter service is not available on your device, please login from Settings then try again." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
			[alertView show];
		}
	} else {
		// share FB as default
		if ([SLComposeViewController isAvailableForServiceType:SLServiceTypeFacebook]) {
			SLComposeViewController *facebook = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
			[facebook setInitialText:[NSString stringWithUTF8String:msg]];
			[facebook addURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
			//UIImage *img = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:imgUrl] ofType:@"png"]];
			UIImage *img = [UIImage imageNamed:[NSString stringWithUTF8String:imgUrl]];
			[facebook addImage:img];
			
			[rootVC presentViewController:facebook animated:YES completion:nil];
		} else {
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Facebook service is not available on your device, please login from Settings then try again." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
			[alertView show];
		}
	}
	
	return 0;
}

int MYMMOAIShareIOS::_postPhotoTwitter(lua_State* L) {
	MOAILuaState state ( L );
	
	cc8* msg = state.GetValue < cc8* >( 1, "" );
	cc8* url = state.GetValue < cc8* >( 2, "" );
	cc8* imgUrl = state.GetValue < cc8* >( 3, "" );
	
	if (msg == NULL) {
		msg = "";
	}
	if (url == NULL) {
		url = "";
	}
	if (imgUrl == NULL) {
		imgUrl = "";
	}
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	
	if ([SLComposeViewController isAvailableForServiceType:SLServiceTypeTwitter]) {
		SLComposeViewController *tweet = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
		[tweet setInitialText:[NSString stringWithUTF8String:msg]];
		NSString *file = [NSString stringWithUTF8String:imgUrl];
		NSFileManager *fileManager = [NSFileManager defaultManager];
		if ([fileManager fileExistsAtPath:file]) {
			UIImage *img = [[UIImage alloc] initWithContentsOfFile:file];
			[tweet addImage:img];
		}
		
		[rootVC presentViewController:tweet animated:YES completion:nil];
	} else {
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error" message:@"Twitter service is not available on your device, please login from Settings then try again." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
		[alertView show];
	}
	
	/*
	ACAccountType *twitterType = [MYMMOAIShareIOS::Get()._accountStore accountTypeWithAccountTypeIdentifier:ACAccountTypeIdentifierTwitter];
	
	SLRequestHandler requestHandler = ^(NSData *responseData, NSHTTPURLResponse *urlResponse, NSError *error) {
		if (responseData) {
			NSInteger statusCode = urlResponse.statusCode;
			if (statusCode >= 200 & statusCode <300) {
				MYMMOAIShareIOS::Get().notifyDidPostPhoto(YES);
			} else {
				NSLog(@"error when posting photo, server response status code: %d, %@", statusCode, [NSHTTPURLResponse localizedStringForStatusCode:statusCode]);
				
				MYMMOAIShareIOS::Get().notifyDidPostPhoto(NO);
			}
		} else {
			NSLog(@"error when posting photo: %@", [error description]);
			
			MYMMOAIShareIOS::Get().notifyDidPostPhoto(NO);
		}
	};
	
	ACAccountStoreRequestAccessCompletionHandler accountStoreHandler = ^(BOOL granted, NSError *error) {
		if (error) {
			NSLog(@"error when request twitter account access: %@", [error description]);
			
			MYMMOAIShareIOS::Get().notifyDidPostPhoto(NO);
			
			return;
		}
		if (granted) {
			NSArray *accounts = [MYMMOAIShareIOS::Get()._accountStore accountsWithAccountType:twitterType];
			if ([accounts count] < 1) {
				MYMMOAIShareIOS::Get().notifyServiceNotAvailable();
				return;
			}
			NSURL *rUrl = [NSURL URLWithString:@"https://api.twitter.com/1.1/statuses/update_with_media.json"];
			NSDictionary *params = @{@"status" : [NSString stringWithUTF8String:msg]};
			SLRequest *request = [SLRequest requestForServiceType:SLServiceTypeTwitter requestMethod:SLRequestMethodPOST URL:rUrl parameters:params];
			
			NSString *file = [NSString stringWithUTF8String:imgUrl];
			NSFileManager *fileManager = [NSFileManager defaultManager];
			if ([fileManager fileExistsAtPath:file]) {
				UIImage *img = [[UIImage alloc] initWithContentsOfFile:file];
				NSData *imgData = UIImagePNGRepresentation(img);
				[request addMultipartData:imgData withName:@"media[]" type:@"image/png" filename:@"screenshot.png"];
			}
			
			[request setAccount:[accounts lastObject]];
			[request performRequestWithHandler:requestHandler];
		} else {
			NSLog(@"twitter account not granted");
			
			MYMMOAIShareIOS::Get().notifyServiceNotAvailable();
		}
	};
	
	[MYMMOAIShareIOS::Get()._accountStore requestAccessToAccountsWithType:twitterType options:NULL completion:accountStoreHandler];
	*/
	return 0;
}

// set listener for callback to LUA
int MYMMOAIShareIOS::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );
	
	if ( idx < TOTAL ) {
		
		MYMMOAIShareIOS::Get ().mListeners [ idx ].SetStrongRef ( state, 2 );
	}
	
	return 0;
}

// constructor
MYMMOAIShareIOS::MYMMOAIShareIOS () {
	RTTI_SINGLE ( MOAILuaObject )
}

MYMMOAIShareIOS::~MYMMOAIShareIOS () {

}

// register class with LUA
void MYMMOAIShareIOS::RegisterLuaClass ( MOAILuaState& state ) {
	state.SetField ( -1, "SERVICE_NOT_AVAILABLE",	( u32 )SERVICE_NOT_AVAILABLE );
	state.SetField ( -1, "DID_POST_PHOTO",	( u32 )DID_POST_PHOTO );
	
	luaL_Reg regTable [] = {
		{ "init",						_init },
		{ "share",						_share },
		{ "postPhotoTwitter",			_postPhotoTwitter },
		{ "setListener",				_setListener },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

void MYMMOAIShareIOS::notifyServiceNotAvailable() {
	MOAILuaRef& callback = this->mListeners [ SERVICE_NOT_AVAILABLE ];
	
	if ( callback ) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		state.DebugCall ( 0, 0 );
	}
}

void MYMMOAIShareIOS::notifyDidPostPhoto(BOOL success) {
	MOAILuaRef& callback = this->mListeners [ DID_POST_PHOTO ];
	
	if ( callback ) {
		MOAIScopedLuaState state = callback.GetSelf ();
		
		lua_pushboolean(state, success);
		
		state.DebugCall ( 1, 0 );
	}
}
