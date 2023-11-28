#include "Player.h"

Player::Player() {

	moveSpeed = 1.0f;
	hitbox = RECT();

}


void Player::HandleMovement(DirectX::Keyboard::State& kb, float dTime) {

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