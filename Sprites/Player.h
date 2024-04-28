#pragma once


#include "sprite.h"
#include "EnemyController.h"

#include "Mouse.h"
#include "Keyboard.h"

class Player : public Sprite{



public:
	bool isAlive;

	RECT hitbox;
	Player();

	float tempPosY;

	lua_State* ls_player;

	void HandleMovement(DirectX::Keyboard::State& kb, float dTime);
	void HandleCollisions(vector<Enemy>& enemies);
	void Update();
	void Release();

};

