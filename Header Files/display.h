#include <wincon.h>
void display_message(const char *message, int yOffset,const int SCREEN_WIDTH,const int SCREEN_HEIGHT,HANDLE _output_handle);
void display_count_down(int immunity_count_down, HANDLE _output_handle,const int SCREEN_WIDTH,const int SCREEN_HEIGHT);
void print_at_xy(int x, int y, char *val);
void display_score(int score, int lives);

void display_message(const char *message, int yOffset,const int SCREEN_WIDTH,const int SCREEN_HEIGHT,HANDLE _output_handle){
    char buffer[100] = {0};
    strcpy(buffer, message);
    print_at_xy(SCREEN_WIDTH/2 - strlen(message)/2, 
                (SCREEN_HEIGHT/2 - 1)+yOffset, buffer);
}

void display_count_down(int immunity_count_down, HANDLE _output_handle,const int SCREEN_WIDTH,const int SCREEN_HEIGHT){
    if(immunity_count_down > 0){
        char buffer[3] = {0};
        char *countdown = itoa(immunity_count_down/10, buffer, 10);
        strcpy(buffer, countdown);
        SetConsoleTextAttribute (_output_handle, FOREGROUND_BLUE);
        display_message("GET READY!", -2,SCREEN_WIDTH, SCREEN_HEIGHT, _output_handle);
        display_message(buffer, 0,SCREEN_WIDTH, SCREEN_HEIGHT,_output_handle);
        SetConsoleTextAttribute (_output_handle, FOREGROUND_INTENSITY);
    }
}
void print_at_xy(int x, int y, char *val, HANDLE _output_handle)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(_output_handle, coord);
  printf("%s", (const char *)val);
  fflush(stdout);
}
void display_score(int score, int lives){
    char buffer[50] = {0};
    sprintf(buffer, "SCORE: %4d LIVES: %d", score, lives);
    print_at_xy(0, 0, buffer);
}

