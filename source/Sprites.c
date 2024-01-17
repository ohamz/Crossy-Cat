#include "Sprites.h"
#include "Controls.h"

#include "TruckDelivery.h"
#include "Ambulance.h"
#include "BlueCar.h"
#include "RedCar.h"
#include "SportCar.h"

#define BIG_SPRITE_SIZE 1024
#define SMALL_SPRITE_SIZE 512

u16* availableGFX[5];
u16** spritesGFX;
SpriteSize* spritesSize;
struct Position* spritesPos;
u16* spritesPaletteIndex;
u8* spritesDirection;


u8 speed = 1;
size_t spritesNum = 0;
size_t carCount = 0;
size_t truckCount = 0;
size_t count = 0;

int counterForSpeed = 0;

void configureSprites() {
	// MODIFY THE USED SPRITE
	int i;
	for (i = 0; i < 2; i++) {
		availableGFX[i] = malloc(BIG_SPRITE_SIZE);
	}
	for (i = 2; i < 5; i++) {
		availableGFX[i] = malloc(SMALL_SPRITE_SIZE);
	}

	dmaCopy(TruckDeliveryTiles, availableGFX[0], TruckDeliveryTilesLen);
	dmaCopy(AmbulanceTiles, availableGFX[1], AmbulanceTilesLen);
	dmaCopy(BlueCarTiles, availableGFX[2], BlueCarTilesLen);
	dmaCopy(RedCarTiles, availableGFX[3], RedCarTilesLen);
	dmaCopy(SportCarTiles, availableGFX[4], SportCarTilesLen);

	dmaCopy(TruckDeliveryPal, &SPRITE_PALETTE[32], TruckDeliveryPalLen);
	dmaCopy(AmbulancePal, &SPRITE_PALETTE[48], AmbulancePalLen);
	dmaCopy(BlueCarPal, &SPRITE_PALETTE[64], BlueCarPalLen);
	dmaCopy(RedCarPal, &SPRITE_PALETTE[80], RedCarPalLen);
	dmaCopy(SportCarPal, &SPRITE_PALETTE[96], SportCarPalLen);


	spritesGFX = malloc(BIG_SPRITE_SIZE);
	spritesGFX[0] = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_16Color);
	dmaCopy(availableGFX[0], spritesGFX[spritesNum], BIG_SPRITE_SIZE);

	spritesSize = malloc(sizeof(SpriteSize));
	spritesSize[0] = SpriteSize_64x32;

	spritesPos = malloc(sizeof(struct Position));
	struct Position newPos = {-63, 32};
	spritesPos[0] = newPos;

	spritesPaletteIndex = malloc(sizeof(u16));
	spritesPaletteIndex[0] = 2;

	spritesDirection = malloc(sizeof(u8));
	spritesDirection[0] = 0;

	spritesNum++;
}

void addSprite() {
	if (count++ % 2 == 0) {
		addSprite_32x32(carCount++%3);
	}
	else {
		addSprite_64x32(truckCount++%2);
	}
	counterForSpeed += 1;
	if (counterForSpeed % 15 == 0) {
		speed += 1;
	}
}

void addSprite_64x32(u16 index) {
	u16** tempGFX = malloc(spritesNum*BIG_SPRITE_SIZE);
	memcpy(tempGFX, spritesGFX, spritesNum*sizeof(u16*));
	free(spritesGFX);
	spritesGFX = malloc((spritesNum+1)*sizeof(u16*));
	memcpy(spritesGFX+1, tempGFX, spritesNum*sizeof(u16*));
	spritesGFX[0] = oamAllocateGfx(&oamMain, SpriteSize_64x32, SpriteColorFormat_16Color);
	free(tempGFX);

	u16** tempSize = malloc(spritesNum*sizeof(SpriteSize));
	memcpy(tempSize, spritesSize, spritesNum*sizeof(SpriteSize));
	free(spritesSize);
	spritesSize = malloc((spritesNum+1)*sizeof(SpriteSize));
	memcpy(spritesSize+1, tempSize, spritesNum*sizeof(SpriteSize));
	spritesSize[0] = SpriteSize_64x32;
	free(tempSize);

	u16** tempPaletteIndex = malloc(spritesNum*sizeof(u16));
	memcpy(tempPaletteIndex, spritesPaletteIndex, spritesNum*sizeof(u16));
	free(spritesPaletteIndex);
	spritesPaletteIndex = malloc((spritesNum+1)*sizeof(u16));
	memcpy(spritesPaletteIndex+1, tempPaletteIndex, spritesNum*sizeof(u16));
	spritesPaletteIndex[0] = index+2;
	free(tempPaletteIndex);

	u8* tempDirection = malloc(spritesNum*sizeof(u8));
	memcpy(tempDirection, spritesDirection, spritesNum*sizeof(u8));
	free(spritesDirection);
	spritesDirection = malloc((spritesNum+1)*sizeof(u8));
	memcpy(spritesDirection+1, tempDirection, spritesNum*sizeof(u8));
	u8 dir = (count % 2 == 0 || count % 5 == 0) ? 0 : 1;
	spritesDirection[0] = dir;
	free(tempDirection);

	struct Position* tempPos = malloc(spritesNum*sizeof(struct Position));
	memcpy(tempPos, spritesPos, spritesNum*sizeof(struct Position));
	free(spritesPos);
	spritesPos = malloc((spritesNum+1)*sizeof(struct Position));
	memcpy(spritesPos+1, tempPos, spritesNum*sizeof(struct Position));
	struct Position pos = {-63, 0};
	struct Position posReverse = {255, 0};
	spritesPos[0] = (spritesDirection[0] == 0) ? pos : posReverse;
	free(tempPos);

	dmaCopy(availableGFX[index], spritesGFX[0], BIG_SPRITE_SIZE);
	spritesNum++;
}

void addSprite_32x32(u16 index) {
	u16** tempGFX = malloc(spritesNum*BIG_SPRITE_SIZE);
	memcpy(tempGFX, spritesGFX, spritesNum*sizeof(u16*));
	free(spritesGFX);
	spritesGFX = malloc((spritesNum+1)*sizeof(u16*));
	memcpy(spritesGFX+1, tempGFX, spritesNum*sizeof(u16*));
	spritesGFX[0] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);
	free(tempGFX);

	u16** tempSize = malloc(spritesNum*sizeof(SpriteSize));
	memcpy(tempSize, spritesSize, spritesNum*sizeof(SpriteSize));
	free(spritesSize);
	spritesSize = malloc((spritesNum+1)*sizeof(SpriteSize));
	memcpy(spritesSize+1, tempSize, spritesNum*sizeof(SpriteSize));
	spritesSize[0] = SpriteSize_32x32;
	free(tempSize);

	u16** tempPaletteIndex = malloc(spritesNum*sizeof(u16));
	memcpy(tempPaletteIndex, spritesPaletteIndex, spritesNum*sizeof(u16));
	free(spritesPaletteIndex);
	spritesPaletteIndex = malloc((spritesNum+1)*sizeof(u16));
	memcpy(spritesPaletteIndex+1, tempPaletteIndex, spritesNum*sizeof(u16));
	spritesPaletteIndex[0] = index+4;
	free(tempPaletteIndex);

	u8* tempDirection = malloc(spritesNum*sizeof(u8));
	memcpy(tempDirection, spritesDirection, spritesNum*sizeof(u8));
	free(spritesDirection);
	spritesDirection = malloc((spritesNum+1)*sizeof(u8));
	memcpy(spritesDirection+1, tempDirection, spritesNum*sizeof(u8));
	u8 dir = (count % 2 == 0 || count % 5 == 0) ? 0 : 1;
	spritesDirection[0] = dir;
	free(tempDirection);

	struct Position* tempPos = malloc(spritesNum*sizeof(struct Position));
	memcpy(tempPos, spritesPos, spritesNum*sizeof(struct Position));
	free(spritesPos);
	spritesPos = malloc((spritesNum+1)*sizeof(struct Position));
	memcpy(spritesPos+1, tempPos, spritesNum*sizeof(struct Position));
	struct Position pos = {-31, 0};
	struct Position posReverse = {255, 0};
	spritesPos[0] = (spritesDirection[0] == 0) ? pos : posReverse;
	free(tempPos);

	dmaCopy(availableGFX[index+2], spritesGFX[0], SMALL_SPRITE_SIZE);
	spritesNum++;
}

void updateSprites() {
	int i;
	for (i = 0; i < spritesNum; i++) {
		if (spritesDirection[i] == 0) {
			spritesPos[i].x += speed;
			if (spritesPos[i].x >= 256)
				spritesPos[i].x = (spritesSize[i] == SpriteSize_64x32) ? -63 : -31;

			oamSet(&oamMain, 	// oam handler
				i+4,				// Number of sprite
				spritesPos[i].x, spritesPos[i].y,			// Coordinates
				0,				// Priority
				spritesPaletteIndex[i],				// Palette to use
				spritesSize[i],			// Sprite size
				SpriteColorFormat_16Color,	// Color format
				spritesGFX[i],			// Loaded graphic to display
				-1,				// Affine rotation to use (-1 none)
				false,			// Double size if rotating
				false,			// Hide this sprite
				false, false,	// Horizontal or vertical flip
				false			// Mosaic
			);
		} else {
			spritesPos[i].x -= speed;
			if (spritesPos[i].x <= -64) spritesPos[i].x = 255;

			oamSet(&oamMain, 	// oam handler
				i+4,				// Number of sprite
				spritesPos[i].x, spritesPos[i].y,			// Coordinates
				0,				// Priority
				spritesPaletteIndex[i],				// Palette to use
				spritesSize[i],			// Sprite size
				SpriteColorFormat_16Color,	// Color format
				spritesGFX[i],			// Loaded graphic to display
				-1,				// Affine rotation to use (-1 none)
				false,			// Double size if rotating
				false,			// Hide this sprite
				true, false,	// Horizontal or vertical flip
				false			// Mosaic
			);
		}
	}
}

void removeSprite() {
	oamFreeGfx(&oamMain, spritesGFX[spritesNum-1]);
/*
	u16** tempGFX = malloc(spritesNum*BIG_SPRITE_SIZE);
	memcpy(tempGFX, spritesGFX, spritesNum*sizeof(u16*));
	free(spritesGFX);
	spritesGFX = malloc((spritesNum-1)*sizeof(u16*));
	memcpy(spritesGFX, tempGFX, (spritesNum-1)*sizeof(u16*));
	free(tempGFX);

	u16** tempSize = malloc(spritesNum*sizeof(SpriteSize));
	memcpy(tempSize, spritesSize, spritesNum*sizeof(SpriteSize));
	free(spritesSize);
	spritesSize = malloc((spritesNum-1)*sizeof(SpriteSize));
	memcpy(spritesSize+1, tempSize, (spritesNum-1)*sizeof(SpriteSize));
	free(tempSize);

	u16** tempPaletteIndex = malloc(spritesNum*sizeof(u16));
	memcpy(tempPaletteIndex, spritesPaletteIndex, spritesNum*sizeof(u16));
	free(spritesPaletteIndex);
	spritesPaletteIndex = malloc((spritesNum-1)*sizeof(u16));
	memcpy(spritesPaletteIndex+1, tempPaletteIndex, (spritesNum-1)*sizeof(u16));
	free(tempPaletteIndex);

	u8* tempDirection = malloc(spritesNum*sizeof(u8));
	memcpy(tempDirection, spritesDirection, spritesNum*sizeof(u8));
	free(spritesDirection);
	spritesDirection = malloc((spritesNum-1)*sizeof(u8));
	memcpy(spritesDirection+1, tempDirection, (spritesNum-1)*sizeof(u8));
	free(tempDirection);

	struct Position* tempPos = malloc(spritesNum*sizeof(struct Position));
	memcpy(tempPos, spritesPos, spritesNum*sizeof(struct Position));
	free(spritesPos);
	spritesPos = malloc((spritesNum-1)*sizeof(struct Position));
	memcpy(spritesPos+1, tempPos, (spritesNum-1)*sizeof(struct Position));
	free(tempPos);
*/
	spritesNum--;
}

u8 checkCollision() {
	struct Position catPos = getCatPos();

	int i;
	for (i = 0; i < spritesNum; i++) {
		if (spritesPos[i].y == catPos.y) {
			switch (spritesSize[i]) {
				case SpriteSize_64x32:
					if (spritesPos[i].x +64-8 >= catPos.x && spritesPos[i].x <= catPos.x +32-8)
						return 1;
					break;
				case SpriteSize_32x32:
					if (spritesPos[i].x +32-8 >= catPos.x && spritesPos[i].x <= catPos.x +32-8)
						return 1;
					break;
				default:
					break;
			}
		}
	}
	return 0;
}

void spritesGoDown() {
	int i;
	for (i = 0; i < spritesNum; i++) {
		spritesPos[i].y += 4;
		if (spritesPos[i].y == 224) {
			removeSprite();
		}
	}
}

