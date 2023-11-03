#include <stdio.h>
#include <string.h>
#include <unistd.h>//for clear screen
#include <time.h>//for random
#include <stdlib.h>//for random

//you can change next 3 settings
#define HEIGHT 120//is for Height || 16 + 2
#define WIDE 60//is for Wide      || 4 + 2
#define CNT_OF_CELL 800//how much cell will be spawned randomly on the map

void print_screen(char dp[WIDE*HEIGHT]);
int neighbours(char dp[WIDE*HEIGHT], int i, int j);
void clear_screen(void);
void create_map(char dp[WIDE*HEIGHT], int spawn_needed);
void copy(char mas[WIDE*HEIGHT], char dp[WIDE*HEIGHT]);
int if_end(char mas[WIDE*HEIGHT], char dp[WIDE*HEIGHT]);

char cell = '*';//the look of our cells
char death = ' ';//the look of empty space


int main(){
    char mas[WIDE*HEIGHT]; //our map
    char prev_mas[WIDE*HEIGHT];
    
    srand(time(NULL));//initialisation for rand. called once.
    create_map(mas, 1); 
    create_map(prev_mas, 0);
    

    //infinity loop made with for
    //infinity loop made with for
    for (;;){
        //draw our map
        print_screen(mas);
        //check every argument in array
        for (int i = 1; i < WIDE -1; i++)
        {  
            for (int j = 1; j < HEIGHT -1; j++)
            {
                int neib = 0;
                neib = neighbours(mas, i, j);
                //if cell has 2or3 neighbours it will live, overwise it'll die
                if (mas[HEIGHT*i+j] == cell){
                    if ((2 <= neib) && (neib <= 3))
                        prev_mas[HEIGHT*i+j] = cell;
                    else
                        prev_mas[HEIGHT*i+j] = death;
                }
                if (mas[HEIGHT*i+j] == death){
                    if (neib == 3)
                        prev_mas[HEIGHT*i+j] = cell;
                    else
                        prev_mas[HEIGHT*i+j] = death;
                }    
            }
        }
        if (if_end(mas, prev_mas)){//if game over print game over
            clear_screen();
            printf("Game Over");
            break;
        }
        copy(mas, prev_mas);//it will copy prev_mas to mas
    }
    return 0;
}





int neighbours(char dp[WIDE*HEIGHT], int wide, int height){ //returns count of neighbours
    int i, j;
    int cnt = 0;
    int step = 1;//how big will be our radius of looking around for neighbours
    for(i = (wide - step); i <= (wide + step); i++){
        for(j = (height - step); j <= (height + step); j++){
            if (dp[HEIGHT*i+j] == cell)
                cnt++;
        }
    }
    //if place, which neighbours we a checking, is a cell
    //we shouldnt count it
    return cnt - (dp[HEIGHT*wide+height] == cell);
}

void print_screen(char dp[WIDE*HEIGHT]){
    clear_screen();
    //draw our array(screen)
    for (int i = 0; i < WIDE; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            printf("%c", dp[HEIGHT*i+j]);
        }
        printf("\n");
    }
    sleep(1);
}

void clear_screen() 
{ 
    printf("\033[2J"); /* Clear the entire screen. */ 
    printf("\033[0;0f"); /* Move cursor to the top left hand corner */ 
}

void create_map(char dp[WIDE*HEIGHT], int spawn_needed)
{   
    if (spawn_needed)
    {
        for (int i = 1; i <= CNT_OF_CELL; i++ ){
            dp[rand()%(WIDE*HEIGHT)+1] = cell;
        }
    }

    //make boarders
    for (int i = 0; i < WIDE; i++)
    {
       
        for (int j = 0; j < HEIGHT; j++)
        {   if (dp[HEIGHT*i+j] != cell)
                dp[HEIGHT*i+j] = death;

            if ((i == 0) || (i == (WIDE-1))){
                dp[HEIGHT*i+j] = '-';
            }
            if ((j==0) || (j == (HEIGHT-1))){
                dp[HEIGHT*i+j] = '|';
            }
        }
        
    }
    //make corners look like +
    dp[0] = '+';
    dp[HEIGHT-1] = '+';
    dp[(WIDE-1)*HEIGHT] = '+';
    dp[(WIDE-1)*HEIGHT+HEIGHT-1] = '+';

    
}

void copy(char mas[WIDE*HEIGHT], char dp[WIDE*HEIGHT])
{
    memcpy(mas, dp, WIDE*HEIGHT);
}

int if_end(char mas[WIDE*HEIGHT], char dp[WIDE*HEIGHT]){
    //checks if game is over
    for(int i = 0; i < WIDE; i++){
        for (int j = 0; j < HEIGHT; j++){
            if (mas[HEIGHT*i+j] != dp[HEIGHT*i+j])
                return 0; //if arrays arent the same
        }
    }
    return 1;//if arrays are the same
}
