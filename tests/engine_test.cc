
#include <core/Engine.h>
#include <core/Paddle.h>
#include "core/Ball.h"
#include <iostream>
#include <catch2/catch.hpp>
#include <vector>
#include "cinder/gl/gl.h"
#include <cinder/Color.h>
#include <exception>

/*
 * Test file for Environment and Particle objects
 * Coordinate system based on MS Paint Canvas (XD?)
 * (0,0) is top left corner
 */

using pong::Engine;
using pong::Paddle;
using pong::Ball;

TEST_CASE("Update Method"){
    SECTION("No collisions"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.Update();

        REQUIRE(engine.getBall().getPosition() == glm::vec2(510, 250));
        REQUIRE(engine.getBall().getVelocity() == glm::vec2(10, 0));

    }

    SECTION("Collision with left Paddle"){
        pong::Ball ball(glm::vec2(25,10), glm::vec2(-10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.Update();

        REQUIRE(engine.getBall().getPosition() == glm::vec2(35, 10));
        REQUIRE(engine.getBall().getVelocity() == glm::vec2(10, 0));
    }

    SECTION("Collision with right Paddle"){
        pong::Ball ball(glm::vec2(975,10), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.Update();

        REQUIRE(engine.getBall().getPosition() == glm::vec2(965, 10));
        REQUIRE(engine.getBall().getVelocity() == glm::vec2(-10, 0));
    }

    SECTION("Top Wall Collision"){
        pong::Ball ball(glm::vec2(500,5), glm::vec2(0,-10), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.Update();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(0, 10));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(500, 15));
    }

    SECTION("Bottom Wall Collision"){
        pong::Ball ball(glm::vec2(500,495), glm::vec2(0,10), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.Update();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(0, -10));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(500, 485));
    }

    SECTION("Predict destination"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(25,-25), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        REQUIRE(Approx(engine.PredictBallDestination()) == 235);
    }

    SECTION("MovetoDestination"){
        pong::Ball ball(glm::vec2(920,250), glm::vec2(20,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,205), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.MoveAI(engine.PredictBallDestination());
        REQUIRE(engine.getRightPaddle().getTopRightPosition() == glm::vec2(1000, 200)); //moves 5 units to align center with destination
    }
}

TEST_CASE("Handle Wall Collisions Method"){
    SECTION("Top Wall Collision"){
        pong::Ball ball(glm::vec2(500,5), glm::vec2(0,-10), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleWallCollisions();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(0, 10));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(500, 5));
    }

    SECTION("Bottom Wall Collision"){
        pong::Ball ball(glm::vec2(500,495), glm::vec2(0,10), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleWallCollisions();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(0, -10));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(500, 495));
    }

    SECTION("No collisions"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleWallCollisions();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(10, 0));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(500, 250));
    }

    SECTION("Velocity direction opposite from wall, should not collide"){
        pong::Ball ball(glm::vec2(500,495), glm::vec2(0,-10), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleWallCollisions();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(0, -10));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(500, 495));
    }
}

TEST_CASE("HandlePaddleCollisions Method"){
    SECTION("Collision with left Paddle"){
        pong::Ball ball(glm::vec2(25,10), glm::vec2(-10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandlePaddleCollisions();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(10, 0));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(25, 10));
    }

    SECTION("Collision with right Paddle"){
        pong::Ball ball(glm::vec2(975,10), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandlePaddleCollisions();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(-10, 0));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(975, 10));
    }

    SECTION("No collisions"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandlePaddleCollisions();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(10, 0));
        REQUIRE(engine.getBall().getPosition() == glm::vec2(500, 250));
    }
}

TEST_CASE("HandleScoring Method"){
    SECTION("Right Scores"){
        pong::Ball ball(glm::vec2(5,300), glm::vec2(-10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleScoring();

        REQUIRE(engine.getRightScore() == 1);
        REQUIRE(engine.getLeftScore() == 0);
    }

    SECTION("Left Scores"){
        pong::Ball ball(glm::vec2(995,300), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleScoring();

        REQUIRE(engine.getRightScore() == 0);
        REQUIRE(engine.getLeftScore() == 1);
    }

    SECTION("Velocity in opposite direction, nobody scores"){
        pong::Ball ball(glm::vec2(995,300), glm::vec2(-10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleScoring();

        REQUIRE(engine.getRightScore() == 0);
        REQUIRE(engine.getLeftScore() == 0);
    }

    SECTION("Nobody scores"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.HandleScoring();

        REQUIRE(engine.getRightScore() == 0);
        REQUIRE(engine.getLeftScore() == 0);
    }
}

TEST_CASE("isWon Method"){
        SECTION("No Winner"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.setLeftScore(2);
        engine.setRightScore(3);

        REQUIRE_FALSE(engine.isWon());
        }

    SECTION("Left Wins"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.setLeftScore(5);
        engine.setRightScore(3);

        REQUIRE(engine.isWon());
        REQUIRE(engine.getWinner() == "left");
    }

    SECTION("Right Wins"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(10,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.setLeftScore(3);
        engine.setRightScore(5);

        REQUIRE(engine.isWon());
        REQUIRE(engine.getWinner() == "right");
    }
}

TEST_CASE("Predict Destination"){
    SECTION("Top Wall Bounce"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(25,-25), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        REQUIRE(Approx(engine.PredictBallDestination()) == 235);
    }

    SECTION("Bottom Wall Bounce"){
        pong::Ball ball(glm::vec2(500,250), glm::vec2(25,25), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        REQUIRE(Approx(engine.PredictBallDestination()) == 265);
    }

    SECTION("No Bounce"){
        pong::Ball ball(glm::vec2(940,250), glm::vec2(20,-10), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        REQUIRE(engine.PredictBallDestination() == 232.5);
    }
}

TEST_CASE("MoveAI"){
    SECTION("Move down"){
        pong::Ball ball(glm::vec2(940,250), glm::vec2(20,-10), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,0), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.MoveAI(engine.PredictBallDestination());
        REQUIRE(engine.getRightPaddle().getTopRightPosition() == glm::vec2(1000, 10)); //moves down 10 units
    }

    SECTION("Move up"){
        pong::Ball ball(glm::vec2(940,20), glm::vec2(20,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,200), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.MoveAI(engine.PredictBallDestination());
        REQUIRE(engine.getRightPaddle().getTopRightPosition() == glm::vec2(1000, 190)); //moves up 10 units
    }

    SECTION("Move less than 10 units"){
        pong::Ball ball(glm::vec2(920,250), glm::vec2(20,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,205), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.MoveAI(engine.PredictBallDestination());
        REQUIRE(engine.getRightPaddle().getTopRightPosition() == glm::vec2(1000, 200)); //moves 5 units to align center with destination
    }

    SECTION("Already at destination"){
        pong::Ball ball(glm::vec2(920,250), glm::vec2(20,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,200), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.MoveAI(engine.PredictBallDestination());
        REQUIRE(engine.getRightPaddle().getTopRightPosition() == glm::vec2(1000, 200)); //doesn't move
    }
}

TEST_CASE("ChangeVelocityByMode"){
    SECTION("Change Mode"){
        pong::Ball ball(glm::vec2(920,250), glm::vec2(20,0), 5);
        pong::Paddle left_paddle(glm::vec2(20,0), 100, 20);
        pong::Paddle right_paddle(glm::vec2(1000,200), 100, 20);
        pong::Engine engine(ball, left_paddle, right_paddle);

        engine.setMode("hard");
        engine.ChangeVelocityByMode();

        REQUIRE(engine.getBall().getVelocity() == glm::vec2(10, -10)); //correct velocity for hard mode
    }

}