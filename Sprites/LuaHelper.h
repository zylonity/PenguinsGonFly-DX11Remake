#pragma once

#include <string>
#include <functional>
#include <map>
#include <assert.h>
#include <iostream>
#include "SimpleMath.h"

extern "C"
{
	#include "../lua-5.4.4/include/lua.h"
	#include "../lua-5.4.4/include/lauxlib.h"
	#include "../lua-5.4.4/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "../lua-5.4.4/liblua54.a")
#endif

bool LuaOK(lua_State* L, int id);

int LuaGetInt(lua_State* L, const std::string& name);
float LuaGetFloat(lua_State* L, const std::string& name);
std::string LuaGetStr(lua_State* L, const std::string& name);
bool LuaGetBool(lua_State* L, const std::string& name);

struct SpriteDetails {
	std::string TexLoc;
	int PosX, PosY;
	bool isAlpha;
	float scale;
	bool isAnim;
	int spriteAmount;
	float animSpeed;
};

struct BasicSpriteDetails {
	std::string TexLoc;
	float scale;
};

struct TextDetails {
	std::string text;
	int PosX, PosY;
	DirectX::SimpleMath::Color colour;
	float scale;
};


DirectX::SimpleMath::Vector2 LuaGetVector2(lua_State* L, const std::string& name);
SpriteDetails LuaGetSpriteInfo(lua_State* L, const std::string& name);
BasicSpriteDetails LuaGetBasicSpriteInfo(lua_State* L, const std::string& name);
TextDetails LuaGetTextDetails(lua_State* L, const std::string& name);

//No need to pass function name, since its not like you can edit the C# code in runtime
DirectX::SimpleMath::Vector2 LuaMovePlayer(lua_State* L, bool& up, bool& down, bool& left, bool& right, float& deltaTime);

void LuaCallScoreUpdate(lua_State* L, float& deltaTime);

void LuaCallBasicFunction(lua_State* L, const std::string& fname);

