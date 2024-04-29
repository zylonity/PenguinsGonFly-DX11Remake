#pragma once


#include <vector>

#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"
#include "Keyboard.h"
#include "LuaHelper.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


class Text {
protected:
	MyD3D d3d;

	wstring fontLocation;



	std::unique_ptr<SpriteBatch> spriteBatch;
	std::unique_ptr<SpriteFont> spriteFont;

	DirectX::Keyboard::KeyboardStateTracker m_keys;

	

	int currentChar;

public:
	Vector2 pos;
	float scale;
	bool isVisible;
	bool inputInit = false;
	bool inputAllowed;
	Color colour;

	wstring text;

	Text();

	void createText(MyD3D& d3dToPass, wstring textt = L"Hello World", Vector2 posToPass = Vector2(0, 0), Color col = Color::Color(Colors::White), float scl = 1.0f);

	void setFont(wstring fontLocation);

	void changeText(wstring textt);

	void InputMode(int charLimit, std::unique_ptr<DirectX::Keyboard>& m_keyboard);

	void write();

	void Text::createTextFromLua(MyD3D& d3dToPass, TextDetails txtDeets);
	void Text::changeTextStr(string strText);



};
