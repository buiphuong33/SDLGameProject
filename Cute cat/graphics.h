#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "defs.h"
#include <vector>
#include "game.h"


struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;

	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
                    logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
        }


    }

	void prepareScene(SDL_Texture * background = nullptr)
    {
        SDL_RenderClear(renderer);
        if (background != nullptr) SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture1(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()
    {
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }

    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }

    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
    }

    SDL_Texture* renderText(const string text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
        }

        SDL_FreeSurface( textSurface );
        return texture;
    }

    SDL_Surface* createTextSurface (const string& text, TTF_Font* font, SDL_Color textColor) {
        return TTF_RenderText_Solid(font, text.c_str(), textColor);
    }

    void drawText(SDL_Texture* texture, int x, int y) {
        SDL_Rect dstRect = {x, y, 10, 10}; // Chỉ định vị trí vẽ văn bản
        SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h); // Lấy kích thước văn bản
        SDL_RenderCopy(renderer, texture, NULL, &dstRect); // Vẽ văn bản lên màn hình
    }

    SDL_Texture* createText (SDL_Surface* coinSurface) {
        return SDL_CreateTextureFromSurface(renderer, coinSurface);
    }

    /*void render(const ScrollingBackground& background) {
        renderTexture(background.texture, background.scrollingOffset, 0);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0);
    }*/
    void setcolor()
    {
        SDL_SetRenderDrawColor(renderer,220,193,193,255);
    }
    void renderclear()
    {
         SDL_RenderClear(renderer);
    }
    void cop(SDL_Texture* ground, SDL_Rect* matdat3)
    {
         SDL_RenderCopy(renderer, ground, NULL, matdat3);
    }
   SDL_Texture *loadTexture(SDL_Surface* ground_surface)
   {
       SDL_Texture* ground1 = SDL_CreateTextureFromSurface(renderer, ground_surface);
       return ground1;
   }
    //render main character
    void render( const Character& character) {
        const SDL_Rect* clip = character.getCurrentClip();
        SDL_Rect renderQuad = {character.posX, character.posY, clip->w, clip->h};
        SDL_RenderCopy(renderer, character.texture, clip, &renderQuad);
    }

    void renderCoin(const Coin& coin) {
        const SDL_Rect* clip = coin.getCurrentClip();
        SDL_Rect renderQuad = {coin.posX, coin.posY, clip->w, clip->h};
        SDL_RenderCopy(renderer, coin.texture, clip, &renderQuad);
    }

    void renderBat(const Bat& bat) {
        const SDL_Rect* clip = bat.getCurrentClip();
        SDL_Rect renderQuad = {bat.posX, bat.posY, clip->w, clip->h};
        SDL_RenderCopy(renderer, bat.texture, clip, &renderQuad);
    }

    void waitUntilKeyPressed()
    {
        SDL_Event e;
        while (true) {
            if ( SDL_PollEvent(&e) != 0 &&
                 (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
                return;
            SDL_Delay(100);
        }
    }
    //render buttons
    void render_rect(SDL_Texture* texture, int x, int y, int w, int h) {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
};

#endif // _GRAPHICS__H
