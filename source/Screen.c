
#include "Screen.h"
#include "Sprites.h"
#include "Audio.h"
#include "Timer.h"

#include "OrangeCat.h"
#include "WhiteCat.h"
#include "BlackCat.h"
#include "GreyCat.h"
#include "Controls_SUB.h"
#include "GameMap.h"
#include "MainMenu.h"
#include "MainMenuSUB.h"
#include "ChooseYourCat.h"
#include "ChooseYourCatSub.h"

u8 GreenTile[64] = {1};
static u16 *gfxCat;
static GameMode gamemode;
static CatColor color;

void setupGame() {
	//setup the main background to Extended Rotoscale Mode
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;
	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;

	configureMainScreen();

	//setup the sub background to Extended Rotoscale
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	configureSubScreen();

	fillMainScreen();
	fillSubScreen();
}

void configureMainScreen() {
	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256 | BG_PRIORITY(2);
	BGCTRL[3] = BG_BMP_BASE(5) | BgSize_B8_256x256 | BG_PRIORITY(1);

    REG_BG2PA = 1 << 8;
	REG_BG2PB = 0;
	REG_BG2PC = 0;
	REG_BG2PD = 1 << 8;

	REG_BG3PA = 1 << 8;
	REG_BG3PB = 0;
	REG_BG3PC = 0;
	REG_BG3PD = 1 << 8;
}

void configureSubScreen() {
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

    REG_BG2PA_SUB = 1 << 8;
	REG_BG2PB_SUB = 0;
	REG_BG2PC_SUB = 0;
	REG_BG2PD_SUB = 1 << 8;
}

void fillMainScreen() {
	switch(gamemode) {
		case MAIN_MENU:
			dmaCopy(MainMenuBitmap, BG_BMP_RAM(0), MainMenuBitmapLen);
    		dmaCopy(MainMenuPal, BG_PALETTE, MainMenuPalLen);
			playMainMenuMusic();
			break;
		case CHANGE_CAT:
			dmaCopy(ChooseYourCatBitmap, BG_BMP_RAM(0), ChooseYourCatBitmapLen);
    		dmaCopy(ChooseYourCatPal, BG_PALETTE, ChooseYourCatPalLen);
			break;
		case NORMAL_GAME:
			fillNormalGameScreen();
			createCatSprite();
			initializeScore();
			configureSprites();
			stopMusic();
			playGameplayMusic();
			break;
		case NORMAL_GAME_OVER:
			dmaCopy(GameMapBitmap+8192, BG_MAP_RAM(5), GameMapBitmapLen/2);
    		break;
	}

}

void fillNormalGameScreen() {
	int i;
	for (i = 0; i < 6; i+=3) {
		dmaCopy(GameMapBitmap,BG_GFX+(i*GameMapBitmapLen/8/2), GameMapBitmapLen/8);
		dmaCopy(GameMapBitmap+2048,BG_GFX+((i+2)*GameMapBitmapLen/8/2), GameMapBitmapLen/8);
	}

	for (i = 1; i < 6; i+=3) {
		dmaCopy(GameMapBitmap+4096,BG_GFX+(i*GameMapBitmapLen/8/2), GameMapBitmapLen/8);
	}
	dmaCopy(GameMapPal, BG_PALETTE, GameMapPalLen);
}

void createCatSprite() {
	// Set up memory bank to work in sprite mode (offset since we are using VRAM A for backgrounds)
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	// Initialize sprite manager and the engine
	oamInit(&oamMain, SpriteMapping_1D_64, false);

	// Allocate space for the graphic to show in the sprite
	gfxCat = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);

	dmaCopy(OrangeCatTiles, gfxCat, OrangeCatTilesLen/5);
	switch(color) {
		case ORANGE:
			dmaCopy(OrangeCatPal, SPRITE_PALETTE, OrangeCatPalLen);
			break;
		case WHITE:
			dmaCopy(WhiteCatPal, SPRITE_PALETTE, WhiteCatPalLen);
			break;
		case BLACK:
			dmaCopy(BlackCatPal, SPRITE_PALETTE, BlackCatPalLen);
			break;
		case GREY:
			dmaCopy(GreyCatPal, SPRITE_PALETTE, GreyCatPalLen);
			break;
	}
}

void fillSubScreen() {
	switch(gamemode) {
		case MAIN_MENU:
			dmaCopy(MainMenuSUBBitmap, BG_BMP_RAM_SUB(0), MainMenuSUBBitmapLen);
    		dmaCopy(MainMenuSUBPal, BG_PALETTE_SUB, MainMenuSUBPalLen);
			break;
		case CHANGE_CAT:
			dmaCopy(ChooseYourCatSubBitmap, BG_BMP_RAM_SUB(0), ChooseYourCatSubBitmapLen);
    		dmaCopy(ChooseYourCatSubPal, BG_PALETTE_SUB, ChooseYourCatSubPalLen);
			break;
		case NORMAL_GAME:
			dmaCopy(Controls_SUBBitmap, BG_BMP_RAM_SUB(0), Controls_SUBBitmapLen);
    		dmaCopy(Controls_SUBPal, BG_PALETTE_SUB, Controls_SUBPalLen);
			break;
		case NORMAL_GAME_OVER:
    		break;
	}
}


u16* getGfxCat() {
	return gfxCat;
}

GameMode getGameMode() {
	return gamemode;
}

void setGameMode(GameMode mode) {
	gamemode = mode;
	fillMainScreen();
	fillSubScreen();
	if (mode == NORMAL_GAME) {
		setTimer0();
	}
}

void setCatColor(CatColor c) {
	color = c;
}
