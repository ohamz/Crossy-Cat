#include <nds.h>

/* Method that initializes the sprites that handle the Highscore */
void initializeScore();

/* Method that increments the score of the player every time the cat moves up during the game */
void incrementScore();


/* Method that reads the highscore value that is stored in the file "CrossyCatrecord.txt" */
void readHighScore();

/* Method that stores the highscore value in the file "CrossyCatrecord.txt" from the local variable  */
void writeHighScore();

/* Method that displays the score during the game */
void displayScore();

/* Method that displays the highscore on the main menu */
void displayHighScore();

/* Method that stores the values to be displayed in the game in the memory of the sprites */
void refreshDisplay();

/* Method that stores the values to be displayed in the main menu in the memory of the sprites */
void refreshDisplayHighscore();
