#include "Buttons.h"
#include "GameManager.h"
#include "ModeMgr.h"
#include <fstream> 

Button::Button() {
	ButtonAmnt = 3;
	currentShow = 0;
	hitbox = RECT();
	clicked = false;
	hovering = false;
	isVisible = true;
	sortingNums = true;
}

bool Button::HandleClick(std::unique_ptr<DirectX::Mouse>& m_mouse, string mode) {

	currentShow = 0;

	auto ms = m_mouse->GetState();

	if (ms.x > hitbox.left &&
		ms.x < hitbox.right &&
		ms.y > hitbox.top &&
		ms.y < hitbox.bottom) {
		hovering = true;
		currentShow = 1;
	}
	else {
		hovering = false;
		clicked = false;
	}

	if (hovering == true && ms.leftButton) {
		clicked = true;
		currentShow = 2;
	}

	if (hovering == true && clicked == true && ms.leftButton == false) {
		if (mode == "QUIT") {
			PostQuitMessage(0);
		}
		else if (mode == "SUBMIT") {

			if (GameManager::Get().userScores.size() > 0) {
				for (int i = 0; i < GameManager::Get().userScores.size(); i++) {
					if (GameManager::Get().GetScore() > GameManager::Get().userScores[i]) {
						GameManager::Get().userScores.insert(GameManager::Get().userScores.begin() + i, GameManager::Get().GetScore());
						GameManager::Get().userNames.insert(GameManager::Get().userNames.begin() + i, GameManager::Get().GetName());

						break;
					}

					if (i == GameManager::Get().userScores.size() - 1 && GameManager::Get().GetScore() < GameManager::Get().userScores[i]) {
						GameManager::Get().userScores.push_back(GameManager::Get().GetScore());
						GameManager::Get().userNames.push_back(GameManager::Get().GetName());
					}
					

				}
			}
			else {
				GameManager::Get().userScores.push_back(GameManager::Get().GetScore());
				GameManager::Get().userNames.push_back(GameManager::Get().GetName());
			}
			
			clicked = false;
			return true;
		}
		else {
			GameManager::Get().GetModeMgr().SwitchMode(mode);
			clicked = false;
			return true;
		}
	}
	return false;
}

void Button::setHitbox() {

	for (int i = 0; i < ButtonAmnt; i++) {
		spriteRects.push_back(RECT());
		spriteRects[i].left = i * (desc.Width / ButtonAmnt);
		spriteRects[i].top = 0;
		spriteRects[i].bottom = desc.Height;
		spriteRects[i].right = (i + 1) * (desc.Width / ButtonAmnt);
	}

	pos.x = (pos.x - (((desc.Width / ButtonAmnt) / 2) * scale));
	pos.y = pos.y - ((desc.Height / 2) * scale);

	hitbox.left = pos.x;
	hitbox.top = pos.y;
	hitbox.right = pos.x + ((desc.Width / ButtonAmnt) * scale);
	hitbox.bottom = pos.y + (desc.Height * scale);


}

void Button::RenderSprite() {

	if (isVisible) {
		CommonStates dxstate(&d3d.GetDevice());
		spriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied(), dxstate.PointWrap());

		spriteBatch->Draw(texture, pos, &spriteRects[currentShow], Colors::White, 0.0f, Vector2(0, 0), scale);



		spriteBatch->End();
	}

}