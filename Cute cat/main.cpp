#include <iostream>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "defs.h"
#include "game.h"
#include <bits/stdc++.h>
#include <cstdlib>
#include <fstream>
using namespace std;
int highestCoins = 0;

// Hàm để lưu và cập nhật điểm cao nhất
void updateHighestCoins(int currentCoins) {
    if (currentCoins > highestCoins) {
        highestCoins = currentCoins;
        // Lưu điểm cao nhất vào tệp
        ofstream file("highest_coins.txt");
        if (file.is_open()) {
            file << highestCoins;
            file.close();
        }
    }
}
void readHighestCoins () {
    ifstream file("highest_coins.txt");
    if(file.is_open()) {
        file >> highestCoins;
        file.close();
    }
}

enum ScreenState {
    SCREEN_1, // intro game
    SCREEN_2, // man hinh chinh choi game
    SCREEN_3, // game over
    SCREEN_4, // dieu chinh am thanh
};

int main(int argc, char *argv[])
{
    readHighestCoins();
    srand(time(NULL));
    int coinCount = 0;

    int ROCKET_SPEED = MIN_ROCKET_SPEED;
    int BUSH_SPEED = MIN_BUSH_SPEED;
    int BOM_SPEED = MIN_BOM_SPEED;
    int COIN_SPEED = MIN_BOM_SPEED;
    int LAYER5_SPEED = MIN_LAYER5_SPEED;
    int LAYER4_SPEED = MIN_LAYER4_SPEED;
    int BOX_SPEED = MIN_BOX_SPEED;

    Graphics graphics;
    graphics.init();
    ScreenState currentState = SCREEN_1;
    //load sound
    Mix_Music *bgMusic = graphics.loadMusic("sound//backgroundMusic.mp3");
    Mix_Chunk *Jump = graphics.loadSound("sound//jumpSound3.wav");
    Mix_Chunk *Collect = graphics.loadSound("sound//collectCoins.wav");
    Mix_Chunk *GiftCollect = graphics.loadSound("sound//giftCollect2.wav");
    Mix_Chunk *Collide = graphics.loadSound("sound//mewcollision.wav");
    Mix_Chunk *GameOver = graphics.loadSound("sound//gameOverSound.mp3");
    //load font
    TTF_Font* font = graphics.loadFont("assets/DkHandRegular-orna.ttf", 30);
    SDL_Color color = {0, 0, 0, 255}; // mau van ban
    SDL_Color scoreColor = {255, 255, 255, 255};

    SDL_Texture* intro = graphics.loadTexture1("img/introBg.png");
    graphics.prepareScene(intro);
    SDL_Texture* gameover = graphics.loadTexture1("img/gameOver.png");
    // load music setting
    SDL_Texture* settingBg = graphics.loadTexture1("img/musicSetting.png");

    SDL_Texture* playbutton= graphics.loadTexture1("img/playbutton3.png");
    SDL_Texture* settingButton = graphics.loadTexture1("img/settingButton.png");
    SDL_Texture* replayButton = graphics.loadTexture1("img/replayButton.png");
    SDL_Texture* exitButton = graphics.loadTexture1("img/exitButton.png");
    SDL_Texture* turnOnButton = graphics.loadTexture1("img/turnOn.png");
    SDL_Texture* turnOffButton = graphics.loadTexture1("img/turnOff.png");


    graphics.setcolor();
    graphics.renderclear();
    SDL_Surface* layer1_surface = SDL_LoadBMP(LAYER1);
    SDL_Surface* layer2_surface = SDL_LoadBMP(LAYER2);
    SDL_Surface* layer3_surface = SDL_LoadBMP(LAYER3);
    SDL_Surface* layer4_surface = SDL_LoadBMP(LAYER4);
    SDL_Surface* layer5_surface = SDL_LoadBMP(LAYER5);

    SDL_SetColorKey(layer1_surface, SDL_TRUE, SDL_MapRGB(layer1_surface->format,0xFF,0,0xFF));
    SDL_SetColorKey(layer2_surface, SDL_TRUE, SDL_MapRGB(layer2_surface->format,0xFF,0,0xFF));
    SDL_SetColorKey(layer3_surface, SDL_TRUE, SDL_MapRGB(layer3_surface->format,0xFF,0,0xFF));
    SDL_SetColorKey(layer4_surface, SDL_TRUE, SDL_MapRGB(layer4_surface->format,0xFF,0,0xFF));
    SDL_SetColorKey(layer5_surface, SDL_TRUE, SDL_MapRGB(layer5_surface->format,0xFF,0,0xFF));

    SDL_Texture* layer1 = graphics.loadTexture(layer1_surface);
    SDL_Texture* layer2 = graphics.loadTexture(layer2_surface);
    SDL_Texture* layer3 = graphics.loadTexture(layer3_surface);
    SDL_Texture* layer4 = graphics.loadTexture(layer4_surface);
    SDL_Texture* layer5 = graphics.loadTexture(layer5_surface);

    SDL_FreeSurface(layer1_surface);
    SDL_FreeSurface(layer2_surface);
    SDL_FreeSurface(layer3_surface);
    SDL_FreeSurface(layer4_surface);
    SDL_FreeSurface(layer5_surface);

    SDL_Rect r1Layer1;
    r1Layer1.x = 0;
    r1Layer1.y = 0;
    r1Layer1.w = SCREEN_WIDTH;
    r1Layer1.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer1;
    r2Layer1.x = (SCREEN_WIDTH-1);
    r2Layer1.y = 0;
    r2Layer1.w = SCREEN_WIDTH;
    r2Layer1.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer2;
    r1Layer2.x = 0;
    r1Layer2.y = 0;
    r1Layer2.w = SCREEN_WIDTH;
    r1Layer2.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer2;
    r2Layer2.x = (SCREEN_WIDTH-1);
    r2Layer2.y = 0;
    r2Layer2.w = SCREEN_WIDTH;
    r2Layer2.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer3;
    r1Layer3.x = 0;
    r1Layer3.y = 0;
    r1Layer3.w = SCREEN_WIDTH;
    r1Layer3.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer3;
    r2Layer3.x = (SCREEN_WIDTH-1);
    r2Layer3.y = 0;
    r2Layer3.w = SCREEN_WIDTH;
    r2Layer3.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer4;
    r1Layer4.x = 0;
    r1Layer4.y = 0;
    r1Layer4.w = SCREEN_WIDTH;
    r1Layer4.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer4;
    r2Layer4.x = (SCREEN_WIDTH-1);
    r2Layer4.y = 0;
    r2Layer4.w = SCREEN_WIDTH;
    r2Layer4.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer5;
    r1Layer5.x = 0;
    r1Layer5.y = 0;
    r1Layer5.w = SCREEN_WIDTH;
    r1Layer5.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer5;
    r2Layer5.x = (SCREEN_WIDTH-LAYER5_SPEED);
    r2Layer5.y = 0;
    r2Layer5.w = SCREEN_WIDTH;
    r2Layer5.h = SCREEN_HEIGHT;

    // khai bao nhan vat chinh
    Character cat;
    SDL_Texture* catTexture = graphics.loadTexture1(WHITE_CAT_FILE);
    cat.init(catTexture, WHITE_CAT_FRAMES, WHITE_CAT_CLIPS);

    // enemy
    Bat bat;
    SDL_Texture* batTexture = graphics.loadTexture1(BAT_FILE);
    bat.init(batTexture, BAT_FRAMES, BAT_CLIPS);
    Bush bush;
    SDL_Texture* bushTexture = graphics.loadTexture1("img/mushroom.png");
    rainDrop raindrop;
    SDL_Texture* rainDropTexture = graphics.loadTexture1("img/rainDrop.png");
    Box box;
    SDL_Texture* mysteryBox = graphics.loadTexture1("img/mysteryBox.png");

    SDL_Texture* scarfTexture = graphics.loadTexture1("img/scarf.png");
    SDL_Texture* scarfSticker = graphics.loadTexture1("img/scarfSticker.png");
    SDL_Texture* magneticTexture = graphics.loadTexture1("img/magnetic.png");
    SDL_Texture* magneticSticker = graphics.loadTexture1("img/magneticSticker.png");
    SDL_Texture* doubleCoinTexture = graphics.loadTexture1("img/doubleCoin2.png");
    SDL_Texture* doubleCoinSticker = graphics.loadTexture1("img/doubleCoinSticker.png");
    SDL_Texture* coinScore = graphics.loadTexture1("img/coinScore.png");
    //effect
    SDL_Texture* smokeAnimation = graphics.loadTexture1("img/smoke.png");
    Smoke smoke;
    SDL_Texture* smokeTexture = graphics.loadTexture1(SMOKE_FILE);
    smoke.init(smokeTexture, SMOKE_FRAMES, SMOKE_CLIPS);
    //heart
    SDL_Texture* heartTexture = graphics.loadTexture1("img/heart.png");
    //coin
    Coin coin;
    SDL_Texture* CoinTexture = graphics.loadTexture1(COIN_SPRITE_FILE);
    coin.init(CoinTexture, COIN_FRAMES, COIN_CLIPS);

    vector<Coin> coins(5);
    coins[0].init(CoinTexture, COIN_FRAMES, COIN_CLIPS);
    coins[0].posX = rand() % SCREEN_WIDTH + SCREEN_WIDTH;
    for (int i=1; i<5; i++) {
        coins[i].init(CoinTexture, COIN_FRAMES, COIN_CLIPS);
        coins[i].posX = coins[0].posX + 50*i;
    }
    int coinPosX =  rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
    int visibleCoins = 5;
    int hearts = 3;
    bool quit = false;
    bool collisionOccurred = false;
    SDL_Event e;
    int d=1;
    int delayTimer = 0;
    int x;
    int y;
    bool soundClick = false;
    bool musicClick = false;
    Uint32 startTime = 0;
    Uint32 currentTime = 0;
    Uint32 deltaTime = 0;
    Uint32 lastLevelUp = 0;
    Uint32 levelUpInterval = 20000;
    Uint32 lastBoxAppear = 0;
    Uint32 boxAppearInterval = 10000;
    Uint32 giftStartTime = 0;
    Uint32 lastCoinAppear = 0;
    Uint32 coinAppearInterval = 3000;
    int gift = NONE;
    int countdown;
    while(!quit ) {
        while( SDL_PollEvent( &e ) != 0 ) {
            SDL_GetMouseState(&x, &y);
            if( e.type == SDL_QUIT ) quit = true;
            else if (e.type == SDL_MOUSEBUTTONDOWN){
                 if (x>=PLAY_X && x<=PLAY_X+PLAY_W && y>=PLAY_Y && y<=PLAY_Y+PLAY_H) {
                    if (currentState == SCREEN_1) {
                        currentState = SCREEN_2;
                        startTime = SDL_GetTicks();
                        bush.bushCount=0;
                        bat.batCount = 0;
                        cat.posX = SCREEN_WIDTH-700;
                        cat.posY = GROUND-15;
                        coinCount=0;
                        visibleCoins = 5;
                        for (int i=0; i<5; i++) {
                            coins[i].visible = true;
                            coins[i].posX = coinPosX + 50*i;
                        }
                        bush.posX = rand()% SCREEN_WIDTH + SCREEN_WIDTH;
                        bat.posX = rand()% SCREEN_WIDTH + SCREEN_WIDTH;
                        raindrop.reset();
                        lastBoxAppear = 0;


                        LAYER4_SPEED = MIN_LAYER4_SPEED;
                        LAYER5_SPEED = MIN_LAYER5_SPEED;
                    }
                 }
                 else if(x>=SETTING_X && x<=SETTING_X+SETTING_W && y>=SETTING_Y && y<=SETTING_Y+SETTING_H) {
                    if(currentState == SCREEN_1) {
                        currentState = SCREEN_4;
                    }
                 }
                 else if(x>=REPLAY_X && x<=REPLAY_X+REPLAY_W && y>=REPLAY_Y && y<=REPLAY_Y+REPLAY_H) {
                    if(currentState == SCREEN_3) {

                        currentState = SCREEN_1;
                    }
                 }
                 else if (x>=EXIT_X && x<=EXIT_X+EXIT_W && y>=EXIT_Y && y<=EXIT_Y+EXIT_H) {
                    if(currentState == SCREEN_3) quit=true;
                 }
                 else if( x>=SOUND_X && x<=SOUND_X+SOUND_W && y>=SOUND_Y && y<=SOUND_Y+SOUND_H) {
                    if(currentState == SCREEN_4) {
                        if(soundClick==false) soundClick = true;
                        else soundClick = false;
                    }
                 }
                else if (x>=MUSIC_X && x<=MUSIC_X+MUSIC_W && y>=MUSIC_Y && y<=MUSIC_Y+MUSIC_H){
                    if(currentState == SCREEN_4) {
                        if(musicClick==false) musicClick = true;
                        else musicClick = false;
                    }
                }
                else if (x>=BACK_X && x<=BACK_X+ BACK_W && y>=BACK_Y && y<=BACK_Y+BACK_H) {
                    if(currentState == SCREEN_4) {
                        currentState = SCREEN_1;
                    }
                }
            }
        }
        if (currentState == SCREEN_1) {
            graphics.prepareScene(intro);
            if(!musicClick) {
                    graphics.play(bgMusic);
            }
            if (x>=PLAY_X && x<=PLAY_X+PLAY_W && y>=PLAY_Y && y<=PLAY_Y+PLAY_H) {
                graphics.render_rect(playbutton, PLAY_X, PLAY_Y, PLAY_W, PLAY_H);
                graphics.render_rect(settingButton, SETTING_X+10, SETTING_Y+10, SETTING_W-20, SETTING_H-20);
            }
            else if(x>=SETTING_X && x<=SETTING_X+SETTING_W && y>=SETTING_Y && y<=SETTING_Y+SETTING_H) {
                graphics.render_rect(settingButton, SETTING_X, SETTING_Y, SETTING_W, SETTING_H);
                graphics.render_rect(playbutton, PLAY_X+10, PLAY_Y+10, PLAY_W-20, PLAY_H-20);
            }
            else {
                graphics.render_rect(playbutton, PLAY_X+10, PLAY_Y+10, PLAY_W-20, PLAY_H-20);
                graphics.render_rect(settingButton, SETTING_X+10, SETTING_Y+10, SETTING_W-20, SETTING_H-20);
            }

            graphics.presentScene();
        }
        else if (currentState == SCREEN_2){
            if(!musicClick) {
                graphics.play(bgMusic);
            }
            currentTime = SDL_GetTicks();
            deltaTime = currentTime-startTime;

            graphics.setcolor();
            graphics.renderclear();

            r1Layer1.x-=1;
            r2Layer1.x-=1;

            r1Layer2.x-=3;
            r2Layer2.x-=3;

            r1Layer3.x-=4;
            r2Layer3.x-=4;

            r1Layer4.x-=8;
            r2Layer4.x-=8;

            r1Layer5.x-=LAYER5_SPEED;
            r2Layer5.x-=LAYER5_SPEED;

            if(r1Layer1.x <-(SCREEN_WIDTH)) r1Layer1.x = (SCREEN_WIDTH-15);
            if(r2Layer1.x <-(SCREEN_WIDTH)) r2Layer1.x = (SCREEN_WIDTH-15);

            if(r1Layer2.x <-(SCREEN_WIDTH)) r1Layer2.x = (SCREEN_WIDTH-15);
            if(r2Layer2.x <-(SCREEN_WIDTH)) r2Layer2.x = (SCREEN_WIDTH-15);

            if(r1Layer3.x <-(SCREEN_WIDTH)) r1Layer3.x = (SCREEN_WIDTH-15);
            if(r2Layer3.x <-(SCREEN_WIDTH)) r2Layer3.x = (SCREEN_WIDTH-15);

            if(r1Layer4.x <-(SCREEN_WIDTH)) r1Layer4.x = (SCREEN_WIDTH-LAYER4_SPEED);
            if(r2Layer4.x <-(SCREEN_WIDTH)) r2Layer4.x = (SCREEN_WIDTH-LAYER4_SPEED);

            if(r1Layer5.x <-(SCREEN_WIDTH-LAYER5_SPEED)) r1Layer5.x = (SCREEN_WIDTH-LAYER5_SPEED);
            if(r2Layer5.x <-(SCREEN_WIDTH-LAYER5_SPEED)) r2Layer5.x = (SCREEN_WIDTH-LAYER5_SPEED);

            graphics.cop(layer1, &r1Layer1);
            graphics.cop(layer1, &r2Layer1);

            graphics.cop(layer2, &r1Layer2);
            graphics.cop(layer2, &r2Layer2);

            graphics.cop(layer3, &r1Layer3);
            graphics.cop(layer3, &r2Layer3);

            graphics.cop(layer4, &r1Layer4);
            graphics.cop(layer4, &r2Layer4);

            graphics.cop(layer5, &r1Layer5);
            graphics.cop(layer5, &r2Layer5);
            // render coin
            graphics.renderTexture(coinScore, 720, 10);
            //render heart
            for(int i=0; i< hearts; i++) {
                graphics.renderTexture(heartTexture, 300+50*i, 10);
            }

            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_LEFT] && !cat.outsideTheLeft()) cat.moveLeft();
            if (currentKeyStates[SDL_SCANCODE_RIGHT] && !cat.outsideTheRight()) cat.moveRight();
            if (currentKeyStates[SDL_SCANCODE_UP]) {
                if (cat.onGround()) {
                    cat.status = JUMP;
                }
                if(!soundClick)
                graphics.play(Jump);
            }
            cat.jumpUp();
            cat.tick();
            graphics.render (cat);

            string coinText = "x" + to_string(coinCount);
            SDL_Surface* coinSurface = graphics.createTextSurface(coinText, font, color );
            SDL_Texture* score = graphics.createText(coinSurface);
            graphics.drawText(score, 780, 20);

            SDL_Rect r1 = cat.getCharacterRect();
            SDL_Rect r3 = bush.getBushRect();
            SDL_Rect r4 = bat.getBatRect();
            SDL_Rect r5 = raindrop.getRainDropRect();
            SDL_Rect r6 = box.getBoxRect();
            if(deltaTime-lastCoinAppear>=coinAppearInterval) {
                for (int i=0; i<5; i++) {
                    if(coins[i].visible) {
                        coins[i].coinMove(LAYER5_SPEED);
                        coins[i].tick();
                        graphics.renderCoin(coins[i]);
                        SDL_Rect r2 = coins[i].getCoinRect();
                        if(SDL_HasIntersection(&r1, &r2) || coins[i].posX<0|| (gift==MAGNETIC && InsideMagneticDistance(r1, r2))|| (SDL_HasIntersection(&r1, &r2) && gift==DOUBLE_COIN)) {
                            if((SDL_HasIntersection(&r1, &r2) && gift!=DOUBLE_COIN)|| (gift==MAGNETIC && InsideMagneticDistance(r1, r2)) ) {
                                if(!soundClick) {
                                    graphics.play(Collect);
                                }
                                coinCount++;
                            }
                            if(SDL_HasIntersection(&r1, &r2) && gift==DOUBLE_COIN) {
                                if(!soundClick) {
                                    graphics.play(Collect);
                                }
                                coinCount+=2;
                                cerr << coinCount << endl;
                            }
                            coins[i].visible = false;
                            visibleCoins--;
                        }
                    }
                }
            }
            if(visibleCoins == 0) {
                lastCoinAppear = deltaTime;
                for (int i=0; i<5; i++) {
                    coins[i].visible = true;
                    coins[i].posX = coinPosX + 50*i;
                }
                visibleCoins = 5;
            }
            bush.bushMove(LAYER5_SPEED);
            graphics.render_rect(bushTexture, bush.posX, bush.posY, 50, 50);

            if(bush.bushCount >= 1) {
                bat.batMove(LAYER5_SPEED);
                bat.tick();
                graphics.renderBat(bat);

            }
            if(bat.batCount>=1) {
                raindrop.Move(8);
                graphics.render_rect(rainDropTexture, raindrop.posX, raindrop.posY, 20, 30);

            }
            if(deltaTime - lastBoxAppear > boxAppearInterval) {
                box.boxMove(LAYER5_SPEED);
                graphics.render_rect(mysteryBox, box.posX, box.posY-100, 50, 50);
                if(box.posX + 50 <0  ) {
                    box.posX = rand()% SCREEN_WIDTH + SCREEN_WIDTH;
                    lastBoxAppear = deltaTime;

                }
                else if(SDL_HasIntersection(&r1, &r6)) {

                    giftStartTime = deltaTime;
                    lastBoxAppear = deltaTime;
                    int xBox = box.posX;
                    int yBox = box.posY;
                    gift = rand()%3;

                    for (int i=0; i<=50; i+=10) {
                        if(!soundClick) graphics.play(GiftCollect);
                        if(gift == DOUBLE_COIN) {
                            graphics.render_rect(doubleCoinTexture, xBox-30-i, yBox-150-i, 120+2*i, 100+2*i);
                        }
                        else if(gift == SCARF) {
                            graphics.render_rect(scarfTexture, xBox-30-i, yBox-150-i, 120+2*i, 100+2*i);
                        }
                        else if(gift == MAGNETIC) {
                            graphics.render_rect(magneticTexture, xBox-50-i, yBox-170-i, 120+2*i, 100+2*i);

                        }
                            SDL_Delay(50);
                            graphics.presentScene();
                    }

                    SDL_Delay(1000);
                    box.posX = rand()% SCREEN_WIDTH + SCREEN_WIDTH;
                }
            }
            if(gift==SCARF) {
                countdown = 11-(deltaTime - giftStartTime)/1000;
                if(countdown >=0 ) {
                    graphics.render_rect(scarfSticker, 20, 10, 50, 50);
                    string countDownNumber = to_string(countdown);
                    SDL_Surface* countDownSurface = graphics.createTextSurface(countDownNumber, font, color );
                    SDL_Texture* countDownTexture = graphics.createText(countDownSurface);
                    graphics.drawText(countDownTexture, 36, 10);
                }
                if(countdown<0) gift = NONE;
            }
            if(gift==MAGNETIC) {
                countdown = 11-(deltaTime - giftStartTime)/1000;
                if(countdown >=0 ) {
                    graphics.render_rect(magneticSticker, 20, 10, 50, 50);
                    string countDownNumber = to_string(countdown);
                    SDL_Surface* countDownSurface = graphics.createTextSurface(countDownNumber, font, color );
                    SDL_Texture* countDownTexture = graphics.createText(countDownSurface);
                    graphics.drawText(countDownTexture, 36, 10);
                }
                if(countdown<0) gift = NONE;
            }
            if(gift == DOUBLE_COIN) {
                countdown = 11-(deltaTime - giftStartTime)/1000;
                if(countdown >=0 ) {
                    graphics.render_rect(doubleCoinSticker, 20, 10, 50, 50);
                    string countDownNumber = to_string(countdown);
                    SDL_Surface* countDownSurface = graphics.createTextSurface(countDownNumber, font, color );
                    SDL_Texture* countDownTexture = graphics.createText(countDownSurface);
                    graphics.drawText(countDownTexture, 36, 10);
                }
                if(countdown<0) gift = NONE;
            }

            if(gift!=SCARF) {
                if(SDL_HasIntersection(&r1, &r3)|| SDL_HasIntersection(&r1, &r4) || hearts==0) {
                    graphics.play(GameOver);

                    graphics.render_rect(smokeAnimation, cat.posX-50, cat.posY-100, 300, 300);
                    graphics.presentScene();
                    SDL_Delay(1000);
                    updateHighestCoins(coinCount);
                    currentState = SCREEN_3;
                }
                if(SDL_HasIntersection(&r1, &r5)) {
                    raindrop.reset();
                    hearts--;
                    graphics.play(Collide);
                }
            }

            if(deltaTime - lastLevelUp >levelUpInterval) {
                update(LAYER5_SPEED);
                update(LAYER4_SPEED);
                lastLevelUp = deltaTime;
            }


            SDL_FreeSurface(coinSurface);
            SDL_DestroyTexture(score);
            graphics.presentScene();

        }

        else if (currentState == SCREEN_3) {
            Mix_PauseMusic();
            graphics.prepareScene(gameover);

            if(x>=REPLAY_X && x<=REPLAY_X+REPLAY_W && y>=REPLAY_Y && y<=REPLAY_Y+REPLAY_H) {
                graphics.render_rect (replayButton, REPLAY_X, REPLAY_Y, REPLAY_W, REPLAY_H);
                graphics.render_rect (exitButton,EXIT_X+10, EXIT_Y+10, EXIT_W-20, EXIT_H-20);
            }
            else if(x>=EXIT_X && x<=EXIT_X+EXIT_W && y>=EXIT_Y && y<=EXIT_Y+EXIT_H) {
                graphics.render_rect (exitButton,EXIT_X, EXIT_Y, EXIT_W, EXIT_H);
                graphics.render_rect (replayButton, REPLAY_X+10, REPLAY_Y+10, REPLAY_W-20, REPLAY_H-20);
            }
            else {
                graphics.render_rect (exitButton,EXIT_X+10, EXIT_Y+10, EXIT_W-20, EXIT_H-20);
                graphics.render_rect (replayButton, REPLAY_X+10, REPLAY_Y+10, REPLAY_W-20, REPLAY_H-20);
            }

            string coinScore = "YOUR COINS:  " + to_string(coinCount);
            SDL_Surface* coinScoreSurface = graphics.createTextSurface(coinScore, font, scoreColor );
            SDL_Texture* your_score = graphics.createText(coinScoreSurface);
            graphics.drawText(your_score, 250, 330);

            string highestCoinsText = "HIGHEST COINS:  " +to_string(highestCoins);
            SDL_Surface* HighestCoinsSurface = graphics.createTextSurface(highestCoinsText, font, scoreColor);
            SDL_Texture* highestCoinsTexture = graphics.createText(HighestCoinsSurface);
            graphics.drawText(highestCoinsTexture, 250, 250);
            graphics.presentScene();

        }
        else if(currentState == SCREEN_4) {
            graphics.prepareScene(settingBg);
            graphics.render_rect(turnOnButton, MUSIC_X, MUSIC_Y, MUSIC_W, MUSIC_H);
            graphics.render_rect(turnOnButton, SOUND_X, SOUND_Y, SOUND_W, SOUND_H);
            if(musicClick) {
                    graphics.render_rect(turnOffButton, MUSIC_X, MUSIC_Y, MUSIC_W, MUSIC_H);
                    Mix_PauseMusic();
            }
            if(!musicClick) {
                    graphics.render_rect(turnOnButton, MUSIC_X, MUSIC_Y, MUSIC_W, MUSIC_H);
                    graphics.play(bgMusic);
            }
            if(soundClick) {
                graphics.render_rect(turnOffButton, SOUND_X, SOUND_Y, SOUND_W, SOUND_H);
            }
            if(!soundClick) {
                graphics.render_rect(turnOnButton, SOUND_X, SOUND_Y, SOUND_W, SOUND_H);
            }

            graphics.presentScene();

        }
        SDL_Delay(20);
        }
        SDL_DestroyTexture( layer1 );
        SDL_DestroyTexture( layer2 );
        SDL_DestroyTexture( layer3 );
        SDL_DestroyTexture( layer4 );
        SDL_DestroyTexture( layer5 );

        SDL_DestroyTexture(batTexture);
        SDL_DestroyTexture(catTexture);
        SDL_DestroyTexture(bushTexture);
        SDL_DestroyTexture(rainDropTexture);
        SDL_DestroyTexture(CoinTexture);
        SDL_DestroyTexture(playbutton);
        SDL_DestroyTexture(settingButton);
        SDL_DestroyTexture(replayButton);
        SDL_DestroyTexture(exitButton);
        SDL_DestroyTexture(settingBg);
        SDL_DestroyTexture(intro);
        SDL_DestroyTexture(gameover);
        //SDL_DestroyTexture()

        TTF_CloseFont( font );
        Mix_FreeChunk(Jump);
        Mix_FreeChunk(Collect);
        Mix_FreeChunk(Collide);
        Mix_FreeMusic(bgMusic);

    //SDL_Delay(20);
    graphics.quit();
    return 0;
    }
