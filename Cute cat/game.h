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
bool collision (const SDL_Rect &r1, const SDL_Rect &r2) {
    return (r1.x+r1.w>=r2.x && r1.x+r1.w<=r2.w&&r1.y+r1.h>=r2.y);
}
void update(int &speed) {
    speed+=1;
}

bool InsideMagneticDistance(const SDL_Rect& r1, const SDL_Rect& r2) {
    if(r2.x-r1.x<= MAGNETIC_DISTANCE) {
        return true;
    }
    return false;
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

     void tick() {
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
    int posY = GROUND-30;
    int status = RUN;
    int step = INITIAL_STEP;
    bool onGround() {
        return posY == GROUND-30;
    }
    void jumpUp() {
        if (status == JUMP && posY >= MAX_HEIGHT) posY+= -JUMP_SPEED;
        if (posY <= MAX_HEIGHT) status = FALL;
        if (status == FALL && posY < GROUND-30) posY+=FALL_SPEED

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
	int	posY = GROUND-90  ;
	int rocketCount = 0;
	void rocketMove(const int &movespeed) {
	    posX -= movespeed;
        if (posX + MAX_ENEMY_WIDTH < 0) {
            posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
            rocketCount++;
        }
	}

    SDL_Rect getRocketRect()  const{
    return {posX+10, posY+10, 50, 40};
    }

};


struct Bush {
    int posX = rand() % (SCREEN_WIDTH) + 2*SCREEN_WIDTH;
	int	posY = GROUND-15 ;
	int bushCount = 0;
	void bushMove(const int &movespeed) {
	    posX -= movespeed;
        if (posX + MAX_ENEMY_WIDTH < 0) {
            posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
            bushCount++;
        }
	}

    SDL_Rect getBushRect()  const{
    return {posX+10, posY+10, 50, 50};
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
	int	posY = GROUND -150 ;

	void coinMove(const int &movespeed) {
	    posX -= ( movespeed);
        if (posX + MAX_COIN_WIDTH < 0) {
		posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
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
struct Box {
    bool active;
    int posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
	int	posY = GROUND -50 ;
	void boxMove(const int &movespeed) {
	    posX -= movespeed;
        if (posX + MAX_BOX_WIDTH < 0) {
            posX = rand() % (SCREEN_WIDTH) + SCREEN_WIDTH;
        }
	}

    SDL_Rect getBoxRect()  const{
    return {posX, posY-100, 50, 50};
    }
};

#endif // _GAME__H
