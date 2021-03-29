#include <iostream>
using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 800;
#define HEIGHT 500;

bool running,fullScreen;
SDL_Renderer* renderer;
SDL_Window* window;

int lastFrame, fps, frameCount;

void input(){
    SDL_Event e;
    while(SDL_PollEvent(&e)){ //si apreto la cruz roja de la ventana
        if(e.type == SDL_QUIT) running = false;
    }
    const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
    if(keyStates[SDL_SCANCODE_ESCAPE]) running = false; //si apreto la tecla de escape
    if(keyStates[SDL_SCANCODE_F]) fullScreen = !fullScreen; //si apreto la tecla F
}

/*
void drawOne(SDL_Rect numeros[],int sel){
    
}
*/

void draw(SDL_Rect numeros[],int sel){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_Rect fondo;
    fondo.x = fondo.y = 0;
    fondo.w = WIDTH;
    fondo.h = HEIGHT;
    SDL_RenderFillRect(renderer,&fondo);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    for(int i = 0; i<100;i++){        
        if(sel == i){
            SDL_SetRenderDrawColor(renderer,252,38,0,100);
        }
        else{
            SDL_SetRenderDrawColor(renderer,3,152,252,255);
        }
        SDL_RenderFillRect(renderer,&numeros[i]);
        
        //SDL_RenderPresent(renderer);
    }
    SDL_RenderPresent(renderer);
    
    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if(timerFPS < (1000/100)){
        SDL_Delay((1000/100)-timerFPS);
    }
}
void update(){
    if(fullScreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullScreen) SDL_SetWindowFullscreen(window, 0);
}

int main(){
    srand(time(0));
    SDL_Rect numeros[100];
    for(int i = 1; i<=100;i++){        
        numeros[i-1].x = 800/100*i - 800/100;
        numeros[i-1].y = 0;
        numeros[i-1].w = 800/100;
        numeros[i-1].h = rand() % 500;
        SDL_RenderFillRect(renderer,&numeros[i]);
        SDL_RenderPresent(renderer);
    }

    fullScreen = false;
    running = true;
    int lastTime = 0;
    // retutns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    if(SDL_CreateWindowAndRenderer(800,500,0,&window,&renderer) != 0) cout << "Error al crear ventana\n";
    SDL_SetWindowTitle(window,"Brute Force Sorting Algorithm");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"2");
    //window = SDL_CreateWindow("GAME",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500, 500, 0);
    int seleccionado;
    bool ordenado = false;
    while (running){ //bucle principal
        lastFrame = SDL_GetTicks();
        if(lastFrame>=(lastTime+1000)){
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
        }
        cout<<fps<<endl;
        
        //sort brute force
        SDL_Rect menor;
        //menor = numeros[0];
        int indice;
        //ordenamos por valor de altura
        if(!ordenado){
            for(int j = 0; j<100;j++){
                update();
                input();
                //draw(numeros,indice);
                //SDL_Delay(100);
                menor = numeros[j];
                indice = j;
                for(int i = j; i<100;i++){
                    if(numeros[i].h < menor.h){
                        indice = i;
                        menor.h = numeros[i].h;
                    }
                    //-----------
                    lastFrame = SDL_GetTicks();
                    if (lastFrame >= (lastTime + 1000))
                    {
                        lastTime = lastFrame;
                        fps = frameCount;
                        frameCount = 0;
                    }
                    //-----------
                    draw(numeros,i);
                }
                if(j != indice){ //hago switch
                    int valor = numeros[j].h;
                    numeros[j].h = menor.h;
                    numeros[indice].h = valor;
                }
            }
            ordenado = true;
        }
        update();
        input();
        seleccionado = 99;
        //draw(numeros,seleccionado);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}