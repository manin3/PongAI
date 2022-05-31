#include <core/Engine.h>
#include <core/Ball.h>
#include <core/Paddle.h>
#include <visualizer/Pong_App.h>


/*
 * Visualizer for Pong Game
*/

namespace pong {

PongApp::PongApp(){
    ci::app::setWindowSize((int) kXWindowSize, (int) kYWindowSize);
}

void PongApp::setup(){
    Engine.ChangeVelocityByMode();
}

void PongApp::draw() {
    ci::gl::clear(ci::Color("black"));
    ci::app::setFrameRate(240.0f);

    if (!Engine.isWon()){
        DrawPaddlesAndBall();
        ci::gl::drawStringCentered(std::to_string(Engine.getLeftScore()) + " : "
        + std::to_string(Engine.getRightScore()),
        glm::vec2(kXWindowSize / 2,kYWindowSize / 50),ci::Color("white"), ci::Font("Arial", 40));

        ci::Rectf easy_button((float) kXWindowSize / 2 - 85, 430, (float) kXWindowSize / 2 - 35, 450);
        ci::Rectf normal_button((float) kXWindowSize / 2 - 25, 430, (float) kXWindowSize / 2 + 25, 450);
        ci::Rectf hard_button((float) kXWindowSize / 2 + 35, 430, (float) kXWindowSize / 2 + 85, 450);

        ci::gl::color(128,0,128);
        ci::gl::drawSolidRect(easy_button);
        ci::gl::drawSolidRect(normal_button);
        ci::gl::drawSolidRect(hard_button);

        ci::gl::drawStringCentered("Easy", glm::vec2 (kXWindowSize / 2 - 60, 430), ci::Color("White"),
                                   ci::Font("Arial", 25));
        ci::gl::drawStringCentered("Normie", glm::vec2 (kXWindowSize / 2, 432), ci::Color("White"),
                                   ci::Font("Arial", 22));
        ci::gl::drawStringCentered("Hard", glm::vec2 (kXWindowSize / 2 + 60, 430), ci::Color("White"),
                                   ci::Font("Arial", 25));
    }

    else{
        if (Engine.getWinner() == "left"){
            ci::gl::drawStringCentered("LEFT WINS!",glm::vec2(kXWindowSize / 2, kYWindowSize / 2 - 50),
                                       ci::Color("white"),ci::Font("Comic Sans", 100));
        }

        if (Engine.getWinner() == "right"){
            ci::gl::drawStringCentered("RIGHT WINS!",glm::vec2(kXWindowSize / 2, kYWindowSize / 2 - 50),
                                       ci::Color("white"),ci::Font("Comic Sans", 100));
        }
    }
}

void PongApp::update() {
    Engine.Update();
}

void PongApp::DrawPaddlesAndBall() {
    ci::gl::color(1,0,0);
    ci::gl::drawSolidCircle(Engine.getBall().getPosition(), (float) Engine.getBall().getRadius());

    ci::Rectf left_paddle_rect(Engine.getLeftPaddle().getTopRightPosition().x - (float) Engine.getLeftPaddle().getWidth(),
                               Engine.getLeftPaddle().getTopRightPosition().y,
                               Engine.getLeftPaddle().getTopRightPosition().x,
                               Engine.getLeftPaddle().getTopRightPosition().y + (float) Engine.getLeftPaddle().getLength());
    ci::Rectf right_paddle_rect(Engine.getRightPaddle().getTopRightPosition().x - (float) Engine.getRightPaddle().getWidth(),
                                Engine.getRightPaddle().getTopRightPosition().y,
                                Engine.getRightPaddle().getTopRightPosition().x,
                                Engine.getRightPaddle().getTopRightPosition().y + (float) Engine.getRightPaddle().getLength());

    ci::gl::color(0,5,1);
    ci::gl::drawSolidRect(left_paddle_rect);
    ci::gl::color(0,1,0);
    ci::gl::drawSolidRect(right_paddle_rect);
}

void PongApp::keyDown(ci::app::KeyEvent event) {
    if (event.getChar() == 'w'){
        glm::vec2 newPos(Engine.getLeftPaddle().getTopRightPosition().x,
                  Engine.getLeftPaddle().getTopRightPosition().y - 10);
        Engine.setLeftPaddleTopRightPosition(newPos);
    }

    if (event.getChar() == 's'){
        glm::vec2 newPos(Engine.getLeftPaddle().getTopRightPosition().x,
                         Engine.getLeftPaddle().getTopRightPosition().y + 10);
        Engine.setLeftPaddleTopRightPosition(newPos);
    }
}

void PongApp::mouseDown(ci::app::MouseEvent event) {
    glm::vec2 mouse_loc = event.getPos();
    glm::vec2 easy_vel(5,-5);

    if (event.isLeft() && mouse_loc.x > kXWindowSize / 2 - 85 && mouse_loc.x < kXWindowSize / 2 - 35 &&
    mouse_loc.y > 430 && mouse_loc.y < 450){
        Engine.setMode("easy");
    }

    if (event.isLeft() && mouse_loc.x > kXWindowSize / 2 - 25 && mouse_loc.x < kXWindowSize / 2 + 25 &&
        mouse_loc.y > 430 && mouse_loc.y < 450){
        Engine.setMode("normal");
    }

    if (event.isLeft() && mouse_loc.x > kXWindowSize / 2 + 35 && mouse_loc.x < kXWindowSize / 2 + 85 &&
        mouse_loc.y > 430 && mouse_loc.y < 450){
        Engine.setMode("hard");
    }
}


}  // namespace pong
