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
--Main Menu
mm_background0 = background0
mm_background1 = background1
mm_background2 = background2
mm_background3 = background3
mm_background4 = background4
--Leaderboard
lb_background0 = background0
lb_background1 = background1
lb_background2 = background2
lb_background3 = background3
lb_background4 = background4


-- Player Sprite
player = {TexLoc = "bin/data/Entities/birdneutralsprite.dds", PosX = 200, PosY = 100, IsAlpha = true, Scale = 5, IsAnim = true, NumSprites = 5, AnimSpeed = 10}