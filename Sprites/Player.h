#pragma once


#include "sprite.h"
#include "Mouse.h"
#include "Keyboard.h"

class Player : public Sprite{



public:
	float moveSpeed;
	RECT hitbox;
	Player();

	void HandleMovement(DirectX::Keyboard::State& kb, float dTime);

};