#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
    ofCreateWindow(settings);
    ofRunApp(new ofApp);
}
