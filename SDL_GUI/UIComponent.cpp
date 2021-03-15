#include "UIComponent.h"

namespace SDL_GUI {

	UIComponent::UIComponent(SDL_Renderer* renderer, std::string name, int x, int y, size_t w, size_t h, bool visible) {
		this->renderer = renderer;
		this->name = name;
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		this->visible = visible;
		this->OnSizeChanged.AddListener(std::bind(&UIComponent::SizeChanged, this, std::placeholders::_1));
	}

	UIComponent::~UIComponent() {}

	void UIComponent::SizeChanged(UIComponent* sender) {}

	std::string UIComponent::GetName() {
		return name;
	}

	void UIComponent::Show() {
		visible = true;
	}

	void UIComponent::Hide() {
		visible = false;
	}

	bool UIComponent::IsVisible() {
		return visible;
	}

	void UIComponent::SetPos(int x, int y) {
		rect.x = x;
		rect.y = y;
	}

	void UIComponent::SetX(int x) {
		SetPos(x, rect.y);
	}

	void UIComponent::SetY(int y) {
		SetPos(rect.x, y);
	}

	void UIComponent::SetSize(size_t w, size_t h) {
		if(rect.w == w && rect.h == h)
			return;
		rect.w = w;
		rect.h = h;
		OnSizeChanged(this);
	}

	void UIComponent::SetWidth(size_t w) {
		SetSize(w, rect.h);
	}

	void UIComponent::SetHeight(size_t h) {
		SetSize(rect.w, h);
	}

	const SDL_Rect& UIComponent::GetRect() {
		return rect;
	}

}