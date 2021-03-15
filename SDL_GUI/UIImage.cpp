#include "UIImage.h"

namespace SDL_GUI {

	UIImage::UIImage(SDL_Renderer* renderer, std::string imgName, int x, int y) : 
			UIComponent(renderer, imgName, 0, 0, false) {
		texture = LoadTexture(renderer, imgName);
		rect.x = x;
		rect.y = y;
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	UIImage::~UIImage() {
		SDL_DestroyTexture(texture);
	}

	void UIImage::Render() {
		if(!visible)
			return;
		SDL_Rect src{ 0, 0, rect.w, rect.h };
		SDL_RenderCopy(renderer, texture, &src, &rect);
	}

}
