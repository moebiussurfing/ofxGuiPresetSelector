#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(30);
    ofSetWindowTitle("PRESET MANAGER");

    //--

    // ofParameterGroup params

#ifdef USE_OF_PARAMETER_GROUP

    // define and group parameters
    params.add( numSquares.set("num squares", 1, 1, 24) );
    params.add( separation.set("separation", 5, 1, 100) );
    params.add( squareSide.set("square side", 50, 5, 200) );

    // create gui for the group
    panel = gui.addPanel();
    group = panel->addGroup(params);
    panel->setPosition(400, 10);

#endif

    //-

    // PRESET MANNAGER

    // GUI

    PRESETS_manager.setup_Gui();

    //-

    // ofParameterGroup params

#ifdef USE_OF_PARAMETER_GROUP
    PRESETS_manager.set_pathKit_Folder("assets/groups/kit_1");
    params.setName("myGroupParameters");
    PRESETS_manager.add( params, { '1', '2', '3', '4', '5', '6', '7', '8'} );
#endif

    //-

    // custom DATA

#ifdef USE_CUSTOM_DATAGRID
    PRESETS_manager.set_pathKit_Folder("assets/patterns/kit_1");
    myDataGrid.setName("stepSequencer");
    PRESETS_manager.add( myDataGrid, { '1', '2', '3', '4', '5', '6', '7', '8'} );
#endif

    //-

    // TODO: easy listener temp solution to trig when save/load is done
    // then will load refresh grid sequencer states

    PRESETS_manager.DONE_save.addListener(this, &ofApp::Changed_DONE_save);
    PRESETS_manager.DONE_load.addListener(this, &ofApp::Changed_DONE_load);

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

    //--
}


//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString( ofGetFrameRate() ) );
}

//--------------------------------------------------------------
void ofApp::exit(){
    //-

    // TODO: easy listener temp solution to trig when save/load is done
    // then will load refresh grid sequencer states

    PRESETS_manager.DONE_save.removeListener(this, &ofApp::Changed_DONE_save);
    PRESETS_manager.DONE_load.removeListener(this, &ofApp::Changed_DONE_load);
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(128);

    //-

#ifdef USE_OF_PARAMETER_GROUP
    // draw object linked to grouped parameters

    ofPushStyle();
    ofSetColor(ofColor::white);
    ofNoFill();
    ofPushMatrix();
    ofTranslate( 120, 300 );
    for( int i=0; i<numSquares; ++i){
        ofDrawRectangle(0, 0, squareSide, squareSide);
        ofTranslate( separation, separation );
    }
    ofPopMatrix();
    ofPopStyle();
#endif

    //-

    // PRESET MANAGER

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


// TODO: easy listener temp solution
//--------------------------------------------------------------
void ofApp::Changed_DONE_save(bool & DONE_save) {

    ofLogNotice("ofApp") << "Changed_DONE_save: " << ofToString( DONE_save?"TRUE":"FALSE" ) ;

    // extra stuff when finish loading/saving

    if (PRESETS_manager.DONE_save)
    {
        PRESETS_manager.DONE_save = false;

    //        GRID_getFrom_Sequencer();// get sequencer state before saving in preset manager
    }
}

//--------------------------------------------------------------
void ofApp::Changed_DONE_load(bool & DONE_load){
    ofLogNotice("ofApp") << "Changed_DONE_load: " << ofToString( DONE_load?"TRUE":"FALSE" ) ;

    // extra stuff when finish loading/saving

    if (PRESETS_manager.DONE_load)
    {
        PRESETS_manager.DONE_load = false;

        //-

//        // 1. put local grid to sequencer grid:
//
////        ofLogNotice("ofxSEQ") << "ofxSequencer size rows:" << sequencer.grid.size();
//        for(int i=0 ; i < sequencer.grid.size() ; i++)
//        {
////            ofLogNotice("ofxSEQ") << "ofxSequencer size cols:" << sequencer.grid[i].size() ;
//            for(int j=0 ; j < sequencer.grid[i].size() ; j++)
//            {
//                sequencer.grid[i][j] = (bool) myDataGrid.grid[i][j];
//            }
//        }
//
//        //-
//
//        // 2. refresh from sequencer grid to draw params
//
//        sequencer.set_SequencerFromGrid();

        //-
    }
}