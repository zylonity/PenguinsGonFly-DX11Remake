#pragma once

#include "sprite.h"
#include "EnemyController.h"

#include "Mouse.h"
#include "Keyboard.h"
#include <fstream> 
class Button : public Sprite {

	int ButtonAmnt;
	int currentShow;

	std::wfstream leaderboard;

	bool sortingNums;

public:

	bool clicked;
	bool hovering;
	bool isVisible;

	RECT hitbox;
	Button();

	bool HandleClick(std::unique_ptr<DirectX::Mouse>& m_mouse, string mode);

	void setHitbox();

	void RenderSprite() override;

};