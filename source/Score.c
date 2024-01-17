
#include <stdio.h>
#include "Score.h"
#include "Screen.h"

#include "Numbers.h"

static int score = 0;
static int highscore = 0;

static u16** displayGfx;

void initializeScore() {
	u16* digit1 = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_16Color);
    u16* digit2 = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_16Color);
    u16* digit3 = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_16Color);

    dmaCopy(NumbersTiles, digit1, NumbersTilesLen / 5);
    dmaCopy(NumbersTiles, digit2, NumbersTilesLen / 5);
    dmaCopy(NumbersTiles, digit3, NumbersTilesLen / 5);

    dmaCopy(NumbersPal, &SPRITE_PALETTE[16], NumbersPalLen);

    int i;
    for (i = 0; i < 3; ++i) {
        displayGfx[i] = malloc(256);
    }
    
    displayGfx[0] = digit1;
    displayGfx[1] = digit2;
    displayGfx[2] = digit3;
    
    displayScore();
}

void incrementScore() {
    score += 1;

    if (score > highscore) {
        highscore = score;
    }
    displayScore();
}

void reinitializeScore() {
    score = 0;
}

void readHighScore() {
    //Open the file in read mode
    FILE* file = fopen("/CrossyCatrecord.txt", "r");
	if(file != NULL) {
		//Read the value and put it into the variable max_score
		fscanf(file,"%i\n",&highscore);
		// close the file
		fclose(file);
	}
}

void writeHighScore() {
    //Open the file in write mode to overwrite
	FILE* file = fopen("/CrossyCatrecord.txt", "w+");
	if(file != NULL) {
		//Print the value in the file
		fprintf(file, "%i\n", highscore);
		//Close the file
		fclose(file);
	}
    //printf("Score: %d\n", score);
    //printf("Highscore : %d\n", highscore);
}

void displayScore() {
    if (getGameMode() != NORMAL_GAME) return;
    int d1, d2, d3 = 0;
    d1 = score % 10;
    d2 = (score / 10) % 10;
    d3 = (score / 100) % 10;

    dmaCopy(NumbersTiles + d1 * 32, displayGfx[2], NumbersPalLen / 5);
    dmaCopy(NumbersTiles + d2 * 32, displayGfx[1], NumbersPalLen / 5);
    dmaCopy(NumbersTiles + d3 * 32, displayGfx[0], NumbersPalLen / 5);

    refreshDisplay();
}

void displayHighScore() {
    if (getGameMode() != MAIN_MENU) return;
    int d1, d2, d3 = 0;
    d1 = score % 10;
    d2 = (score / 10) % 10;
    d3 = (score / 100) % 10;

    dmaCopy(NumbersTiles + d1 * 256, displayGfx[2], NumbersPalLen / 5);
    dmaCopy(NumbersTiles + d2 * 256, displayGfx[1], NumbersPalLen / 5);
    dmaCopy(NumbersTiles + d3 * 256, displayGfx[0], NumbersPalLen / 5);

    refreshDisplayHighscore();
}

void refreshDisplay() {
	int i;
    for (i = 0; i < 3; ++i) {
        oamSet(&oamMain, 	// oam handler
			i + 1,				// Number of sprite
			i * 16 + 5, 5,			// Coordinates
			0,				// Priority
			1,				// Palette to use
			SpriteSize_16x16,			// Sprite size
			SpriteColorFormat_16Color,	// Color format
			displayGfx[i],			// Loaded graphic to display
			-1,				// Affine rotation to use (-1 none)
			false,			// Double size if rotating
			false,			// Hide this sprite
			false, false,	// Horizontal or vertical flip
			false			// Mosaic
		);
    }
}

void refreshDisplayHighscore() {
    int i;
    for (i = 0; i < 3; ++i) {
        oamSet(&oamMain, 	// oam handler
			i + 1,				// Number of sprite
			i * 16 + 196, 6,			// Coordinates
			0,				// Priority
			1,				// Palette to use
			SpriteSize_16x16,			// Sprite size
			SpriteColorFormat_16Color,	// Color format
			displayGfx[i],			// Loaded graphic to display
			-1,				// Affine rotation to use (-1 none)
			false,			// Double size if rotating
			false,			// Hide this sprite
			false, false,	// Horizontal or vertical flip
			false			// Mosaic
		);
    }
}
