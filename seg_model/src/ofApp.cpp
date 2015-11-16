#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    gui_reset.addListener(this, &ofApp::resetModel);
    gui_update.addListener(this, &ofApp::updateModel);

    gui_group_a.addListener(this, &ofApp::onSlidersUpdate);
    gui_group_b.addListener(this, &ofApp::onSlidersUpdate);
    gui_empty.addListener(this, &ofApp::onSlidersUpdate);
    gui_grid_size.addListener(this, &ofApp::onGridSizeUpdate);
    gui_sim.addListener(this, &ofApp::onSlidersUpdate);

    gui.setup();
    gui.add(gui_grid_size.setup("grid size",50, 10, 200));
    gui.add(gui_group_a.setup("A",0.5,0,1));
    gui.add(gui_group_b.setup("B",0.3,0,1));
    gui.add(gui_empty.setup("Empty",0.2,0,1));
    gui.add(gui_sim.setup("Similiarity",0.3,0,1));
    gui.add(gui_reset.setup("RESET"));
    gui.add(gui_update.setup("STEP"));
    gui.add(gui_autostep.setup("auto step", false));

    map.allocate(50,50, OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (gui_autostep) {
        updateModel();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(ofColor::black);

    ofImage img;
    ofPixels pix;
    pix.allocate(ofGetWidth(),ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    img.allocate(ofGetWidth(),ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    map.resizeTo(pix, OF_INTERPOLATE_NEAREST_NEIGHBOR);
    img.setFromPixels(pix);
    img.draw(0,0,ofGetWidth(),ofGetHeight());

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::resetModel(){
    float r,a,b;
    a = (float)gui_group_a;
    b = (float)gui_group_b + a;

    vacant.clear();
    for (int i=0; i<map.getHeight(); i++) {
        for (int j=0; j<map.getWidth(); j++) {
            r = ofRandomuf();
            if (r<=a) {
                map.setColor(i, j, ofColor::red);
            } else if(r>a && r<=b) {
                map.setColor(i, j, ofColor::blue);
            } else {
                map.setColor(i, j, ofColor::black);
                vacant.push_back(ofVec2f(i, j));
            }
        }
    }

    ofRandomize(vacant);
}

void ofApp::onSlidersUpdate(float &val) {
    float a,b;
    if (gui_group_a+gui_group_b != 1 - gui_empty && gui_group_a+gui_group_b!=0) {
        a = gui_group_a * (1 - gui_empty) / (gui_group_a + gui_group_b);
        b = gui_group_b * (1 - gui_empty) / (gui_group_a + gui_group_b);

        gui_group_a = a;
        gui_group_b = b;
    } else if (gui_group_a+gui_group_b==0) {
        gui_group_a = (1 - gui_empty) / 2;
        gui_group_b = (1 - gui_empty) / 2;
    }
    resetModel();
}

void ofApp::onGridSizeUpdate(int &val) {
    map.allocate(val, val, OF_IMAGE_COLOR_ALPHA);
    resetModel();
}

void ofApp::updateModel() {
    ofPixels new_map;
    new_map = ofPixels(map);
//    new_map.allocate(map.getWidth(),map.getHeight(), map.getImageType());
//    new_map.setColor(ofColor::black);
    float sim = gui_sim * 8;

    for (int i=0;i<map.getWidth();i++) {
        for (int j=0;j<map.getWidth();j++) {
            float r,b;
            ofColor c;

            for (int n=-1;n<2;n++) {
                for (int k=-1;k<2;k++) {
                    c = map.getColor(i+n,j+k);
                    r = r + c.r;
                    b = b + c.b;
                }
            }

            c = map.getColor(i,j);
            r = (r - c.r)/255;
            b = (b - c.b)/255;

            if ((c.r>=254 && sim>r) || (c.b>=254 && sim>b)) {
                int q = (int)ofRandom(vacant.size());
                int x = (int)vacant[q].x;
                int y = (int)vacant[q].y;

                new_map.setColor(x, y, c);
                vacant.erase(vacant.begin() + q);

                new_map.setColor(i, j, ofColor::black);
                vacant.push_back(ofVec2f(i, j));
            }

        }
    }

    map = new_map;
}
