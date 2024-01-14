void draw_wall(const int SCREEN_WIDTH,const int SCREEN_HEIGHT,int *wall_y_pos,int *left_wall_spike,int *right_wall_spike,char left_wall[],char right_wall[],HANDLE _output_handle){
    char wall_row[SCREEN_WIDTH+1];
    int wall_index = *wall_y_pos * -1;
    *left_wall_spike = 0;
    *right_wall_spike = 0;
    for(int i=2;i<20;i++,wall_index++){
        for(int j=1;j<SCREEN_WIDTH;j++){
            wall_row[j] = ' ';
        }
        wall_row[SCREEN_WIDTH+1] = '\0';
        wall_row[0] = '|';
        wall_row[SCREEN_WIDTH] = '|';
        if(left_wall[wall_index] == '>'){            
            wall_row[1] = '>';
            if(i==SCREEN_HEIGHT/2){
                *left_wall_spike = 1;
            }
        }
        if(left_wall[wall_index] == 'D'){            
            wall_row[1] = 'D';
            if(i==SCREEN_HEIGHT/2){
                *left_wall_spike = 1;
            }
        }
        if(right_wall[wall_index] == '<'){            
            wall_row[SCREEN_WIDTH-1] = '<';
            if(i==SCREEN_HEIGHT/2){
                *right_wall_spike = 1;
            }
        }
        COORD coord;
  		coord.X = 0;
  		coord.Y = i;
  		SetConsoleCursorPosition(_output_handle, coord);
  		printf("%s", wall_row);
  		fflush(stdout);
    }
}
void draw_avatar(int *point,int *avatar_x,int *avatar_y,const int SCREEN_HEIGHT,char avatar[],HANDLE _output_handle){
    if(*avatar_y >= SCREEN_HEIGHT) return;
    if(*point==1){
	SetConsoleTextAttribute (_output_handle, FOREGROUND_RED);
	}else if(*point==2){
	SetConsoleTextAttribute (_output_handle, FOREGROUND_GREEN);
	}else if(*point==3){
	SetConsoleTextAttribute (_output_handle, FOREGROUND_BLUE);
	}
    COORD coord;
  	coord.X = *avatar_x;
  	coord.Y = *avatar_y;
  	SetConsoleCursorPosition(_output_handle, coord);
 	printf("%s", avatar);
  	fflush(stdout);
    SetConsoleTextAttribute (_output_handle, FOREGROUND_INTENSITY);  
}


