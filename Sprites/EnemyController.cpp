#include "EnemyController.h"

Enemy::Enemy() {

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
	timer = 5;
}

void EnemyController::EnemySpawn(float dTime) {

	if (timer > 0) {
		timer -= dTime;

		for (int i = 0; i < enemies.size(); i++) {
			//enemies[i].pos.x -= enemies[i].moveSpeed * dTime;
		}

	}
	else {

		timer = 5;
	}

}

