#ifndef _DEFS__H
#define _DEFS__H

#define SCREEN_WIDTH 928
#define SCREEN_HEIGHT 522
#define WINDOW_TITLE "Cute cat"

#define GROUND 440
#define MAX_HEIGHT 250
#define JUMP_SPEED  12;
#define FALL_SPEED  12;

#define JUMP 1
#define FALL 2
#define RUN	0

#define ENEMY_POSITION_RANGE 0
#define ENEMY_SPEED 9
#define MAX_ENEMY_WIDTH 100

#define BULLET_SPEED 15

//#define BUSH_SPEED 9

#define INITIAL_STEP 6

//#define COIN_SPEED 8
#define MAX_BOX_WIDTH 100
#define MAX_COIN_WIDTH 100

#define MIN_ROCKET_SPEED 12
#define MIN_BUSH_SPEED 9
#define MIN_BOM_SPEED 8
#define MIN_LAYER5_SPEED 8
#define MIN_LAYER4_SPEED 8
#define MIN_COIN_SPEED 8
#define MIN_BOX_SPEED 8
const int FLYING_FRAMES = 5;

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

const int COIN_GAP = 50;
const char* LAYER1 = "img/layer1.bmp";
const char* LAYER2 = "img/layer2.bmp";
const char* LAYER3 = "img/layer3.bmp";
const char* LAYER4 = "img/layer4.bmp";
const char* LAYER5 = "img/layer5.bmp";

const char* CAT_SPRITE_FILE ="img/helloKitty.png";
const int CAT_CLIPS[][4] = {
    {0,0, 70, 80},
    {70, 0, 70, 80},
    {70*2, 0, 70, 80}
};
const int CAT_FRAMES = sizeof(CAT_CLIPS)/sizeof(int)/4;
/*const char* CAT_SPRITE_FILE = "img/mycat.png";
const int CAT_CLIPS[][4] = {
    {  0, 7, 70, 53},
    { 74, 7, 70, 53},
    {74*2, 7, 70, 53},
    { 74*3, 7, 70, 53},
    { 74*4, 7, 70, 53},
    { 74*5, 7, 70, 53}};
const int CAT_FRAMES = sizeof(CAT_CLIPS)/sizeof(int)/6;*/

const int GREYCAT_CLIPS[][4] = {
    {  2, 12, 67, 53},
    { 76,12, 67, 53},
    { 150, 12, 67, 53},
    { 224, 12, 67, 53},
    { 298, 12, 67, 53}};
const int GREYCAT_FRAMES = sizeof(GREYCAT_CLIPS)/sizeof(int)/5;

const char* FIRE_SPRITE_FILE = "img/fire.png";
const int FIRE_CLIPS[][4] = {
    {0, 76, 68, 118},
    {70, 52, 68, 118},
    {140, 13, 68, 118},
    {210, 2, 68, 118}};
const int FIRE_FRAMES = sizeof(FIRE_CLIPS)/sizeof(int)/4;

const char* CAT_INTRO = "img/cat_intro.png";
const int CAT_INTRO_CLIPS[][4] = {
    {  0, 0, 217, 200},
    { 217, 0, 217, 200}};

const int CAT_INTRO_FRAMES = sizeof(CAT_CLIPS)/sizeof(int)/2;

const char* COIN_SPRITE_FILE = "img/coinSprite.png";
const int COIN_CLIPS[][4] = {
    {0, 0, 49, 49},
    {49, 0, 49, 49},
    {49*2, 0, 49, 49},
    {49*3, 0, 49, 49},
    {49*4, 0, 49, 49},
    {49*5, 0, 49, 49}};
const int COIN_FRAMES = sizeof(COIN_CLIPS)/sizeof(int)/6;

#endif
