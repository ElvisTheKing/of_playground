#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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

        void onSlidersUpdate(float &val);
        void onGridSizeUpdate(int &val);

        void resetModel();
        void updateModel();
        void saveImg();

        ofxGuiGroup gui;
        ofxIntSlider gui_grid_size;
        ofxFloatSlider gui_group_a, gui_group_b, gui_empty, gui_sim;
        ofxButton gui_reset, gui_update;
        ofxToggle gui_autostep;

        ofPixels map;
        vector<ofVec2f> vacant;
        int image_counter = 0;
};
