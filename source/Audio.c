#include "Audio.h"

#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"

void configureAudio() {

    //Init the sound library
	mmInitDefaultMem((mm_addr)soundbank_bin);

    //Load module Main Menu Music
	mmLoad(MOD_MAINMENUMUSIC);

    //Load module Gameplay Music
	mmLoad(MOD_GAMEPLAYMUSIC);

    //Load effect Cat Jump
    mmLoadEffect(SFX_CATJUMP);

    //Load effect Game Over
    mmLoadEffect(SFX_GAMEOVER);

    //Load effect New High Score
    mmLoadEffect(SFX_NEWHIGHSCORE);

    //Load effect Cat Meow
    mmLoadEffect(SFX_CATMEOW);

    playMainMenuMusic();
}

void playMainMenuMusic() {
    mmStart(MOD_MAINMENUMUSIC, MM_PLAY_LOOP);
    mmSetModuleVolume(1024);
}

void playGameplayMusic() {
    mmStart(MOD_GAMEPLAYMUSIC, MM_PLAY_LOOP);
    mmSetModuleVolume(1014);
}

void playCatJumpEffect() {
    mmEffect(SFX_CATJUMP);
}

void playGameOverEffect() {
    mmEffect(SFX_GAMEOVER);
}

void playNewHighScoreEffect() {
    mmEffect(SFX_NEWHIGHSCORE);
}

void playCatMeowEffect() {
    mmEffect(SFX_CATMEOW);
}

void stopMusic() {
    mmStop();
}
