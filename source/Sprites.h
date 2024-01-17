#ifndef SPRITES_H_
#define SPRITES_H_

#include <nds.h>
#include <string.h>

/* Structure that represents position of a sprite */
struct Position {
  int x;
  int y;
};

/* Initialize requirements for sprites, and add first Truck */
void configureSprites();

/* Add a new sprite at top of screen */
void addSprite();

/* Choose to add 64x32 sprite in addSprite() (Truck) */
void addSprite_64x32(u16 index);

/* Choose to add 32x32 sprite in addSprite() (Cat) */
void addSprite_32x32(u16 index);

/* Remove sprite when it goes out of screen (bottom) */
void removeSprite();

/* Check for collisions between sprites and Cat */
u8 checkCollision();

/* Display the new state of all sprites */
void updateSprites();

/* All sprites go down when Cat goes up */
void spritesGoDown();


#endif
