#include "model.hxx"
#include <catch.hxx>
#include <iostream>

struct Test_access{
    Model& m;

    //using Dimensions = ge211::Dims<int>;
    //using Maze = std::vector<ge211::Posn<int>>;
    using Small_balls = std::vector<Ball>;
    using Large_balls = std::vector<Ball>;
    using Ghosts = std::vector<Ghost>;

    /*Maze& get_maze(){
        return m.maze_;
    }
    */

    Small_balls& get_small_balls(){
        return m.balls_;
    }

    Large_balls& get_special_balls(){
        return m.special_balls_;
    }

    Ghosts& get_ghosts(){
        return m.ghosts_;
    }

    Pacman& get_pacman(){
        return m.pacman_;
    }

};

TEST_CASE("Pacman hits a big ball"){
    Model model;
    Test_access t{model};

    CHECK_FALSE(t.get_pacman().live);

    t.m.begin();

    CHECK_FALSE(t.get_pacman().invincible);
    CHECK_FALSE(t.get_pacman().dead);
    CHECK(t.get_pacman().live);

    int num_big_balls = t.get_special_balls().size();

    t.get_pacman().position = {150, 150};

    t.m.on_frame(0.01);

    CHECK(t.get_pacman().invincible);
    CHECK(num_big_balls > t.get_special_balls().size());
    CHECK(t.get_ghosts()[0].alive);

    t.get_pacman().position = {40, 40};
    t.m.on_frame(0.0001);
    CHECK_FALSE(t.get_ghosts()[0].alive);
}

TEST_CASE("Game ends"){
    Model model;
    Test_access t{model};

    t.m.begin();

    CHECK_FALSE(t.m.game_over());
    t.get_special_balls().clear();
    t.get_small_balls().clear();

    CHECK(t.m.game_over());

    Model model2;
    Test_access t2{model2};

    t2.m.begin();
    CHECK_FALSE(t2.m.game_over());
    t2.get_pacman().position = {40, 40};
    t2.m.on_frame(0.01);
    CHECK(t2.m.game_over());

}

TEST_CASE("Pacman hits a wall")
{
    Model model;
    Test_access t{model};
    CHECK_FALSE(t.get_pacman().live);

    t.m.begin();

    CHECK(t.get_pacman().live);

    //Hits top
    t.get_pacman().position = {160, 30};
    t.get_pacman().velocity = {0, -10};
    t.m.on_frame(1);
    CHECK(t.get_pacman().position.x == 160);
    CHECK(t.get_pacman().position.y == 30);

    //Hits bottom
    t.get_pacman().position = {160, 550};
    t.get_pacman().velocity = {0, 10};
    t.m.on_frame(1);
    CHECK(t.get_pacman().position.x == 160);
    CHECK(t.get_pacman().position.y == 550);

    //Hits side
    t.get_pacman().position = {30, 200};
    t.get_pacman().velocity = {-10, 0};
    t.m.on_frame(1);
    CHECK(t.get_pacman().position.x == 30);
    CHECK(t.get_pacman().position.y == 200);

    //Hits interior block
    t.get_pacman().position = {55, 200};
    t.get_pacman().velocity = {10, 0};
    t.m.on_frame(1);
    CHECK(t.get_pacman().position.x == 55);
    CHECK(t.get_pacman().position.y == 200);
}

TEST_CASE("Hitting a ghost") {
    Model model;
    Test_access t{model};

    CHECK_FALSE(t.get_pacman().live);

    t.m.begin();

    //While invincible
    CHECK(t.get_pacman().live);
    t.get_pacman().invincible = true;
    CHECK(t.get_pacman().invincible);
    t.get_pacman().position = {40, 40};
    t.m.on_frame(0.0001);
    CHECK_FALSE(t.get_ghosts()[0].alive);

    //While normal
    t.get_pacman().invincible = false;
    CHECK_FALSE(t.get_pacman().invincible);
    t.get_pacman().position = {725, 40};
    t.m.on_frame(0.0001);
    CHECK(t.get_ghosts()[1].alive);
    CHECK(t.get_pacman().dead);
}

TEST_CASE("Teleporting from one side to the other") {
    Model model;
    Test_access t{model};

    CHECK_FALSE(t.get_pacman().live);

    t.m.begin();

    CHECK(t.get_pacman().live);
    //Left to right
    t.get_pacman().position = {0, 270};
    t.get_pacman().velocity = {-10, 0};
    t.m.on_frame(1);
    CHECK(t.get_pacman().position.y == 270);
    CHECK(t.get_pacman().position.x == 779);

    //Right to left
    t.get_pacman().position = {780, 270};
    t.get_pacman().velocity = {10, 0};
    t.m.on_frame(1);
    CHECK(t.get_pacman().position.y == 270);
    CHECK(t.get_pacman().position.x == 1);

}

TEST_CASE("Arrow key moves Pacman") {
    Model model;
    Test_access t{model};

    CHECK_FALSE(t.get_pacman().live);

    t.m.begin();

    CHECK(t.get_pacman().live);
    CHECK(t.get_pacman().velocity.height == 0);
    CHECK(t.get_pacman().velocity.width == 0);
    //Right arrow
    t.m.move_pacman_right();
    CHECK(t.get_pacman().velocity.width == 100);
    //Up arrow
    t.m.move_pacman_up();
    CHECK(t.get_pacman().velocity.height == -100);
    //Down arrow
    t.m.move_pacman_down();
    CHECK(t.get_pacman().velocity.height == 100);
    //Left arrow
    t.m.move_pacman_left();
    CHECK(t.get_pacman().velocity.width == - 100);
}
