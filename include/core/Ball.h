//
// Created by mnaga on 11/2/2020.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "cinder/gl/gl.h"
#include <cinder/Color.h>

//Class for Ball information

namespace pong{

    class Ball{
    public:

        /**
         * Constructor for Ball object
         * @param initial_position
         * @param initial_velocity
         * @param this_radius
         */
        Ball(glm::vec2 initial_position, glm::vec2 initial_velocity, double this_radius);

        /**
         * Getter for position
         * @return position
         */
        const glm::vec2 &getPosition() const;

        /**
         * Getter for velocity
         * @return velocity
         */
        const glm::vec2 &getVelocity() const;

        /**
         * Getter for radius
         * @return radius
         */
        double getRadius() const;

        /**
         * Setter for position
         * @param position
         */
        void setPosition(const glm::vec2 &position);

        /**
         * Setter for velocity
         * @param velocity
         */
        void setVelocity(const glm::vec2 &velocity);

        /**
         * Setter for radius
         * @param radius
         */
        void setRadius(double radius);

    private:
        glm::vec2 position;
        glm::vec2 velocity;
        double radius;
    };

}



#endif //PONG_BALL_H
