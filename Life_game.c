#include <stdio.h>
#include <unistd.h>//for clear screen
#include <time.h>//for rand
#include <stdlib.h>//for rand

#define HEIGHT 160 + 2//is for Height
#define WIDE 40 + 2//is for Wide
#define CNT_OF_CELL 800//how much cell will be spawned randomly on the map

void print_screen(char dp[WIDE][HEIGHT]);
int neighbours(char dp[WIDE][HEIGHT], int i, int j);
void clear_screen(void);
void create_map(char dp[WIDE][HEIGHT]);

char cell = '*';
char death = ' ';
char mas[WIDE][HEIGHT]; //our map

int main(){
    srand(time(NULL));//initialisation for rand. called once.
    create_map(mas); 

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
                if (mas[i][j] == cell){
                    if ((2 == neib) || (neib == 3))
                        mas[i][j] = cell;
                    else
                        mas[i][j] = death;
                }
                if (mas[i][j] == death){
                    if (neib == 3)
                        mas[i][j] = cell;
                    else
                        mas[i][j] = death;
                }
                    
            }
            printf("\n");
        }
    
    }

   
    return 0;
}


int neighbours(char dp[WIDE][HEIGHT], int wide, int height){ //returns count of neighbours
    int i, j;
    int cnt = 0;
    int step = 1;//how big will be our radius of looking around for neighbours
    for(i = (wide - step); i <= (wide + step); i++){
        for(j = (height - step); j <= (height + step); j++){
            if (dp[i][j] == cell)
                cnt++;
        }
    }
    //if place, which neighbours we a checking, is a cell
    //we shouldnt count it
    if (dp[wide][height] == cell) 
        return cnt-1;
    else
        return cnt;
}

void print_screen(char dp[WIDE][HEIGHT]){
    clear_screen();
    //draw our array(screen)
    for (int i = 0; i < WIDE; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            printf("%c", dp[i][j]);
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

void create_map(char dp[WIDE][HEIGHT])
{
    
    //spawn our cell on the map
    for (int i = 0; i < CNT_OF_CELL; i++ ){
        dp[rand()%WIDE][rand()%HEIGHT] = cell;
    }

    //make boarders
    for (int i = 0; i < WIDE; i++)
    {
       
        for (int j = 0; j < HEIGHT; j++)
        {   if (dp[i][j] != cell)
                dp[i][j] = death;

            if ((i == 0) || (i == (WIDE-1))){
                dp[i][j] = '-';
            }
            if ((j==0) || (j == (HEIGHT-1))){
                dp[i][j] = '|';
            }
        }
        
    }
    //make corners look like +
    dp[0][0] = '+';
    dp[0][HEIGHT-1] = '+';
    dp[WIDE-1][0] = '+';
    dp[WIDE-1][HEIGHT-1] = '+';

        
}


