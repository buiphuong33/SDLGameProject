    /*SDL_Surface* surface = SDL_LoadBMP(path);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,0xFF,0,0xFF));
    SDL_Texture* texture = loadTexture(surface);
    SDL_FreeSurface(surface);

    SDL_Rect texture1;
    texture1.x = 0;
    texture1.y = 0;
    texture1.w = SCREEN_WIDTH;
    texture1.h = SCREEN_HEIGHT;

    SDL_Rect texture2;
    texture1.x = -(SCREEN_WIDTH);
    texture1.y = 0;
    texture1.w = SCREEN_WIDTH;
    texture1.h = SCREEN_HEIGHT;

    bool quit = false;
    SDL_Event e;
    while( !quit ) {

        while( SDL_PollEvent( &e ) != 0 ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
        graphics.setcolor();
        graphics.renderclear();
        SDL_Delay(5);
        ground1.x-=3;
        ground2.x-=3;
        if(ground1.x <-(SCREEN_WIDTH)) ground1.x = (SCREEN_WIDTH-10);
        if(ground2.x <-(SCREEN_WIDTH)) ground2.x = (SCREEN_WIDTH-10);
        graphics.cop(ground, &ground1);
        graphics.cop(ground, &ground2);
        graphics.presentScene();
    }
*/
