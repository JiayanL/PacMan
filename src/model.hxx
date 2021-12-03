#pragma once

#include <ge211.hxx>
#include "ball.hxx"
#include "pacman.hxx"
#include <vector>
#include "magic_numbers.hxx"


//Enum class of ghost. Can be either orange, pink, or white
enum class Ghost_type
{
    orange, pink, white
};

//Struct for a ghost
struct Ghost {
    //Determines the color of the ghost
    Ghost_type type;
    //Top left position for a ghost
    ge211::Posn<int> position;
    //Velocity of a ghost
    ge211::Dims<double> velocity;
    //Bool for whether or not a ghost is alive
    bool alive;

    //Returns next position of ghost
    Ghost next(double dt);

    //Return ghost's position
    ge211::Posn<int> get_ghost_position();

    //Changes direction of ghost
    void change_direction();
};

class Model
{
public:
    using Maze = std::vector<ge211::Posn<int>>;
    using Small_balls = std::vector<Ball>;
    using Large_balls = std::vector<Ball>;
    using Ghosts = std::vector<Ghost>;

    //Constructs a model
    Model();

    //Returns the maze of the model
    std::vector<ge211::Posn<int>> maze() const;

    //Returns small balls
    std::vector<Ball> small_balls() const;

    //Returns the big balls of the mod
    std::vector<Ball> special_balls() const;

    //Returns ghost in the model
    Ghosts const&
    get_Ghosts() const
    {
        return ghosts_;
    }

    //Starts game
    void begin();

    //Moves game past dt frames
    void on_frame(double dt);

    //Increases Pacman's left velocity and sets vertical velocity to zero
    void move_pacman_left();

    //Increases Pacman's right velocity and sets vertical velocity to zero
    void move_pacman_right();

    //Increases Pacman's up velocity and sets its horizontal velocity to zero
    void move_pacman_up();

    //Increases Pacman's down velocity and sets its horizontal velocity to zero
    void move_pacman_down();

    //Returns Pacman's invincibility status
    bool invincible(){
        return pacman_.invincible;
    }

    //Returns Pacman's position
    ge211::Posn<int> get_pacman_position();

    //Return whether or not game has ended
    bool game_over();


private:
    //A vector of all of the blocks that make up the game
    Maze maze_;
    //A vector made up of the small balls that pacman eats
    Small_balls balls_;
    //A vector made up of the special balls that pacman eats
    Large_balls special_balls_;
    //A variable that represents pacman
    Pacman pacman_;
    //A vector of the ghosts
    Ghosts ghosts_;

    //Makes interior block
    void make_interior_block(int x, int y);

    //Creates friend struct so tests can access model
    friend struct Test_access;

};

