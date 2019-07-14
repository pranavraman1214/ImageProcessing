#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofimgsrc.draw(0, 0);
    for (int i = 0; i < face_x_coordinates.size(); i++) {
        ofColor(255,255,255);
        ofNoFill();
        ofDrawEllipse(face_x_coordinates.at(i), face_y_coordinates.at(i), face_width.at(i), face_height.at(i));
        //ofDrawCircle(face_x_coordinates.at(i), face_y_coordinates.at(i), face_width.at(i));
        
        std::cout <<"X Coordinate: " <<face_x_coordinates.at(i) << std:: endl;
        std::cout <<"Y Coordinate: "<<face_y_coordinates.at(i) << std:: endl;
        std::cout <<"Face Width: "<<face_width.at(i) << std:: endl;
        std::cout <<"Face Height: "<<face_height.at(i) << std:: endl;
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
        resize();
    }
    if (key == 'a') {
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
    std::vector<cv::Rect> faces;
    cv:: CascadeClassifier face_image;
face_image.load("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/data/haarcascades/haarcascade_frontalcatface.xml");
    cv:: Mat grayscale_image;
    cv:: cvtColor(imgsrc, grayscale_image, cv::COLOR_BGR2GRAY);
    face_image.detectMultiScale(grayscale_image, faces, 1.1, 2,
                                0|cv::CASCADE_SCALE_IMAGE, cv::Size(10, 10) );
    for (size_t i = 0; i < faces.size(); i++) {
        cv::Rect current_rectangle = faces[i];
        face_x_coordinates.push_back(current_rectangle.x + current_rectangle.width * .5);
        face_y_coordinates.push_back(current_rectangle.y + current_rectangle.height * .5);
        face_height.push_back(current_rectangle.height);
        face_width.push_back(current_rectangle.width);
    }
    
}
