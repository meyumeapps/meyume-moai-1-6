//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef AKU_IOS_BILLING_HOST_H
#define AKU_IOS_BILLING_HOST_H

#include <moai-core/host.h>

AKU_API void	AKUAndroidTwitterAppFinalize				();
AKU_API void	AKUAndroidTwitterAppInitialize				();
AKU_API void	AKUAndroidTwitterContextInitialize			();


AKU_API void	AKUAndroidTwitterNotifyLoginComplete		(int code, const char * token, const char * tokenSecret);
AKU_API void	AKUAndroidTwitterNotifyTweetComplete		(int code);

#endif
