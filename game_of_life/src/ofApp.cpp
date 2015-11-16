#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shaders/seg");

    button_init_noise.addListener(this, &ofApp::initNoise);
    res_slider.addListener(this, &ofApp::resolutionChanged);
    framerate_slider.addListener(this, &ofApp::framerateChanged);

    gui.setup();
    gui.add(button_init_noise.setup("init noise"));
    gui.add(res_slider.setup("Resolution", 40, 0, ofGetWidth()));
    gui.add(framerate_slider.setup("Framerate", 30, 2, 240));

    fbo.allocate(width, height);
    fbo.begin();
    fbo.end();

    ofSetFrameRate(framerate_slider);
}

//-------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofTexture temp_tex = fbo.getTexture();

    fbo.begin();
    shader.begin();

    shader.setUniformTexture("tex0", temp_tex, 1);
    shader.setUniform1i("init_flag", init_flag);
    shader.setUniform1f("time", ofGetElapsedTimef());
    init_flag = 0;

    ofDrawRectangle(0, 0, width, height);
    shader.end();
    fbo.end();

    ofClear(0,0,0,255);
    ofPixels pixels;
    ofImage img;
    img.clear();
    fbo.readToPixels(pixels);

    pixels.resize(ofGetWidth(), ofGetHeight(), OF_INTERPOLATE_NEAREST_NEIGHBOR);
    img.setFromPixels(pixels);
    img.draw(0,0, ofGetWidth(),ofGetHeight());

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    this->resolutionChanged(width);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::initNoise() {
    init_flag = 1;
}

void ofApp::resolutionChanged(int &resolution) {
    width = resolution;
    height =  (int)((float)ofGetHeight() / ofGetWidth() * width);
    this->initNoise();
    fbo.allocate(width, height);
}

void ofApp::framerateChanged(int &framerate) {
    ofSetFrameRate(framerate);
}
