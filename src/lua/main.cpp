#include <iostream>

#include "lua.hpp"

using namespace std;

lua_State* L;

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
	* 调用lua
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

	/*
	* lua调c++ 并回调
	*/

	end:
	lua_close(L);
	std::cout << endl;
	system("pause");
	return 0;
}
