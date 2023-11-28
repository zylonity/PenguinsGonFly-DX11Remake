#pragma once

#include <vector>

#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


class Sprite {
private:
	ID3D11ShaderResourceView* pT;
	MyD3D d3d;
	int spriteAmount;
	bool isAlpha;

	vector<RECT> spriteRects;
	Vector2 winSize;
	std::unique_ptr<SpriteBatch> spriteBatch;
	ID3D11Resource* resource;
	ID3D11Texture2D* text2D;
	D3D11_TEXTURE2D_DESC desc;
	
//protected:



public:
	Vector2 pos;
	Vector2 texSize;
	float animSpeed;
	float moveSpeed;
	float scale;

	bool isAnimated;
	
	RECT sprRect;



	Sprite(Vector2 globPos, Vector2 wSize, ID3D11ShaderResourceView* textPointer, MyD3D& d3dToPass, bool alpha = false, bool isAnim = false, int spriteAmount = 1, float speed = 10.0f, float scale = 1.0f);

	void Render();

	void setTexRect(RECT rectToPass);
	

};
