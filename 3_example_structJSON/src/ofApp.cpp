#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    ofDisableAntiAliasing();
    ofSetWindowTitle("ofxGuiSelector example");

    //--

    // setup DATA

    setup_group();

    //-

    // GUI

    panel = gui.addPanel();
    group = panel->addGroup(params);

    panel->setPosition(400, 10);

    //-

    // PRESET MANAGER

//    PRESETS_manager.add( *panel, { '1', '2', '3', '4', '5'} );
//    // PRESETS_manager.add( gui, 6 ); // add without activating key switch, 6 presets
//    // PRESETS_manager.add( anotherGui, {'q', 'w', 'e', 'r', 't', 'y'} ); // add another gui with other keys
//    // PRESETS_manager.setModeKey( OF_KEY_TAB ); // change the key you have to hold for saving
//    // remember that the switch key change the keycodes
//    // so it shouldn't work
//
//    // remember to have a bin/data folder in your app directories
//    // the first time you save you probably have to press the key twices, the first it just create the .xml file

    //-

#ifdef USE_OF_PARAMETER_GROUP
    // ofParameterGroup params
    PRESETS_manager.add( params, { '1', '2', '3', '4', '5'} );
#endif

//-

#ifdef USE_CUSTOM_DATAGRID
    // custom DATA
    PRESETS_manager.add( myDataGrid, { '1', '2', '3', '4', '5'} );
#endif

    //-

    // x, y, button size
    PRESETS_manager.setPosition_CLICKER( 20, 10, 50 );

    PRESETS_manager.load( 1 ); // load the second preset of the first added gui
    //PRESETS_manager.load( 0, 1 ); // load the first preset of the second added gui

    // remember to have a bin/data folder in your app directories
    // there are already 3 saved presets in the bin/data folder of this example
}

//--------------------------------------------------------------
void ofApp::setup_group()
{
    //-

    // group

#ifdef USE_OF_PARAMETER_GROUP
    // setup 'ofParameterGroup params'
    params.setName("squares");
    // it is really important to set the name as it will be used as base for the .xml preset files
    // remember to give each ofxPanel an unique name
    params.add( numSquares.set("num squares", 1, 1, 24) );
    params.add( separation.set("separation", 5, 1, 100) );
    params.add( squareSide.set("square side", 50, 5, 200) );
#endif

    //-

    // grid matrix

#ifdef USE_CUSTOM_DATAGRID
    myDataGrid.setName("stepSequencer");
#endif

    //-
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString( ofGetFrameRate() ) );
}

//--------------------------------------------------------------
void ofApp::exit(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(128);

//    ofSetColor(255, 95, 95);
//    ofNoFill();
//    ofPushMatrix();
//    ofTranslate( 320, 50 );
//    for( int i=0; i<numSquares; ++i){
//        ofDrawRectangle(0, 0, squareSide, squareSide);
//        ofTranslate( separation, separation );
//    }
//    ofPopMatrix();

    PRESETS_manager.draw();
    // draws some minimalistic graphics to monitor the active preset
    // when graphics are drawn you can also click on them for saving/loading

    string info = "press 1-5 for loading a preset, press CTRL+1-5 for saving presets\n";
    info += "or click on the PRESETS_manager buttons above\n";
    info += "the last button save the currently selected preset";
    ofDrawBitmapString( info , 20, ofGetHeight() - 40 );
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
