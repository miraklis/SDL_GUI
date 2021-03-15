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
    if(cmd == "alLeft") {
        panel->AlignTextHorizontal(SDL_GUI::HorizontalAlign::Left);
    }
    if(cmd == "alCenter") {
        panel->AlignTextHorizontal(SDL_GUI::HorizontalAlign::Center);
    }
    if(cmd == "alRight") {
        panel->AlignTextHorizontal(SDL_GUI::HorizontalAlign::Right);
    }
    if(cmd == "alTop")
        panel->AlignItems(SDL_GUI::VerticalAlign::Top);
    if(cmd == "alMiddle")
        panel->AlignItems(SDL_GUI::VerticalAlign::Middle);
    if(cmd == "alBottom")
        panel->AlignItems(SDL_GUI::VerticalAlign::Bottom);
    if(cmd == "pnLBL1") {
        static int cnt = 0;
        if(cnt % 2 == 0) {
            (*panel)[0]->SetText("11");
            (*panel)[1]->SetText("222222");
            (*panel)[2]->SetText("3333");
        } else {
            (*panel)[0]->SetText("11111");
            (*panel)[1]->SetText("222");
            (*panel)[2]->SetText("3333333333");
        }
        cnt++;
    }
    if(cmd == "pnLBL2") {
        static int cnt = 0;
        if(cnt % 2 == 0) {
            (*panel)[0]->SetWidth(50);
            (*panel)[1]->SetWidth(50);
            (*panel)[2]->SetWidth(50);
        } else {
            (*panel)[0]->SetWidth(300);
            (*panel)[1]->SetWidth(300);
            (*panel)[2]->SetWidth(300);
        }
        cnt++;
    }
    if(cmd == "pnLBL3") {
        (*panel)[0]->SetFont("ka1.ttf", 32);
        (*panel)[1]->SetFont("ka1.ttf", 32);
        (*panel)[2]->SetFont("ka1.ttf", 32);
    }
    if(cmd == "pnLBL4") {
        if(panel->IsVisible())
            panel->Hide();
        else
            panel->Show();
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
    menu = make_unique<SDL_GUI::UIMenu>(renderer, "menu", 400, 10, 0, 0, SDL_GUI::sFonts::TTF_TIMES, 16, SDL_GUI::HorizontalAlign::Left, SDL_GUI::VerticalAlign::Middle, SDL_GUI::VerticalAlign::Top, bg, fg, selBG, selFG, nullptr, menuCommand);
    menu->AddItem("lblMove", "Label Move");
    menu->AddItem("lblSize", "Label Change Size");
    menu->AddItem("lblHorizontalAlign", "Label Change Horizontal Align");
    menu->AddItem("lblVerticalAlign", "Label Change Vertical Align");
    menu->AddItem("lblText", "Label Change Text");
    menu->AddItem("lblFont", "Label Change Font");
    menu->Show();

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
        SDL_RenderPresent(renderer);
    }
    if(lbl)
        delete lbl;
    SDL_Quit();
    return 0;
}