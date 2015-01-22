
#ifndef	MYMMOAIAPPIOS_H
#define	MYMMOAIAPPIOS_H

#ifndef DISABLE_MYM_MOAI_APP

#import <moai-core/headers.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

class MYMMOAIAppIOS :
	public MOAIGlobalClass < MYMMOAIAppIOS, MOAILuaObject > {
private:
		static int _init ( lua_State* L );
		static int _setListener(lua_State* L);
		static int _openUrl(lua_State* L);
		static int _getUserDefaultsProp(lua_State* L);
		static int _setUserDefaultsProp(lua_State* L);
		static int _getDeviceVersion(lua_State* L);
		static int _setAutoRender(lua_State* L);
	
public:

	DECL_LUA_SINGLETON ( MYMMOAIAppIOS );

	enum {
		APP_DID_BECOME_ACTIVATE,
		APP_WILL_RESIGN_ACTIVE,
		APP_WILL_ENTER_FOREGROUND,
		APP_DID_ENTER_BACKGROUND,
		APP_WILL_TERMINATE,
		APP_OPENED_FROM_URL,
		TOTAL
	};
		
		BOOL autoRender;
	
	MOAILuaStrongRef		mListeners [ TOTAL ];
	
					MYMMOAIAppIOS				();
					~MYMMOAIAppIOS				();
		void appDidBecomeActive();
		void appWillResignActive();
		void appWillEnterForeground();
		void appDidEnterBackground();
		void appWillTerminate();
		bool appOpenFromUrl(NSURL *url, NSString *sourceApp);
		void RegisterLuaClass( MOAILuaState& state );
};

#endif  //DISABLE_MYM_MOAI_APP

#endif  //MYMMOAIAPPIOS_H
