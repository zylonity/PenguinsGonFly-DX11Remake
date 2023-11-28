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
protected:
	ID3D11ShaderResourceView* texture;
	DDS_ALPHA_MODE alpha;
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
	float scale;

	bool isAnimated;
	
	RECT sprRect;



	Sprite();

	void createSprite(MyD3D& d3dToPass, wstring textureLocation, Vector2 globPos, bool alpha = false, float scale = 1.0f, bool isAnim = false, int spriteAmount = 1, float speed = 10.0f);

	void RenderSprite();

	void setTexRect(RECT rectToPass);
	

};
