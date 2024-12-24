#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "data.h"

bool CheckCollision(SDL_Rect rect1, SDL_Rect rect2){
    if((rect1.x+rect1.w) > rect2.x && rect1.x < (rect2.x + rect2.w) && (rect1.y+rect1.h) > rect2.y && rect1.y < (rect2.y + rect2.h)){
        return true;
    }
    return false;
}




class Snake{
    public:
        int x;
        int y;
        int w;
        int h;
        int dirX;
        int dirY;

        std::vector<SDL_Rect> body = {};

        void Move(bool* isOpen, SDL_Rect *fruit){
            for(int i = body.size()-1; i > -1; i--){
                if(i == 0){
                    body[i].x += dirX*w;
                    body[i].y += dirY*h;
                    if(body[i].x < 0){
                        body[i].x = WIDTH-(WIDTH/CELL_COUNT_X);
                    }
                    else if(body[i].y > HEIGHT){
                        body[i].y = 0;
                    }

                    else if(body[i].y < 0){
                        body[i].y = HEIGHT-(HEIGHT/CELL_COUNT_Y);
                    }
                    else if(body[i].x > WIDTH){
                        body[i].x = 0;
                    }

                    for(int i = 0; i < body.size(); i++){
                        if(i == 0){
                            continue;
                        }
                        if(body[0].x == body[i].x && body[0].y == body[i].y){

                            *isOpen = false;
                        }
                    }
                }
                else{
                    body[i].x = body[i-1].x;
                    body[i].y = body[i-1].y;
                }
            }
            if(body[0].x == fruit->x && body[0].y == fruit->y ){
                AddBody();
                fruit->x = (rand() % CELL_COUNT_X)*(WIDTH/CELL_COUNT_X);
                fruit->y = (rand() % CELL_COUNT_Y)*(HEIGHT/CELL_COUNT_Y);
            }

        }


        void AddBody(){
            SDL_Rect rect;
            rect.x = body[body.size()-1].x - dirX*w;
            rect.y = body[body.size()-1].y - dirY*h;
            rect.w = w+1;
            rect.h = h+1;

            body.push_back(rect);
        }

        void Render(SDL_Renderer* renderer){
            SDL_Rect* bodyArray = &body[0];
            SDL_SetRenderDrawColor(renderer, 1, 77, 3, 0);
            SDL_RenderFillRects(renderer, bodyArray, body.size());
            SDL_SetRenderDrawColor(renderer, 4, 31, 5, 0);
            SDL_RenderDrawRects(renderer, bodyArray, body.size());
        }

        Snake(int X, int Y, int W, int H, int dirx, int diry){
            x=X;
            y=Y;
            w=W;
            h=H;
            dirX=dirx;
            dirY=diry;

            SDL_Rect rect;
            rect.x = x;
            rect.y = x;
            rect.w = w+1;
            rect.h = h+1;
            body.push_back(rect);
        }

};





void DrawGrid(SDL_Renderer* renderer, int width, int height, int cell_count_y, int cell_count_x);


Snake snake(0, 0, (WIDTH/CELL_COUNT_X), (HEIGHT/CELL_COUNT_Y), 1, 0);

SDL_Rect fruit;


void start(){

    fruit.x = (rand() % CELL_COUNT_X)*(WIDTH/CELL_COUNT_X);
    fruit.y = (rand() % CELL_COUNT_X)*(HEIGHT/CELL_COUNT_Y);
    fruit.w = (WIDTH/CELL_COUNT_X);
    fruit.h = (HEIGHT/CELL_COUNT_Y);
}

void input(SDL_Event e){
        /* Look for a keypress */
    if(e.type == SDL_KEYDOWN){
        if(e.key.keysym.sym == SDLK_LEFT && snake.dirX != 1){
            snake.dirY = 0;
            snake.dirX = -1;
        }
        else if(e.key.keysym.sym == SDLK_RIGHT && snake.dirX != -1){
            snake.dirY = 0;
            snake.dirX = 1;
        }
        else if(e.key.keysym.sym == SDLK_UP && snake.dirY != 1){
            snake.dirX = 0;
            snake.dirY = -1;
        }
        else if(e.key.keysym.sym == SDLK_DOWN && snake.dirY != -1){
            snake.dirX = 0;
            snake.dirY = 1;
        }
    }
}

void update(bool* isOpen){
    snake.Move(isOpen, &fruit);
}

void render(SDL_Renderer* renderer){
    DrawGrid(renderer, WIDTH, HEIGHT, CELL_COUNT_X, CELL_COUNT_Y);
    snake.Render(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &fruit);
    
}



void DrawGrid(SDL_Renderer* renderer, int width, int height, int cell_count_y, int cell_count_x){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int i = (width/cell_count_x); i < width; i+=(width/cell_count_x)){
        SDL_RenderDrawLine(renderer, i, 0, i, height);
    }
    for(int i = (height/cell_count_y); i < height; i+=(height/cell_count_y)){
        SDL_RenderDrawLine(renderer, 0, i, width, i);
    }
}

