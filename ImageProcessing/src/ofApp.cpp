#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    ofimgsrc.draw(0, 0);
    for (int i = 0; i < eye_x_coordinates.size(); i++) {
        ofSetColor(57,255,20);
        ofNoFill();
        ofDrawEllipse(eye_x_coordinates.at(i), eye_y_coordinates.at(i), eye_width.at(i), eye_height.at(i));
    }
    
    for (int i = 0; i < alternate_face_x_coordinates.size(); i++) {
        ofSetColor(255, 57, 18);
        ofNoFill();
        ofDrawEllipse(alternate_face_x_coordinates.at(i), alternate_face_y_coordinates.at(i), alternate_face_width.at(i), alternate_face_height.at(i));
    }
    
    for (int i = 0; i < profile_face_x_coordinates.size(); i++) {
        ofSetColor(0, 0, 255);
        ofNoFill();
        ofDrawEllipse(profile_face_x_coordinates.at(i), profile_face_y_coordinates.at(i), profile_face_width.at(i), profile_face_height.at(i));
    }
    ofSetColor(255, 255, 255);
}
void ofApp::windowResized(int w, int h) {
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        ofFileDialogResult loadFileResult = ofSystemLoadDialog();
        string path = loadFileResult.getPath();
        ofimgsrc.load(path);
        resize();
    }
    if (key == 'i') {
        image_sharpening();
    }
    if (key == 'f') {
        facialDetection(); 
    }
}
void ofApp:: resize() {
    for (float i = 1.0 ; i > 0; i-=.1) {
        if (i * ofimgsrc.getHeight() <= ofGetScreenHeight() && i * ofimgsrc.getWidth() <= ofGetScreenWidth()) {
            ofSetWindowShape(i*ofimgsrc.getWidth(), i * ofimgsrc.getHeight());
            ofimgsrc.resize(i * ofimgsrc.getWidth(), i* ofimgsrc.getHeight());
            huge_image = false;
            altering_factor = i;
            imgsrc = ofxCv :: toCv(ofimgsrc);
            break;
        }
    }
    if (huge_image) {
        std:: cout << "Your image is too big to be displayed and/or shrunk" << std::endl;
    }
}

void ofApp::image_sharpening(){
    cv :: Mat kernal = (cv :: Mat_<double>(3.5, 3.5) << 0, -1, 0, -1, 5* 1.2, -1, 0, -1, 0);
    cv::filter2D(imgsrc.clone(), imgsrc, imgsrc.depth(), kernal);
    ofimgsrc.update();
}

void ofApp::facialDetection() {
    cv:: Mat grayscale_image;
    cv:: cvtColor(imgsrc, grayscale_image, cv::COLOR_BGR2GRAY);
    
    cv:: CascadeClassifier eye_image;
    std:: vector<cv:: Rect> eyes;
eye_image.load("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/data/haarcascades/haarcascade_eye.xml");
    eye_image.detectMultiScale(grayscale_image, eyes, 1.1, 3,
                                1|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
    for (size_t i = 0; i < eyes.size(); i++) {
        cv::Rect current_rectangle = eyes[i];
        eye_x_coordinates.push_back(current_rectangle.x + current_rectangle.width * .5);
        eye_y_coordinates.push_back(current_rectangle.y + current_rectangle.height * .5);
        eye_height.push_back(current_rectangle.height);
        eye_width.push_back(current_rectangle.width);
    }
    
    std:: vector<cv:: Rect> alternate_faces;
    cv:: CascadeClassifier alternate_face_image;
alternate_face_image.load("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/data/haarcascades/haarcascade_frontalface_alt.xml");
    alternate_face_image.detectMultiScale(grayscale_image, alternate_faces, 1.1, 2,
                                          30|cv::CASCADE_SCALE_IMAGE, cv::Size(40, 40));
    for (size_t i = 0; i < alternate_faces.size(); i++) {
        cv::Rect current_rectangle = alternate_faces[i];
        alternate_face_x_coordinates.push_back(current_rectangle.x + current_rectangle.width * .5);
        alternate_face_y_coordinates.push_back(current_rectangle.y + current_rectangle.height * .5);
        alternate_face_height.push_back(current_rectangle.height);
        alternate_face_width.push_back(current_rectangle.width);
    }
   
    cv:: CascadeClassifier face_profile_image;
    std:: vector<cv:: Rect> profile_faces;
face_profile_image.load("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/data/haarcascades/haarcascade_frontalface_alt2.xml");
    face_profile_image.detectMultiScale(grayscale_image, profile_faces, 1.1, 4,
                                        30|cv::CASCADE_SCALE_IMAGE, cv::Size(40, 40));
    for (size_t i = 0; i < profile_faces.size(); i++) {
        cv::Rect current_rectangle = profile_faces[i];
        profile_face_x_coordinates.push_back(current_rectangle.x + current_rectangle.width * .5);
        profile_face_y_coordinates.push_back(current_rectangle.y + current_rectangle.height * .5);
        profile_face_height.push_back(current_rectangle.height);
        profile_face_width.push_back(current_rectangle.width);
    }
}

