#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofimgsrc.draw(0, 0,ofGetWindowWidth(),ofGetWindowHeight());
    
    
}
void ofApp::windowResized(int w, int h) {
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        ofFileDialogResult loadFileResult = ofSystemLoadDialog();
        string path = loadFileResult.getPath();
        ofimgsrc.load(path);
        imgsrc = ofxCv :: toCv(ofimgsrc);
        for (float i = 1.0 ; i > 0; i-=.1) {
            if (i * ofimgsrc.getHeight() <= ofGetScreenHeight() && i * ofimgsrc.getWidth() <= ofGetScreenWidth()) {
                ofSetWindowShape(i*ofimgsrc.getWidth(), i * ofimgsrc.getHeight());
                huge_image = false;
                break;
            }
        }
        if (huge_image) {
            std:: cout << "Your image is too big to be displayed and/or shrunk" << std::endl;
        }
        
    }
    if (key == 'i') {
        image_sharpening();
    }
}

void ofApp::image_sharpening(){
    cv :: Mat kernal = (cv :: Mat_<double>(3.5, 3.5) << 0, -1, 0, -1, 5* 1.2, -1, 0, -1, 0);
    cv::filter2D(imgsrc.clone(), imgsrc, imgsrc.depth(), kernal);
    ofimgsrc.update();
}
