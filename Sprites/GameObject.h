#pragma once

#include "sprite.h"

#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"

class GameObject {

protected:
	ID3D11ShaderResourceView* texture;
	DDS_ALPHA_MODE alpha;
	MyD3D d3d;
	Sprite sprite;
	//RECT hitbox;
	bool isActive;

public:

	Vector2 position;

	GameObject(MyD3D& d3dToPass, Vector2 pos);

	void CreateSprite(wstring textureLocation, bool isAlpha = false, float scale = 1);
	void CreateAnimatedSprite(wstring textureLocation, bool isAlpha = false, bool isAnim = false, int sprAmount = 1, float animSpeed = 1, float scale = 1);

	void Update();
	void Render();
	
};
