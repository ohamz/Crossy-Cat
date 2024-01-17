#include <nds.h>
#include <stdio.h>

#define GREEN ARGB16(1,0,20,0)

/* enum that represents Game Mode */
typedef enum {
    MAIN_MENU = 0,
    CHANGE_CAT = 1,
    NORMAL_GAME = 2,
    NORMAL_GAME_OVER = 3
} GameMode;

/* enum that represents Cat Color*/
typedef enum {
    ORANGE = 0,
    WHITE = 1,
    BLACK = 2,
    GREY = 3
} CatColor;

/* Creates and enables the backgrounds and VRAMs */
void setupGame();

/* Configure backgrounds in Main engine */
void configureMainScreen();

/* Configure backgrounds in Sub engine */
void configureSubScreen();

/* Display background on Main engine with respect to current Game Mode */
void fillMainScreen();

/* Display background with respect to Game Mode */
void fillNormalGameScreen();

/* Initialize the main sprite (Cat) */
void createCatSprite();

/* Display background on Sub engine with respect to current Game Mode */
void fillSubScreen();

/* Getter for Cat GFX */
u16* getGfxCat();

/* Getter for Game Mode */
GameMode getGameMode();

/* Setter for Game Mode */
void setGameMode(GameMode mode);

/* Setter for Cat Color */
void setCatColor(CatColor c);
