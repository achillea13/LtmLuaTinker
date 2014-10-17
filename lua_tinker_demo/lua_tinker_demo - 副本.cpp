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

#include "lua_tinker.h"


/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 1	-------------------------------*/
/*
int cpp_func(int arg1, int arg2)
{
	return arg1 + arg2;
}

int _tmain(int argc, _TCHAR* argv[])
{

		// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = lua_open();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);

	// LuaTinker �� �̿��ؼ� �Լ��� ����Ѵ�.
	lua_tinker::def(L, "cpp_func", cpp_func);

	// sample1.lua ������ �ε�/�����Ѵ�.
	lua_tinker::dofile(L, "sample1.lua");

	// sample1.lua �� �Լ��� ȣ���Ѵ�.
	int result = lua_tinker::call<int>(L, "lua_func", 3, 4);

	// lua_func(3,4) �� ����� ���
	printf("lua_func(3,4) = %d\n", result);

	// ���α׷� ����
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
	// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = lua_open();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);

	// LuaTinker �� �̿��ؼ� cpp_int �� Lua�� ����
	lua_tinker::set(L, "cpp_int", cpp_int);

	// sample1.lua ������ �ε�/�����Ѵ�.
	lua_tinker::dofile(L, "sample2.lua");

	// sample1.lua �� �Լ��� ȣ���Ѵ�.
	int lua_int = lua_tinker::get<int>(L, "lua_int");

	// lua_int �� ���
	printf("lua_int = %d\n", lua_int);

	// ���α׷� ����
	lua_close(L);

	getchar();
	return 0;
}
*/
/*---------------------------------------	sample 2	-------------------------------*/
/*-------------------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 3	-------------------------------*/

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
	// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = lua_open();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);
	// Lua ���ڿ� �Լ����� �ε��Ѵ�.- string ���
	luaopen_string(L);

	// base Ŭ������ Lua �� �߰��Ѵ�.
	lua_tinker::class_add<base>(L, "base");
	// base �� �Լ��� ����Ѵ�.
	lua_tinker::class_def<base>(L, "is_base", &base::is_base);

	// test Ŭ������ Lua �� �߰��Ѵ�.
	lua_tinker::class_add<test>(L, "test");
	// test �� base �� ��� �޾����� �˷��ش�.
	lua_tinker::class_inh<test, base>(L);
	// test Ŭ���� �����ڸ� ����Ѵ�.
	lua_tinker::class_con<test>(L, lua_tinker::constructor<test,int>);
	// test �� �Լ����� ����Ѵ�.
	lua_tinker::class_def<test>(L, "is_test", &test::is_test);
	lua_tinker::class_def<test>(L, "ret_void", &test::ret_void);
	lua_tinker::class_def<test>(L, "ret_int", &test::ret_int);
	lua_tinker::class_def<test>(L, "ret_mul", &test::ret_mul);
	lua_tinker::class_def<test>(L, "get", &test::get);
	lua_tinker::class_def<test>(L, "set", &test::set);
	lua_tinker::class_mem<test>(L, "_test", &test::_test);
	
	// Lua ���� ����ȣ g_test �� �����͸� ����Ѵ�.
	lua_tinker::set(L, "g_test", &g_test);

	// sample3.lua ������ �ε�/�����Ѵ�.
	lua_tinker::dofile(L, "sample3.lua");

	// ���α׷� ����
	lua_close(L);

	getchar();
	return 0;
}

/*---------------------------------------	sample 3	-------------------------------*/
/*-------------------------------------------------------------------------------------*/







/*-------------------------------------------------------------------------------------*/
/*---------------------------------------	sample 4	-------------------------------*/
/*
int _tmain(int argc, _TCHAR* argv[])
{
	// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = lua_open();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);

	// Lua ���̺��� �����ϰ� ���ÿ� Ǫ���Ѵ�.
	lua_tinker::table haha(L, "haha");

	// haha.value = 1 ���� �ִ´�.
	haha.set("value", 1);

	// table ���� table�� ����� �ִ´�.
	haha.set("inside", lua_tinker::table(L));

	// haha.inside �� �����͸� �������� �����Ѵ�.
	lua_tinker::table inside = haha.get<lua_tinker::table>("inside");

	// inside.value = 2 ���� �ִ´�.
	inside.set("value", 2);

	// sample4.lua ������ �ε�/�����Ѵ�.
	lua_tinker::dofile(L, "sample4.lua");

	// Lua ���� ������ haha.test ���� �д´�.
	const char* test = haha.get<const char*>("test");
	printf("haha.test = %s\n", test);

	// ������ ������� �ʰ� Lua ���ÿ� �� ���̺��� �����Ѵ�.(��������)
	lua_tinker::table temp(L);

	// �� ���̺�.name �� ���� �ִ´�.
	temp.set("name", "local table !!");

	// table�� �� ���ڷ� ����Ͽ� print_table �� ȣ���Ѵ�.
	lua_tinker::call<void>(L, "print_table", temp);

	// �Լ��� �����ϴ� table�� �޴´�.
	lua_tinker::table ret = lua_tinker::call<lua_tinker::table>(L, "return_table", "give me a table !!");
	printf("ret.name =\t%s\n", ret.get<const char*>("name"));

	// ���α׷� ����
	lua_close(L);

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
	// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = lua_open();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);


	// lua_State* �� �����ִ� ������ ������ �����ش�.
	printf("%s\n","-------------------------- current stack");
	lua_tinker::enum_stack(L);

	// ���ÿ� 1�� �о�ִ´�.
	lua_pushnumber(L, 1);

	// ���� ������ ������ �ٽ� ����Ѵ�.
	printf("%s\n","-------------------------- stack after push '1'");
	lua_tinker::enum_stack(L);


	// sample5.lua ������ �ε�/�����Ѵ�.
	lua_tinker::dofile(L, "sample5.lua");

	// test_error() �Լ��� ȣ���Ѵ�.
	// test_error() �� ������ test_error_3() ȣ���� �õ��ϴ� ������ �߻���Ų��.
	// �Լ� ȣ���� �߻��� ������ printf()�� ���ؼ� ��µȴ�.
	printf("%s\n","-------------------------- calling test_error()");
	lua_tinker::call<void>(L, "test_error");

	// test_error_3()�� �������� �ʴ� �Լ��̴�. ȣ�� ��ü�� �����Ѵ�.
	printf("%s\n","-------------------------- calling test_error_3()");
	lua_tinker::call<void>(L, "test_error_3");

	// printf() ��� ������ �����ϴ� ���� ��� ��ƾ�� ����� �� �ִ�.
	// �� ����ó�� �Լ���1���� ��� ���ڿ��� �߻��� ������ �����ϰ� �ȴ�.
	// C++ ���� ����� ��� void function(const char*) ���°� �����ϴ�.
	lua_tinker::def(L, "_ALERT", show_error);

	lua_tinker::call<void>(L, "_ALERT", "test !!!");

	// test_error() �Լ��� ȣ���Ѵ�.
	// �Լ� ȣ���� �߻��� ������ Lua�� ��ϵ� _ALERT()�� ���ؼ� ��µȴ�.
	printf("%s\n","-------------------------- calling test_error()");
	lua_tinker::call<void>(L, "test_error");


	// ���α׷� ����
	lua_close(L);

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
	printf("# TestFunc ������\n");
	return lua_yield(L, 0);
}

int TestFunc2(lua_State* L, float a)
{
	printf("# TestFunc2(L,%f) ������\n", a);
	return lua_yield(L, 0);
}

class TestClass
{
public:

	// �Լ� ���°� int(T::*)(lua_State*) �Ǵ� int(T::*)(lua_State*,T1) �� ��츸 lua_yield() �� �� �� �ִ�.
	// �Լ� ���ڰ� �� �ʿ��� ��� lua_tinker.h �� "class member functor (non-managed)" �ڸ�Ʈ �κ��� �����ؼ� ���� �߰��� ��
	int TestFunc(lua_State* L)
	{
		printf("# TestClass::TestFunc ������\n");
		return lua_yield(L, 0);
	}

	int TestFunc2(lua_State* L, float a)
	{
		printf("# TestClass::TestFunc2(L,%f) ������\n", a);
		return lua_yield(L, 0);
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	// Lua �� �ʱ�ȭ �Ѵ�.
	lua_State* L = lua_open();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);
	// Lua ���ڿ� �Լ����� �ε��Ѵ�.- string ���
	luaopen_string(L);

	// TestFunc �Լ��� Lua �� ����Ѵ�.
	lua_tinker::def(L, "TestFunc", &TestFunc);
	lua_tinker::def(L, "TestFunc2", &TestFunc2);

	// TestClass Ŭ������ Lua �� �߰��Ѵ�.
	lua_tinker::class_add<TestClass>(L, "TestClass");
	// TestClass �� �Լ��� ����Ѵ�.
	lua_tinker::class_def<TestClass>(L, "TestFunc", &TestClass::TestFunc);
	lua_tinker::class_def<TestClass>(L, "TestFunc2", &TestClass::TestFunc2);

	// TestClass �� ���� ������ �����Ѵ�.
	TestClass g_test;
	lua_tinker::set(L, "g_test", &g_test);

	// sample3.lua ������ �ε��Ѵ�.
	lua_tinker::dofile(L, "sample6.lua");

	// Thread �� �����Ѵ�.
	lua_newthread(L);
	lua_pushstring(L, "ThreadTest");
	lua_gettable(L, LUA_GLOBALSINDEX);

	// Thread �� �����Ѵ�.
	printf("* lua_resume() ȣ��\n");
	lua_resume(L, 0);

	// Thread �� �ٽ� �����Ѵ�.
	printf("* lua_resume() ȣ��\n");
	lua_resume(L, 0);

	// Thread �� �ٽ� �����Ѵ�.
	printf("* lua_resume() ȣ��\n");
	lua_resume(L, 0);

	// Thread �� �ٽ� �����Ѵ�.
	printf("* lua_resume() ȣ��\n");
	lua_resume(L, 0);

	// Thread �� �ٽ� �����Ѵ�.
	printf("* lua_resume() ȣ��\n");
	lua_resume(L, 0);

	// ���α׷� ����
	lua_close(L);

	return 0;
}
*/
/*---------------------------------------	sample 6	-------------------------------*/
/*-------------------------------------------------------------------------------------*/
