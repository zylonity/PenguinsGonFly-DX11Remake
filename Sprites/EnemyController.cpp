#include "EnemyController.h"

Enemy::Enemy() {
	alive = false;
	respawnTimer = 5.0f;
	moveSpeed = 1.0f;
	hitbox = RECT();
}

void Enemy::SetHitbox() {
	hitbox.top = pos.y + 180;
	hitbox.left = pos.x + 100;
	hitbox.bottom = (pos.y + sprRect.bottom * scale - 190);
	hitbox.right = (pos.x + sprRect.right) - 50;

}


int EnemyController::randomNumber(int a, int b) {

	int min, max;
	if (a > b) {
		min = b;
		max = a;
	}
	else if (b > a) {
		min = a;
		max = b;
	}
	else if (b == a) {
		return b;
	}

	LARGE_INTEGER seed;
	QueryPerformanceCounter(&seed);

	std::mt19937 rng(seed.QuadPart);
	std::uniform_int_distribution<int> gen(min, max); // uniform, unbiased

	return gen(rng);

}

EnemyController::EnemyController() {

}

void EnemyController::SpawnEnemies(MyD3D& d3d) {
	for (int i = 0; i < 5; i++) {
		enemies.push_back(Enemy::Enemy());
	}

	
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].createSprite(d3d, L"bin/data/Entities/penguinplane_backwards.dds", Vector2(-400, 250), true, 3.5f, true, 3, 10.0f);

		enemies[i].respawnTimer = randomNumber(7, 2);
		enemies[i].pos.y = randomNumber(450, -140);
		enemies[i].moveSpeed = randomNumber(800, 500);

	}
}

void EnemyController::EnemySpawn(float dTime) {


	for (int i = 0; i < enemies.size(); i++) {

		enemies[i].SetHitbox();

		//Check if passed map
		if (enemies[i].pos.x >= -380) {
			enemies[i].pos.x -= enemies[i].moveSpeed * dTime;
		}
		else if (enemies[i].pos.x <= -380) {
			//Set random timer and kill
			if (enemies[i].alive) {
				enemies[i].respawnTimer = randomNumber(7, 2);
				enemies[i].alive = false;
			}
			else {
				if (enemies[i].respawnTimer >= 0) {
					enemies[i].respawnTimer -= dTime;
				}
				else {
					enemies[i].moveSpeed = randomNumber(800, 500);
					enemies[i].pos.y = randomNumber(450, -140);
					enemies[i].alive = true;
					enemies[i].pos.x = 1250;

				}
			}

			
			
			
		}


	}


}

void EnemyController::RenderEnemies() {
	for (int i = 0; i < enemies.size(); i++) {

		enemies[i].RenderSprite();


	}
}
