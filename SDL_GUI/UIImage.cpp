#include "UIImage.h"

namespace SDL_GUI {

	UIImage::UIImage(SDL_Renderer* renderer, std::string imgName, int x, int y) : 
			UIComponent(renderer, imgName, 0, 0) {
		_texture = LoadTexture(renderer, imgName);
		_rect.x = x;
		_rect.y = y;
		SDL_QueryTexture(_texture, nullptr, nullptr, &_rect.w, &_rect.h);
	}

	UIImage::~UIImage() {
		SDL_DestroyTexture(_texture);
	}

	void UIImage::Render() {
		if(!_visible)
			return;
		SDL_Rect src{ 0, 0, _rect.w, _rect.h };
		SDL_RenderCopy(_renderer, _texture, &src, &_rect);
	}

}
