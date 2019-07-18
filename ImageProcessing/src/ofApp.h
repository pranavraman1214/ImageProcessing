#pragma once

#include "ofMain.h"
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
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
    void resize(); 
    void facialDetection();
    void facialRecognition();
    cv:: Mat imgsrc;
    std:: vector<double> alternate_face_height;
    std:: vector<double> alternate_face_width;
    std:: vector<double> alternate_face_x_coordinates;
    std:: vector<double> alternate_face_y_coordinates;
    std:: vector<double> profile_face_height;
    std:: vector<double> profile_face_width;
    std:: vector<double> profile_face_x_coordinates;
    std:: vector<double> profile_face_y_coordinates;
    std:: vector<double> eye_height;
    std:: vector<double> eye_width;
    std:: vector<double> eye_x_coordinates;
    std:: vector<double> eye_y_coordinates;
    cv:: Mat laplaciansharpened;
    ofImage ofimgsrc;
    float altering_factor = 1; 
    bool huge_image = true;
};
