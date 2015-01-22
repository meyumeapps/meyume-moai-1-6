
#import <moai-core/headers.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Accounts/Accounts.h>

class MYMMOAIShareIOS :
	public MOAIGlobalClass < MYMMOAIShareIOS, MOAILuaObject > {
private:
		static int _init ( lua_State* L );
		static int _share(lua_State* L);
		static int _postPhotoTwitter(lua_State* L);
		static int _setListener( lua_State* L );
	
public:

	DECL_LUA_SINGLETON ( MYMMOAIShareIOS );
		
		enum {
			SERVICE_NOT_AVAILABLE,
			DID_POST_PHOTO,
			TOTAL
		};
		
		MOAILuaStrongRef		mListeners [ TOTAL ];
		
		ACAccountStore *_accountStore;

		BOOL autoRender;
	
					MYMMOAIShareIOS				();
					~MYMMOAIShareIOS				();
		
		void RegisterLuaClass( MOAILuaState& state );
		
		void notifyServiceNotAvailable();
		void notifyDidPostPhoto(BOOL success);
};
