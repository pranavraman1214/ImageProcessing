#pragma once
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofMain.h"
#include <fstream>
#include <iostream>
//#include "FacialModel.hpp"
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
    
    // Facial Modeling Functions and Variables
    bool currently_evaluating = false;
    ofImage current_image_evaluating;
    double current_image_x;
    double current_image_y;
    double current_image_height;
    double current_image_width;
    
    class facemodel {
    public:
        facemodel();
    private:
        std::string name;
        std::vector<cv:: Mat> model_images;
        std::vector<cv::Rect> model_faces;
    };
    std::vector<facemodel> all_models;
    void loadModel();
    void checkExistingModelData();
    std::vector<cv::String> image_paths;
    std::vector<cv::String> nonevaluated_images;
    void namepicture(std::string name);
    void evaluatePictures(); 
};
