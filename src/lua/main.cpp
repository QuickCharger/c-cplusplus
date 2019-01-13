#include <iostream>

#include "lua.hpp"

using namespace std;

lua_State* L;
int tId = -1;

/*
* 返回值是压栈的数量, 即返回值的数量, 此处只返回n/2这一个值 所以返回1
*/
int halfValue(lua_State *L)
{
	int n = 0;
	if (lua_isinteger(L, -1))
	{
		n = lua_tonumber(L, -1);
		//cout << __FUNCTION__ << ". get value: " << n << endl;
		lua_pop(L, 1);
	}
	lua_pushinteger(L, n/2);
	return 1;
}

int luaAsy(lua_State* L)
{
	if (lua_isfunction(L, -1))
	{
		tId = luaL_ref(L, LUA_REGISTRYINDEX);		// 保存该线程 ?
		if (tId == LUA_REFNIL || tId == LUA_NOREF)
		{
			cout << "err. cannot ref thread" << endl;
			return 0;
		}
		cout << "save lua thread. id: " << tId << endl;
	}
	//lua_pop(L, 1);
	if (lua_isinteger(L, -1))
	{
		int n = lua_tonumber(L, -1);
		cout << "10 + 2 = "<< n << endl;
	}
	lua_pop(L, 1);
	return 0;
}

/*
* 最后填充null 是lua规定, 原文如下:
* Any array of luaL_Reg must end with a sentinel entry in which both name and func are NULL.
*/
static const luaL_Reg cpplib[] = {
	{"halfValue", halfValue},
	{"asy", luaAsy},
	{nullptr, nullptr}
};

int cppFunc(lua_State* L)
{
	luaL_newlib(L, cpplib);
	return 1;
}

int main(int argc, char* argv[])
{
	L = luaL_newstate();
	std::string str;
	int n = 0;
	if (!L)
	{
		std::cout << "初始化lua失败" << endl;
		goto end;
	}

	/*
	* Opens all standard Lua libraries
	*/
	luaL_openlibs(L);

	/*
	* luaL_dofile 执行失败后, reason会压栈
	*/
	int ret = luaL_dofile(L, "test.lua");
	if (ret)
	{
		std::cout << "载入lua文件失败. 请确保文件与" << argv[0] << "同目录" << endl;
		std::cout << "reason " << lua_tostring(L, -1);
		goto end;
	}

	/*
	* 读取lua全局变量示例
	*/
	{
		/*
		* lua_getgloabl(L, name);
		* 将lua中的全局name压入栈中
		*/
		std::cout << "myStr = \"this is from lua\"" << endl;
		lua_getglobal(L, "myStr");
		{
			str = lua_tostring(L, -1);
			std::cout << "str: " << str.c_str() << endl;
		}
		lua_pop(L, 1);

		std::cout << endl << "myTable = { name = \"qwer \", id = 1234 }" << endl;
		lua_getglobal(L, "myTable");
		{

			if (!lua_istable(L, -1))
			{
				std::cout << "myTable 不是table" << endl;
				goto end;
			}
			std::cout << "myTable size: " << luaL_len(L, -1) << endl;
			n = lua_getfield(L, -1, "name");
			if (n == LUA_TSTRING)
			{
				str = lua_tostring(L, -1);
				std::cout << "name: " << str.c_str() << endl;
			}
			lua_pop(L, 1);
			n = lua_getfield(L, -1, "id");
			if (n == LUA_TNUMBER)
			{
				n = lua_tointeger(L, -1);
				std::cout << "id: " << n << endl;
			}
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		std::cout << endl << "myTable2 = { 111, 222, 333 }" << endl;
		lua_getglobal(L, "myTable2");
		if (!lua_istable(L, -1))
		{
			std::cout << "myTable2 不是table" << endl;
			goto end;
		}
		n = luaL_len(L, -1);
		std::cout << "myTable2 size: " << n << endl;
		for (int i = 0; i < n; ++i)
		{
			lua_pushnumber(L, i + 1);
			lua_gettable(L, -2);
			{
				std::cout << "value: " << lua_tointeger(L, -1) << endl;
			}
			lua_pop(L, 1);
		}
		lua_pop(L, 1);

		std::cout << endl << "myTable3 = {{name=\"qwer\", id=1234},{name=\"asdf\", id=2345},{name=\"zxcv\", id=3456}}" << endl;
		lua_getglobal(L, "myTable3");
		{
			if (!lua_istable(L, -1))
			{
				std::cout << "myTable3 不是table" << endl;
				goto end;
			}
			int nTableSize = luaL_len(L, -1);
			std::cout << "myTable3 size: " << n << endl;
			for (int i = 0; i < nTableSize; ++i)
			{
				// 获取数组中每个成员
				lua_pushnumber(L, i + 1);
				lua_gettable(L, -2);
				{
					n = lua_getfield(L, -1, "name");
					if (n == LUA_TSTRING)
					{
						str = lua_tostring(L, -1);
						std::cout << "name: " << str.c_str() << endl;
					}
					lua_pop(L, 1);

					n = lua_getfield(L, -1, "id");
					if (n == LUA_TNUMBER)
					{
						n = lua_tointeger(L, -1);
						std::cout << "id: " << n << endl;
					}
					lua_pop(L, 1);
				}
				lua_pop(L, 1);
			}
		}
		lua_pop(L, 1);
	}
	cout << endl;

	/*
	* 调用lua, 压栈顺序: 函数名 参数
	*/
	{
		lua_getglobal(L, "add");
		lua_pushinteger(L, 1);
		lua_pushinteger(L, 2);
		lua_call(L, 2, 1, 0);		// 输入2个, 输出1个
		if (lua_isinteger(L, -1))
		{
			n = lua_tonumber(L, -1);
			cout << "1 + 2 = " << n << endl;
			lua_pop(L, 1);
		}
	}
	cout << endl;

	/*
	* lua调c++
	*/
	{
		luaL_requiref(L, "cppFunc", cppFunc, 1);

		int x = 10;
		int y = 2;
		lua_getglobal(L, "add2");
		lua_pushinteger(L, x);
		lua_pushinteger(L, y);
		lua_call(L, 2, 1, 0);
		if (lua_isinteger(L, -1))
		{
			n = lua_tonumber(L, -1);
			cout << "halfValue("<< x << ")" << "+" << y << "= " << n << endl;
			lua_pop(L, 1);
		}
	}
	cout << endl;

	/*
	* lua调c++ c++回调lua
	*/
	{
		//luaL_requiref(L, "cppFunc", cppFunc, 1);

		int x = 10;
		int y = 2;
		lua_getglobal(L, "add_asy");
		lua_pushinteger(L, x);
		lua_pushinteger(L, y);
		lua_call(L, 2, 2, 0);

		x = 10;
		lua_rawgeti(L, LUA_REGISTRYINDEX, tId);		// 线程入栈
		lua_pushinteger(L, x);
		lua_call(L, 1, 1, 0);
		int type = lua_type(L, -1);
		if (type == LUA_TNUMBER)
		{
			n = lua_tonumber(L, -1);
			cout << "Asy call. input " << x << ". output " << n << endl;
		}
		lua_pop(L, 1);
		luaL_unref(L, LUA_REGISTRYINDEX, tId);		// 解除tId线程 ?
		cout << "unsave lua thread. id: " << tId << endl;
	}


	end:
	lua_close(L);
	std::cout << endl;
	system("pause");
	return 0;
}
