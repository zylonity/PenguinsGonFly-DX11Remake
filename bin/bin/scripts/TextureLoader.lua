--Define the sprites from lua!
--TexLoc: String with the location of the texture
--PosX, PosY: Floats with the starting X and Y position
--IsAlpha: Boolean if the texture has transparency
--Scale: Float with the initial scale of the texture
--IsAnim: Boolean if the texture is animated
--NumSprites: Integer with the number of sprites in the texture
--AnimSpeed: Float with the speed of the animation


-- Background Scale
backgroundsScale = 6;

-- Background Sprites
--Game
background0 = {TexLoc = "bin/data/Background/sky.dds", PosX = 0, PosY = 0, IsAlpha = false, Scale = backgroundsScale, IsAnim = false, NumSprites = 0, AnimSpeed = 0}
background1 = {TexLoc = "bin/data/Background/TinyCloud5.dds", PosX = 0, PosY = 0, IsAlpha = true, Scale = backgroundsScale, IsAnim = false, NumSprites = 0, AnimSpeed = 0}
background2 = {TexLoc = "bin/data/Background/SmallCloud3.dds", PosX = 0, PosY = 0, IsAlpha = true, Scale = backgroundsScale, IsAnim = false, NumSprites = 0, AnimSpeed = 0}
background3 = {TexLoc = "bin/data/Background/MedCloud5.dds", PosX = 0, PosY = 0, IsAlpha = true, Scale = backgroundsScale, IsAnim = false, NumSprites = 0, AnimSpeed = 0}
background4 = {TexLoc = "bin/data/Background/BigCloud3.dds", PosX = 0, PosY = 0, IsAlpha = true, Scale = backgroundsScale, IsAnim = false, NumSprites = 0, AnimSpeed = 0}
-- Background scroll speeds
bg0scrollspeed = 100
bg1scrollspeed = 110
bg2scrollspeed = 140
bg3scrollspeed = 170
bg4scrollspeed = 200

--Main Menu
mm_background0 = background0
mm_background1 = background1
mm_background2 = background2
mm_background3 = background3
mm_background4 = background4
-- Background scroll speeds
mm_bg0scrollspeed = bg0scrollspeed
mm_bg1scrollspeed = bg1scrollspeed
mm_bg2scrollspeed = bg2scrollspeed
mm_bg3scrollspeed = bg3scrollspeed
mm_bg4scrollspeed = bg4scrollspeed

--Leaderboard
lb_background0 = background0
lb_background1 = background1
lb_background2 = background2
lb_background3 = background3
lb_background4 = background4
-- Background scroll speeds
lb_bg0scrollspeed = bg0scrollspeed
lb_bg1scrollspeed = bg1scrollspeed
lb_bg2scrollspeed = bg2scrollspeed
lb_bg3scrollspeed = bg3scrollspeed
lb_bg4scrollspeed = bg4scrollspeed

--Game over
gmo_background0 = background0
gmo_background1 = background1
gmo_background2 = background2
gmo_background3 = background3
gmo_background4 = background4
gmo_redHue = {TexLoc = "bin/data/Background/dead.dds", PosX = 0, PosY = 0, IsAlpha = true, Scale = 1, IsAnim = false, NumSprites = 0, AnimSpeed = 0}
-- Background scroll speeds
gmo_bg0scrollspeed = bg0scrollspeed
gmo_bg1scrollspeed = bg1scrollspeed
gmo_bg2scrollspeed = bg2scrollspeed
gmo_bg3scrollspeed = bg3scrollspeed
gmo_bg4scrollspeed = bg4scrollspeed



-- Player Sprite
player = {TexLoc = "bin/data/Entities/birdneutralsprite.dds", PosX = 200, PosY = 100, IsAlpha = true, Scale = 5, IsAnim = true, NumSprites = 5, AnimSpeed = 10}


-- Button textures!
-- TexLoc: String with the location of the texture
-- Scale: Float with the initial scale of the texture
-- The game will handle positions and other data
startButton = {TexLoc = "bin/data/Buttons/StartButton1.dds", Scale = 3}
leaderboardButton = {TexLoc = "bin/data/Buttons/leaderboard.dds", Scale = 3}
quitButton = {TexLoc = "bin/data/Buttons/quitbutton.dds", Scale = 3}
muteButton = {TexLoc = "bin/data/Buttons/loud.dds", Scale = 3}
mainMenuButton = {TexLoc = "bin/data/Buttons/mainmenu1.dds", Scale = 3} 
restartButton = {TexLoc = "bin/data/Buttons/restart.dds", Scale = 3} 
submitButton = {TexLoc = "bin/data/Buttons/submit.dds", Scale = 3} 

-- Logo texture
logo = {TexLoc = "bin/data/dds/msai.dds", Scale = 2.5}