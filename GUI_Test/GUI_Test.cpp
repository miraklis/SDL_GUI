#define SDL_MAIN_HANDLED

#include <iostream>
#include <memory>
using namespace std;

#include "SDL.h"
#include "SDL_GUI.h"
#include "UIMenu.h"
#include "UIPanel.h"

SDL_Color white = { 255, 255, 255, 255 };
SDL_Color black = { 0,0,0,255 };
SDL_Color red = { 255, 0, 0, 255 };
SDL_Color green = { 0, 255, 0, 255 };
SDL_Color blue = { 0, 0, 255, 255 };
SDL_Color dred = { 128, 0, 0, 255 };
SDL_Color dgreen = { 0, 128, 0, 255 };
SDL_Color dblue = { 0, 0, 128, 255 };

SDL_Renderer* renderer;
bool running{ true };
unique_ptr<SDL_GUI::UIMenu> menu;
unique_ptr<SDL_GUI::UIPanel> panel;
SDL_GUI::UIInputBox* in;

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

void inputfinished(bool entered, string s) {
    in->SetFocus(false);
    menu->SetFocus(true);
    unique_ptr<SDL_GUI::UILabel> lbl = std::make_unique<SDL_GUI::UILabel>(
        renderer, "lbl4", s,
        0, 0, 0, 0, false,
        SDL_GUI::sFonts::TTF_TIMES, 48,
        dred, white,
        SDL_GUI::HorizontalAlign::Left, SDL_GUI::VerticalAlign::Top);
    panel->AddItem(std::move(lbl));
}

bool menuCommand(string cmd) {
    if(cmd=="esc")
        running = false;
    if(cmd == "panelHorizontalAlign") {
        static int cnt = 0;
        if(cnt % 3 == 0)
            panel->SetHorizontalAlign(SDL_GUI::HorizontalAlign::Left);
        else if(cnt % 3 == 1)
            panel->SetHorizontalAlign(SDL_GUI::HorizontalAlign::Center);
        else
            panel->SetHorizontalAlign(SDL_GUI::HorizontalAlign::Right);
        cnt++;
    }
    if(cmd == "panelVerticalAlign") {
        static int cnt = 0;
        if(cnt % 3 == 0)
            panel->SetVerticalAlign(SDL_GUI::VerticalAlign::Top);
        else if(cnt % 3 == 1)
            panel->SetVerticalAlign(SDL_GUI::VerticalAlign::Middle);
        else
            panel->SetVerticalAlign(SDL_GUI::VerticalAlign::Bottom);
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
    if(cmd == "panelRemove") {
        panel->RemoveItem("lbl2");
    }
    return true;
}

int main()
{
    initSDL();

    menu = make_unique<SDL_GUI::UIMenu>(renderer, "menu", 0, 0, nullptr, menuCommand);
    menu->SetDefaultColors(dred, white, red, white);
    menu->SetDefaultHorAlign(SDL_GUI::HorizontalAlign::Center);
    menu->SetDefaultVerAlign(SDL_GUI::VerticalAlign::Middle);
    menu->AddLabel("panelHorizontalAlign", "Change Horizontal Align");
    menu->AddLabel("panelVerticalAlign", "Change Vertical Align");
    menu->AddLabel("panelChange", "Change Item");
    menu->AddLabel("panelRemove", "Remove Item");
    menu->Show();
    
    int sX = 400;
    int sY = 300;
    panel = std::make_unique<SDL_GUI::UIPanel>(renderer, "panel", sX, sY);
    panel->SetDefaultColors(red, white);
    panel->AddLabel("lbl1", "This is first test");
    panel->AddLabel("lbl2", "This is second test");
    panel->AddLabel("lbl3", "This is third test");
    panel->Show();

    std::unique_ptr<SDL_GUI::UIInputBox> input = std::make_unique<SDL_GUI::UIInputBox>(renderer, "input");
    input->SetFocus(true);
    input->SetMaxChar(10);
    input->OnInputFinished.AddListener(inputfinished);
    panel->AddItem(std::move(input));
    in = static_cast<SDL_GUI::UIInputBox*>(panel->operator[]("input"));

    while(running) {
        menu->HandleEvents();
        if(in)
            in->HandleInput();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(renderer, 0, sY, 1000, sY);
        SDL_RenderDrawLine(renderer, sX, 0, sX, 1000);
        menu->Render();
        panel->Render();
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return 0;
}