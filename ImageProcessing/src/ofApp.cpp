#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofimgsrc.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    for (int i = 0; i < face_x_coordinates.size(); i++) {
        ofDrawEllipse(face_x_coordinates.at(i), face_y_coordinates.at(i), face_width.at(i), face_height.at(i));
    }
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
        //resize();
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
            huge_image = false;
            altering_factor = i;
            cv:: resize(imgsrc, imgsrc, cv::Size(i * ofimgsrc.getWidth(), i * ofimgsrc.getHeight()));
            ofimgsrc.update();
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
    std::vector<cv::Rect> faces;
    cv:: CascadeClassifier face_image;
face_image.load("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/data/haarcascades/haarcascade_frontalcatface.xml");
    cv:: Mat grayscale_image;
    cv:: cvtColor(imgsrc, grayscale_image, cv::COLOR_BGR2GRAY);
    face_image.detectMultiScale(grayscale_image, faces, 1.1, 2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Rect current_rectangle = faces[i];
        face_x_coordinates.push_back(current_rectangle.x * altering_factor);
        face_y_coordinates.push_back(current_rectangle.y * altering_factor);
        face_height.push_back(current_rectangle.height * altering_factor);
        face_width.push_back(current_rectangle.width * altering_factor);
    }
    
}
