

#include "LuaHelper.h"

using namespace std;

bool LuaOK(lua_State* L, int id) {
	if (id != LUA_OK) {
		cout << lua_tostring(L, -1) << endl;
		return false;
	}
	return true;
}

int LuaGetInt(lua_State* L, const std::string& name) {
	lua_getglobal(L, name.c_str());
	if (!lua_isinteger(L, -1))
		assert(false);
	return (int)lua_tointeger(L, -1);

}
float LuaGetFloat(lua_State* L, const std::string& name) {
	lua_getglobal(L, name.c_str());
	return lua_tonumber(L, -1);
}
std::string LuaGetStr(lua_State* L, const std::string& name) {
	lua_getglobal(L, name.c_str());
	if (!lua_isstring(L, -1))
		assert(false);
	return lua_tostring(L, -1);

}

bool LuaGetBool(lua_State* L, const std::string& name) {
	lua_getglobal(L, name.c_str());
	if (!lua_isboolean(L, -1))
		assert(false);
	return lua_toboolean(L, -1);

}

DirectX::SimpleMath::Vector2 LuaGetVector2(lua_State* L, const std::string& name) {
	int x, y;
	float fx, fy;

	lua_getglobal(L, name.c_str());
	if (!lua_istable(L, -1))
		assert(false);

	lua_pushstring(L, "x");
	lua_gettable(L, -2);

	//if integer or float
	if (lua_tonumber(L, -1) == (int)lua_tonumber(L, -1)) {
		x = (int)lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_pushstring(L, "y");
		lua_gettable(L, -2);

		y = (int)lua_tointeger(L, -1);
		lua_pop(L, 1);
		return DirectX::SimpleMath::Vector2(x, y);
	}
	else {
		fx = lua_tonumber(L, -1);
		lua_pop(L, 1);

		lua_pushstring(L, "y");
		lua_gettable(L, -2);

		fy = lua_tonumber(L, -1);
		lua_pop(L, 1);
		return DirectX::SimpleMath::Vector2(fx, fy);
	}


}