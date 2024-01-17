/*
 * Template Nintendo DS
 * May 2011
 */

#include <nds.h>
#include <fat.h>
#include "Screen.h"
#include "Controls.h"
#include "Audio.h"
#include "Score.h"

int main(void) {
	
    fatInitDefault();
    consoleDemoInit();
    setGameMode(MAIN_MENU);
    //readHighScore();
    
    setupGame();

    configureAudio();

    while(1) {
        checkControls();
        //updateSprites();
        //swiWaitForVBlank();
        //oamUpdate(&oamMain);
    }
}
