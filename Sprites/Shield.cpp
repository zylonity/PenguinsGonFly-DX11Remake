#include "Shield.h"

Shield::Shield() {
	alive = false;
	respawnTimer = 5.0f;
	moveSpeed = 1.0f;
	hitbox = RECT();
}

void Shield::SetHitbox() {
	hitbox.top = pos.y;
	hitbox.left = pos.x;
	hitbox.bottom = (pos.y + sprRect.bottom * scale);
	hitbox.right = (pos.x + sprRect.right);

}


int ShieldController::randomNumber(int a, int b) {

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

ShieldController::ShieldController() {

}

void ShieldController::SpawnShields(MyD3D& d3d, lua_State* ls_textures) {
	shield = Shield();

	BasicSpriteDetails shieldDetails = LuaGetBasicSpriteInfo(ls_textures, "shieldIcon");

	//Assigns random pos and speed at spawn
	shield.createSprite(d3d, shieldDetails.TexLoc, Vector2(-400, 250), true, shieldDetails.scale);

	shield.respawnTimer = randomNumber(3);
	shield.pos.y = randomNumber(450, -140);
	shield.moveSpeed = 500;
}

void ShieldController::ShieldUpdate(float dTime, float difficulty) {


	shield.SetHitbox();

	//Check if passed map
	if (shield.pos.x >= -380) {
		shield.pos.x -= shield.moveSpeed * dTime;
	}
	else if (shield.pos.x <= -380) {
		//Set random timer and kill
		if (shield.alive) {
			shield.respawnTimer = randomNumber(7, 2);
			shield.alive = false;
		}
	}

	if (!shield.alive) {
		if (shield.respawnTimer >= 0) {
			shield.respawnTimer -= dTime;
		}
		else {
			//Makes enemy faster depending on difficulty
			shield.moveSpeed = randomNumber(800 + difficulty, 500 + difficulty);
			shield.pos.y = randomNumber(450, -140);
			shield.alive = true;
			shield.pos.x = 1250;
			shield.isVisible = true;

		}
	}
	
}

void ShieldController::RenderShield() {
	shield.RenderSprite();
}

void ShieldController::ShieldHit() {
	shield.alive = false;
	shield.respawnTimer = randomNumber(25, 10);
}