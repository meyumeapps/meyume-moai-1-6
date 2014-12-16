// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAILUASTATE_H
#define MOAILUASTATE_H

class MOAILuaRef;
class MOAILuaObject;

//================================================================//
// MOAILuaState
//================================================================//
class MOAILuaState {
private:

	lua_State*	mState;

	//----------------------------------------------------------------//
	bool			Decode					( int idx, ZLStreamAdapter& reader );
	bool			Encode					( int idx, ZLStreamAdapter& writer );
	void			ReportBadCast			( int idx, cc8* typeName );

public:

	friend class MOAIScopedLuaState;

	//----------------------------------------------------------------//
	int				AbsIndex				( int idx );
	bool			Base64Decode			( int idx );
	bool			Base64Encode			( int idx );
	bool			CheckParams				( int idx, cc8* format, bool verbose = true ); // "BCFLNSTU"
	void			ClearField				( int idx, cc8* key );
	void			CloneTable				( int idx );
	void			CopyToTop				( int idx );
	int				DebugCall				( int nArgs, int nResults );
	bool			Deflate					( int idx, int level, int windowBits );
	ZLBox			GetBox					( int idx );
	ZLColorVec		GetColor				( int idx, float r, float g, float b, float a );
	u32				GetColor32				( int idx, float r, float g, float b, float a );
	void			GetField				( int idx, cc8* name );
	void			GetField				( int idx, int key );
	STLString		GetField				( int idx, cc8* key, cc8* value );
	STLString		GetField				( int idx, int key, cc8* value );
	STLString		GetField				( int idx, cc8* key, const STLString& value );
	STLString		GetField				( int idx, int key, const STLString& value );
	bool			GetFieldWithType		( int idx, cc8* name, int type );
	bool			GetFieldWithType		( int idx, int key, int type );
	bool			GetSubfieldWithType		( int idx, cc8* format, int type, ... );
	static cc8*		GetLuaTypeName			( int type );
	void*			GetPtrUserData			( int idx );
	STLString		GetStackDump			();
	STLString		GetStackTrace			( cc8* title, int level );
	int				GetTop					();
	void*			GetUserData				( int idx, void* value );
	void*			GetUserData				( int idx, cc8* name, void* value );
	STLString		GetValue				( int idx, cc8* value );
	bool			HasField				( int idx, cc8* name );
	bool			HasField				( int idx, int key );
	bool			HasField				( int idx, cc8* name, int type );
	bool			HasField				( int idx, int name, int type );
	bool			HasKeys					( int idx );
	bool			HexDecode				( int idx );
	bool			HexEncode				( int idx );
	bool			Inflate					( int idx, int windowBits );
	bool			IsNil					();
	bool			IsNil					( int idx );
	bool			IsTableOrUserdata		( int idx );
	bool			IsType					( int idx, int type );
	bool			IsType					( int idx, cc8* name, int type );
	void			LoadLibs				();
	void			MoveToTop				( int idx );
	void			Pop						( int n );
	bool			PrepMemberFunc			( int idx, cc8* name );
	bool			PrintErrors				( FILE* file, int status );
	void			PrintStackDump			();
	void			PrintStackDump			( FILE* file );
	void			PrintStackTrace			( FILE* file, cc8* title, int level );
	void			Push					();
	void			Push					( bool value );
	void			Push					( cc8* value );
	void			Push					( double value );
	void			Push					( float value );
	void			Push					( int value );
	void			Push					( u16 value );
	void			Push					( u32 value );
	void			Push					( u64 value );
	void			Push					( lua_CFunction value );
	void			Push					( MOAILuaObject* luaObject );
	void			Push					( MOAILuaRef& ref );
	void			Push					( const void* value );
	void			Push					( void* data, size_t size );
	void			PushPtrUserData			( void* ptr );
	int				PushTableItr			( int idx );
	void			RegisterModule			( int idx, cc8* name, bool autoLoad );
	void			RegisterModule			( lua_CFunction loader, cc8* name, bool autoload );
	void			RegisterModule			( void* data, size_t size, cc8* name, bool autoload );
	int				RelIndex				( int idx );
	int				Run						( void* data, size_t size, int nArgs, int nResults );
	void			SetPath					( cc8* path );
	void			SetTop					( int top );
	bool			TableItrNext			( int itr );
					MOAILuaState			();
					MOAILuaState			( lua_State* state );
	virtual			~MOAILuaState			();
	int				YieldThread				( int nResults );
	
	//----------------------------------------------------------------//
	inline lua_State* operator -> () const {
		return mState;
	};

	//----------------------------------------------------------------//
	inline lua_State& operator * () const {
		return *mState;
	};

	//----------------------------------------------------------------//
	inline operator lua_State* () {
		return mState;
	};

	//----------------------------------------------------------------//
	inline operator bool () {
		return ( this->mState != 0 );
	}
	
	//----------------------------------------------------------------//
	template < typename TYPE > TYPE						GetField			( int idx, int key, TYPE value );
	template < typename TYPE > TYPE						GetField			( int idx, cc8* key, TYPE value );
	template < typename TYPE > TYPE*					GetLuaObject		( int idx, bool verbose );
	template < typename TYPE > TYPE*					GetLuaObject		( int idx, cc8* name, bool verbose );
	template < typename TYPE > ZLMetaRect < TYPE >		GetRect				( int idx );
	template < typename TYPE > TYPE						GetValue			( int idx, TYPE value );
	template < typename TYPE > ZLMetaVec2D < TYPE >		GetVec2D			( int idx );
	template < typename TYPE > ZLMetaVec3D < TYPE >		GetVec3D			( int idx );
	template < typename TYPE > TYPE						PopValue			( TYPE value );
	template < typename TYPE > void						Push				( ZLMetaRect < TYPE >& rect );
	template < typename TYPE > void						ReadArray			( int size, TYPE* values, TYPE value );
	template < typename TYPE > void						SetField			( int idx, cc8* key, TYPE value );
	template < typename TYPE > void						SetFieldByIndex		( int idx, int key, TYPE value );
	template < typename TYPE > void						SetGlobal			( cc8* key, TYPE value );
	template < typename TYPE > void						WriteArray			( int size, TYPE* values );
};

//----------------------------------------------------------------//
template <> bool		MOAILuaState::GetValue < bool >			( int idx, bool value );
template <> cc8*		MOAILuaState::GetValue < cc8* >			( int idx, cc8* value );
template <> double		MOAILuaState::GetValue < double >		( int idx, double value );
template <> float		MOAILuaState::GetValue < float >		( int idx, float value );
template <> s8			MOAILuaState::GetValue < s8 >			( int idx, s8 value );
template <> s16			MOAILuaState::GetValue < s16 >			( int idx, s16 value );
template <> s32			MOAILuaState::GetValue < s32 >			( int idx, s32 value );
template <> s64			MOAILuaState::GetValue < s64 >			( int idx, s64 value );
template <> u8			MOAILuaState::GetValue < u8 >			( int idx, u8 value );
template <> u16			MOAILuaState::GetValue < u16 >			( int idx, u16 value );
template <> u32			MOAILuaState::GetValue < u32 >			( int idx, u32 value );
template <> u64			MOAILuaState::GetValue < u64 >			( int idx, u64 value );
template <> void*		MOAILuaState::GetValue < void* >		( int idx, void* value );

#endif