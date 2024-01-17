#include <nds.h>
#include "Sprites.h"

/* Struct that stores the X and Y positions of the cat and returns them when needed */
struct Position getCatPos();


/*
 * Method that checks the inputs of the Keypad of the NDS and
 * changes the state of the Sprites and Backgrounds accordingly
 */
void checkControls();

/* Method that changes the coordinates and display of the cat when it goes left */
void goingLeft();

/* Method that changes the coordinates and display of the cat when it goes right */
void goingRight();

/* Method that changes the coordinates and display of the cat when it goes up */
void goingUp();

/* Method that changes the display of the cat when it dies, as well as
 * trigerring sound effects, and changing the general state of the game
 */
void killCat();

/* Method that handles the inputs of the touchpad of the NDS according to the state of the game */
void touchpadHandler();

/* Helper function that helps create the top layer of the background when the cat goes up */
void createBackground();

/* Helper function that choooses what background to add, and adds it with its sprite if applies */
void generateBackground(int i);

/* Method that updates the state of the cat after every movement */
void updateState();
