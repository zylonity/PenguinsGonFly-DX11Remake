#include "GameOver.h"
const std::string GameOver::MODE_NAME = "OVER";
GameOver::GameOver(MyD3D& d3d)
{
	DDS_ALPHA_MODE alpha;

	bgScale = LuaGetFloat(GameManager::Get().ls_textures, "backgroundsScale");

	//Add background
	background.push_back(Sprite::Sprite());
	background[0].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "gmo_background0"));
	background[0].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(LuaGetFloat(GameManager::Get().ls_textures, "gmo_bg0scrollspeed"));

	background.push_back(Sprite::Sprite());
	background[1].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "gmo_background1"));
	background[1].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(LuaGetFloat(GameManager::Get().ls_textures, "gmo_bg1scrollspeed"));

	background.push_back(Sprite::Sprite());
	background[2].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "gmo_background2"));
	background[2].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(LuaGetFloat(GameManager::Get().ls_textures, "gmo_bg2scrollspeed"));

	background.push_back(Sprite::Sprite());
	background[3].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "gmo_background3"));
	background[3].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(LuaGetFloat(GameManager::Get().ls_textures, "gmo_bg3scrollspeed"));

	background.push_back(Sprite::Sprite());
	background[4].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "gmo_background4"));
	background[4].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(LuaGetFloat(GameManager::Get().ls_textures, "gmo_bg4scrollspeed"));

	redHue.createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "gmo_redHue"));

	score.createText(d3d, L"", Vector2(770, 200));
	scoretxt.createText(d3d, L"Final score:", Vector2(450, 200));

	GG.createSprite(d3d, L"bin/data/Background/GG.dds", Vector2(0, 0), true);

	initials.createText(d3d, L"Initials: ", Vector2(390, 320));
	input.createText(d3d, L"", Vector2(590, 320));

	submitBtn.createButtonFromLua(d3d, LuaGetBasicSpriteInfo(GameManager::Get().ls_textures, "submitButton"), Vector2(800, 360));
	restartBtn.createButtonFromLua(d3d, LuaGetBasicSpriteInfo(GameManager::Get().ls_textures, "restartButton"), Vector2(640, 450));
	leaderboardBtn.createButtonFromLua(d3d, LuaGetBasicSpriteInfo(GameManager::Get().ls_textures, "leaderboardButton"), Vector2(640, 540));
	mmBtn.createButtonFromLua(d3d, LuaGetBasicSpriteInfo(GameManager::Get().ls_textures, "mainMenuButton"), Vector2(640, 630));

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