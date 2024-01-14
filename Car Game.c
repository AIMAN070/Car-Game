#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "sound.h"
#include "display.h"
#include "update.h"
#include "draw.h"
// global variables
HANDLE _output_handle;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int SCREEN_WIDTH = 12;
const int SCREEN_HEIGHT = 20;
int lives, game_state, GAME_STATE_OVER,GAME_STATE_PLAYING,GOAL_POINTS,WALL_SPEED,score;
char avatar[2], game_over_string[30], left_wall[60], right_wall[60],left_spike[3], right_spike[3];
int wall_y_pos, avatar_x,avatar_y,avatar_SPEED, avatar_delta,left_wall_spike,right_wall_spike, immunity_count_down;
// function declaration
void init();
int zero_lives(){
    if(lives == 0)
	{return 1;}
    return 0;
}
void set_game_state_over()
	{game_state = GAME_STATE_OVER;}
char get_input(){
    char ch;
    if(kbhit())
	{ch = getch();}
    return ch;
}
void decrement_lives()
	{lives--;}
void draw(int point){
    draw_wall(SCREEN_WIDTH,SCREEN_HEIGHT,&wall_y_pos,&left_wall_spike,&right_wall_spike,left_wall,right_wall,_output_handle);
	draw_avatar(&point,&avatar_x,&avatar_y,SCREEN_HEIGHT,avatar,_output_handle);
    display_score(score,lives);
    display_count_down(immunity_count_down, _output_handle, SCREEN_WIDTH, SCREEN_HEIGHT);    
}
void clean_up()
	{printf("Thanks for playing.");}
void clear_screen(){
    char buffer[] = "            ";

    for(int i=0;i<3;i++)
    {
        COORD coord;
  		coord.X = 0;
  		coord.Y = i;
 		SetConsoleCursorPosition(_output_handle, coord);
 		printf("%s", buffer);
  		fflush(stdout);
    }
}
int collides_with_spike(){
    if(game_state == GAME_STATE_OVER)
	{return 0;}
    if(avatar_x == 1 && left_wall_spike == 1)
	{return 1;}
    else if(avatar_x == SCREEN_WIDTH-1 && right_wall_spike == 1)
	{return 1;}
	return 0;
}
void hidecursor()
{
   _output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(_output_handle, &info);
}


int main(){
	int point=1;
    init();
    printf("\nChoose Car:\nPress 'N' or 'n' for Ninja Car\nPress 'D' or 'd' for Dinosaur Car\n");
    char chra;
    chra = getch();
    
    if(chra == 'n' || chra=='N')
    {
    	//Ninja selected
    	printf("\nNinja Car selected!\n");
    	strcpy(avatar, "X");
	}
	else if(chra == 'D' || chra=='d')
	{
		//Dianosaur selected
		printf("\nDinosaur Car selected!\n");
		strcpy(avatar, "D");
	}
	else
	{
		//Default to Ninja if invalid input
		printf("\nInvalid choice. Defaulting to Ninja Car.\n");
		strcpy(avatar, "X");
	}
	printf("\nChoose colour for your car:\nPress 'R' or 'r' for red\nPress 'G' or 'g' for green\nPress 'B' or 'b' for blue\n");
	char colour_choice = getch();
	
	if (chra == 'n' || chra=='N')
    {
        // Ninja color choice
      //  int color_choice;
        switch (tolower(colour_choice))
        {
        case 'r':
            // Red Ninja Car
            point=1;
            printf("\nRed Ninja Car selected!\n");
            break;
        case 'g':
            // Green Ninja Car
            point=2;
            printf("\nGreen Ninja Car selected!\n");
			break;
        case 'b':
            // Blue Ninja Car
            point=3;
            printf("\nBlue Ninja Car selected!\n");
			break;
        default:
        	// Default to Red Ninja for invalid input
			point=1;
            printf("\nInvalid color choice. Defaulting to Red Ninja Car.\n");
            break;
        }
    }
    else if (chra == 'D' || chra=='d')
    {
        // Dinosaur Car color choice
    //    int color_choice;
        switch (tolower(colour_choice))
        {
        case 'r':
            // Red Dinosaur Car
            point=1;
            printf("\nRed Dinosaur Car selected!\n");
            break;
        case 'g':
            // Green Dinosaur Car
            point=2;
            printf("\nGreen Dinosaur Car selected!\n");
			break;
        case 'b':
            // Blue Dinosaur Car
            point=3;
            printf("\nBlue Dinosaur Car selected!\n");
			break;
        default:
            // Default to Red Dinosaur Car for invalid input
            point=1;
            printf("\nInvalid color choice. Defaulting to Red Dinosaur Car.\n");
            break;
        }
    }
    printf("\nInstructions:\nPress 'Space Bar' to move your car\n");
    printf("\nPress enter to play the game...\n");
	getchar();
    system("@cls||clear");

    // 1000/30
    // game loop
    while(1){

        if(immunity_count_down > 0)
		{immunity_count_down--;}

        clear_screen();    
        char ch = get_input();

        //clear screen and quit
        if(game_state == GAME_STATE_OVER && ch == 'q'){
            system("@cls||clear");
            break;
        }

        clear_screen();
        update_wall( &wall_y_pos, &WALL_SPEED, &SCREEN_HEIGHT);
        // Check which character is selected and call the respective update function
        update_avatar(ch,&avatar_x,&avatar_y,&avatar_delta,&game_state,&GAME_STATE_PLAYING,&avatar_SPEED, SCREEN_HEIGHT,SCREEN_WIDTH, &immunity_count_down,&lives,&score,&GOAL_POINTS);
        draw(point);
        if(collides_with_spike() && immunity_count_down <= 0){
            decrement_lives();
            immunity_count_down = 30;
            playe_sound();
        }
        
        if(zero_lives()){
            set_game_state_over();
            play_sound();
            display_message(game_over_string, -2, SCREEN_WIDTH, SCREEN_HEIGHT, _output_handle);
            display_message("'q' to quit...", 0,SCREEN_WIDTH, SCREEN_HEIGHT,_output_handle);
        }
        Sleep(100);
    }
	clean_up();
}

void init(){
    score = 0;
    lives = 3;
    GOAL_POINTS = 10;
    GAME_STATE_OVER = 1;
    GAME_STATE_PLAYING = 2;
    WALL_SPEED = 1;

    avatar_x = 1;
    avatar_y = SCREEN_HEIGHT/2;
    avatar_SPEED = 6;
    avatar_delta = 0;
    left_wall_spike = 0;
    right_wall_spike = 0;
    immunity_count_down = 30;

    game_state = GAME_STATE_PLAYING;
    wall_y_pos = -20;
    strcpy(left_spike, "|>");
    strcpy(right_spike, "<|");
    strcpy(game_over_string, "GAME OVER");
    strcpy(left_wall,  "|||>|||||||||||||>>||||||>>||||||>>||||");
    strcpy(right_wall, "|||||||||<||||<||||||||<||||||<<||||||<");
    hidecursor();
}

void print_at_xy(int x, int y, char *val)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(_output_handle, coord);
  printf("%s", (const char *)val);
  fflush(stdout);
}

