#include "UIComponent.h"

namespace SDL_GUI {

	UIComponent::UIComponent(std::string name, int x, int y) 
		: UIComponent(name, x, y, 0, 0)
	{}

	UIComponent::UIComponent(std::string name, int x, int y, size_t w, size_t h) 
	{
		_name = name;
		_rect.x = x;
		_rect.y = y;
		_rect.w = w;
		_rect.h = h;
		_visible = false;
	}

	UIComponent::~UIComponent() 
	{}

	void UIComponent::Show() 
	{
		_visible = true;
	}

	void UIComponent::Hide() 
	{
		_visible = false;
	}

	void UIComponent::SetPos(int x, int y) 
	{
		if(_rect.x == x && _rect.y == y)
			return;
		_rect.x = x;
		_rect.y = y;
	}

	void UIComponent::SetX(int x) 
	{
		SetPos(x, _rect.y);
	}

	void UIComponent::SetY(int y) 
	{
		SetPos(_rect.x, y);
	}

	void UIComponent::SetSize(size_t w, size_t h) 
	{
		if(_rect.w == w && _rect.h == h)
			return;
		_rect.w = w;
		_rect.h = h;
	}

	void UIComponent::SetWidth(size_t w) 
	{
		SetSize(w, _rect.h);
	}

	void UIComponent::SetHeight(size_t h) 
	{
		SetSize(_rect.w, h);
	}

	std::string UIComponent::GetName() const 
	{
		return _name;
	}

	bool UIComponent::IsVisible() const 
	{
		return _visible;
	}

	const SDL_Rect& UIComponent::GetRect() const 
	{
		return _rect;
	}

	int UIComponent::GetPosX() const 
	{
		return _rect.x;
	}

	int UIComponent::GetPosY() const 
	{
		return _rect.y;
	}

	size_t UIComponent::GetWidth() const 
	{
		return _rect.w;
	}

	size_t UIComponent::GetHeight() const 
	{
		return _rect.h;
	}

}