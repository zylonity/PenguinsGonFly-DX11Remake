#pragma once

#include "sprite.h"
#include <random>

class Enemy : public Sprite {

public:
	float moveSpeed;
	RECT hitbox;
	Enemy();

	void SetHitbox();  
};

class EnemyController {

	Vector2 spawnerPos;

	float timer;

public:
	vector<Enemy> enemies;
	EnemyController();
	void EnemySpawn(float dTime);

	int randomNumber(int a, int b = 0);
};