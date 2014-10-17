// lua_tinker_demo.cpp : Defines the entry point for the console application.
//

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

extern "C" 
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
};

//#include "lua_tinker.h"

#include "LuaTable.h"


/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 1	-------------------------------*/
/*
int cpp_func(int arg1, int arg2)
{
	return arg1 + arg2;
}

int _tmain(int argc, _TCHAR* argv[])
{

		// Lua 甫 檬扁拳 茄促.
	lua_State* L = lua_open();

	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
	luaopen_base(L);

	// LuaTinker 甫 捞侩秦辑 窃荐甫 殿废茄促.
	lua_tinker::def(L, "cpp_func", cpp_func);

	// sample1.lua 颇老阑 肺靛/角青茄促.
	lua_tinker::dofile(L, "sample1.lua");

	// sample1.lua 狼 窃荐甫 龋免茄促.
	int result = lua_tinker::call<int>(L, "lua_func", 3, 4);

	// lua_func(3,4) 狼 搬苞拱 免仿
	printf("lua_func(3,4) = %d\n", result);

	// 橇肺弊伐 辆丰
	lua_close(L);
	
	return 0;
}
*/
/*---------------------------------------	sample 1	-------------------------------*/
/*-------------------------------------------------------------------------------------*/




/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 2	-------------------------------*/
/*
static int cpp_int = 100;

int _tmain(int argc, _TCHAR* argv[])
{
	// Lua 甫 檬扁拳 茄促.
	lua_State* L = lua_open();

	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
	luaopen_base(L);

	// LuaTinker 甫 捞侩秦辑 cpp_int 甫 Lua俊 傈崔
	lua_tinker::set(L, "cpp_int", cpp_int);

	// sample1.lua 颇老阑 肺靛/角青茄促.
	lua_tinker::dofile(L, "sample2.lua");

	// sample1.lua 狼 窃荐甫 龋免茄促.
	int lua_int = lua_tinker::get<int>(L, "lua_int");

	// lua_int 蔼 免仿
	printf("lua_int = %d\n", lua_int);

	// 橇肺弊伐 辆丰
	lua_close(L);

	getchar();
	return 0;
}
*/
/*---------------------------------------	sample 2	-------------------------------*/
/*-------------------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 3	-------------------------------*/
/*
struct A
{
	A(int v) : value(v) {}
	int value;
};

struct base
{
	base() {}

	const char* is_base(){ return "this is base"; }
};

class test : public base
{
public:
	test(int val) : _test(val) {}
	~test() {}

	const char* is_test(){ return "this is test"; }

	void ret_void() {}
	int ret_int()				{ return _test;			}
	int ret_mul(int m) const	{ return _test * m;		}
	A get()						{ return A(_test);		}
	void set(A a)				{ _test = a.value;		}

	int _test;
};

test g_test(11);

int _tmain(int argc, _TCHAR* argv[])
{
	// Lua 甫 檬扁拳 茄促.
	lua_State* L = lua_open();

	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
	luaopen_base(L);
	// Lua 巩磊凯 窃荐甸阑 肺靛茄促.- string 荤侩
	luaopen_string(L);

	// base 努贰胶甫 Lua 俊 眠啊茄促.
	lua_tinker::class_add<base>(L, "base");
	// base 狼 窃荐甫 殿废茄促.
	lua_tinker::class_def<base>(L, "is_base", &base::is_base);

	// test 努贰胶甫 Lua 俊 眠啊茄促.
	lua_tinker::class_add<test>(L, "test");
	// test 啊 base 俊 惑加 罐疽澜阑 舅妨霖促.
	lua_tinker::class_inh<test, base>(L);
	// test 努贰胶 积己磊甫 殿废茄促.
	lua_tinker::class_con<test>(L, lua_tinker::constructor<test,int>);
	// test 狼 窃荐甸阑 殿废茄促.
	lua_tinker::class_def<test>(L, "is_test", &test::is_test);
	lua_tinker::class_def<test>(L, "ret_void", &test::ret_void);
	lua_tinker::class_def<test>(L, "ret_int", &test::ret_int);
	lua_tinker::class_def<test>(L, "ret_mul", &test::ret_mul);
	lua_tinker::class_def<test>(L, "get", &test::get);
	lua_tinker::class_def<test>(L, "set", &test::set);
	lua_tinker::class_mem<test>(L, "_test", &test::_test);
	
	// Lua 傈开 函荐龋 g_test 狼 器牢磐甫 殿废茄促.
	lua_tinker::set(L, "g_test", &g_test);

	// sample3.lua 颇老阑 肺靛/角青茄促.
	lua_tinker::dofile(L, "sample3.lua");

	// 橇肺弊伐 辆丰
	lua_close(L);

	getchar();
	return 0;
}
*/
/*---------------------------------------	sample 3	-------------------------------*/
/*-------------------------------------------------------------------------------------*/







/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 4	-------------------------------*/
/*
int _tmain(int argc, _TCHAR* argv[])
{
	// Lua 甫 檬扁拳 茄促.
	lua_State* L = lua_open();

	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
	luaopen_base(L);

	// Lua 抛捞喉阑 积己窍绊 胶琶俊 仟浆茄促.
	lua_tinker::table haha(L, "haha");

	// haha.value = 1 蔼阑 持绰促.
	haha.set("value", 1);

	// table 郴俊 table阑 父甸绢 持绰促.
	haha.set("inside", lua_tinker::table(L));

	// haha.inside 狼 器牢磐甫 胶琶困肺 汗荤茄促.
	lua_tinker::table inside = haha.get<lua_tinker::table>("inside");

	// inside.value = 2 蔼阑 持绰促.
	inside.set("value", 2);

	// sample4.lua 颇老阑 肺靛/角青茄促.
	lua_tinker::dofile(L, "sample4.lua");

	// Lua 俊辑 积己茄 haha.test 蔼阑 佬绰促.
	const char* test = haha.get<const char*>("test");
	printf("haha.test = %s\n", test);

	// 傈开俊 殿废窍瘤 臼绊 Lua 胶琶俊 后 抛捞喉阑 积己茄促.(瘤开函荐)
	lua_tinker::table temp(L);

	// 后 抛捞喉.name 俊 蔼阑 持绰促.
	temp.set("name", "local table !!");

	// table阑 狼 牢磊肺 荤侩窍咯 print_table 阑 龋免茄促.
	lua_tinker::call<void>(L, "print_table", temp);

	// 窃荐啊 府畔窍绰 table阑 罐绰促.
	lua_tinker::table ret = lua_tinker::call<lua_tinker::table>(L, "return_table", "give me a table !!");
	printf("ret.name =\t%s\n", ret.get<const char*>("name"));

	// 橇肺弊伐 辆丰
	lua_close(L);

	getchar();
	return 0;
}
*/
/*---------------------------------------	sample 4	-------------------------------*/
/*-------------------------------------------------------------------------------------*/






/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 5	-------------------------------*/
/*

void show_error(const char* error)
{
	printf("_ALERT -> %s\n", error);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Lua 甫 檬扁拳 茄促.
	lua_State* L = lua_open();

	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
	luaopen_base(L);


	// lua_State* 啊 爱绊乐绰 泅犁狼 胶琶阑 焊咯霖促.
	printf("%s\n","-------------------------- current stack");
	lua_tinker::enum_stack(L);

	// 胶琶俊 1阑 剐绢持绰促.
	lua_pushnumber(L, 1);

	// 泅犁 胶琶狼 郴侩阑 促矫 免仿茄促.
	printf("%s\n","-------------------------- stack after push '1'");
	lua_tinker::enum_stack(L);


	// sample5.lua 颇老阑 肺靛/角青茄促.
	lua_tinker::dofile(L, "sample5.lua");


	printf("*************  check stack after dofile		begin **************\n");

	lua_tinker::enum_stack(L);
	printf("*************  check stack after dofile		end	  **************\n");



	// test_error() 窃荐甫 龋免茄促.
	// test_error() 绰 角青吝 test_error_3() 龋免阑 矫档窍促 俊矾甫 惯积矫挪促.
	// 窃荐 龋免吝 惯积茄 俊矾绰 printf()甫 烹秦辑 免仿等促.
	printf("%s\n","-------------------------- calling test_error()");
	lua_tinker::call<void>(L, "test_error");

	// test_error_3()绰 粮犁窍瘤 臼绰 窃荐捞促. 龋免 磊眉啊 角菩茄促.
	printf("%s\n","-------------------------- calling test_error_3()");
	lua_tinker::call<void>(L, "test_error_3");

	// printf() 措脚 蜡历啊 力傍窍绰 俊矾 免仿 风凭阑 荤侩且 荐 乐促.
	// 捞 俊矾贸府 窃荐绰1俺狼 风酒 巩磊凯肺 惯积茄 俊矾甫 傈崔窍霸 等促.
	// C++ 俊辑 殿废且 版快 void function(const char*) 屈怕啊 利钦窍促.
	lua_tinker::def(L, "_ALERT", show_error);

	lua_tinker::call<void>(L, "_ALERT", "test !!!");

	// test_error() 窃荐甫 龋免茄促.
	// 窃荐 龋免吝 惯积茄 俊矾绰 Lua俊 殿废等 _ALERT()甫 烹秦辑 免仿等促.
	printf("%s\n","-------------------------- calling test_error()");
	lua_tinker::call<void>(L, "test_error");


	// 橇肺弊伐 辆丰
	lua_close(L);



	getchar();
	return 0;
}
*/
/*---------------------------------------	sample 5	-------------------------------*/
/*-------------------------------------------------------------------------------------*/






/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 6	-------------------------------*/
/*
int TestFunc(lua_State* L)
{
	printf("# TestFunc 角青吝\n");
	return lua_yield(L, 0);
}

int TestFunc2(lua_State* L, float a)
{
	printf("# TestFunc2(L,%f) 角青吝\n", a);
	return lua_yield(L, 0);
}

class TestClass
{
public:

	// 窃荐 屈怕啊 int(T::*)(lua_State*) 肚绰 int(T::*)(lua_State*,T1) 老 版快父 lua_yield() 甫 镜 荐 乐促.
	// 窃荐 牢磊啊 歹 鞘夸且 版快 lua_tinker.h 狼 "class member functor (non-managed)" 内膏飘 何盒阑 曼绊秦辑 流立 眠啊且 巴
	int TestFunc(lua_State* L)
	{
		printf("# TestClass::TestFunc 角青吝\n");
		return lua_yield(L, 0);
	}

	int TestFunc2(lua_State* L, float a)
	{
		printf("# TestClass::TestFunc2(L,%f) 角青吝\n", a);
		return lua_yield(L, 0);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	// Lua 甫 檬扁拳 茄促.
	lua_State* L = lua_open();

	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
	luaopen_base(L);
	// Lua 巩磊凯 窃荐甸阑 肺靛茄促.- string 荤侩
	luaopen_string(L);

	// TestFunc 窃荐甫 Lua 俊 殿废茄促.
	lua_tinker::def(L, "TestFunc", &TestFunc);
	lua_tinker::def(L, "TestFunc2", &TestFunc2);

	// TestClass 努贰胶甫 Lua 俊 眠啊茄促.
	lua_tinker::class_add<TestClass>(L, "TestClass");
	// TestClass 狼 窃荐甫 殿废茄促.
	lua_tinker::class_def<TestClass>(L, "TestFunc", &TestClass::TestFunc);
	lua_tinker::class_def<TestClass>(L, "TestFunc2", &TestClass::TestFunc2);

	// TestClass 甫 傈开 函荐肺 急攫茄促.
	TestClass g_test;
	lua_tinker::set(L, "g_test", &g_test);

	// sample3.lua 颇老阑 肺靛茄促.
	lua_tinker::dofile(L, "sample6.lua");

	// Thread 甫 矫累茄促.
	lua_newthread(L);
	lua_pushstring(L, "ThreadTest");
	lua_gettable(L, LUA_GLOBALSINDEX);

	// Thread 甫 矫累茄促.
	printf("* lua_resume() 龋免\n");
	lua_resume(L, 0);

	// Thread 甫 促矫 矫累茄促.
	printf("* lua_resume() 龋免\n");
	lua_resume(L, 0);

	// Thread 甫 促矫 矫累茄促.
	printf("* lua_resume() 龋免\n");
	lua_resume(L, 0);

	// Thread 甫 促矫 矫累茄促.
	printf("* lua_resume() 龋免\n");
	lua_resume(L, 0);

	// Thread 甫 促矫 矫累茄促.
	printf("* lua_resume() 龋免\n");
	lua_resume(L, 0);

	// 橇肺弊伐 辆丰
	lua_close(L);

	return 0;
}
*/
/*---------------------------------------	sample 6	-------------------------------*/
/*-------------------------------------------------------------------------------------*/










/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 7	-------------------------------*/


/*
double getfield(lua_State *L,char * key){  
    double res;  
    //默认栈顶是table，将key入栈  
    lua_pushstring(L,key);  
    lua_gettable(L,-2);   //查找键值为key的元素，置于栈顶  
    if(!lua_isnumber(L,-1)){  
 //       

		if ( !lua_istable(L,-1) )
			luaL_error(L,"num get error! %s\n",lua_tostring(L,-1));  
		else
		{
			double gg = getfield( L, "gg" );
			printf( "gg = %.2f\n", gg );

			return res;
		}
    }  
    res = lua_tonumber(L,-1);  
    lua_pop(L,1); //删掉产生的查找结果  
    return res;  
}  

void getcolor( lua_State *L, char *key )
{
	lua_getglobal( L, key );
	if ( !lua_istable(L,-1) )
	{
		printf( "error...\n" );
	}

	double red;
	double green;
	double blue;

	red  = getfield( L, "r" );
	green = getfield( L, "g");
	blue = getfield( L, "b" );

	getfield(L, "t");

	printf( "the color is r = %.2f, g = %.2f, b = %.2f \n ", red, green, blue );


}


int _tmain(int argc, _TCHAR* argv[])
{
//	lua_State* L = lua_open();
//
//	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
//	luaopen_base(L);
//
// //   luaL_openlibs(L);  
// //   if((luaL_loadfile(L,"sample7.lua") || lua_pcall(L,0,0,0))!= 0){  
// //       luaL_error(L,"loadfile error! \n %s",lua_tostring(L,-1));  
// //   }  
//
//
//	lua_tinker::dofile( L, "sample7.lua" );
//
//	lua_tinker::table tab( L, 1 );
//	double r = tab.get<double>(1);
//	double g = tab.get<double>(2);
//	
//
//
//
//
//
//
//
//	lua_State* L2 = lua_open();
//
//	// Lua 扁夯 窃荐甸阑 肺靛茄促.- print() 荤侩
//	luaopen_base(L2);
//	lua_tinker::dofile( L2, "sample8.lua" );
//
//
//	lua_tinker::enum_stack( L2 );
//	printf("******************* before ...  end *******************\n");
//
//	lua_tinker::table tab8( L2, "background" );
////	double r2 = tab8.get<double>("r");
////	double g2 = tab8.get<double>("g");
//
//	lua_tinker::enum_stack( L2 );
//	printf("******************* before ...  end *******************\n");
//	
//	lua_tinker::table tab12 = tab8.get<lua_tinker::table>("t");
//
//	lua_tinker::enum_stack( L2 );
//	printf("******************* before ...  end *******************\n");
//
//	lua_tinker::table tab22 = tab12.get<lua_tinker::table>(1);
//	tab12 = tab22;
//
//	lua_tinker::enum_stack( L2 );
//	printf("******************* before ...  end *******************\n");
////	lua_tinker::table *tab222 = &tab22;
////	int v12 = tab22.get<int>(1);
////	int v22 = tab22.get<int>(2);
//
////	int v122 = tab222->get< int >(1);
////	int v222 = tab222->get< int >(2);
//
//
////	lua_tinker::table tabtemp(L2);
//	lua_tinker::table tab32 = tab12.get< lua_tinker::table>(2);
//
//
//	//int rr2 = tab22.get< int >("rr");
//	//int gg2 = tab22.get< int >("gg");
//
////	getcolor( L, "background" );
//	printf("******************* after ...  start *******************\n");
//	lua_tinker::enum_stack( L2 );
//	printf("******************* after ...  end *******************\n");
//
//	lua_close(L2);



	LuaTable lt;
	lt.DoFile( "sample8.lua" );

	if ( lt.BeginTable( "background" ) == true )
	{
		int r;
		bool bFlag;
		bFlag = lt.get<int>("r",r);
		double g;
		bFlag = lt.get<double>("g",g);
		double b;
		bFlag = lt.get<double>("b",b);

		if ( lt.BeginTable("t") == true )
		{
			if ( lt.BeginTable(1) == true )
			{
				int int1,int2;
				bFlag = lt.get<int>(1, int1);
				bFlag = lt.get<int>(2, int2);

				lt.EndTable();
			}

			if ( lt.BeginTable(23) == true )
			{
				int rr, gg,test;
				bFlag = lt.get<int>("rr",rr);
				bFlag = lt.get< int >("gg",gg);
				bFlag = lt.get< int >("test",test);

				lua_tinker::enum_stack(lt.m_L);
				lt.EndTable();
			}

			if ( lt.BeginTable(2) == true )
			{
				int rr, gg,test;
				bFlag = lt.get<int>("rr",rr);
				bFlag = lt.get< int >("gg",gg);
				bFlag = lt.get< int >("test",test);

				lua_tinker::enum_stack(lt.m_L);
				lt.EndTable();
			}


			lt.EndTable();
		}


		lt.EndTable();
	}

	if ( lt.BeginTable("bg") == true )
	{
		bool bFlag;
		int i,z,y;
		char cbuff[128] = {0};
		char* pbuff = cbuff;
		bFlag = lt.get<int>("a",i);
		bFlag = lt.get< int >("b",z);
		bFlag = lt.get< char* >("c",pbuff);


		lt.EndTable();
	}

	int lua_int;
	bool bFlag = lt.get<int>("luaint",lua_int);



	getchar();

	return 0;

}

*/
/*---------------------------------------	sample 7	-------------------------------*/
/*-------------------------------------------------------------------------------------*/



int _tmain(int argc, _TCHAR* argv[])
{

}





/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 8	-------------------------------*/






/*---------------------------------------	sample 8	-------------------------------*/
/*-------------------------------------------------------------------------------------*/