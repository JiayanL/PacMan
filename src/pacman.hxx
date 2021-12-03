
#pragma once
#include <ge211.hxx>
#include "ball.hxx"
#include "magic_numbers.hxx"



struct Pacman{
public:
    //The top left position of the pacman
    ge211::Posn<double> position;
    //The velocity of the pacman
    ge211::Dims<double> velocity;
    //Determines whether or not the game is live, over, or pacman is in
    //invincible mode
    bool live, dead, invincible;
    //Determines how long the pacman is invincible for
    double time_invincible;

    //Constructor for Pacman
    Pacman();

    //Determines where Pacman will be at the next frame
    Pacman next(double dt) const;

    //Checks if pacman hits a vertical wall
    bool hits_vertical_wall(ge211::Posn<int>& block);

    //Checks if pacman hits a horizontal wall

    bool hits_horizontal_wall(ge211::Posn<int>& block);

    //Checks if pacman hits a ghost
    bool hits_ghost(ge211::Posn<int> ghost);

    //destroys a ball
    bool destroy_balls(std::vector<Ball>& balls);

    //Checks if pacman hits a ball
    bool hits_ball(Ball ball);

};