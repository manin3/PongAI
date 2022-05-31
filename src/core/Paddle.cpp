//
// Created by mnaga on 11/15/2020.
//

#include "core/Paddle.h"
#include <iostream>
#include "cinder/gl/gl.h"

//Class For Paddle Information
namespace pong{

    Paddle::Paddle(glm::vec2 top_right, double this_length, double this_width){
        top_right_position = top_right;
        length = this_length;
        width = this_width;
    }

    const glm::vec2 &Paddle::getTopRightPosition() const {
        return top_right_position;
    }

    double Paddle::getLength() const {
        return length;
    }

    double Paddle::getWidth() const {
        return width;
    }

    void Paddle::setTopRightPosition(glm::vec2 &topRightPosition){
        top_right_position = topRightPosition;
    }

}