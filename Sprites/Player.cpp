#include "Player.h"
#include "GameManager.h"

Player::Player() {



	hitbox = RECT();

	isAlive = true;

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

void Player::Update() {

	hitbox.top = pos.y + 55;
	hitbox.left = pos.x + 10;
	hitbox.bottom = (pos.y + sprRect.bottom * scale - 40);
	hitbox.right = (pos.x + sprRect.right) - 10;
}

void Player::HandleCollisions(vector<Enemy>& enemies) {


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
void Player::Release() {
	lua_close(ls_player);
}