#include "Player.h"
#include "GameManager.h"

Player::Player() {



	hitbox = RECT();

	isAlive = true;
	isShielded = false;

	shieldTimer = 5.0f;

	ls_player = luaL_newstate();
	luaL_openlibs(ls_player);

	if (!LuaOK(ls_player, luaL_dofile(ls_player, "bin/scripts/Player.lua")))
		assert(false);



	tempPosY = LuaGetVector2(ls_player, "playerPos").y;
}



void Player::HandleMovement(DirectX::Keyboard::State& kb, float dTime) {
	//Had to make it booleans otherwise it could only move in one direction at a time
	bool up, down, left, right = false;

	up = kb.W || kb.Up;
	down = kb.S || kb.Down;
	left = kb.A || kb.Left;
	right = kb.D || kb.Right;

	pos = LuaMovePlayer(ls_player, up, down, left, right, dTime);

}

void Player::Update(float& dTime) {

	hitbox.top = pos.y + 55;
	hitbox.left = pos.x + 10;
	hitbox.bottom = (pos.y + sprRect.bottom * scale - 40);
	hitbox.right = (pos.x + sprRect.right) - 10;

	outsideShield.pos.x = (pos.x - (outsideShield.texSize.x + outsideShield.texSize.x / 3));
	outsideShield.pos.y = (pos.y - (outsideShield.texSize.y + outsideShield.texSize.y / 3));

	if (isShielded && shieldTimer >= 0) {
		shieldTimeIndicator.isVisible = true;
		shieldTimeRemaining.isVisible = true;
		if((int)shieldTimer < 4)
			shieldTimeRemaining.colour = Color::Color(Colors::Yellow);
		if ((int)shieldTimer < 2)
			shieldTimeRemaining.colour = Color::Color(Colors::Red);
		
		shieldTimeRemaining.changeText(std::to_wstring((int)shieldTimer));
		shieldTimer -= dTime;
		outsideShield.isVisible = true;
	}

	if (shieldTimer <= 0) {
		isShielded = false;
		shieldTimer = 5.0f;
		outsideShield.isVisible = false;
		shieldTimeIndicator.isVisible = false;
		shieldTimeRemaining.isVisible = false;
		shieldTimeRemaining.colour = Color::Color(Colors::White);
	}
}


void Player::HandleEnemyCollision(vector<Enemy>& enemies) {

	if (!isShielded) {
		for (int i = 0; i < enemies.size(); i++) {
			if (hitbox.right > enemies[i].hitbox.left &&
				hitbox.left < enemies[i].hitbox.right &&
				hitbox.top < enemies[i].hitbox.bottom &&
				hitbox.bottom > enemies[i].hitbox.top
				) {
				isAlive = false;
				isVisible = false;


			}
		}
	}

}

void Player::HandleShieldCollision(ShieldController& shield_c) {

	if (hitbox.right > shield_c.shield.hitbox.left &&
		hitbox.left < shield_c.shield.hitbox.right &&
		hitbox.top < shield_c.shield.hitbox.bottom &&
		hitbox.bottom > shield_c.shield.hitbox.top
		) {
		shield_c.shield.isVisible = false;
		shield_c.ShieldHit();
		isShielded = true;
	}

}

void Player::Release() {
	lua_close(ls_player);
}

