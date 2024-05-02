#pragma once


#include "sprite.h"
#include "EnemyController.h"
#include "Shield.h"
#include "ScreenText.h"

#include "Mouse.h"
#include "Keyboard.h"

class Player : public Sprite{



public:
	bool isAlive;

	bool isShielded;
	float shieldTimer;

	Sprite outsideShield;

	Text shieldTimeIndicator;
	Text shieldTimeRemaining;

	RECT hitbox;
	Player();

	float tempPosY;

	lua_State* ls_player;

	void HandleMovement(DirectX::Keyboard::State& kb, float dTime);
	void HandleEnemyCollision(vector<Enemy>& enemies);
	void HandleShieldCollision(ShieldController& shield_c);
	void Update(float& dTime);
	void Release();
	

};

