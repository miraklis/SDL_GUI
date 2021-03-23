#ifndef UIINPUTBOX_H
#define UIINPUTBOX_H

#include "UILabel.h"

namespace SDL_GUI {

    class UIInputBox : public UILabel {
    public:
        UIInputBox(SDL_Renderer* renderer, std::string name, SDL_Rect rect);
        ~UIInputBox();
        void HandleInput();
        void SetFocus(bool focus);
        void SetMaxChar(size_t maxChar);
        Event<bool, std::string> OnInputFinished;
    private:
        bool focus;
        size_t maxChar;
    };

}

#endif // UIINPUTBOX_H