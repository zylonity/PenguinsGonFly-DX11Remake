#pragma once

#include "sprite.h"
#include <random>

class Shield : public Sprite {

public:
	float moveSpeed;
	float respawnTimer;
	bool alive;
	RECT hitbox;
	Shield();

	void SetHitbox();
};

class ShieldController {

	Vector2 spawnerPos;

	float timer;


public:
	Shield shield;

	bool shieldActive;

	ShieldController();

	void SpawnShields(MyD3D& d3d);

	void ShieldSpawn(float dTime, float difficulty);
	void RenderShield();


	int randomNumber(int a, int b = 0);
};