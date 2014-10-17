#ifndef __LTM_LUATABLE__
#define __LTM_LUATABLE__


/*--------------------------------------------------------

	class	: LuaTable
	auther	: LiuTangming

	1、用来读取lua中配置的数据，包括表数据

---------------------------------------------------------*/
#include <vector>
#include <string>
#include "lua_tinker.h"

#define LUATABLE_NOW_TABLE_VALID !m_vecTable.empty()
#define LUATABLE_NOW_TABLE m_vecTable[m_vecTable.size()-1]

class LuaTable
{


public:
	LuaTable( lua_State *L = NULL );
	virtual ~LuaTable();

	// 读取lua文件数据
	void	DoFile( const char *filename );

	// 进入表数据
	bool	BeginTable( const int idx );
	bool	BeginTable( const char *name );
	bool	EndTable();

	// 读取数据
	bool	GetValue( int idx, int &v ) { return get<int>(idx,v); }
	bool	GetValue( int idx, float &v ) { return get<float>(idx,v); }
	bool	GetValue( int idx, double &v ) { return get<double>(idx,v); }
	bool	GetValue( int idx, char* v )
	{
		char* ptemp = NULL;
		if ( v == NULL || get<char*>(idx, ptemp) == false || ptemp == NULL )
			return false;
		strcpy( v, ptemp );
		return true;
	}
	bool	GetValue( int idx, std::string &v )
	{
		char* ptemp = NULL;
		if ( get<char*>(idx,ptemp) == false || ptemp == NULL )
			return false;
		v.append(ptemp);
		return true;
	}

	bool	GetValue( const char* key, int &v ) { return get<int>(key,v); }
	bool	GetValue( const char* key, float &v ) { return get<float>(key,v); }
	bool	GetValue( const char* key, double &v ) { return get<double>(key,v); }
	bool	GetValue( const char* key, char* v )
	{
		char* ptemp = NULL;
		if ( v == NULL || get<char*>(key, ptemp) == false || ptemp == NULL )
			return false;
		strcpy( v, ptemp );
		return true;
	}
	bool	GetValue( const char* key, std::string &v )
	{
		char* ptemp = NULL;
		if ( get<char*>(key,ptemp) == false || ptemp == NULL )
			return false;
		v.append(ptemp);
		return true;
	}



protected:

	// 读取数据
	template<typename T>
	bool get(const char* name, T &value)
	{
		if ( LUATABLE_NOW_TABLE_VALID )
			return LUATABLE_NOW_TABLE.get<T>(name,value);
		else
			return lua_tinker::get<T>(m_L,name,value);
		
	}

	template<typename T>
	bool get( const int idx, T& value )
	{
		if ( LUATABLE_NOW_TABLE_VALID )
			return LUATABLE_NOW_TABLE.get<T>( idx, value );

	}


public:
	lua_State			*m_L;
	bool				m_bAutoDestroy;				// 是否需要在类析构时关闭m_L
	
	std::vector< lua_tinker::table >	m_vecTable;
};







#endif