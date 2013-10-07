#pragma once

#include "ofMain.h"
#include "GRT.h"
#include "ofxGui.h"
#include "ofxUI.h"

#define TEST 1
#define TRAIN 0

using namespace GRT;

class testApp : public ofBaseApp{

	public:
    
        void modeToTrain(); //called when mode buttons are toggled
        void modeToTest(); //called when mode buttons are toggled
        void drawChanged();
        void exit();
        void guiEvent(ofxUIEventArgs &e);

    
		void setup();
		void update();
		void draw();

    
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    ofxUICanvas *gui;
    
    
    //current mode
    int mode;
	
    //gui

    //gui elements
    ofxGuiGroup modeGroup;
    ofxToggle trainMode;
    ofxToggle testMode;

    //drawing buttons
     ofxGuiGroup drawGroup;
   	ofxToggle drawButton;
    ofxToggle moveButton;
    ofxToggle deletePointButton;
    ofxButton clearAllPointsButton;
    //shape generation buttons
   ofxButton spiralButton;
   ofxButton polygonButton;
  ofxButton lineButton;
    
    //grt action buttions
    ofxGuiGroup grtGroup;
    ofxButton saveButton;
    ofxButton predictButton;
    ofxButton trainButton;
    ofxButton deleteLastButton;
    ofxButton clearAllDataButton;
    
	ofxLabel drawLabel;
    ofxLabel modeLabel;
    ofxLabel shapeLabel;
    ofxLabel classLabel;
    
    string outputStr;

    

};
