#ifndef UIINPUTBOX_H
#define UIINPUTBOX_H

#include "UIPanel.h"
#include "UILabel.h"

namespace SDL_GUI {

    class UIInputBox : public UIPanel {
    public:
        UIInputBox(SDL_Renderer* renderer, std::string name, std::string title);
        UIInputBox(SDL_Renderer* renderer, std::string name, std::string title,
                    int x, int y, size_t maxChar, std::string fontName, size_t fontSize,
                    SDL_Color& bgColor, SDL_Color& fgColor, HorizontalAlign hTextAlign);
        ~UIInputBox() override;
        void HandleInput();
        void SetFocus(bool focus);
        void SetMaxChar(size_t maxChar);
        Event<bool, std::string> OnInputFinished;
    private:
        std::unique_ptr<UILabel> _title;
        std::unique_ptr<UILabel> _content;
        bool _focus;
        size_t _maxChar;
    };

}

#endif // UIINPUTBOX_H