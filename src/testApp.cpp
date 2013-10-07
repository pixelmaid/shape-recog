#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
    mode = TRAIN;
    gui = new ofxUICanvas(0,0,320,320);		//ofxUICanvas(float x, float y, float width, float height)
    
    gui->addWidgetDown(new ofxUILabel("OFXUI TUTORIAL", OFX_UI_FONT_LARGE));
    gui->addWidgetDown(new ofxUISlider(304,16,0.0,255.0,100.0,"BACKGROUND VALUE"));
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->loadSettings("GUI/guiSettings.xml");
    
   /* trainMode.setBackgroundColor(ofColor(255,0,0));
    
	modeGroup.setup("mode"); // most of the time you don't need a name
    modeGroup.setPosition(ofPoint(0,0));
    modeGroup.add(modeLabel.setup("current mode","train"));
    modeGroup.add(trainMode.setup("train",true));
    modeGroup.add(testMode.setup("test",false));
    
    
    drawGroup.setup("Drawing Tools");
    drawGroup.setPosition(ofPoint(0,modeGroup.getHeight()+10));
    drawGroup.add(drawButton.setup("draw",true));
    drawGroup.add(moveButton.setup("move",false));
    drawGroup.add(deletePointButton.setup("delete points",false));
    drawGroup.add(clearAllPointsButton.setup("clear all points"));
    drawGroup.add(spiralButton.setup("generate spiral"));
    drawGroup.add(polygonButton.setup("generate polygon"));
    drawGroup.add(lineButton.setup("generate line"));
    */
    
    /*
	gui.add(filled.setup("fill", true));
	gui.add(radius.setup( "radius", 140, 10, 300 ));
	gui.add(center.setup("center",ofVec2f(ofGetWidth()*.5,ofGetHeight()*.5),ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight())));
	gui.add(color.setup("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
	gui.add(circleResolution.setup("circle res", 5, 3, 90));
	gui.add(twoCircles.setup("two circles"));
	gui.add(ringButton.setup("ring"));
	gui.add(screenSize.setup("screen size", ""));
    
	bHide = true;
    
	ring.loadSound("ring.wav");*/

}

void testApp::modeToTrain(){
    if(mode!=TRAIN){
        mode=TRAIN;
    testMode = false;
    trainMode = true;
        //trainMode.setName("train");
        modeLabel = "train";
    testMode.setBackgroundColor(ofColor(255,0,0));
    trainMode.setBackgroundColor(ofColor(0,0,0));
        printf("mode to train");
    }

}

void testApp::modeToTest(){
    if(mode!=TEST){
        mode=TEST;
        modeLabel = "test";
    trainMode = false;
    testMode = true;

       // trainMode.setName("test");
        trainMode.setBackgroundColor(ofColor(255,0,0));
        testMode.setBackgroundColor(ofColor(0,0,0));
        printf("mode to test\n");
    }
    

}


void testApp::drawChanged(){
    printf("draw changed");

}

void testApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.widget->getName() == "BACKGROUND VALUE")
    {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        ofBackground(slider->getScaledValue());
    }
}


//--------------------------------------------------------------
void testApp::update(){
    if(trainMode){
        modeToTrain();
    }
    if(testMode){
        modeToTest();
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
   	// auto draw?
	// should the gui control hiding?

    modeGroup.draw();
	drawGroup.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    
  }

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
