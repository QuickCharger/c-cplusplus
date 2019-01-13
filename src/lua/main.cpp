#include <iostream>

#include "lua.hpp"

using namespace std;

lua_State* L;
int tId = -1;

/*
* ����ֵ��ѹջ������, ������ֵ������, �˴�ֻ����n/2��һ��ֵ ���Է���1
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
		tId = luaL_ref(L, LUA_REGISTRYINDEX);		// ������߳� ?
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
* ������null ��lua�涨, ԭ������:
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
		std::cout << "��ʼ��luaʧ��" << endl;
		goto end;
	}

	/*
	* Opens all standard Lua libraries
	*/
	luaL_openlibs(L);

	/*
	* luaL_dofile ִ��ʧ�ܺ�, reason��ѹջ
	*/
	int ret = luaL_dofile(L, "test.lua");
	if (ret)
	{
		std::cout << "����lua�ļ�ʧ��. ��ȷ���ļ���" << argv[0] << "ͬĿ¼" << endl;
		std::cout << "reason " << lua_tostring(L, -1);
		goto end;
	}

	/*
	* ��ȡluaȫ�ֱ���ʾ��
	*/
	{
		/*
		* lua_getgloabl(L, name);
		* ��lua�е�ȫ��nameѹ��ջ��
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
				std::cout << "myTable ����table" << endl;
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
			std::cout << "myTable2 ����table" << endl;
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
				std::cout << "myTable3 ����table" << endl;
				goto end;
			}
			int nTableSize = luaL_len(L, -1);
			std::cout << "myTable3 size: " << n << endl;
			for (int i = 0; i < nTableSize; ++i)
			{
				// ��ȡ������ÿ����Ա
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
	* ����lua, ѹջ˳��: ������ ����
	*/
	{
		lua_getglobal(L, "add");
		lua_pushinteger(L, 1);
		lua_pushinteger(L, 2);
		lua_call(L, 2, 1, 0);		// ����2��, ���1��
		if (lua_isinteger(L, -1))
		{
			n = lua_tonumber(L, -1);
			cout << "1 + 2 = " << n << endl;
			lua_pop(L, 1);
		}
	}
	cout << endl;

	/*
	* lua��c++
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
	* lua��c++ c++�ص�lua
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
		lua_rawgeti(L, LUA_REGISTRYINDEX, tId);		// �߳���ջ
		lua_pushinteger(L, x);
		lua_call(L, 1, 1, 0);
		int type = lua_type(L, -1);
		if (type == LUA_TNUMBER)
		{
			n = lua_tonumber(L, -1);
			cout << "Asy call. input " << x << ". output " << n << endl;
		}
		lua_pop(L, 1);
		luaL_unref(L, LUA_REGISTRYINDEX, tId);		// ���tId�߳� ?
		cout << "unsave lua thread. id: " << tId << endl;
	}


	end:
	lua_close(L);
	std::cout << endl;
	system("pause");
	return 0;
}
