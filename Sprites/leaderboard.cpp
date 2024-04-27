#include "leaderboard.h"
#include <algorithm>
const std::string Leaderboard::MODE_NAME = "LEADER";
Leaderboard::Leaderboard(MyD3D& d3d)
{
	DDS_ALPHA_MODE alpha;

	bgScale = LuaGetFloat(GameManager::Get().ls_textures, "backgroundsScale");

	//Add background
	background.push_back(Sprite::Sprite());
	background[0].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "lb_background0"));
	background[0].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(100);

	background.push_back(Sprite::Sprite());
	background[1].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "lb_background1"));
	background[1].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(110);

	background.push_back(Sprite::Sprite());
	background[2].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "lb_background2"));
	background[2].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(140);

	background.push_back(Sprite::Sprite());
	background[3].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "lb_background3"));
	background[3].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(170);

	background.push_back(Sprite::Sprite());
	background[4].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "lb_background4"));
	background[4].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(200);

	quitBtn.createSprite(d3d, L"bin/data/Buttons/quitbutton.dds", Vector2(1160, 630), true, 3);
	mmBtn.createSprite(d3d, L"bin/data/Buttons/mainmenu1.dds", Vector2(150, 630), true, 3);

	title.createText(d3d, L"LEADERBOARD", Vector2(460, 0));

	
	sortingNums = true;

	for (int i = 1; i <= 10; i++) {
		positions[i - 1].createText(d3d, std::to_wstring(i), Vector2(430, 0 + (i * 60)));
		namestxt[i - 1].createText(d3d, L"ABC", Vector2(600, 0 + (i * 60)));
		scorestxt[i - 1].createText(d3d, L"000", Vector2(780, 0 + (i * 60)));
	}

	//Take every user and score out of the csv file and into an array
	scores.open("leaderboard.csv");

	wstring num = L"";
	wstring name = L"";
	wstring line;
	while (getline(scores, line)) {
		num = L"";
		name = L"";
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ',') {
				sortingNums = false;
			}
			else {
				if (sortingNums) {
					num += line[i];
				}
				else {
					name += line[i];
				}
				
			}

		}
		sortingNums = true;

		GameManager::Get().userScores.push_back(stoi(num));
		GameManager::Get().userNames.push_back(name);

	}
	scores.close();


	//Sort the array
	if (GameManager::Get().userNames.size() > 0) {
		for (int j = 0; j < GameManager::Get().userNames.size() - 1; j++) {
			for (int i = 0; i < GameManager::Get().userScores.size(); i++) {
				if (i != GameManager::Get().userScores.size() - 1) {
					if (GameManager::Get().userScores[i] < GameManager::Get().userScores[i + 1]) {
						swap(GameManager::Get().userScores[i], GameManager::Get().userScores[i + 1]);
						swap(GameManager::Get().userNames[i], GameManager::Get().userNames[i + 1]);
					}
				}

			}
		}
	}
	

	


	quitBtn.setHitbox();
	mmBtn.setHitbox();

}

void Leaderboard::Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse)
{
	//Update the text on screen with array
	//TODO: I don't need to run this every frame, try call it when switching to leaderboard screen somehow
	for (int i = 0; i < 10; i++) {
		if (i >= GameManager::Get().userNames.size()) {
			continue;
		}
		else {
			namestxt[i].changeText(GameManager::Get().userNames[i]);
			scorestxt[i].changeText(to_wstring(GameManager::Get().userScores[i]));
		}
	}

	quitBtn.HandleClick(m_mouse, "QUIT");

	if(mmBtn.HandleClick(m_mouse, "MENU"))
		ResetScreen();

}

void Leaderboard::Render(float dTime, MyD3D& d3d)
{
	WinUtil& wu = WinUtil::Get();


	d3d.BeginRender(Vector4(0, 0, 0, 0));

	//put background to render here
	if (background.empty() == false) {
		for (int i = 0; i < background.size(); i++) {
			background[i].RenderSprite();
		}
	}

	title.write();
	
	for (int i = 0; i < 10; i++) {
		positions[i].write();
		namestxt[i].write();
		scorestxt[i].write();
	}

	quitBtn.RenderSprite();
	mmBtn.RenderSprite();

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

void Leaderboard::ResetScreen() {
	

	for (int i = 0; i < background.size(); i++) {
		background[i].pos = Vector2(0, 0);
	}

}

std::string Leaderboard::GetMName() const {

	return MODE_NAME;
}