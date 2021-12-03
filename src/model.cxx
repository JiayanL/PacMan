#include "model.hxx"
#include "magic_numbers.hxx"
//#include <iostream>

Model::Model()
        : maze_(),
        balls_({}),
        special_balls_({}),
        pacman_(Pacman()),
        ghosts_({Ghost{Ghost_type::orange, ge211::Posn<int>{ghost_40, ghost_40},
                         ge211::Dims<double>{0, ghost_200}, true},
                   Ghost{Ghost_type::pink, ge211::Posn<int>{ghost_732,
                                                            ghost_40},
                         ge211::Dims<double>{-ghost_200, 0}, true},
                   Ghost{Ghost_type::white, ge211::Posn<int>{ghost_40,
                                                             ghost_532},
                         ge211::Dims<double>{ghost_200, 0}, true}})
{
    //Dimensions: 800 x 600
    //Makes top and bottom barriers
    for (int i = 0; i <= game_width; i++) {
        for (int j = 0; j<= 2; j++) {
            maze_.push_back({i * block_scale, j * block_scale});
            maze_.push_back({i * block_scale, (57 + j)  * block_scale});
        }
    }

    //Makes side barriers
    for (int i = 0; i <= int_height; i++)
    {
        for (int j = 0; j <= 2; j++) {
            //Left upper
            maze_.push_back({j * block_scale, i * block_scale});
            //Right upper
            maze_.push_back({(j + side_vert) * block_scale,
                             i * block_scale});
            //Left lower
            maze_.push_back({j * block_scale,
                             (i + side_hor) * block_scale});
            //Right lower
            maze_.push_back({(j + side_vert) * block_scale,
                             (i + side_hor) * block_scale});

        }
    }


    //Makes interior barrier
    for (double i = 7.5; i < game_width; i += block_scale) {
        for (int j = 8; j <= 18; j += 9) {
            make_interior_block(i * block_scale , j * block_scale);
            make_interior_block(i * block_scale, j * block_scale + 310);
        }
    }

    //Makes middle block(s)
    for (int i = 27; i <= 52; i++) {
        for (int j = int_height; j <= side_hor; j++) {
            maze_.push_back({i * block_scale, j * block_scale});
        }
    }

    for (double i = 7.5; i <= 17.5; i += 10) {
            make_interior_block(i * block_scale , block_280);
            make_interior_block(i * block_scale + 500, block_280);
    }

    for(int r = ball_50; r <= ball_1000; r+= ball_50){
        for(int c = ball_50; c <= ball_1000; c+= ball_50){
            if(r % 3 == 0 && c % 3 == 0) {
                special_balls_.push_back(Ball({r, c}));
            } else {
                balls_.push_back(Ball({r, c}));
            }
        }
    }
}

std::vector<ge211::Posn<int>>
Model::maze() const
{
    return maze_;
}

std::vector<Ball>
Model::small_balls() const
{
    return balls_;
}

void
Model::begin()
{
    pacman_.live = true;
}

std::vector<Ball>
Model::special_balls() const
{
    return special_balls_;
}

void
Model::make_interior_block(int x, int y) {
    for (int i = 0; i <= 4; i++) {
        for (int j = 0; j <= 4; j++) {
            maze_.push_back({x + (i * block_scale), y + (j * block_scale)});
        }
    }
}

void
Model::on_frame(double dt)
{
    //Runs code if pacman is alive
    if(!pacman_.live || pacman_.dead){
        return;
    }

    //If the game is over, pacman freezes
    if(game_over()){
        pacman_.dead = true;
    }


    if(pacman_.time_invincible >= 10){
        pacman_.time_invincible = 0;
        pacman_.invincible = false;
    }

    if(pacman_.invincible){
        pacman_.time_invincible += dt;
    }

    Pacman pacman_copy = pacman_.next(dt);
    Ghost ghost_copy_orange = ghosts_[0].next(dt);
    Ghost ghost_copy_pink = ghosts_[1].next(dt);
    Ghost ghost_copy_white = ghosts_[2].next(dt);
    Ghosts ghosts_copy = {ghost_copy_orange, ghost_copy_pink, ghost_copy_white};


    for(Ghost &g : ghosts_copy) {
        if (g.position.x > ghost_732 || g.position.x < ghost_40
            || g.position.y > ghost_532 || g.position.y < ghost_40) {
            g.change_direction();
            g = g.next(2 * dt);
        }


        if(pacman_copy.hits_ghost(g.position) && g.alive){
            if(pacman_copy.invincible){
                g.alive = false;
            } else {
                pacman_copy.dead = true;
                pacman_ = pacman_copy;
                return;
            }
        }
    }

    ghosts_ = ghosts_copy;

    if(pacman_copy.position.x <= 0){
        pacman_copy.position.x = 779;
    } else if(pacman_copy.position.x >= 780){
        pacman_copy.position.x = 1;
    }

    for(auto b : maze_){
        if(pacman_copy.hits_horizontal_wall(b)){
            pacman_copy.velocity.width = 0;
            pacman_copy.position = pacman_.position;
        }

        if(pacman_copy.hits_vertical_wall(b)){
            pacman_copy.velocity.height = 0;
            pacman_copy.position = pacman_.position;
        }
    }


    pacman_copy.destroy_balls(balls_);

    if(pacman_copy.destroy_balls(special_balls_)){
        pacman_copy.invincible = true;
        pacman_copy.time_invincible = 0;
    }

    pacman_ = pacman_copy;

}

void
Model::move_pacman_left()
{
    pacman_.velocity.width = -velocity_value;
    pacman_.velocity.height = 0;
}

void
Model::move_pacman_right()
{
    pacman_.velocity.width = velocity_value;
    pacman_.velocity.height = 0;
}

void
Model::move_pacman_up()
{
    pacman_.velocity.height = -velocity_value;
    pacman_.velocity.width = 0;
}

void
Model::move_pacman_down()
{
    pacman_.velocity.height = velocity_value;
    pacman_.velocity.width = 0;
}

ge211::Posn<int>
Model::get_pacman_position()
{
    return {static_cast<int>(pacman_.position.x),
            static_cast<int>(pacman_.position.y)};
}


bool
Model::game_over()
{
    return pacman_.dead
    || (special_balls_.size() <= 24 && balls_.size() <= 258);
}

Ghost
Ghost::next(double dt)
{
    Ghost result(*this);

    result.position.x += result.velocity.width * dt;
    result.position.y += result.velocity.height * dt;

    return result;
}

void
Ghost::change_direction()
{
    velocity.width *= -1;
    velocity.height *= -1;
}
ge211::Posn<int>
Ghost::get_ghost_position()
{
    return {static_cast<int>(position.x),
            static_cast<int>(position.y)};
}

