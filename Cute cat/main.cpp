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


using namespace std;
enum ScreenState {
    SCREEN_1, // poster game
    SCREEN_2, // man hinh chinh
    SCREEN_3, // game over
    SCREEN_4, // dieu chinh am thanh
};

int main(int argc, char *argv[])
{
    /*ifstream file("highest_score.txt");
    if(file.is_open()) {
        file >> highestCoins;
        file.close();
    }*/
    readHighestCoins();
    srand(time(NULL));
    int coinCount = 0;
    int hearts = 3;
    int ROCKET_SPEED = 20;
    //srand(time(NULL));
    Graphics graphics;
    graphics.init();
    ScreenState currentState = SCREEN_1;
    //tai am thanh
    Mix_Music *bgMusic = graphics.loadMusic("sound//backgroundMusic.mp3");
    Mix_Chunk *Jump = graphics.loadSound("sound//jumpSound3.wav");
    Mix_Chunk *Collect = graphics.loadSound("sound//collectCoins.wav");
    Mix_Chunk *Collide = graphics.loadSound("sound//mewcollision.wav");
    Mix_Chunk *GameOver = graphics.loadSound("sound//gameOverSound.mp3");
    //load font
    TTF_Font* font = graphics.loadFont("assets/DkHandRegular-orna.ttf", 30);
    SDL_Color color = {0, 0, 0, 255}; // mau van ban
    SDL_Color scoreColor = {255, 255, 255, 255};

    SDL_Texture* intro = graphics.loadTexture1("img/introBg.png");
    graphics.prepareScene(intro);
    SDL_Texture* gameover = graphics.loadTexture1("img/gameOver.png");
    // load man hinh dieu chinh am thanh
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
    r2Layer1.x = -(SCREEN_WIDTH);
    r2Layer1.y = 0;
    r2Layer1.w = SCREEN_WIDTH;
    r2Layer1.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer2;
    r1Layer2.x = 0;
    r1Layer2.y = 0;
    r1Layer2.w = SCREEN_WIDTH;
    r1Layer2.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer2;
    r2Layer2.x = -(SCREEN_WIDTH);
    r2Layer2.y = 0;
    r2Layer2.w = SCREEN_WIDTH;
    r2Layer2.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer3;
    r1Layer3.x = 0;
    r1Layer3.y = 0;
    r1Layer3.w = SCREEN_WIDTH;
    r1Layer3.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer3;
    r2Layer3.x = -(SCREEN_WIDTH);
    r2Layer3.y = 0;
    r2Layer3.w = SCREEN_WIDTH;
    r2Layer3.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer4;
    r1Layer4.x = 0;
    r1Layer4.y = 0;
    r1Layer4.w = SCREEN_WIDTH;
    r1Layer4.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer4;
    r2Layer4.x = -(SCREEN_WIDTH);
    r2Layer4.y = 0;
    r2Layer4.w = SCREEN_WIDTH;
    r2Layer4.h = SCREEN_HEIGHT;

    SDL_Rect r1Layer5;
    r1Layer5.x = 0;
    r1Layer5.y = 0;
    r1Layer5.w = SCREEN_WIDTH;
    r1Layer5.h = SCREEN_HEIGHT;

    SDL_Rect r2Layer5;
    r2Layer5.x = -(SCREEN_WIDTH);
    r2Layer5.y = 0;
    r2Layer5.w = SCREEN_WIDTH;
    r2Layer5.h = SCREEN_HEIGHT;

    // khai bao nhan vat chinh
    Character cat;
    SDL_Texture* catTexture = graphics.loadTexture1(CAT_SPRITE_FILE);
    cat.init(catTexture, CAT_FRAMES, CAT_CLIPS);
    // khai bao chuong ngai vat
    Bush bush;
    SDL_Texture* bushTexture = graphics.loadTexture1("img/bush.png");
    Rocket rocket;
    SDL_Texture* rocketTexture = graphics.loadTexture1("img/rocket.png");
    Bom bom;
    SDL_Texture* bomTexture = graphics.loadTexture1("img/bom.png");
    // khai bao mang song
    SDL_Texture* heart1 = graphics.loadTexture1("img/heart.png");
    SDL_Texture* heart2 = graphics.loadTexture1("img/heart.png");
    SDL_Texture* heart3 = graphics.loadTexture1("img/heart.png");
    SDL_Texture* coinScore = graphics.loadTexture1("img/coinScore.png");
    //effect
    SDL_Texture *smokeTexture = graphics.loadTexture1("img/smoke.png");

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
    bool quit = false;
    bool collisionOccurred = false;
    SDL_Event e;
    int d=1;
    int delayTimer = 0;
    int x;
    int y;
    bool soundClick = false;
    bool musicClick = false;
    Uint32 startTime = SDL_GetTicks();
    Uint32 timeElapsed = 0;

    while(!quit ) {
        Uint32 currentTime = SDL_GetTicks();
        while( SDL_PollEvent( &e ) != 0 ) {
            SDL_GetMouseState(&x, &y);
            if( e.type == SDL_QUIT ) quit = true;
            else if (e.type == SDL_MOUSEBUTTONDOWN){
                 if (x>=PLAY_X && x<=PLAY_X+PLAY_W && y>=PLAY_Y && y<=PLAY_Y+PLAY_H) {
                    if (currentState == SCREEN_1) {
                        currentState = SCREEN_2;
                    }
                 }
                 else if(x>=SETTING_X && x<=SETTING_X+SETTING_W && y>=SETTING_Y && y<=SETTING_Y+SETTING_H) {
                    if(currentState == SCREEN_1) {
                        currentState = SCREEN_4;
                    }
                 }
                 else if(x>=REPLAY_X && x<=REPLAY_X+REPLAY_W && y>=REPLAY_Y && y<=REPLAY_Y+REPLAY_H) {
                    if(currentState == SCREEN_3) {
                       // hearts=3;
                        bush.bushCount=0;
                        rocket.rocketCount=0;
                        cat.posX = SCREEN_WIDTH-700;
                        cat.posY = GROUND;
                        coinCount=0;
                        for (int i=0; i<5; i++) {
                            coins[i].visible = true;
                            coins[i].posX = coinPosX + 50*i;
                        }
                        bush.posX = rand()% SCREEN_WIDTH + SCREEN_WIDTH;
                        rocket.posX = rand()% SCREEN_WIDTH + SCREEN_WIDTH;
                        bom.posX = rand()% 500;
                        bom.posY = rand()%(SCREEN_HEIGHT) - SCREEN_HEIGHT;
                        startTime = currentTime;
                        ROCKET_SPEED =20;
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

            r1Layer5.x-=8;
            r2Layer5.x-=8;

            if(r1Layer1.x <-(SCREEN_WIDTH)) r1Layer1.x = (SCREEN_WIDTH-15);
            if(r2Layer1.x <-(SCREEN_WIDTH)) r2Layer1.x = (SCREEN_WIDTH-15);

            if(r1Layer2.x <-(SCREEN_WIDTH)) r1Layer2.x = (SCREEN_WIDTH-15);
            if(r2Layer2.x <-(SCREEN_WIDTH)) r2Layer2.x = (SCREEN_WIDTH-15);

            if(r1Layer3.x <-(SCREEN_WIDTH)) r1Layer3.x = (SCREEN_WIDTH-15);
            if(r2Layer3.x <-(SCREEN_WIDTH)) r2Layer3.x = (SCREEN_WIDTH-15);

            if(r1Layer4.x <-(SCREEN_WIDTH)) r1Layer4.x = (SCREEN_WIDTH-15);
            if(r2Layer4.x <-(SCREEN_WIDTH)) r2Layer4.x = (SCREEN_WIDTH-15);

            if(r1Layer5.x <-(SCREEN_WIDTH)) r1Layer5.x = (SCREEN_WIDTH-15);
            if(r2Layer5.x <-(SCREEN_WIDTH)) r2Layer5.x = (SCREEN_WIDTH-15);

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
            //render hearts
           /* for (int i=0; i<hearts; i++) {
                graphics.renderTexture(heart1, 10+50*i, 10);
            }*/
            // render coin
            graphics.renderTexture(coinScore, 720, 10);

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

            string coinText = "x" + to_string(coinCount);
            SDL_Surface* coinSurface = graphics.createTextSurface(coinText, font, color );
            SDL_Texture* score = graphics.createText(coinSurface);
            graphics.drawText(score, 780, 20);

            SDL_Rect r1 = cat.getCharacterRect();
            //SDL_Rect r2 = coin.getCoinRect();
            SDL_Rect r3 = bush.getBushRect();
            SDL_Rect r4 = rocket.getRocketRect();
            SDL_Rect r5 = bom.getBomRect();

            for (int i=0; i<5; i++) {
                coins[i].tick();
                coins[i].coinMove(1);
                SDL_Rect r2 = coins[i].getCoinRect();
                if(coins[i].visible) {
                    graphics.renderCoin(coins[i]);
                    if(overlap(r1, r2) || coins[i].posX<0) {
                        if(overlap(r1, r2)) {
                            if(!soundClick) graphics.play(Collect);
                            coinCount++;
                        }
                        coins[i].visible = false;
                        visibleCoins--;

                    }
                }
            }
            if(visibleCoins ==0) {
                for (int i=0; i<5; i++) {
                    coins[i].visible = true;
                    coins[i].posX = coinPosX + 50*i;
                }
                visibleCoins = 5;
            }


            /*if((vacham(r1, r3)||vacham(r1, r4)) && hearts==3) {
                cerr << "collide" << endl;
                hearts--;
                if(vacham(r1, r3)) {
                    graphics.render_rect(smokeTexture, bush.posX, bush.posY, 50, 50);
                    bush.posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
                }
                else {
                    graphics.render_rect(smokeTexture, rocket.posX, rocket.posY, 50, 50);
                    rocket.posX = rand() % SCREEN_WIDTH + SCREEN_WIDTH;
                }
                graphics.play(Collide);

            }
            else if((vacham(r1, r3)||vacham(r1, r4)) && hearts==2) {
                //graphics.renderTexture(whiteHeart, 60, 10);
                hearts--;
                cerr << "collide" << endl;
                if(vacham(r1, r3)) {
                    graphics.render_rect(smokeTexture, bush.posX, bush.posY, 50, 50);
                    bush.posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
                }
                else {
                    graphics.render_rect(smokeTexture, rocket.posX, rocket.posY, 50, 50);
                    rocket.posX = rand() % SCREEN_WIDTH + SCREEN_WIDTH;
                }
                graphics.play(Collide);

            }
            else if((vacham(r1, r3)||vacham(r1, r4)) && hearts==1) {
                //SDL_DestroyTexture(heart1);
                graphics.renderTexture(whiteHeart, 10, 10);
                hearts--;
                cerr << "collide" << endl;
                if(vacham(r1, r3)) {
                    graphics.render_rect(smokeTexture, bush.posX, bush.posY, 50, 50);
                    bush.posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
                }
                else {
                    graphics.render_rect(smokeTexture, rocket.posX, rocket.posY, 50, 50);
                    rocket.posX = rand() % SCREEN_WIDTH + SCREEN_WIDTH;
                }
                graphics.play(Collide);

            }*/
            bush.bushMove(BUSH_SPEED);
            //cerr << bush.bushCount << endl;
            graphics.render (cat);
            graphics.render_rect(bushTexture, bush.posX, bush.posY-15, 70, 70);
            if(bush.bushCount >= 5) {
                rocket.rocketMove(ROCKET_SPEED);
                graphics.render_rect(rocketTexture, rocket.posX, rocket.posY-70, 70, 50);
            }
            if(rocket.rocketCount==5) {
                bom.enemyMove(BOM_SPEED);
                graphics.render_rect(bomTexture, bom.posX, bom.posY, 90, 70);
            }
            if(SDL_HasIntersection(&r1, &r3)|| SDL_HasIntersection(&r1, &r4)|| SDL_HasIntersection(&r1, &r5)) {
                cerr << "collide" << endl;

                //hearts--;
                /*if(vacham(r1, r3)) {
                    graphics.render_rect(smokeTexture, bush.posX, bush.posY, 100, 100);

                    //bush.posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;

                }
                else {
                    //graphics.render_rect(smokeTexture, rocket.posX, rocket.posY, 100, 100);

                    //rocket.posX = rand() % SCREEN_WIDTH + SCREEN_WIDTH;

                }*/
                //if(!soundClick)graphics.play(Collide);
                //if(hearts==0) {
                    currentState = SCREEN_3;
                    updateHighestCoins(coinCount);
                    graphics.play(GameOver);
                //}
                SDL_Delay(1000);

            }
            /*if(currentTime-timeElapsed>=20000) {
                update(ROCKET_SPEED);
                cerr << ROCKET_SPEED << endl;
                timeElapsed = currentTime;
            }*/
            SDL_FreeSurface(coinSurface);
            SDL_DestroyTexture(score);

            //graphics.render_rect(bomTexture, bom.posX, bom.posY, 90, 70);
            graphics.presentScene();

            /*graphics.play(GameOver);
            graphics.prepareScene(gameover);
            string coinScore = "x" + to_string(coinCount);
            SDL_Surface* coinScoreSurface = graphics.createTextSurface(coinScore, font, color );
            SDL_Texture* your_score = graphics.createText(coinScoreSurface);
            graphics.drawText(your_score, 300, 300);
            graphics.render_rect(replayButton, 400, 200, 100, 100);
            Mix_FreeChunk(Collide);
            Mix_FreeMusic(bgMusic);*/
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

        SDL_DestroyTexture(rocketTexture);
        SDL_DestroyTexture(catTexture);
        SDL_DestroyTexture(bushTexture);
        SDL_DestroyTexture(CoinTexture);
        TTF_CloseFont( font );
        Mix_FreeChunk(Jump);
        Mix_FreeChunk(Collect);
        Mix_FreeChunk(Collide);
        Mix_FreeMusic(bgMusic);

    //SDL_Delay(20);
    graphics.quit();
    return 0;
    }
