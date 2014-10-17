#include <iostream>

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};



#include "LuaTable.h"



LuaTable::LuaTable(lua_State *L)
{
	if ( L == NULL )
	{
		m_L = lua_open();
		luaopen_base(m_L);
		m_bAutoDestroy = true;
	}
	else
	{
		m_L	= L;
		m_bAutoDestroy = false;
	}
}

LuaTable::~LuaTable()
{
	if ( m_bAutoDestroy )
		lua_close( m_L );
}



void LuaTable::DoFile( const char *filename )
{
	lua_tinker::dofile( m_L, filename );
}


bool LuaTable::BeginTable( const int idx )
{
	if ( m_L == NULL )
		return false;
 
	if ( LUATABLE_NOW_TABLE_VALID == false )
		return false;

	lua_tinker::table tabtemp(m_L);
	bool bFlag = LUATABLE_NOW_TABLE.get<lua_tinker::table>(idx, tabtemp);
	if ( !bFlag )
		return false;

	m_vecTable.push_back( tabtemp );

	return true;
}

bool LuaTable::BeginTable( const char *name )
{

	if ( m_L == NULL )
		return false;

	if ( LUATABLE_NOW_TABLE_VALID == false )
	{
		lua_tinker::table tabTemp( m_L, name );
		m_vecTable.push_back( tabTemp );
	}
	else
	{
		lua_tinker::table tabtemp(m_L);;
		bool bFlag= LUATABLE_NOW_TABLE.get<lua_tinker::table>(name,tabtemp);
		if ( !bFlag )
			return false;

		m_vecTable.push_back( tabtemp );
	}

	return true;
}

bool LuaTable::EndTable()
{
	if ( m_L == NULL )
		return false;

	if ( LUATABLE_NOW_TABLE_VALID == false )
		return false;

	m_vecTable.pop_back();
	return true;
}