#pragma once

#include <ge211.hxx>
#include "model.hxx"
#include "magic_numbers.hxx"

//List of all the colors use in the game
extern ge211::Color const maze_color, ball_color, pacman_color, orange,
white, pink;

class View {

public:
    using Ghosts = std::vector<Ghost>;

    //Constructs a view with a given model
    explicit View(Model& m);

    //Draws sprites
    void draw(ge211::Sprite_set& set);

    //Draws ghosts
    void draw_ghosts(Ghosts ghosts, ge211::Sprite_set& set);

    //Creates a block for the maze
    ge211::Rectangle_sprite const
    maze_block{{10, 10}, maze_color};

    //Creates a pacman sprite
    ge211::Circle_sprite
    pacman{10, pacman_color};

    //Sprite for normal balls
    ge211::Circle_sprite const
    small_ball{2, ball_color};

    //Sprite for special balls
    ge211::Circle_sprite const
    large_ball{6, ball_color};

    //Sprite for orange ghost
    ge211::Rectangle_sprite const
            orange_ghost{{ghost_width, ghost_height}, orange};

    //Sprite for white ghost
    ge211::Rectangle_sprite const
            white_ghost{{ghost_width, ghost_height}, white};

    //Sprite for pink ghost
    ge211::Rectangle_sprite const
            pink_ghost{{ghost_width, ghost_height}, pink};

    //Sprite for blue ghost, when pacman is in invincible mode
    ge211::Rectangle_sprite const
        blue_ghost{{ghost_width, ghost_height}, maze_color};

    //Font for game over sprite
    ge211::Font const
    sans40{"sans.ttf", ghost_40};

    //Sprite to show game over
    ge211::Text_sprite
    game_over{"Game over", sans40};



private:
    //Reference to a model
    Model& model_;

};