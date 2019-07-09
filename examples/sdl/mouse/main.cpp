#include <string>
#include <sstream>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

void drawBackground(SDL_Surface* screen) {
  SDL_FillRect( screen, NULL, 
    SDL_MapRGB(screen->format, 0xff, 0xff, 0xff) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

int main( int argc, char* argv[] ) {
  try {
   std::string filename = "fonts/FreeSerifBold.ttf";
   if ( argc == 2 ) { filename = argv[1]; }
   int size = 32;
   SDL_Init ( SDL_INIT_VIDEO ) ;
   atexit ( SDL_Quit ) ;
   SDL_Surface* screen = SDL_SetVideoMode (640 , 480 , 0, SDL_ANYFORMAT);
   if ( TTF_Init() == -1 ) {
      throw std::string("TTF_Init failed: ") + TTF_GetError();
   }
   atexit(TTF_Quit); // remember to quit SDL_ttf
   TTF_Font *font = TTF_OpenFont(filename.c_str(), size);
   if ( !font ) {
      throw std::string("TTF_OpenFont failed: ") + TTF_GetError();
   }

   std::string name = "Mouse Coordinates: ";
   SDL_Event event ;
   int x_coordinate = 0, y_coordinate = 0;
   while ( true ) {
     drawBackground(screen);
      SDL_PumpEvents();
      std::stringstream strm; 
      strm << name << x_coordinate << ", " << y_coordinate << std::ends;
      std::string message = strm.str();
      SDL_Color fg_color = {0, 0, 255, 0};
      SDL_Surface *stext = 
         TTF_RenderText_Solid(font, message.c_str(), fg_color);
      SDL_Rect dest = {120,240,0,0};
      // if srect is NULL, entire surface is copied
      SDL_BlitSurface( stext, NULL, screen, &dest );
      SDL_Flip(screen);
      if ( SDL_PollEvent ( &event ) ) {
         if ( event.type == SDL_QUIT ) break ;
         else if( event.type == SDL_MOUSEMOTION ) {
               SDL_GetMouseState(&x_coordinate, &y_coordinate);
         }
         else if( event.type == SDL_KEYDOWN ) {
            if( event.key.keysym.sym == SDLK_ESCAPE ) break;
         }
      }
   }
   TTF_CloseFont(font);
  }
  catch(const std::string& msg) { std::cout << msg << std::endl; }
  catch(...) { std::cout << "Oops!" << std::endl; }
  return 0;
}

