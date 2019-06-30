#pragma once

#include "ofMain.h"
#include <opencv2/opencv.hpp>
#include "ofxOpenCv.h"
#include "ofxCv.h"



class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void image_sharpening();
    void windowResized(int w, int h);
    cv:: Mat imgsrc;
    cv:: Mat laplaciansharpened;
    ofImage ofimgsrc;
    bool huge_image = true;
};
