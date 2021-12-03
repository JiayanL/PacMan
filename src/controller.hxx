#pragma once

#include <ge211.hxx>
#include "model.hxx"
#include "view.hxx"

class Controller : public ge211::Abstract_game
{
public:
    //Constructs a controller by creating a new model and view
    Controller();

protected:
    //Draws sprites sets
    void draw(ge211::Sprite_set& set) override;
    //Runs program by last_frame_seconds frames
    void on_frame(double last_frame_seconds) override;
    //Changes Pacman's velocity based on key press
    void on_key(ge211::Key key) override;

private:
    //Model to get rules of the game and access
    //maze, pacman, balls, and ghosts
    Model model_;
    //View to draw the game
    View view_;
};