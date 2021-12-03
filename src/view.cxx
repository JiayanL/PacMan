#include "view.hxx"
#include "magic_numbers.hxx"
//#include <iostream>

ge211::Color const maze_color {0, 0, view_255};
ge211::Color const ball_color {view_255, view_255, 0};
ge211::Color const pacman_color {0, view_255, 0};
ge211::Color const orange {view_255, 128, 0};
ge211::Color const pink {view_255, 102, 178};
ge211::Color const white {view_255, view_255, view_255};


View::View(Model& m)
:model_(m)
{}

void View::draw(ge211::Sprite_set& set)
{
    if(model_.game_over()){
        set.add_sprite(game_over, {300, 270}, 4);
    }

    set.add_sprite(pacman, model_.get_pacman_position(), 3);

    draw_ghosts(model_.get_Ghosts(),set);

    for(ge211::Posn<int> current : model_.maze()){
        set.add_sprite(maze_block, current, 2);
    }

    for(Ball ball : model_.small_balls()){
        set.add_sprite(small_ball, ball.top_left, 1);
    }

    for (Ball ball : model_.special_balls()){
        set.add_sprite(large_ball, ball.top_left, 1);
    }

}

void
View::draw_ghosts(View::Ghosts ghosts, ge211::Sprite_set& set)
{
    if(model_.invincible())
    {
        for(auto g : ghosts){
            if(g.alive){
                set.add_sprite(blue_ghost, g.position, 3);
            }
        }

    } else{
        for (auto g : ghosts) {
            if(g.alive){
                if (g.type == Ghost_type::orange) {
                    set.add_sprite(orange_ghost, g.get_ghost_position(), 3);
                } else if (g.type == Ghost_type::white) {
                    set.add_sprite(white_ghost, g.get_ghost_position(), 3);
                } else {
                    set.add_sprite(pink_ghost, g.get_ghost_position(), 3);
                }
            }

        }
    }

}




