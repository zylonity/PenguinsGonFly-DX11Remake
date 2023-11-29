#include "Player.h"

Player::Player() {



	moveSpeed = 1.0f;
	hitbox = RECT();

	isAlive = true;

}



void Player::HandleMovement(DirectX::Keyboard::State& kb, float dTime) {

	if (isAlive) {
		if (pos.y >= 0 && pos.y <= 570) {
			if (kb.W || kb.Up) {
				pos.y -= moveSpeed * dTime;
			}
			if (kb.S || kb.Down) {
				pos.y += moveSpeed * dTime;
			}
		}
		else if (pos.y <= 0) {
			pos.y = 0;
		}
		else if (pos.y >= 550) {
			pos.y = 570;
		}


		if (pos.x >= 0 && pos.x <= 1100) {
			if (kb.A || kb.Left) {
				pos.x -= moveSpeed * dTime;
			}
			if (kb.D || kb.Right) {
				pos.x += moveSpeed * dTime;
			}
		}
		else if (pos.x <= 0) {
			pos.x = 0;
		}
		else if (pos.x >= 1100) {
			pos.x = 1100;
		}
	}
	

}

void Player::Update() {

	hitbox.top = pos.y + 55;
	hitbox.left = pos.x + 10;
	hitbox.bottom = (pos.y + sprRect.bottom * scale - 40);
	hitbox.right = (pos.x + sprRect.right) - 10;
}

void Player::HandleCollisions(vector<Enemy>& enemies) {

	assert(enemies.size() == 1);
	//assert(isAlive == true);



	if (hitbox.right > enemies[0].hitbox.left &&
		hitbox.left < enemies[0].hitbox.right &&
		hitbox.top < enemies[0].hitbox.bottom &&
		hitbox.bottom > enemies[0].hitbox.top
		) {

		isAlive = false;

		

	}

}
