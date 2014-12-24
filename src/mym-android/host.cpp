// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <mym-android/host.h>
#include <mym-android/MYMMOAIChartboostAndroid.h>
#include <mym-android/MYMMOAIAudioAndroid.h>
#include <mym-android/MYMMOAIAmazonAnalytics.h>
#include <mym-android/MYMMOAIAmazonGameCircle.h>
#include <mym-android/MYMMOAIAmazonIAP.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUMYMAndroidAppFinalize () {
}

//----------------------------------------------------------------//
void AKUMYMAndroidAppInitialize () {
}

//----------------------------------------------------------------//
void AKUMYMAndroidContextInitialize () {
	
	MYMMOAIChartboostAndroid::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIChartboostAndroid );
	
	MYMMOAIAudioAndroid::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIAudioAndroid );
	
	MYMMOAIAmazonAnalytics::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIAmazonAnalytics );
	
	MYMMOAIAmazonGameCircle::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIAmazonGameCircle );
	
	MYMMOAIAmazonIAP::Affirm ();
	REGISTER_LUA_CLASS ( MYMMOAIAmazonIAP );
	
}
