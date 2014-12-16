// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-android-twitter/host.h>
#include <moai-android-twitter/MOAITwitterAndroid.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUAndroidTwitterAppFinalize () {
}

//----------------------------------------------------------------//
void AKUAndroidTwitterAppInitialize () {
}

//----------------------------------------------------------------//
void AKUAndroidTwitterContextInitialize () {

	REGISTER_LUA_CLASS ( MOAITwitterAndroid );
}


void AKUAndroidTwitterNotifyLoginComplete (int code, const char * token, const char * tokenSecret) {
	MOAITwitterAndroid::Get ().NotifyLoginComplete ( code, token, tokenSecret );
}

void AKUAndroidTwitterNotifyTweetComplete (int code) {
	MOAITwitterAndroid::Get ().NotifyTweetComplete ( code );
}
