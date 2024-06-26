#ifndef _DEFS__H
#define _DEFS__H

#define SCREEN_WIDTH 928
#define SCREEN_HEIGHT 522
#define WINDOW_TITLE "Cute cat"

#define GROUND 440
#define MAX_HEIGHT 190
#define JUMP_SPEED  12;
#define FALL_SPEED  12;

#define RUN	10
#define JUMP 11
#define FALL 12

#define SCARF 0
#define DOUBLE_COIN 1
#define MAGNETIC 2
#define NONE 3

#define MAX_ENEMY_WIDTH 100
#define INITIAL_STEP 6

#define MAX_BOX_WIDTH 100
#define MAX_COIN_WIDTH 100
#define COIN_GAP 50
#define HEART_GAP 50
#define MIN_LAYER5_SPEED 8
#define MIN_LAYER4_SPEED 8

#define MAGNETIC_DISTANCE 500

const int PLAY_X =380;
const int PLAY_Y =340;
const int PLAY_W =150;
const int PLAY_H =100;

const int SETTING_X = 380;
const int SETTING_Y = 410;
const int SETTING_W = 150;
const int SETTING_H = 100;

const int REPLAY_X = 260;
const int REPLAY_Y = 390;
const int REPLAY_W = 150;
const int REPLAY_H = 100;

const int EXIT_X = 490;
const int EXIT_Y = 390;
const int EXIT_W = 150;
const int EXIT_H = 100;

const int MUSIC_X = 530;
const int MUSIC_Y = 180;
const int MUSIC_W = 100;
const int MUSIC_H = 50;

const int SOUND_X = 530;
const int SOUND_Y = 275;
const int SOUND_W = 100;
const int SOUND_H = 50;

const int BACK_X = 0;
const int BACK_Y = 364;
const int BACK_W = 150;
const int BACK_H = 68;

const char* LAYER1 = "img/layer1.bmp";
const char* LAYER2 = "img/layer2.bmp";
const char* LAYER3 = "img/layer3.bmp";
const char* LAYER4 = "img/layer4.bmp";
const char* LAYER5 = "img/layer5.bmp";

const char* COIN_SPRITE_FILE = "img/coinSprite.png";
const int COIN_CLIPS[][4] = {
    {0, 0, 49, 49},
    {49, 0, 49, 49},
    {49*2, 0, 49, 49},
    {49*3, 0, 49, 49},
    {49*4, 0, 49, 49},
    {49*5, 0, 49, 49}};
const int COIN_FRAMES = sizeof(COIN_CLIPS)/sizeof(int)/6;

const char* WHITE_CAT_FILE = "img/whiteCat.png";
const int WHITE_CAT_CLIPS[][4] = {
    {304, 13, 84, 67},
    {202, 5, 85, 68},
    {101, 0, 84, 67},
    {0, 8, 83, 72}};
const int WHITE_CAT_FRAMES = sizeof(WHITE_CAT_CLIPS)/sizeof(int)/4;

const char* BAT_FILE = "img/batSprite.png";
const int BAT_CLIPS[][4] = {
    {7, 0, 62, 37},
    {75, 0, 52, 39},
    {138, 0, 57, 50},
    {208, 10, 42, 40},
    {269, 8, 55, 38},
    {333, 6, 60, 30}};
const int BAT_FRAMES = sizeof(BAT_CLIPS)/sizeof(int)/6;

#endif
