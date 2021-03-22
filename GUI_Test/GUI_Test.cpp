#define SDL_MAIN_HANDLED

#include <iostream>
#include <memory>
using namespace std;

#include "SDL.h"
#include "SDL_GUI.h"

SDL_Renderer* renderer;
bool running{ true };
unique_ptr<SDL_GUI::UIPanel> panel;
unique_ptr<SDL_GUI::UIMenu> menu;
SDL_GUI::UILabel* lbl;

void initSDL() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        exit(1);
    }
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    int screenWidth = dm.w/2;
    int screenHeight = dm.h/2;

    SDL_Window* window = SDL_CreateWindow("GUI TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if(!window) {
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        exit(1);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    if(TTF_Init() < 0) {
        exit(1);
    }
}

bool menuCommand(string cmd) {
    if(cmd=="esc")
        running = false;
    if(cmd == "panelHorizontalAlign") {
        static int cnt = 0;
        if(cnt % 3 == 0)
            panel->AlignHorizontal(SDL_GUI::HorizontalAlign::Left);
        else if(cnt % 3 == 1)
            panel->AlignHorizontal(SDL_GUI::HorizontalAlign::Center);
        else
            panel->AlignHorizontal(SDL_GUI::HorizontalAlign::Right);
        cnt++;
    }
    if(cmd == "panelVerticalAlign") {
        static int cnt = 0;
        if(cnt % 3 == 0)
            panel->AlignVertical(SDL_GUI::VerticalAlign::Top);
        else if(cnt % 3 == 1)
            panel->AlignVertical(SDL_GUI::VerticalAlign::Middle);
        else
            panel->AlignVertical(SDL_GUI::VerticalAlign::Bottom);
        cnt++;
    }
    if(cmd == "panelTextHorizontalAlign") {
        static int cnt = 0;
        if(cnt % 3 == 0)
            panel->AlignTextHorizontal(SDL_GUI::HorizontalAlign::Left);
        else if(cnt % 3 == 1)
            panel->AlignTextHorizontal(SDL_GUI::HorizontalAlign::Center);
        else
            panel->AlignTextHorizontal(SDL_GUI::HorizontalAlign::Right);
        cnt++;
    }
    if(cmd == "panelTextVerticalAlign") {
        static int cnt = 0;
        if(cnt % 3 == 0)
            panel->AlignTextVertical(SDL_GUI::VerticalAlign::Top);
        else if(cnt % 3 == 1)
            panel->AlignTextVertical(SDL_GUI::VerticalAlign::Middle);
        else
            panel->AlignTextVertical(SDL_GUI::VerticalAlign::Bottom);
        cnt++;
    }
    if(cmd == "panelMove") {
        static int cnt = 0;
        if(cnt % 2 == 0)
            panel->SetPos(700, 400);
        else
            panel->SetPos(200, 300);
        cnt++;
    }
    if(cmd == "panelChange") {
        static int cnt = 0;
        if(cnt % 2 == 0)
            (*panel)[0]->SetText("abcdefghijklmnopqrstuywxyzabcdefghijklmnopqrseooijenfnv");
        else
            (*panel)[0]->SetText("");
        cnt++;
    }
    if(cmd == "lblMove") {
        static int cnt = 0;
        if(cnt % 2 == 0)
            lbl->SetPos(100, 0);
        else
            lbl->SetPos(0,0);
        cnt++;
    }
    if(cmd == "lblSize") {
        static int cnt = 0;
        if(cnt % 2 == 0)
            lbl->SetWidth(50);
        else
            lbl->SetWidth(200);
        cnt++;
    }
    if(cmd == "lblHorizontalAlign") {
        static int cnt = 0;
        if(cnt %3 == 0)
            lbl->AlignHorizontal(SDL_GUI::HorizontalAlign::Left);
        else if(cnt % 3 == 1)
            lbl->AlignHorizontal(SDL_GUI::HorizontalAlign::Center);
        else
            lbl->AlignHorizontal(SDL_GUI::HorizontalAlign::Right);
        cnt++;
    }
    if(cmd == "lblVerticalAlign") {
        static int cnt = 0;
        if(cnt % 3 == 0)
            lbl->AlignVertical(SDL_GUI::VerticalAlign::Top);
        else if(cnt % 3 == 1)
            lbl->AlignVertical(SDL_GUI::VerticalAlign::Middle);
        else
            lbl->AlignVertical(SDL_GUI::VerticalAlign::Bottom);
        cnt++;
    }
    if(cmd == "lblText") {
        static int cnt = 0;
        if(cnt % 2 == 0)
            lbl->SetText("123");
        else
            lbl->SetText("This is a very long test!!!");
        cnt++;
    }
    if(cmd == "lblFont") {
        static int cnt = 0;
        if(cnt % 2 == 0)
            lbl->SetFont(SDL_GUI::sFonts::TTF_ARCADE, 32);
        else
            lbl->SetFont(SDL_GUI::sFonts::TTF_TIMES, 16);
        cnt++;
    }
    return true;
}

int main()
{
    initSDL();

    SDL_Color bg = { 128, 0, 0, 255 }; // dark red
    SDL_Color fg = { 255, 255, 255, 255 }; // white
    SDL_Color selBG = { 255, 0, 0, 255 }; // red
    SDL_Color selFG = { 255, 255, 255, 255 }; // white
    menu = make_unique<SDL_GUI::UIMenu>(
        renderer, "menu", 500, 150, 0, 0, 
        SDL_GUI::sFonts::TTF_TIMES, 16, 
        SDL_GUI::HorizontalAlign::Center, SDL_GUI::VerticalAlign::Middle,
        bg, fg, selBG, selFG,
        nullptr, menuCommand);
    menu->AddItem("panelHorizontalAlign", "Panel Change Horizontal Align");
    menu->AddItem("panelVerticalAlign", "Panel Change Vertical Align");
    menu->AddItem("panelTextHorizontalAlign", "Panel Change Text Horizontal Align");
    menu->AddItem("panelTextVerticalAlign", "Panel Change Text Vertical Align");
    menu->AddItem("panelMove", "Panel Move");
    menu->AddItem("panelChange", "Panel Change Item");
    menu->AddItem("lblMove", "Label Move");
    menu->AddItem("lblSize", "Label Change Size");
    menu->AddItem("lblHorizontalAlign", "Label Change Horizontal Align");
    menu->AddItem("lblVerticalAlign", "Label Change Vertical Align");
    menu->AddItem("lblText", "Label Change Text");
    menu->AddItem("lblFont", "Label Change Font");
    menu->Show();

    panel = make_unique<SDL_GUI::UIPanel>(
        renderer, "menu", 200, 300, 200, 200, true,
        SDL_GUI::sFonts::TTF_TIMES, 16,
        SDL_GUI::HorizontalAlign::Center, SDL_GUI::VerticalAlign::Middle,
        bg, fg);
    panel->AddItem("Test1", "This is Test");
    panel->AddItem("Test2", "Testing");
    panel->AddItem("Test3", "This is a very Long Test");
    panel->Show();
    lbl = new SDL_GUI::UILabel(renderer, "lbl", "This is a test", SDL_GUI::sFonts::TTF_TIMES, 16, 0, 0, 200, 100, false, 
                               SDL_GUI::HorizontalAlign::Left, SDL_GUI::VerticalAlign::Top, { 0,0,255,255 }, { 255,255,255,255 });
    lbl->Show();

    //SDL_Event event;
    while(running) {
        menu->HandleEvents();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        menu->Render();
        lbl->Render();
        panel->Render();
        SDL_RenderPresent(renderer);
    }
    if(lbl)
        delete lbl;
    SDL_Quit();
    return 0;
}