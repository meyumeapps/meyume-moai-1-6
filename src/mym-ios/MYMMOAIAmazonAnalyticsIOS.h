
#import <moai-core/headers.h>
#import <Foundation/Foundation.h>
#import <AmazonInsightsSDK/AmazonInsightsSDK.h>

//================================================================//
// MYMMOAIAmazonAnalyticsIOS
//================================================================//
class MYMMOAIAmazonAnalyticsIOS :
	public MOAIGlobalClass < MYMMOAIAmazonAnalyticsIOS, MOAILuaObject > {
private:
		static int _init(lua_State* L);
		static int _recordEvent(lua_State* L);
public:

	DECL_LUA_SINGLETON ( MYMMOAIAmazonAnalyticsIOS );
		
		
		AIAmazonInsights *insights;
		bool didInit = false;
	
	MYMMOAIAmazonAnalyticsIOS();
	~MYMMOAIAmazonAnalyticsIOS();
	void RegisterLuaClass( MOAILuaState& state );
};


