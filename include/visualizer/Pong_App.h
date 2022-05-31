
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "../core/Engine.h"
#include <vector>


namespace pong {

//Visualizer Class
class PongApp : public ci::app::App {
 public:
    const double kXWindowSize = 1000;
    const double kYWindowSize = 500;

    pong::Ball ball = pong::Ball(glm::vec2(kXWindowSize / 2,kYWindowSize / 2), glm::vec2(5,-5), 10);
    pong::Paddle left_paddle = pong::Paddle(glm::vec2(20,(kYWindowSize / 2) - 50), 100, 20);
    pong::Paddle right_paddle = pong::Paddle(glm::vec2(1000,(kYWindowSize / 2) - 50), 100, 20);
    pong::Engine Engine = pong::Engine(ball, left_paddle, right_paddle);

/**
 * Constructor
 */
    PongApp();

/**
 * Redraws Every frame
 */
  void draw();

  /**
   * Updates Calculations Every frame
   */
  void update();

  /**
   * Initial setup
   */
  void setup();

  /**
   * Keydown method for moving paddles
   * @param event
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * Changes Difficulty with mouseclick
   * @param event
   */
  void mouseDown(ci::app::MouseEvent event) override;



 private:

    /**
     * Helper method to draw paddles and ball
     */
    void DrawPaddlesAndBall();

};


}  // namespace pong
