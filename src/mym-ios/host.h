//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#include <moai-core/host.h>
#import <Foundation/Foundation.h>

AKU_API void	AKUMYMiOSFinalize				();
AKU_API void	AKUMYMiOSInitialize				();
AKU_API void	AKUMYMiOSContextInitialize		();

AKU_API void	AKUMYMiOSAppDidBecomeActive			();
AKU_API void	AKUMYMiOSAppWillResignActive		();
AKU_API void	AKUMYMiOSAppWillEnterForeground		();
AKU_API void	AKUMYMiOSAppDidEnterBackground		();
AKU_API void	AKUMYMiOSAppWillTerminate			();
AKU_API void	AKUMYMiOSAppOpenedFromUrl			(NSURL *url, NSString *sourceApp);

