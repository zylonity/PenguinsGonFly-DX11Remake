#pragma once
#include <vector>

#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"
#include "sprite.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;


class Enemy {

	Sprite enemySprite;
	RECT enemyHitbox;
	Vector2 enemyPos;

	RECT playerHitbox;
	Vector2 playerPos;

	

	
};