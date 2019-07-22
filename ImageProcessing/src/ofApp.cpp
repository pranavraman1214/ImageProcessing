#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (currently_evaluating) {
        ofSetColor(255, 255, 255);
        std::cout << "Im in the draw loop" << std::endl;
        current_image_evaluating.draw(0,0);
        
    } else {
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
    if (key == '1') {
        image_sharpening();
    }
    if (key == '2') {
        facialDetection(); 
    }
    if (key == '3') {
        loadModel();
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


void ofApp::loadModel() {
cv::glob("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/TestImages/FaceRecognitionModelingImages/*.jpg", image_paths, false);
    vector<cv::Mat> images;
    size_t count = image_paths.size();
    for (size_t i=0; i<count; i++) {
        images.push_back(imread(image_paths[i]));
        std:: cout << image_paths[i] << std::endl;
    }
    checkExistingModelData();
}

void writeToFiles() {
    
}

void ofApp::checkExistingModelData() {
    for (size_t i = 0; i < image_paths.size(); i++ ) {
        std::string line;
        std::ifstream input;
        bool data_exists = false;
        input.open("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/facedata/facepath");
        while (!input.eof()) {
            getline(input,line);
            if (line == image_paths[i]) {
                data_exists = true;
                break;
            }
        }
        if (!data_exists) {
            nonevaluated_images.push_back(image_paths[i]);
            std:: cout << "Non Evaluated Image: " << image_paths[i] << std:: endl;
        }
    }
    evaluatePictures(); 
}

void ofApp::evaluatePictures() {
   currently_evaluating = true;
    for (size_t i = 0; i < nonevaluated_images.size(); i++) {
        std:: vector<cv:: Rect> profile_faces;
        cv:: CascadeClassifier face_profile_image;
    face_profile_image.load("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/data/haarcascades/haarcascade_frontalface_alt2.xml");
        current_image_evaluating.load((std::string)nonevaluated_images[i]);
        std:: cout<<(std::string)nonevaluated_images[i] << std::endl; 
        std:: cout << "Image Loaded" << std::endl;
        cv:: Mat current_mat;
        current_mat = ofxCv :: toCv(current_image_evaluating);
        cv:: Mat grayscale_image;
        cv:: cvtColor(current_mat, grayscale_image, cv::COLOR_BGR2GRAY);
        face_profile_image.detectMultiScale(grayscale_image, profile_faces);
        for (int i = 0; i < profile_faces.size(); i++) {
            cv:: Rect current_rectangle = profile_faces[i];
            current_image_x = current_rectangle.x + current_rectangle.width * .5;
            current_image_y = current_rectangle.y + current_rectangle.height * .5;
            current_image_height = current_rectangle.height;
            current_image_width = current_rectangle.width;
        }
        std::string user_input;
        draw();
        std:: cout << "At user input" << std::endl;
        user_input = ofSystemTextBoxDialog("Name of Person's Face", user_input);
        fstream pathwriter,namewriter;
    pathwriter.open("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/facedata/facepath", std::ios_base::app);
        pathwriter << (std::string)nonevaluated_images[i] << std::endl;
        pathwriter.close();
    namewriter.open("/Users/pranavraman/Documents/PersonalProjects/ImageProcessing/ImageProcessing/facedata/facename", std::ios_base::app);
        namewriter << user_input << std::endl;
        namewriter.close();
        std::cout<< "End of loop";
    }
    currently_evaluating = false;
}



void ofApp::namepicture(std:: string name) {
    
}

