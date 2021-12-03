#include "pacman.hxx"
#include "magic_numbers.hxx"
//#include <iostream>

Pacman::Pacman()
        : position(ge211::Posn<int>{192, 142}),
          velocity({0, 0}),
          live(false),
          dead(false),
          invincible(false),
          time_invincible(0)
{}

Pacman
Pacman::next(double dt) const
{
    Pacman result(*this);

    result.position.x += result.velocity.width * dt;
    result.position.y += result.velocity.height * dt;


    return result;
}


bool
Pacman::hits_ball(Ball ball)
{
    int Pacman_left = position.x;
    int Pacman_right = position.x + pacman_diameter;
    int Pacman_top = position.y;
    int Pacman_bottom = position.y + pacman_diameter;

    //Ball's dimension
    int ball_left = ball.top_left.x;
    int ball_top = ball.top_left.y;
    int ball_bottom = ball.top_left.y + 4;
    int ball_right = ball.top_left.x + 4;

    if(Pacman_right < ball_left
       || Pacman_left > ball_right
       || Pacman_top > ball_bottom
       || Pacman_bottom < ball_top){
        return false;
    }

    return true;
}


bool
Pacman::hits_horizontal_wall(ge211::Posn<int>& block)
{

    if(!((position.x + block_10) < (block.x - block_10)
    || (position.x - block_10) > block.x)){
        if((position.y - block_10 <= block.y)
            && (position.y + block_10 >= block.y - block_10)){
            return true;
        }
    }

    return false;


}

bool
Pacman::hits_vertical_wall(ge211::Posn<int>& block)
{

    if(!((position.y + block_10) < (block.y - block_10)
         || (position.y - block_10) > block.y)){
        if((position.x - block_10 <= block.x)
            && (position.x + block_10 >= block.x - block_10)){
            return true;
        }
    }

    return false;
}

bool
Pacman::hits_ghost(ge211::Posn<int> ghost)
{
    //Pacman's Dimensions
    int Pacman_left = position.x;
    int Pacman_right = position.x + pacman_diameter;
    int Pacman_top = position.y;
    int Pacman_bottom = position.y + pacman_diameter;

    //Ghost's dimension
    int ghost_left = ghost.x;
    int ghost_top = ghost.y;
    int ghost_bottom = ghost.y + ghost_height;
    int ghost_right = ghost.x + ghost_width;

    if(Pacman_right < ghost_left
       || Pacman_left > ghost_right
       || Pacman_top > ghost_bottom
       || Pacman_bottom < ghost_top){
        return false;
    }


    return true;
}

bool
Pacman::destroy_balls(std::vector<Ball>& balls)
{
    for(Ball &current : balls) {
        if (hits_ball(current)){
            current = balls.back();
            balls.pop_back();
            return true;
        }
    }
    return false;
}



