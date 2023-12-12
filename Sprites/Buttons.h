#pragma once

#include "sprite.h"
#include "EnemyController.h"

#include "Mouse.h"
#include "Keyboard.h"

class Button : public Sprite {

public:


	RECT hitbox;
	Button();

	void HandleClick(std::unique_ptr<DirectX::Mouse>& m_mouse, string mode);

	void setHitbox();

};