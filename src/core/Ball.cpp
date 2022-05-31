//
// Created by mnaga on 11/2/2020.
//

#include <core/Ball.h>
#include <iostream>
#include "cinder/gl/gl.h"

//Class containing Ball information

namespace pong{

    Ball::Ball(glm::vec2 initial_position, glm::vec2 initial_velocity, double this_radius){
        position = initial_position;
        velocity = initial_velocity;
        radius = this_radius;
    }

    const glm::vec2 &Ball::getPosition() const {
        return position;
    }

    const glm::vec2 &Ball::getVelocity() const {
        return velocity;
    }

    double Ball::getRadius() const {
        return radius;
    }

    void Ball::setPosition(const glm::vec2 &position) {
        Ball::position = position;
    }

    void Ball::setVelocity(const glm::vec2 &velocity) {
        Ball::velocity = velocity;
    }

    void Ball::setRadius(double radius) {
        Ball::radius = radius;
    }



}