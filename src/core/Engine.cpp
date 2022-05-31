//
// Created by mnaga on 11/2/2020.
//

#include <core/Engine.h>
#include <iostream>
#include <windows.h>


//Class for Game Engine

namespace pong{

    Engine::Engine(Ball &current_ball, Paddle &current_left_paddle, Paddle &current_right_paddle) :
    ball(current_ball.getPosition(), current_ball.getVelocity(), current_ball.getRadius()),
    left_paddle(current_left_paddle.getTopRightPosition(),current_left_paddle.getLength(),current_left_paddle.getWidth()),
    right_paddle(current_right_paddle.getTopRightPosition(),current_right_paddle.getLength(),current_right_paddle.getWidth()) {
        env_height = 500;
        env_length = 1000;
        top_left = glm::vec2(0, 0);
        left_score = 0;
        right_score = 0;
    }

    void Engine::HandleWallCollisions() {

        double top_wall = top_left.y ;
        double bottom_wall = top_left.y + env_height;
        glm::vec2 next_velocity = ball.getVelocity();

        //top wall collision
        if (abs(top_wall - ball.getPosition().y) <= ball.getRadius() && ball.getVelocity().y < 0) {
            next_velocity = glm::vec2(next_velocity.x, -next_velocity.y);

        }else if (abs(bottom_wall - ball.getPosition().y) <= ball.getRadius() && ball.getVelocity().y > 0) {
            //bottom wall collision
            next_velocity = glm::vec2(next_velocity.x, -next_velocity.y);
        }

        ball.setVelocity(next_velocity);
    }

    void Engine::HandlePaddleCollisions() {

        double top_of_left_paddle = left_paddle.getTopRightPosition().y;
        double bottom_of_left_paddle = left_paddle.getTopRightPosition().y + left_paddle.getLength();

        double top_of_right_paddle = right_paddle.getTopRightPosition().y;
        double bottom_of_right_paddle = right_paddle.getTopRightPosition().y + right_paddle.getLength();

        glm::vec2 next_velocity = ball.getVelocity();

        if ((top_of_left_paddle <= ball.getPosition().y && ball.getPosition().y <= bottom_of_left_paddle) &&
                (abs(left_paddle.getWidth() - ball.getPosition().x) <= ball.getRadius()) ||
                (top_of_right_paddle <= ball.getPosition().y && ball.getPosition().y <= bottom_of_right_paddle) &&
                (abs((env_length - right_paddle.getWidth()) - ball.getPosition().x) <= ball.getRadius()) ){
            next_velocity = glm::vec2(-next_velocity.x, next_velocity.y);
        }

        ball.setVelocity(next_velocity);

    }

    void Engine::HandleScoring() {
        double left = top_left.x;
        double right = top_left.x + env_length;
        bool has_scored = false;
        std::string current_scorer;

        //right has scored
        if (abs(left - ball.getPosition().x) <= ball.getRadius() && ball.getVelocity().x < 0) {
            right_score++;
            has_scored = true;
            current_scorer = "right";
        }

        //left has scored
        else if (abs(right - ball.getPosition().x) <= ball.getRadius() && ball.getVelocity().x > 0) {
            left_score++;
            has_scored = true;
            current_scorer = "left";
        }

        if (has_scored){
            ball.setPosition(glm::vec2(env_length / 2, env_height / 2)); //return ball to center

            //ball goes back to winner's side
            if(current_scorer == "right"){
                ChangeVelocityByMode();
            }

            if(current_scorer == "left"){
                ChangeVelocityByMode();
                ball.setVelocity(glm::vec2(ball.getVelocity().x * -1, ball.getVelocity().y));
            }

            Sleep(1500);
        }
    }

    void Engine::Update() {
        HandleScoring();
        MoveAI(PredictBallDestination());
        HandleWallCollisions();
        HandlePaddleCollisions();
        ball.setPosition(ball.getPosition() + ball.getVelocity());
    }

    bool Engine::isWon() {
        if (left_score >= 5){
            winner = "left";
            return true;
        }
        if (right_score >= 5){
            winner = "right";
            return true;
        }
        return false;
    }

    double Engine::PredictBallDestination() {
        glm::vec2 edge_of_right_paddle = glm::vec2(right_paddle.getTopRightPosition().x - right_paddle.getWidth(),
                                                   right_paddle.getTopRightPosition().y - (right_paddle.getLength() / 2)) ;
        double travel_time = (edge_of_right_paddle.x - ball.getPosition().x - ball.getRadius()) / ball.getVelocity().x;
        double y_travel_distance = ball.getVelocity().y * travel_time;
        double destination_y;

        //checks if there is a bottom wall collision
        if (y_travel_distance + ball.getPosition().y > env_height){
            double time_to_collision = (env_height - ball.getPosition().y - ball.getRadius()) / ball.getVelocity().y;
            double remaining_time = travel_time - time_to_collision + ball.getRadius() / ball.getVelocity().y;
            destination_y = -ball.getVelocity().y * remaining_time + env_height;
        }

        //checks if there is a top wall collision
        else if(y_travel_distance + ball.getPosition().y < 0){
            double time_to_collision = (-ball.getPosition().y + ball.getRadius()) / ball.getVelocity().y;
            double remaining_time = travel_time - time_to_collision - ball.getRadius() / ball.getVelocity().y;
            destination_y = -ball.getVelocity().y * remaining_time;
        }

        //if no collision
        else if(y_travel_distance + ball.getPosition().y > 0 &&
                y_travel_distance + ball.getPosition().y < env_height){
            destination_y = ball.getVelocity().y * travel_time + ball.getPosition().y;
        }

        else{destination_y = 0;}

        return destination_y;
    }

    void Engine::MoveAI(double destination) {
        if (ball.getVelocity().x > 0 && ball.getPosition().x > env_length / 2){
            double center = right_paddle.getTopRightPosition().y + right_paddle.getLength() / 2;

            //move down
            if(destination > center && std::abs(destination - center) >= 10){
                glm::vec2 newPos(right_paddle.getTopRightPosition().x, right_paddle.getTopRightPosition().y + 10);
                setRightPaddleTopRightPosition(newPos);
            }

            //move up
            else if(destination < center && std::abs(destination - center) >= 10){
                glm::vec2 newPos(right_paddle.getTopRightPosition().x, right_paddle.getTopRightPosition().y - 10);
                setRightPaddleTopRightPosition(newPos);
            }

            //move to location if close
            else if(std::abs(destination - center) < 10){
                glm::vec2 newPos(right_paddle.getTopRightPosition().x, destination - right_paddle.getLength() / 2);
                setRightPaddleTopRightPosition(newPos);
            }
        }
    }

    void Engine::ChangeVelocityByMode() {
        if (mode == "easy"){
            ball.setVelocity(easy_vel);
        }

        if (mode == "normal"){
            ball.setVelocity(normal_vel);
        }

        if (mode == "hard"){
            ball.setVelocity(hard_vel);
        }
    }

    const Ball &Engine::getBall() const {
        return ball;
    }

    Paddle Engine::getLeftPaddle(){
        return left_paddle;
    }

    const Paddle &Engine::getRightPaddle() const {
        return right_paddle;
    }

    unsigned int Engine::getLeftScore() const {
        return left_score;
    }

    unsigned int Engine::getRightScore() const {
        return right_score;
    }

    void Engine::setLeftPaddleTopRightPosition(glm::vec2 &topRightPosition){
        left_paddle.setTopRightPosition(topRightPosition);
    }

    void Engine::setRightPaddleTopRightPosition(glm::vec2 &topRightPosition){
        right_paddle.setTopRightPosition(topRightPosition);
    }

    void Engine::setLeftScore(unsigned int leftScore) {
        left_score = leftScore;
    }

    void Engine::setRightScore(unsigned int rightScore) {
        right_score = rightScore;
    }

    const std::string &Engine::getWinner() const {
        return winner;
    }

    void Engine::setBallVelocity(glm::vec2 &velocity){
        ball.setVelocity(velocity);
    }

    void Engine::setMode(const std::string &mode) {
        Engine::mode = mode;
    }

    const std::string &Engine::getMode() const {
        return mode;
    }

}