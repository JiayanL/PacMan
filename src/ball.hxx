#pragma once

#include <ge211.hxx>

//Struct for a ball
struct Ball
{
    //INVARIANT: A ball with position
public:
    //Constructs a ball with position
    Ball(ge211::Posn<int> position);

    //top_left position of the ball

    ge211::Posn<int> top_left;
};