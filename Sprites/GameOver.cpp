#include "GameOver.h"
const std::string GameOver::MODE_NAME = "OVER";
GameOver::GameOver(MyD3D& d3d)
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

	redHue.createSprite(d3d, L"bin/data/Background/dead.dds", Vector2(0, 0), true);

	score.createText(d3d, L"", Vector2(770, 200));
	scoretxt.createText(d3d, L"Final score:", Vector2(450, 200));

	GG.createSprite(d3d, L"bin/data/Background/GG.dds", Vector2(0, 0), true);

	initials.createText(d3d, L"Initials: ", Vector2(390, 320));
	input.createText(d3d, L"", Vector2(590, 320));
	submitBtn.createSprite(d3d, L"bin/data/Buttons/submit.dds", Vector2(800, 360), true, 3);

	restartBtn.createSprite(d3d, L"bin/data/Buttons/restart.dds", Vector2(640, 450), true, 3);
	leaderboardBtn.createSprite(d3d, L"bin/data/Buttons/leaderboard.dds", Vector2(640, 540), true, 3);
	mmBtn.createSprite(d3d, L"bin/data/Buttons/mainmenu1.dds", Vector2(640, 630), true, 3);

	submitBtn.setHitbox();
	restartBtn.setHitbox();
	mmBtn.setHitbox();
	leaderboardBtn.setHitbox();

}

void GameOver::Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse)
{

	if (restartBtn.HandleClick(m_mouse, "GAME"))
		ResetScreen();

	if(mmBtn.HandleClick(m_mouse, "MENU"))
		ResetScreen();

	if (leaderboardBtn.HandleClick(m_mouse, "LEADER"))
		ResetScreen();

	if (submitBtn.HandleClick(m_mouse, "SUBMIT")) {
		submitBtn.isVisible = false;
		input.inputAllowed = false;
		initials.isVisible = false;
	}
	input.InputMode(3, m_keyboard);

	GameManager::Get().SetName(input.text);
}

void GameOver::Render(float dTime, MyD3D& d3d)
{
	WinUtil& wu = WinUtil::Get();


	d3d.BeginRender(Vector4(0, 0, 0, 0));

	//put background to render here
	if (background.empty() == false) {
		for (int i = 0; i < background.size(); i++) {
			background[i].RenderSprite();
		}
	}

	redHue.RenderSprite();


	scoretxt.write();
	score.write();
	initials.write();
	input.write();
	score.changeText(std::to_wstring(GameManager::Get().GetScore()));

	GG.RenderSprite();
	submitBtn.RenderSprite();
	restartBtn.RenderSprite();
	mmBtn.RenderSprite();
	leaderboardBtn.RenderSprite();

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

void GameOver::ResetScreen() {
	submitBtn.isVisible = true;
	input.inputAllowed = true;
	initials.isVisible = true;

	for (int i = 0; i < background.size(); i++) {
		background[i].pos = Vector2(0, 0);
	}

	input.text = L"";
	input.inputInit = false;
}

std::string GameOver::GetMName() const {

	return MODE_NAME;
}