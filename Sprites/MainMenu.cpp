#include "MainMenu.h"
const std::string MainMenu::MODE_NAME = "MENU";
MainMenu::MainMenu(MyD3D& d3d)
{
	DDS_ALPHA_MODE alpha;



	background.push_back(Sprite::Sprite());
	background[0].createSprite(d3d, L"bin/data/Background/sky.dds", Vector2(0, 0), false, bgScale);
	background[0].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(100);

	background.push_back(Sprite::Sprite());
	background[1].createSprite(d3d, L"bin/data/Background/TinyCloud5.dds", Vector2(0, 0), true, bgScale);
	background[1].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(110);

	background.push_back(Sprite::Sprite());
	background[2].createSprite(d3d, L"bin/data/Background/SmallCloud3.dds", Vector2(0, 0), true, bgScale);
	background[2].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(140);

	background.push_back(Sprite::Sprite());
	background[3].createSprite(d3d, L"bin/data/Background/MedCloud5.dds", Vector2(0, 0), true, bgScale);
	background[3].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(170);

	background.push_back(Sprite::Sprite());
	background[4].createSprite(d3d, L"bin/data/Background/BigCloud3.dds", Vector2(0, 0), true, bgScale);
	background[4].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(200);

	startBtn.createSprite(d3d, L"bin/data/Buttons/StartButton.dds", Vector2(640, 360), true, 3);
	quitBtn.createSprite(d3d, L"bin/data/Buttons/quitbutton.dds", Vector2(640, 450), true, 3);

	startBtn.setHitbox();
	quitBtn.setHitbox();

}

void MainMenu::Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse)
{
	startBtn.HandleClick(m_mouse, "GAME");
	quitBtn.HandleClick(m_mouse, "QUIT");
}

void MainMenu::Render(float dTime, MyD3D& d3d)
{
	WinUtil& wu = WinUtil::Get();


	d3d.BeginRender(Vector4(0, 0, 0, 0));

	//put background to render here
	if (background.empty() == false) {
		for (int i = 0; i < background.size(); i++) {
			background[i].RenderSprite();
		}
	}

	startBtn.RenderSprite();
	quitBtn.RenderSprite();

	float bgWidth = background[1].texSize.x;

	//Scrolling background

	for (int i = 0; i < bgTimers.size(); i++) {
		bgTimers[i] += dTime;

		float scroll = bgTimers[i] * scrollSpeeds[i];

		if (background[i].pos.x <= -(bgWidth * bgScale)) {
			background[i].pos.x = 0;
			bgTimers[i] = 0;
		}
		else {
			background[i].pos.x = -scroll;
		}
	}



	d3d.EndRender();
}

std::string MainMenu::GetMName() const {

	return MODE_NAME;
}