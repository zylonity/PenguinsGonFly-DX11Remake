#pragma once

#include "sprite.h"
#include <random>

class Enemy : public Sprite {

public:
	float moveSpeed;
	float respawnTimer;
	bool alive;
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

	void SpawnEnemies(MyD3D& d3d);

	void EnemySpawn(float dTime);
	void RenderEnemies();


	int randomNumber(int a, int b = 0);
};