

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

SpriteDetails LuaGetSpriteInfo(lua_State* L, const std::string& name) {
	SpriteDetails temp;

	lua_getglobal(L, name.c_str());
	if (!lua_istable(L, -1))
		assert(false);

	lua_pushstring(L, "TexLoc");
	lua_gettable(L, -2);
	temp.TexLoc = lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "PosX");
	lua_gettable(L, -2);
	temp.PosX = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "PosY");
	lua_gettable(L, -2);
	temp.PosY = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "IsAlpha");
	lua_gettable(L, -2);
	temp.isAlpha = lua_toboolean(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "Scale");
	lua_gettable(L, -2);
	temp.scale = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "IsAnim");
	lua_gettable(L, -2);
	temp.isAnim = lua_toboolean(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "NumSprites");
	lua_gettable(L, -2);
	temp.spriteAmount = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "AnimSpeed");
	lua_gettable(L, -2);
	temp.animSpeed = lua_tonumber(L, -1);
	lua_pop(L, 1);

	return temp;
}

BasicSpriteDetails LuaGetBasicSpriteInfo(lua_State* L, const std::string& name) {
	BasicSpriteDetails temp;
	lua_getglobal(L, name.c_str());
	if (!lua_istable(L, -1))
		assert(false);

	lua_pushstring(L, "TexLoc");
	lua_gettable(L, -2);
	temp.TexLoc = lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "Scale");
	lua_gettable(L, -2);
	temp.scale = lua_tonumber(L, -1);
	lua_pop(L, 1);

	return temp;

}

DirectX::SimpleMath::Vector2 LuaMovePlayer(lua_State* L, bool& up, bool& down, bool& left, bool& right, float& deltaTime) {

	std::string fname = "movePlayer";

	lua_getglobal(L, fname.c_str());
	if (!lua_isfunction(L, -1))
		assert(false);

	lua_pushboolean(L, up);
	lua_pushboolean(L, down);
	lua_pushboolean(L, left);
	lua_pushboolean(L, right);
	lua_pushnumber(L, deltaTime);
	if(!LuaOK(L, lua_pcall(L, 5, 2, 0)))
		assert(false);
	
	float posX = (float)lua_tonumber(L, -2);
	float posY = (float)lua_tonumber(L, -1);
	lua_pop(L, 2);
	
	return DirectX::SimpleMath::Vector2(posX, posY);
}

TextDetails LuaGetTextDetails(lua_State* L, const std::string& name) {
	TextDetails temp;
	float R, G, B, A;

	lua_getglobal(L, name.c_str());
	if (!lua_istable(L, -1))
		assert(false);

	lua_pushstring(L, "text");
	lua_gettable(L, -2);
	temp.text = lua_tostring(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "PosX");
	lua_gettable(L, -2);
	temp.PosX = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "PosY");
	lua_gettable(L, -2);
	temp.PosY = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "R");
	lua_gettable(L, -2);
	R = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "G");
	lua_gettable(L, -2);
	G = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "B");
	lua_gettable(L, -2);
	B = lua_tonumber(L, -1);
	lua_pop(L, 1);

	lua_pushstring(L, "A");
	lua_gettable(L, -2);
	A = lua_tonumber(L, -1);
	lua_pop(L, 1);

	DirectX::XMVECTORF32 tempColour = { { { R, G, B, A } } };
	temp.colour = DirectX::SimpleMath::Color::Color(tempColour);

	lua_pushstring(L, "scale");
	lua_gettable(L, -2);
	temp.scale = lua_tonumber(L, -1);
	lua_pop(L, 1);

	return temp;

}


void LuaCallBasicFunction(lua_State* L, const std::string& fname) {


	lua_getglobal(L, fname.c_str());
	if (!lua_isfunction(L, -1))
		assert(false);

	if (!LuaOK(L, lua_pcall(L, 0, 0, 0)))
		assert(false);
}

void LuaCallScoreUpdate(lua_State* L, float& deltaTime) {
	std::string fname = "updateScore";

	lua_getglobal(L, fname.c_str());
	if (!lua_isfunction(L, -1))
		assert(false);

	lua_pushnumber(L, deltaTime);
	if (!LuaOK(L, lua_pcall(L, 1, 0, 0)))
		assert(false);
}

void LuaCallCFunc(lua_State* L, const std::string& fname) {
	lua_getglobal(L, fname.c_str());
	if (!lua_isfunction(L, -1))
		assert(false);

	if (!LuaOK(L, lua_pcall(L, 0, 0, 0)))
		assert(false);
}

std::map<string, Dispatcher::Command> Dispatcher::library;

int Dispatcher::LuaCall(lua_State* L) {
	std::string name = lua_tostring(L, 1);
	std::map<string, Command>::iterator it = library.find(name);
	assert(it != library.end());
	Command& cmd = (*it).second;
	if (cmd.voidFloatFunction) {
		int param = lua_tonumber(L, 2);
		cmd.voidFloatFunction(param);
		lua_pop(L, 1);
	}
	else if (cmd.voidIntFunction) {
		int param = lua_tointeger(L, 2);
		cmd.voidIntFunction(param);
		lua_pop(L, 1);
	}
	else
		assert(false);

	return 1;
		
}