#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "UIMain.h"

namespace SDL_GUI 
{

	class UIComponent 
	{
	public:
		virtual ~UIComponent();
		virtual void Render() = 0;
		virtual void Show();
		virtual void Hide();
		virtual void SetPos(int x, int y);
		virtual void SetX(int x);
		virtual void SetY(int y);
		virtual void SetSize(size_t w, size_t h);
		virtual void SetWidth(size_t w);
		virtual void SetHeight(size_t h);
		virtual std::string GetName() const;
		virtual bool IsVisible() const;
		virtual const SDL_Rect& GetRect() const;
		virtual int GetPosX() const;
		virtual int GetPosY() const;
		virtual size_t GetWidth() const;
		virtual size_t GetHeight() const;
		Event<UIComponent*> OnResized;
	protected:
		UIComponent(SDL_Renderer* renderer, std::string name, int x, int y);
		UIComponent(SDL_Renderer* renderer, std::string name, int x, int y, size_t w, size_t h);
		SDL_Renderer* _renderer;
		std::string _name;
		SDL_Rect _rect;
		bool _visible;
	};

}

#endif //UICOMPONENT_H