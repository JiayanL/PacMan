#include "controller.hxx"
//#include <iostream>


Controller::Controller()
        : model_(Model()),
          view_(model_)
{}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites);
}

void
Controller::on_frame(double last_frame_seconds)
{
    model_.on_frame(last_frame_seconds);
}

void
Controller::on_key(ge211::Key key)
{
    model_.begin();

    if(key == ge211::Key::left()) {
        model_.move_pacman_left();
    } else if (key == ge211::Key::right()){
        model_.move_pacman_right();
    } else if(key == ge211::Key::down()){
        model_.move_pacman_down();
    } else if(key == ge211::Key::up()){
        model_.move_pacman_up();
    }

}

