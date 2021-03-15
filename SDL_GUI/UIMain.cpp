#include "UIMain.h"

namespace SDL_GUI {

    // Fonts constants
	const char* sFonts::TTF_TIMES = "assets/times.ttf";
	const char* sFonts::TTF_ARCADE = "assets/arcade.ttf";
	const char* sFonts::TTF_BLOX2 = "assets/blox2.ttf";
	const char* sFonts::TTF_KA1 = "assets/ka1.ttf";

    // SDL Helper Utilities
    SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string textureFile) {
        SDL_Surface* tmpSurface = IMG_Load(textureFile.c_str());
        if(!tmpSurface)
            return nullptr;
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
        if(!texture)
            return nullptr;
        return texture;
    }

}