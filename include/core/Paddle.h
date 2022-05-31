//
// Created by mnaga on 11/15/2020.
//

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#include "cinder/gl/gl.h"
#include <cinder/Color.h>

//Class For Paddle Information
namespace pong {

    class Paddle {
    public:

        /**
         * Constructor for Paddle Object
         * @param top_right
         * @param this_length
         * @param this_width
         */
        Paddle(glm::vec2 top_right, double this_length, double this_width);

        /**
         * Getter for top right corner location of paddle
         * @return top right corner position
         */
        const glm::vec2 &getTopRightPosition() const;

        /**
         * Getter for length
         * @return length
         */
        double getLength() const;

        /**
         * Getter for width
         * @return width
         */
        double getWidth() const;

        /**
         * Setter for top right location of paddle
         * @param topRightPosition
         */
        void setTopRightPosition(glm::vec2 &topRightPosition);

    private:
        glm::vec2 top_right_position;
        double length;
        double width;
    };
}


#endif //PONG_PADDLE_H
