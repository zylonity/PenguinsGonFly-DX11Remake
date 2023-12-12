#include "Buttons.h"
#include "GameManager.h"
#include "ModeMgr.h"

Button::Button() {
	hitbox = RECT();

}

void Button::HandleClick(std::unique_ptr<DirectX::Mouse>& m_mouse, string mode) {



	auto ms = m_mouse->GetState();

	if (ms.x > hitbox.left &&
		ms.x < hitbox.right &&
		ms.y > hitbox.top &&
		ms.y < hitbox.bottom) {

		if (ms.leftButton) {
			if (mode == "QUIT") {
				PostQuitMessage(0);
			}
			else {
				GameManager::Get().GetModeMgr().SwitchMode(mode);
			}
		}
	}
}

void Button::setHitbox() {

	pos.x = pos.x - ((desc.Width / 2) * scale);
	pos.y = pos.y - ((desc.Height / 2) * scale);

	hitbox.left = pos.x;
	hitbox.top = pos.y;
	hitbox.right = pos.x + (desc.Width * scale);
	hitbox.bottom = pos.y + (desc.Height * scale);
}