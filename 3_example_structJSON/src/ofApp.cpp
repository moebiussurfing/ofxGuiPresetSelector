#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    //    ofDisableAntiAliasing();
    ofSetWindowTitle("PRESET MANAGER");

    //--

    // ofParameterGroup params

#ifdef USE_OF_PARAMETER_GROUP

    setup_group();

    //-

    // GUI GROUP PARAMETERS

    panel = gui.addPanel();
    group = panel->addGroup(params);
    panel->setPosition(400, 10);

    //-
#endif

    //-

    // PRESET MANNAGER

    // GUI

    PRESETS_manager.setup_Gui();

    //-

    // ofParameterGroup params

#ifdef USE_OF_PARAMETER_GROUP
    PRESETS_manager.set_pathKit_Folder("groups/kit_1");
    params.setName("myGroupParameters");
    PRESETS_manager.add( params, { '1', '2', '3', '4', '5', '6', '7', '8'} );
#endif

    //-

    // custom DATA

#ifdef USE_CUSTOM_DATAGRID
    PRESETS_manager.set_pathKit_Folder("patterns/kit_1");
    myDataGrid.setName("stepSequencer");
    PRESETS_manager.add( myDataGrid, { '1', '2', '3', '4', '5', '6', '7', '8'} );
#endif

    //-

    // x, y, button size
//    PRESETS_manager.setPosition_CLICKER( 20, 10, 50 );

//    PRESETS_manager.load( 1 ); // load the second preset of the first added gui
    //PRESETS_manager.load( 0, 1 ); // load the first preset of the second added gui

    // remember to have a bin/data folder in your app directories
    // there are already 3 saved presets in the bin/data folder of this example

    //-

    // STARTUP INIT

    PRESETS_manager.load_ControlSettings();//this loads selected preset number and gui state

    //-

    // trick to solve auto load fail because the sorting of xml autoSave after preset selector tag
    PRESETS_manager.PRESET_selected_PRE = -1;
    cout << "PRESET_selected:" << PRESETS_manager.PRESET_selected << endl;
    PRESETS_manager.PRESET_selected = PRESETS_manager.PRESET_selected;

    //---

    // DEFAULT STARUP SETTINGS

    PRESETS_manager.set_GUI_position(10, 10);//default
    PRESETS_manager.setPosition_CLICKER(10, 200, 40);//default
    PRESETS_manager.setVisible_ClickPanel(true);//default
    PRESETS_manager.setVisible_Gui(true);//default

    // PRESETS_manager.setDelayedLoading(true);

    //--
}

//--------------------------------------------------------------
void ofApp::setup_group()
{
    //-

    // group

#ifdef USE_OF_PARAMETER_GROUP
    // setup 'ofParameterGroup params'
//    params.setName("myGroupParameters");
    // it is really important to set the name as it will be used as base for the .xml preset files
    // remember to give each ofxPanel an unique name
    params.add( numSquares.set("num squares", 1, 1, 24) );
    params.add( separation.set("separation", 5, 1, 100) );
    params.add( squareSide.set("square side", 50, 5, 200) );
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

    //-

#ifdef USE_OF_PARAMETER_GROUP
    ofPushStyle();
    ofSetColor(ofColor::white);
    ofNoFill();
    ofPushMatrix();
    ofTranslate( 120, 250 );
    for( int i=0; i<numSquares; ++i){
        ofDrawRectangle(0, 0, squareSide, squareSide);
        ofTranslate( separation, separation );
    }
    ofPopMatrix();
    ofPopStyle();
#endif

    //-

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
