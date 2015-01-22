// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <mym-ios/host.h>
#include <mym-ios/MYMMOAIAppIOS.h>
#include <mym-ios/MYMMOAIAmazonAnalyticsIOS.h>
#include <mym-ios/MYMMOAIChartBoostIOS.h>
#include <mym-ios/MYMMOAIFacebookIOS.h>
#include <mym-ios/MYMMOAIShareIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUMYMiOSFinalize () {
}

//----------------------------------------------------------------//
void AKUMYMiOSInitialize () {
}

//----------------------------------------------------------------//
void AKUMYMiOSContextInitialize () {
	
	MYMMOAIAppIOS::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIAppIOS );
	
	MYMMOAIAmazonAnalyticsIOS::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIAmazonAnalyticsIOS );
	
	MYMMOAIChartBoostIOS::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIChartBoostIOS );
	
	MYMMOAIFacebookIOS::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIFacebookIOS );
	
	MYMMOAIShareIOS::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIShareIOS );
	
}

void AKUMYMiOSAppDidBecomeActive () {
	MYMMOAIAppIOS::Get().appDidBecomeActive();
}

void AKUMYMiOSAppWillResignActive () {
	MYMMOAIAppIOS::Get().appWillResignActive();
}

void AKUMYMiOSAppWillEnterForeground () {
	MYMMOAIAppIOS::Get().appWillEnterForeground();
}

void AKUMYMiOSAppDidEnterBackground () {
	MYMMOAIAppIOS::Get().appDidEnterBackground();
}

void AKUMYMiOSAppWillTerminate () {
	MYMMOAIAppIOS::Get().appWillTerminate();
}

void AKUMYMiOSAppOpenedFromUrl (NSURL *url, NSString *sourceApp) {
	MYMMOAIFacebookIOS::Get().handleOpenUrl(url, sourceApp);
	MYMMOAIAppIOS::Get().appOpenFromUrl(url, sourceApp);
}
