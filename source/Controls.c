#include "Controls.h"
#include "Audio.h"
#include "Screen.h"
#include "Timer.h"
#include "Score.h"
#include "OrangeCat.h"
#include "GameMap.h"

#define BG_SIZE 8192

int POS_X = 112, POS_Y = 128; // start position at: Bottom x / Middle y
static u16 *gfxCat;

static int background_count = 0;

struct Position getCatPos() {
  struct Position pos = {POS_X, POS_Y};
  return pos;
}

void checkControls() {
	int i;
	/*for (i = 0; i < 10; i++) {
		swiWaitForVBlank();
	}*/
  gfxCat = getGfxCat();
  touchpadHandler();

  // Read keys
  scanKeys();
  GameMode mode = getGameMode();
  u16 keys = keysDown();

  switch(mode) {
    case MAIN_MENU:
      if (keys & KEY_START) {
        setCatColor(ORANGE);
        setGameMode(NORMAL_GAME);
      } else if (keys & KEY_X) {
        setGameMode(CHANGE_CAT);
      }
      break;
    case CHANGE_CAT:
      break;
    case NORMAL_GAME:
      // Modify position of the sprite accordingly
      if ((keys & KEY_RIGHT) && (POS_X < (240 - 32)))
        goingRight();

      //if ((keys & KEY_DOWN) && (POS_Y < (192 - 32)))
        //goingDown();

      if ((keys & KEY_LEFT) && (POS_X > 16))
        goingLeft();

      if ((keys & KEY_UP || keys & KEY_A) && (POS_Y > 0))
        goingUp();

      updateState();
      break;
    case NORMAL_GAME_OVER:
      updateState();
      break;
  }
}

void goingLeft() {
  resetTimer();
  playCatJumpEffect();
  dmaCopy(OrangeCatTiles +256, gfxCat, OrangeCatTilesLen/5);

  int count = 0;
  while (count < 32) {
    POS_X -= 4;
    count += 4;
    updateState();
  }

  dmaCopy(OrangeCatTiles, gfxCat, OrangeCatTilesLen/5);
}

void goingRight() {
  resetTimer();
  playCatJumpEffect();
  dmaCopy(OrangeCatTiles +128, gfxCat, OrangeCatTilesLen/5);

  int count = 0;
  while (count < 32) {
    POS_X += 4;
    count += 4;
    updateState();
  }

  dmaCopy(OrangeCatTiles, gfxCat, OrangeCatTilesLen/5);
}

void goingDown() {
  resetTimer();
  playCatJumpEffect();
  POS_Y += 32;
}

void goingUp() {
  resetTimer();
  playCatJumpEffect();
	dmaCopy(OrangeCatTiles +384, gfxCat, OrangeCatTilesLen/5);

  int count = 0;
  u8 collisionDetected;
  while (count < 8) {
    updateState();
    int i;
    for (i = 5; i > 0; i--) {
    	dmaCopy(BG_GFX+((i-1)*BG_SIZE/2)+(count*BG_SIZE/8/2),
    			BG_GFX+(i*BG_SIZE/2)+(count*BG_SIZE/8/2),
    			BG_SIZE/8);
    }
    spritesGoDown();
    collisionDetected = checkCollision();
    count += 1;
  }
  // BG Generation
  createBackground();
  dmaCopy(OrangeCatTiles, gfxCat, OrangeCatTilesLen/5);
  incrementScore();
}

void createBackground() {
  if (background_count % 2 == 0) {
    generateBackground(0);          //generate road
  } else {
    if (background_count % 3 == 0) {
      generateBackground(1);        //generate grass 1
    } else if (background_count % 3 == 1) {
      generateBackground(2);        //generate rails
    } else {
      generateBackground(3);        //generate grass 2
    }
  }
  background_count += 1;
}

void generateBackground(int i) {
  if (i == 0) {                   //generate road
    dmaCopy(GameMapBitmap + 4096, BG_GFX, GameMapBitmapLen/8);
    addSprite();
  } else if (i == 1) {            //generate grass 1
    dmaCopy(GameMapBitmap, BG_GFX, GameMapBitmapLen/8);
  } else if (i == 2) {            //generate rails
    dmaCopy(GameMapBitmap + 6144, BG_GFX, GameMapBitmapLen/8);
  } else if ( i == 3) {           //generate grass 2
    dmaCopy(GameMapBitmap + 2048, BG_GFX, GameMapBitmapLen/8);
  }
}

void killCat() {
  stopTimer0();
  dmaCopy(OrangeCatTiles +512, gfxCat, OrangeCatTilesLen/5);
  setGameMode(NORMAL_GAME_OVER);
  stopMusic();
  playGameOverEffect();
  writeHighScore();
  reinitializeScore();
}

void touchpadHandler() {
  touchPosition touch;
	touchRead(&touch);

  GameMode mode = getGameMode();

  switch(mode) {
    case MAIN_MENU:
      if (touch.px || touch.py) {
        setCatColor(ORANGE);
        setGameMode(NORMAL_GAME);
      }
      break;
    case CHANGE_CAT:
      if (touch.px || touch.py) {
        if (touch.py > 48 && touch.py < 97) {
          if (touch.px > 46 && touch.px < 95) {                 //change color to orange
            setCatColor(ORANGE);
            setGameMode(NORMAL_GAME);
          } else if (touch.px > 159 && touch.px < 208) {        //change color to white
            setCatColor(WHITE);
            setGameMode(NORMAL_GAME);
          }
        } else if (touch.py > 125 && touch.py < 174) {
            if (touch.px > 46 && touch.px < 95) {               //change color to grey
              setCatColor(GREY);
              setGameMode(NORMAL_GAME);
            } else if (touch.px > 159 && touch.px < 208) {      //change color to black
              setCatColor(BLACK);
              setGameMode(NORMAL_GAME);
            }
        }
      }
      break;
    case NORMAL_GAME:
      if(touch.px || touch.py) {
        if(touch.px > 99 && touch.px < 155 && touch.py > 19 && touch.py < 75) {              //Go UP
          goingUp();
        } else if(touch.py > 115 && touch.py < 171) {           //Go LEFT or RIGHT
          if (touch.px > 43 && touch.px < 99 && (POS_X > 16)) {                 //Go LEFT 
            goingLeft();
          } else if (touch.px > 115 && touch.px < 221 && (POS_X < (240 - 32))) {        //Go RIGHT
            goingRight();
          }
        } else if((touch.px > 17 && touch.px < 39 && touch.py > 23 && touch.py < 53) || (touch.px > 119 && touch.px < 234 && touch.py > 0 && touch.py < 46) ||
                    (touch.py > 93 && touch.py < 114 && ((touch.px > 57 && touch.px < 82) || (touch.px > 172 && touch.px < 197)))) {  //Cat is touched
          playCatMeowEffect();
        }
      }
      break;
    case NORMAL_GAME_OVER:
      break;
  }

}

void updateState() {
	if (getGameMode() == NORMAL_GAME && checkCollision())
	    killCat();

	oamSet(&oamMain,                  // oam handler
		 0,                         // Number of sprite
		 POS_X, POS_Y,              // Coordinates
		 1,                         // Priority
		 0,                         // Palette to use
		 SpriteSize_32x32,          // Sprite size
		 SpriteColorFormat_16Color, // Color format
		 gfxCat,                    // Loaded graphic to display
		 -1,                        // Affine rotation to use (-1 none)
		 false,                     // Double size if rotating
		 false,                     // Hide this sprite
		 false, false,              // Horizontal or vertical flip
		 false                      // Mosaic
	);

	updateSprites();

	swiWaitForVBlank();
	oamUpdate(&oamMain);
}
