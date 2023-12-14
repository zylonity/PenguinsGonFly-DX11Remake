#include "ScreenText.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

Text::Text() {

}

void Text::setFont(wstring fontLoc) {
	spriteFont = std::make_unique<SpriteFont>(&d3d.GetDevice(), fontLoc.c_str());
}

void Text::createText(MyD3D& d3dToPass, wstring textt, Vector2 posToPass, Color col, float scl) {

	d3d = d3dToPass;
	text = textt;
	pos = posToPass;
	colour = col;
	scale = scl;

	spriteFont = std::make_unique<SpriteFont>(&d3dToPass.GetDevice(), L"bin/data/Fonts/pixeled.spritefont");
	spriteBatch = std::make_unique<SpriteBatch>(&d3dToPass.GetDeviceCtx());


}

void Text::write() {
	if (isVisible) {
		spriteBatch->Begin();
		spriteFont->DrawString(spriteBatch.get(), text.c_str(), XMFLOAT2(pos.x, pos.y), colour, 0, Vector2(0, 0), Vector2(scale, scale));
		spriteBatch->End();
	}

}

void Text::changeText(wstring textt) {
	text = textt;
}

void Text::InputMode(int charLimit, std::unique_ptr<DirectX::Keyboard>& m_keyboard) {
	auto kb = m_keyboard->GetState();
	m_keys.Update(kb);

	if (inputInit == false) {
		for (int i = 0; i < charLimit; i++) {
			text.append(L"_");
		}
		inputInit = true;
		inputAllowed = true;
		currentChar = 0;
	}

	if (inputAllowed) {
		if (currentChar < charLimit) {
			if (m_keys.IsKeyReleased(DirectX::Keyboard::A)) {
				text[currentChar] = L'A';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::B)) {
				text[currentChar] = L'B';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::C)) {
				text[currentChar] = L'C';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::D)) {
				text[currentChar] = L'D';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::E)) {
				text[currentChar] = L'E';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::F)) {
				text[currentChar] = L'F';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::G)) {
				text[currentChar] = L'G';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::H)) {
				text[currentChar] = L'H';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::I)) {
				text[currentChar] = L'I';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::J)) {
				text[currentChar] = L'J';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::K)) {
				text[currentChar] = L'K';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::L)) {
				text[currentChar] = L'L';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::M)) {
				text[currentChar] = L'M';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::N)) {
				text[currentChar] = L'N';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::O)) {
				text[currentChar] = L'O';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::P)) {
				text[currentChar] = L'P';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::Q)) {
				text[currentChar] = L'Q';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::R)) {
				text[currentChar] = L'R';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::S)) {
				text[currentChar] = L'S';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::T)) {
				text[currentChar] = L'T';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::U)) {
				text[currentChar] = L'U';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::V)) {
				text[currentChar] = L'V';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::W)) {
				text[currentChar] = L'W';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::X)) {
				text[currentChar] = L'X';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::Y)) {
				text[currentChar] = L'Y';
				currentChar++;
			}
			else if (m_keys.IsKeyReleased(DirectX::Keyboard::Z)) {
				text[currentChar] = L'Z';
				currentChar++;
			}
		}

		if (currentChar > 0) {
			if (m_keys.IsKeyReleased(DirectX::Keyboard::Back)) {
				text[currentChar - 1] = L'_';
				currentChar--;
			}
		}
	}
	



}