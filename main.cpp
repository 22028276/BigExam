#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "defs.h"
#include "SDL_ttf.h"
#include<algorithm>
#include<time.h>
#include<string>
#include<vector>
#include <SDL_mixer.h>
using namespace std;
struct Graphics graphics;




void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void loadScreen(SDL_Texture* point, char* pointer[], int count, TTF_Font* font, SDL_Color color, SDL_Texture* number1, char* life[], int countLife, SDL_Texture* quiz, int number) {
    if (countLife < 4) {
                const char* num = life[countLife];
                number1 = graphics.renderText(num, font, color);
                const char* pt = pointer[count];
                point = graphics.renderText(pt, font, color);
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                graphics.renderTexture(number1, 165, 455);
                graphics.renderTexture(point, 165, 405);
                graphics.renderTexture(quiz, 300, 350);
                graphics.presentScene();
                }
    else {
                Mix_Chunk *gameFail = graphics.loadSound("gameFail.mp3");
                graphics.play(gameFail);
                const char* num = life[countLife];
                number1 = graphics.renderText(num, font, color);
                const char* pt = pointer[count];
                point = graphics.renderText(pt, font, color);
                quiz = graphics.loadTexture("gameover.png");
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                graphics.renderTexture(number1, 165, 455);
                graphics.renderTexture(point, 165, 405);
                graphics.renderTexture(quiz, 300, 350);
                graphics.presentScene();
                SDL_Delay(5000);
                graphics.quit();
                number = 100;
}
}



int main(int argc, char *argv[])
{

    int number = 0;

int resX[1000] = {389,421,564,493,327,314,495,324,478,460,337,348,335,488,486,506};
int resY[1000] = {538,408,614,613,617,715,515,550,486,565,690,539,435,596,416,501};
srand(static_cast<unsigned int>(time(0)));
    int arr[5] = {};
    while (number < 5) {
        int rand_num = rand() % 16;
        bool exists = false;
        for (int i = 0; i < number; ++i) {
            if (arr[i] == rand_num) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            arr[number] = rand_num;
            number++;
        }
    }
    graphics.init();
    graphics.loadMainScreen();
    SDL_Texture* start = graphics.loadTexture("imgMenu/start.png");
    SDL_Texture* quit = graphics.loadTexture("imgMenu/exit.png");
    graphics.renderTexture(start, 440, 350);
    graphics.renderTexture(quit, 440, 480);
    graphics.presentScene();

    TTF_Font* font = graphics.loadFont("AlexBrush-Regular.ttf", 40);
    SDL_Color color = {255, 36, 0, 0};
    SDL_Texture* mouse  = graphics.loadTexture("circle.png");
    SDL_Texture* point = graphics.renderText("0", font, color);
    graphics.renderTexture(point, 180, 405);

    SDL_Texture* number1 = graphics.renderText("3", font, color);
    graphics.renderTexture(number1, 180, 455);
    Mix_Music *gMusic = graphics.loadMusic("theme.mp3");
    Mix_Chunk *trueMusic = graphics.loadSound("true.mp3");
    Mix_Chunk *failMusic = graphics.loadSound("fail.mp3");
    graphics.play(gMusic);

    char* life[5] = {"3","2","1","0","0"};

    int countLife = 0;
    vector<SDL_Texture*> texList;
    texList.push_back(graphics.loadTexture("quiz/hinh1.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh2.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh3.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh4.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh5.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh6.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh7.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh8.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh9.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh10.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh11.png"));
    texList.push_back(graphics.loadTexture("quiz/hinh12.png"));
    texList.push_back(graphics.loadTexture("quiz/hinh13.png"));
    texList.push_back(graphics.loadTexture("quiz/hinh14.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh15.jpg"));
    texList.push_back(graphics.loadTexture("quiz/hinh16.jpg"));


    char* pointer[10000] = {"0", "100", "200", "300", "400", "500", "600", "700", "800", "900", "1000"};
    int count = 0;
    bool status = false;
    SDL_Event event;
    int x, y;
    while (status == false) {
        SDL_GetMouseState(&x, &y);
        cerr << x << ", " << y << endl;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (mouseX <=708 && mouseX >=484 && mouseY <=504 && mouseY>=410) {
                        status = true;
                }
                else if (mouseX <=694 && mouseX >=484 && mouseY <=633 && mouseY>=550) {
                        graphics.quit();
                        return 0;
                }
        }
    }
    number = 0;
    SDL_Texture* quiz;
    while (number<=4) {
    quiz = texList.at(arr[number]);
    loadScreen(point, pointer, count, font, color, number1, life, countLife, quiz, number);
    graphics.renderTexture(quiz, 300, 350);
    graphics.presentScene();
    status = false;
    while (status == false) {
        SDL_GetMouseState(&x, &y);
        cerr << x << ", " << y << endl;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;

            case SDL_MOUSEBUTTONDOWN:

                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if (mouseX <=900 && mouseX >=300 && mouseY <=750 && mouseY>=350) {
                if ((mouseX <=(resX[arr[number]]+20) && mouseX >=(resX[arr[number]]-20)) || (mouseX <=(resX[arr[number]]+320) && mouseX >= (resX[arr[number]]+280))) {
                     if ((mouseY <=(resY[arr[number]]+10) && mouseY>=(resY[arr[number]]-10))|| (mouseY <=(resY[number]+10) && mouseY>=(resY[number]-10))) {
                graphics.play(trueMusic);
                count++;
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                const char* pt = pointer[count];
                point = graphics.renderText(pt, font, color);
                graphics.renderTexture(point, 165, 405);
                graphics.presentScene();
                number++;
                status = true;
                break;
                }
                else {
                    graphics.play(failMusic);
                    countLife++;
                    loadScreen(point, pointer, count, font, color, number1, life, countLife, quiz, number);
                    status = true;
                }
        }
        else {
                    graphics.play(failMusic);
                    countLife++;
                    loadScreen(point, pointer, count, font, color, number1, life, countLife, quiz, number);
                    status = true;
                }
        }
        SDL_Delay(50);

    }
    }
    }


    if(count == 5) {
    Mix_Chunk *gameWin = graphics.loadSound("Win.mp3");
    graphics.play(gameWin);
    quiz = graphics.loadTexture("completed.png");
    loadScreen(point, pointer, count, font, color, number1, life, countLife, quiz, number);

    graphics.renderTexture(quiz, 300, 350);
    graphics.presentScene();
    }
    SDL_Delay(5000);


    graphics.quit();
    return 0;
}


