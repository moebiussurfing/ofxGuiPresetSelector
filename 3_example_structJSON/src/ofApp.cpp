#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofDisableAntiAliasing();
    ofSetWindowTitle("ofxGuiSelector example");

//    //-
//
//    myDataGrid.id = 1;
//    myDataGrid.name = "grid_" + ofToString(myDataGrid.id) + ".json";
//
//    //-
//
//    // initiate
//
//    for( size_t n = 0; n < NUM_SEQ_NOTES; n++ )
//    {
//        cout << "rowNote_" << n << " -- ";
//
//        for( size_t b = 0; b < NUM_SEQ_BEATS; b++ )
//        {
//            int iState = (int) ofRandom(0, 2);
//            cout << "b" << b << ":" <<iState << " ";
//
//            myDataGrid.grid[n][b] = iState;
//        }
//        cout << endl;
//    }
//
//    //-
//
//    // save
//
//    myDataGrid.save_JSON( myDataGrid.name );
//
//    //-
//
//    // load json
//
//    myDataGrid.load_JSON( myDataGrid.name );
//
//    //-
//
//    // dump grid
//
//    myDataGrid.dump_grid();

    //--

    // setup 'ofParameterGroup params'
    setup_group();

    //-

    // GUI
    
    panel = gui.addPanel();
    group = panel->addGroup(params);
    panel->setPosition(10, 10);

    //-

    // PRESET MANAGER

//    selector.add( *panel, { '1', '2', '3', '4', '5'} );
//    // selector.add( gui, 6 ); // add without activating key switch, 6 presets
//    // selector.add( anotherGui, {'q', 'w', 'e', 'r', 't', 'y'} ); // add another gui with other keys
//    // selector.setModeKey( OF_KEY_TAB ); // change the key you have to hold for saving
//    // remember that the switch key change the keycodes
//    // so it shouldn't work
//
//    // remember to have a bin/data folder in your app directories
//    // the first time you save you probably have to press the key twices, the first it just create the .xml file

    //-

//    selector.add( params, { '1', '2', '3', '4', '5'} );
    selector.add( myDataGrid, { '1', '2', '3', '4', '5'} );

    //-

    // x, y, button size
    selector.setPosition( 20, 360, 50 );

    selector.load( 1 ); // load the second preset of the first added gui
    //selector.load( 0, 1 ); // load the first preset of the second added gui

    // remember to have a bin/data folder in your app directories
    // there are already 3 saved presets in the bin/data folder of this example

}

//--------------------------------------------------------------
void ofApp::setup_group(){

//    // array bool steps
//
//    params.setName("bools");
//    // array bool steps
//    for (int i = 0; i < 16; i++)
//    {
//        bool b = false;
//        std::string n = "s" + ofToString(i);
//
//        step[i].set(n, b);
//        params.add( step[i] );
//    }

    //-

    // int parameters

    params.setName("squares");
    // it is really important to set the name as it will be used as base for the .xml preset files
    // remember to give each ofxPanel an unique name
    params.add( numSquares.set("num squares", 1, 1, 24) );
    params.add( separation.set("separation", 5, 1, 100) );
    params.add( squareSide.set("square side", 50, 5, 200) );

    //-

    myDataGrid.setName("stepSequencer");

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

    ofBackground(0);

    ofSetColor(255, 95, 95);
    ofNoFill();
    ofPushMatrix();
    ofTranslate( 320, 50 );
    for( int i=0; i<numSquares; ++i){
        ofDrawRectangle(0, 0, squareSide, squareSide);
        ofTranslate( separation, separation );
    }
    ofPopMatrix();

    selector.draw();
    // draws some minimalistic graphics to monitor the active preset
    // when graphics are drawn you can also click on them for saving/loading

    string info = "press 1-5 for loading a preset, press CTRL+1-5 for saving presets\n";
    info += "or click on the selector buttons above\n";
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
