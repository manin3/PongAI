#include <visualizer/Pong_App.h>

using pong::PongApp;

void prepareSettings(PongApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PongApp, ci::app::RendererGl, prepareSettings);
