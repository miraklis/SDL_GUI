#ifndef UIMENU_H
#define UIMENU_H

#include "UIMain.h"
#include "UIPanel.h"

namespace SDL_GUI {

	class UIMenu : public UIPanel, public std::enable_shared_from_this<UIMenu> {
	public:
		UIMenu(SDL_Renderer* renderer, std::string name, int x, int y, std::shared_ptr<UIMenu> parent, std::function<bool(std::string)> callback);
		~UIMenu() override;
		void SetDefaultColors(SDL_Color bgColor, SDL_Color fgColor, SDL_Color selBGColor, SDL_Color selFGColor);
		std::shared_ptr<UIMenu> CreateSubMenu(std::string name);
		void HandleEvents();
		void AddItem(std::unique_ptr<UILabel> newItem) override;
		void AddItem(std::string name, std::string caption) override;
		void SelectItem(size_t index);
		void SetFocus(bool focus);
		std::shared_ptr<UIMenu> GetParent();
	private:
		std::function<bool(std::string)> _callback;
		std::shared_ptr<UIMenu> _parent;
		size_t _selectedItem;
		size_t _upLimit;
		SDL_Color _selFGColor;
		SDL_Color _selBGColor;
		bool _focus;
	};

}

#endif //UIMENU_H