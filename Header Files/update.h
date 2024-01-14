void update_wall(int *wall_y_pos,int *WALL_SPEED,const int *SCREEN_HEIGHT){
    *wall_y_pos += *WALL_SPEED;
    if(*wall_y_pos > 0){
        *wall_y_pos = -*SCREEN_HEIGHT;
    }
}
void update_avatar(char ch,int *avatar_x,int *avatar_y,int *avatar_delta,int *game_state,int *GAME_STATE_PLAYING,int *avatar_SPEED,const int SCREEN_HEIGHT,const int SCREEN_WIDTH,int *immunity_count_down,int *lives,int *score, int *GOAL_POINTS){
	*avatar_x += *avatar_delta;
    if(*avatar_x == 1 && ch == ' ' && *game_state == *GAME_STATE_PLAYING){
        *avatar_delta = *avatar_SPEED;
        *avatar_x += *avatar_delta;
        *score += *GOAL_POINTS;
    }
    else if(*avatar_x == SCREEN_WIDTH-1 && ch == ' ' && *game_state == *GAME_STATE_PLAYING){
        *avatar_delta = -*avatar_SPEED;
        *avatar_x += *avatar_delta;
        *score += *GOAL_POINTS;
    }
    else if(*avatar_x <= 1){
        *avatar_delta = 0;
        *avatar_x = 1;        
    }
    else if(*avatar_x >= SCREEN_WIDTH-1){
        *avatar_delta = 0;
        *avatar_x = SCREEN_WIDTH-1;
    }  

    if(*immunity_count_down > 10 && *lives < 3){
        *avatar_x = SCREEN_WIDTH/2;
        *avatar_y += 1;
        if(*avatar_y >= SCREEN_HEIGHT){
            *avatar_y = SCREEN_HEIGHT;
        }
    }
    if(*immunity_count_down < 10 && *immunity_count_down > 1){
        *avatar_x = 1;
        *avatar_y = SCREEN_HEIGHT / 2;
    }
}

