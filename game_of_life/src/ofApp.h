#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAutoReloadedShader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


        void initNoise();
        void resolutionChanged(int &resolution);
        void framerateChanged(int &framerate);

        ofxPanel gui;
        ofxButton button_init_noise;
        ofxIntSlider res_slider,framerate_slider;

        ofxAutoReloadedShader shader;
        ofTexture tex;
        ofFbo fbo;
        bool init_flag = 1;
        int width, height;
};
