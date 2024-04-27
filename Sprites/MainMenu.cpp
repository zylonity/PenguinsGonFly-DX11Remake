#include "MainMenu.h"
#include "GameManager.h"
const std::string MainMenu::MODE_NAME = "MENU";
MainMenu::MainMenu(MyD3D& d3d)
{
	DDS_ALPHA_MODE alpha;

	bgScale = LuaGetFloat(GameManager::Get().ls_textures, "backgroundsScale");

	isActive = true;

	//Add background
	background.push_back(Sprite::Sprite());
	background[0].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "mm_background0"));
	background[0].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(100);

	background.push_back(Sprite::Sprite());
	background[1].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "mm_background1"));
	background[1].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(110);

	background.push_back(Sprite::Sprite());
	background[2].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "mm_background2"));
	background[2].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(140);

	background.push_back(Sprite::Sprite());
	background[3].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "mm_background3"));
	background[3].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(170);

	background.push_back(Sprite::Sprite());
	background[4].createSpriteFromLua(d3d, LuaGetSpriteInfo(GameManager::Get().ls_textures, "mm_background4"));
	background[4].sprRect.right *= 2;
	bgTimers.push_back(0);
	scrollSpeeds.push_back(200);

	startBtn.createSprite(d3d, L"bin/data/Buttons/StartButton1.dds", Vector2(640, 450), true, 3);
	leaderBtn.createSprite(d3d, L"bin/data/Buttons/leaderboard.dds", Vector2(640, 540), true, 3);
	quitBtn.createSprite(d3d, L"bin/data/Buttons/quitbutton.dds", Vector2(640, 630), true, 3);


	startBtn.setHitbox();
	quitBtn.setHitbox();
	leaderBtn.setHitbox();

	muteBtn.createSprite(d3d, L"bin/data/Buttons/loud.dds", Vector2(1222, 670), true, 3);


	muteBtn.setHitbox();


	logo.createSprite(d3d, L"bin/data/dds/msai.dds", Vector2(540, 140), true, 2.5f);
	logo.pos = Vector2(logo.pos.x - logo.texSize.x / 2, logo.pos.y - logo.texSize.y / 2);


	//3D Stuff
	birdScale = 0.08f;
	m_states = std::make_unique<CommonStates>(&d3d.GetDevice());
	m_fxFactory = std::make_unique<EffectFactory>(&d3d.GetDevice());
	m_model = Model::CreateFromCMO(&d3d.GetDevice(), L"bin/data/3D/3d_bird.cmo", *m_fxFactory);
	m_world = Matrix::Identity;
	m_view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f),
		Vector3::Zero, Vector3::UnitY);
	m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		1280.f / 720.f, 0.1f, 10.f);

	pAudio = &GameManager::Get().audio;
}

void MainMenu::Update(float dTime, MyD3D& d3d, std::unique_ptr<DirectX::Keyboard>& m_keyboard, std::unique_ptr<DirectX::Mouse>& m_mouse)
{


	//Set the position and scale of the bird
	m_world = Matrix::CreateRotationY(300.f) * Matrix::CreateScale(birdScale, birdScale, birdScale) * Matrix::CreateTranslation(-0.6f, 0.2f, 0);


	if (startBtn.HandleClick(m_mouse, "GAME")) {
		pAudio->GetSongMgr()->Stop();
		pAudio->GetSongMgr()->Play("game", true, false, &GameManager::Get().musicHdl, GameManager::Get().music_volume);
	}
	quitBtn.HandleClick(m_mouse, "QUIT");
	leaderBtn.HandleClick(m_mouse, "LEADER");

	if (!pAudio->GetSongMgr()->IsPlaying(GameManager::Get().musicHdl))
		pAudio->GetSongMgr()->Play("menu", true, false, &GameManager::Get().musicHdl, GameManager::Get().music_volume);

	pAudio->GetSongMgr()->Mute(GameManager::Get().music_mute);


	muteBtn.HandleClick(m_mouse, "MUTE");
	
	



}

void MainMenu::Render(float dTime, MyD3D& d3d)
{
	WinUtil& wu = WinUtil::Get();


	d3d.BeginRender(Vector4(0, 0, 0, 0));

	//Rendering depends on the order these go in:
	//put background to render here
	if (background.empty() == false) {
		for (int i = 0; i < background.size(); i++) {
			background[i].RenderSprite();
		}
	}

	startBtn.RenderSprite();
	quitBtn.RenderSprite();
	leaderBtn.RenderSprite();
	m_model->Draw(&d3d.GetDeviceCtx(), *m_states, m_world, m_view, m_proj); //3D bird
	logo.RenderSprite();

	muteBtn.RenderSprite();
	
	

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

void MainMenu::ResetMenu() {
	if (background.empty() == false) {
		for (int i = 0; i < background.size(); i++) {
			background[i].pos = Vector2(0,0);
		}
	}
	isActive = true;
}

std::string MainMenu::GetMName() const {

	return MODE_NAME;
}