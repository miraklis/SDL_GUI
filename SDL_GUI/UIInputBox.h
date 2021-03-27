#ifndef UIINPUTBOX_H
#define UIINPUTBOX_H

#include "UILabel.h"

namespace SDL_GUI {

    class UIInputBox : public UILabel {
    public:
        UIInputBox(SDL_Renderer* renderer, std::string name);
        UIInputBox(SDL_Renderer* renderer, std::string name, std::string caption,
                int x, int y, size_t w, size_t h, bool autosize,
                std::string fontName, size_t fontSize,
                SDL_Color& bgColor, SDL_Color& fgColor,
                HorizontalAlign hAlign, VerticalAlign vAlign);
        ~UIInputBox() override;
        void HandleInput() override;
        void SetFocus(bool focus) override;
        void SetMaxChar(size_t maxChar) override;
        Event<bool, std::string> OnInputFinished;
    private:
        bool _focus;
        size_t _maxChar;
    };

}

#endif // UIINPUTBOX_H