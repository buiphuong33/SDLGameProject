#ifndef _GAME__H
#define _GAME__H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "graphics.h"
#include <bits/stdc++.h>
#include <algorithm>
#include <cstdlib>
using namespace std;

bool inside(int x, int y, SDL_Rect r) {
    return x > r.x && x < r.x+r.w && y > r.y && y < r.y+r.h;
}

bool overlap(const SDL_Rect& r1, const SDL_Rect& r2) {
    return inside(r1.x, r1.y, r2)|| inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}

bool vacham (SDL_Rect &r1, SDL_Rect &r2, int speed) {
    return (0 <= r2.x-(r1.x+r1.w) && r2.x-(r1.x+r1.w) <= speed && (r1.y+r1.h) >= r2.y) ;//|| (r1.x<=r2.x+r2.w && r1.y+r1.h>=r2.y && r2.x-(r1.x+r1.w)<=speed) ;
}

void update(int &s) {
    s+=3;
}


struct Character {
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;
    int frameDelay = 5;
    SDL_Rect clip;
    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;

        //SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    /*void tick() {
        currentFrame = (currentFrame +1) % clips.size();
    }*/
     void tick() {
        //currentFrame = (currentFrame +1) % (clips.size());
        static int frameCount = 0;
        if (frameCount >= frameDelay) {
            currentFrame = (currentFrame + 1) % clips.size();
            frameCount = 0;
        } else {
            frameCount++;
        }
    }
    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }


    int posX = SCREEN_WIDTH-700;
    int posY = GROUND;
    int status = 0;
    int step = INITIAL_STEP;
    bool onGround() {
        return posY == GROUND;
    }

    void jumpUp() {
        if (status == JUMP && posY >= MAX_HEIGHT) posY+= -JUMP_SPEED;
        if (posY <= MAX_HEIGHT) status = FALL;
        if (status == FALL && posY < GROUND) posY+=FALL_SPEED

    }
    void moveLeft() {
        posX -=step;
    }
    void moveRight() {
        posX +=step;
    }
    bool outsideTheLeft() {
        return posX < 0;
    }
    bool outsideTheRight() {
        return posX > SCREEN_WIDTH-75;
    }

    SDL_Rect getCharacterRect() const  {
    return {posX, posY, clip.w, clip.h};
    }
};


struct Rocket {
    int posX = rand() % (SCREEN_WIDTH) + 2*SCREEN_WIDTH;
	int	posY = GROUND  ;

	void rocketMove(const int &movespeed) {
	    posX -= movespeed;
        if (posX + MAX_ENEMY_WIDTH < 0) {
		posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
        }
	}

    SDL_Rect getRocketRect()  const{
    return {posX, posY, 70, 70};
    }

};



struct Enemy2 {
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;
    SDL_Rect clip;
    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;


        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        currentFrame = (currentFrame +1) % clips.size();
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
    int posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
	int	posY = GROUND +10 ;

	void enemyMove(const int &movespeed) {
	    posX -= ( ENEMY_SPEED);
        if (posX + MAX_ENEMY_WIDTH < 0) {
		posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
        }
	}

    SDL_Rect getEnemyRect()  const{
    return {posX, posY, clip.w, clip.h};
    }

};


struct Bullet {
    int posX;
    int posY;
    void getPos(Enemy2 enemy) {
        posX = rand() % enemy.posX ;
        posY = GROUND -5;
    }
    void bulletMove(const int &bulletSpeed, Enemy2 enemy) {
        if (enemy.posX <= SCREEN_WIDTH && enemy.posX >0) {
            posX -=(bulletSpeed);
            if (posX<0) {
                posX =enemy.posX ;
            }
        }
    }

};
struct Bush {
    int posX = rand() % (SCREEN_WIDTH) + 2*SCREEN_WIDTH;
	int	posY = GROUND  ;

	void bushMove(const int &movespeed) {
	    posX -= movespeed;
        if (posX + MAX_ENEMY_WIDTH < 0) {
		posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
        }
	}

    SDL_Rect getBushRect()  const{
    return {posX+5, posY+20, 10, 10};
    }
};
struct Coin {
    bool visible = true;
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;
    int frameDelay = 10;
    SDL_Rect clip;
    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        //currentFrame = (currentFrame +1) % (clips.size());
        static int frameCount = 0;
        if (frameCount >= frameDelay) {
            currentFrame = (currentFrame + 1) % clips.size();
            frameCount = 0;
        } else {
            frameCount++;
        }
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
    int posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
	int	posY = GROUND  ;

	void coinMove(const int &movespeed) {
	    posX -= ( COIN_SPEED);
        if (posX + MAX_COIN_WIDTH < 0) {
		posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
        }
	}
	void coinMove2(const int &movespeed, int x, int i) {
	    posX -= ( COIN_SPEED);
        if (posX + MAX_COIN_WIDTH < 0) {
		posX = x+50*i;
        }
	}

    SDL_Rect getCoinRect()  const{
    return {posX, posY, clip.w, clip.h};
    }
};
 struct Bom {
    int posX = rand()% 500;
	int	posY = rand()%(SCREEN_HEIGHT) - SCREEN_HEIGHT;

	void enemyMove(const int &movespeed) {
	    posY += movespeed;
        if (posY > SCREEN_HEIGHT) {
            posX = rand()%500;
            posY = rand() % (SCREEN_HEIGHT) - SCREEN_HEIGHT;
        }
	}

    SDL_Rect getBomRect()  const{
    return {posX, posY, 90, 70};
    }

 };


#endif // _GAME__H
