//
// Created by mnaga on 11/2/2020.
//

#ifndef PONG_ENGINE_H
#define PONG_ENGINE_H


#include "cinder/gl/gl.h"
#include <vector>
#include "Ball.h"
#include "Paddle.h"

//Class for Game Engine

namespace pong{

    class Engine{
    public:
        /**
         * Engine Constructor
         * @param ball
         * @param left_paddle
         * @param right_paddle
         */
        Engine(Ball &ball, Paddle &left_paddle, Paddle &right_paddle);

        /**
         * Checks if Ball is colliding with wall, and modifies velocity
         */
        void HandleWallCollisions();

        /**
         * Checks if Ball is colliding with Paddle, and modifies velocity
         */
        void HandlePaddleCollisions();

        /**
         * Checks if a player has currently scored, and increments score
         */
        void HandleScoring();

        /**
         * Moves frame forward by one
         */
        void Update();

        /**
         * Checks if a player has won and sets winner variable
         * @return true if a player has won
         */
        bool isWon();

        /**
         * Finds the final Y coordinate of ball
         * @return Y coordinate of ball destination
         */
        double PredictBallDestination();

        /**
         * Moves AI towards given destination on the y axis
         * @param destination
         */
        void MoveAI(double destination);

        /**
         * Changes Velocity Depending on Current Mode
         */
        void ChangeVelocityByMode();

        /**
         * Getter for Ball Object
         * @return Ball ball
         */
        const Ball &getBall() const;

        /**
         * Getter for left Paddle object
         * @return left_paddle
         */
        Paddle getLeftPaddle();

        /**
         * Getter for right Paddle object
         * @return right_paddle
         */
        const Paddle &getRightPaddle() const;

        /**
         * Getter for Left Player Score
         * @return unsigned int left score
         */
        unsigned int getLeftScore() const;

        /**
         * Getter for Right Player Score
         * @return unsigned int right score
         */
        unsigned int getRightScore() const;

        /**
         * Setter for left paddle position
         * @param topRightPosition
         */
        void setLeftPaddleTopRightPosition(glm::vec2 &topRightPosition);

        /**
         * Setter for right paddle position
         * @param topRightPosition
         */
        void setRightPaddleTopRightPosition(glm::vec2 &topRightPosition);

        /**
         * Setter for Ball Velocity
         * @param velocity
         */
        void setBallVelocity(glm::vec2 &velocity);

        /**
         * Setter for left score (used for testing)
         * @param leftScore
         */
        void setLeftScore(unsigned int leftScore);

        /**
         * Setter for right score (used for testing)
         * @param rightScore
         */
        void setRightScore(unsigned int rightScore);

        /**
         * Getter for winner
         * @return left or right depending on winner
         */
        const std::string &getWinner() const;

        /**
         * Setter For mode
         * @param mode
         */
        void setMode(const std::string &mode);

        /**
         * Getter For Mode
         * @return current Mode
         */
        const std::string &getMode() const;


    private:
            Ball ball;
            Paddle left_paddle;
            Paddle right_paddle;
            glm::vec2 top_left; //(0,0)
            double env_height;
            double env_length;
            unsigned left_score;
            unsigned right_score;
            std::string winner;
            std::string mode = "normal"; //mode set to normal by default
            glm::vec2 easy_vel = glm::vec2(2,-2);
            glm::vec2 normal_vel = glm::vec2(5,-5);
            glm::vec2 hard_vel = glm::vec2(10,-10);
    };

}


#endif //PONG_ENGINE_H
