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
void loadScreen(SDL_Texture* point, char* pointer[], int count, TTF_Font* font, SDL_Color color, SDL_Texture* number, char* life[], int countLife, SDL_Texture* quiz) {
    if (countLife < 4) {
                const char* num = life[countLife];
                number = graphics.renderText(num, font, color);
                const char* pt = pointer[count];
                point = graphics.renderText(pt, font, color);
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                graphics.renderTexture(number, 165, 455);
                graphics.renderTexture(point, 165, 405);
                graphics.renderTexture(quiz, 300, 350);
                graphics.presentScene();
                }
    else {
                Mix_Chunk *gameFail = graphics.loadSound("gameFail.mp3");
                graphics.play(gameFail);
                const char* num = life[countLife];
                number = graphics.renderText(num, font, color);
                point = graphics.renderText("0", font, color);
                quiz = graphics.loadTexture("gameover.png");
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                graphics.renderTexture(number, 165, 455);
                graphics.renderTexture(point, 165, 405);
                graphics.renderTexture(quiz, 300, 350);
                graphics.presentScene();
                SDL_Delay(5000);
                graphics.quit();
}
}



int main(int argc, char *argv[])
{
    srand((int)time(0));
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

    SDL_Texture* number = graphics.renderText("3", font, color);
    graphics.renderTexture(number, 180, 455);
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


    char* pointer[10000] = {"0", "100", "200", "300", "400", "500",};
    bool checkStatus[20] = {false};
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
        SDL_Texture* quiz = texList.at(0);
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
                if (mouseX <=398 && mouseX >=378 && mouseY <=546 && mouseY>=526 && checkStatus[count] == false) {
                graphics.play(trueMusic);
                checkStatus[count] = true;
                count++;
                graphics.renderTexture(mouse, 378, 526);
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                const char* pt = pointer[count];
                point = graphics.renderText(pt, font, color);
                graphics.renderTexture(point, 165, 405);
                graphics.presentScene();

                status = true;
                break;
                }
                else {
                    graphics.play(failMusic);
                    countLife++;
                    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
                }
        }
        }
        SDL_Delay(100);
    }
    quiz = graphics.loadTexture("quiz/hinh2.JPG");
    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);


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
                if (mouseX <=441 && mouseX >=421 && mouseY <=428 && mouseY>=408 && checkStatus[count] == false) { // Hien thi dap an
                graphics.play(trueMusic);
                checkStatus[count] = true;
                count++;
                graphics.renderTexture(mouse, 378, 526);
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                point = graphics.renderText("200", font, color);
                graphics.renderTexture(point, 165, 405);
                graphics.presentScene();
                status = true;
                break;
                }
                else {
                    graphics.play(failMusic);
                    countLife++;
                    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
                }
        }
        }
        SDL_Delay(100);
    }





    quiz = graphics.loadTexture("quiz/hinh3.JPG");
    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
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
                if (mouseX <=567 && mouseX >=547 && mouseY <=624 && mouseY>=604 && checkStatus[count] == false) { // Hien thi dap an
                graphics.play(trueMusic);
                checkStatus[count] = true;
                count++;
                graphics.renderTexture(mouse, 378, 526);
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                point = graphics.renderText("300", font, color);
                graphics.renderTexture(point, 165, 405);
                graphics.presentScene();
                status = true;
                break;
                }
                else {
                    graphics.play(failMusic);
                    countLife++;
                    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
                }
        }
        }
        SDL_Delay(100);
    }



    quiz = graphics.loadTexture("quiz/hinh4.JPG");
    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
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
                if (mouseX <=513 && mouseX >=493 && mouseY <=633 && mouseY>=613 && checkStatus[count] == false) { // Hien thi dap an
                graphics.play(trueMusic);
                checkStatus[count] = true;
                count++;
                graphics.renderTexture(mouse, 378, 526);
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                point = graphics.renderText("400", font, color);
                graphics.renderTexture(point, 165, 405);
                graphics.presentScene();
                status = true;
                break;
                }
                else {
                    graphics.play(failMusic);
                    countLife++;
                    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
                }
        }
        }
        SDL_Delay(100);
    }



    quiz = graphics.loadTexture("quiz/hinh5.JPG");
    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
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
                if (mouseX <=900 && mouseX >=300 && mouseY <=750 && mouseY>=350){
                if (mouseX <=333 && mouseX >=313 && mouseY <=628 && mouseY>=608 && checkStatus[count] == false) { // Hien thi dap an
                graphics.play(trueMusic);
                checkStatus[count] = true;
                count++;
                graphics.renderTexture(mouse, 378, 526);
                SDL_RenderClear(graphics.renderer);
                graphics.loadMainScreen();
                point = graphics.renderText("500", font, color);
                graphics.renderTexture(point, 165, 405);
                graphics.presentScene();
                status = true;
                break;
                }
                else {
                    graphics.play(failMusic);
                    countLife++;
                    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);
                }
        }
        }
        SDL_Delay(100);
    }

    if(count == 5) {
    Mix_Chunk *gameWin = graphics.loadSound("Win.mp3");
    graphics.play(gameWin);
    quiz = graphics.loadTexture("completed.png");
    loadScreen(point, pointer, count, font, color, number, life, countLife, quiz);

    graphics.renderTexture(quiz, 300, 350);
    graphics.presentScene();
    }






    SDL_Delay(5000);


    graphics.quit();
    return 0;
}

