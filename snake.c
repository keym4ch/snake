#include <stdio.h>
#include <unistd.h>
#include <conio.h>
#include <stdlib.h>

//Attempted to add a tail. The solution doesn't seem logical, the next version will be made using curses.h library.
//This is the final version of the snake.exe for now, a.k.a. "taillessSnake.exe".


int xdir,ydir,h,w;
useconds_t interval;
int x,y,fx,fy,score=0,gameover;                 //Used global variables for simplicity, will change this in the future to pointers.

void draw(int height, int width);
void input();
void movement();
void logic();
void setGame();
void spawnFruit();
void gameOver();                                //All necessary functions to run the game.

int main(void){

    float speed;

    printf("Input height & width: ");
    scanf("%d%d",&h,&w);


    w*=2;           //Since the space between rows are almost twice as much as columns, I multiply
                    // rows (or widht) with 2 to compensate.
    
    printf("Set speed (1-10)");
    scanf("%f",&speed);
    
    interval=700000/speed;          //Note how the function usleep() takes input in microseconds rather than miliseconds.
    int seed=speed/w*h;
    
    srand(seed);
    setGame();

    while(!gameover){
        
        draw(h,w);
        input();
        movement();
        logic();
    }
    gameOver();
    return(0);
    
}

void draw(int height,int width){
    
    system("cls");                  //Clears the screen for the next "frame".
    printf("Score:%d\n",score);     //Score on top left
    for (int i=0 ; i<height ; i++){
        
        for(int k=0 ; k < width ; k++){    
            
            if(i==height-1||i==0)       
                printf("#");            
            else if(k==width-1||k==0)
                printf("#");                    //Previous two ifs draw the borders.
            else if (k==x&&i==y)
                printf(":");                    //This is for the "head"
            else if (k==fx&&i==fy)
                printf("?");                    //The fruit.
            else
                printf(" ");                    //And the rest, a.k.a. nothingness.
            }                                       
            
        printf("\n");
        }
    }


void input(){       //Unless you want to implement no wait time for getch(), this function is necessary 
                    // since we don't want the system to wait for the input for the next "frame".
    if(kbhit()){
        
        switch(getch()){
            
            case 'w':
                ydir=-1; 
                xdir=0; break;
            case 'a':
                xdir=-1; 
                ydir=0; break;
            case 's':
                ydir=1; 
                xdir=0; break;
            case 'd':
                xdir=1; 
                ydir=0; break;
        
        }
            

    }
}

void movement(){
    
    usleep(interval);
    x+=xdir;
    y+=ydir; 
}

void setGame(){
    
    x=w/2;y=h/2;gameover=0;         //Even I don't know why I concluded this was a necessary function.
    spawnFruit();
}

void spawnFruit(){
    
    fx=2+rand()%(w-3);              
    fy=2+rand()%(h-3);
}

void logic(){

    if(x==0||y==0||x==w-1||y==h-1)      //Collision detection.
        gameover=1;

    else if(x==fx&&y==fy){              //Fruit collision detection.
        if(interval>4000)
            interval-= 3000;
        
        spawnFruit();
        score++;
    }
}

void gameOver(){
    
    system("cls");
    printf("\n\n\n\n                Game Over!");
    printf("\n                Score: %d\n",score);
    getch();
}
