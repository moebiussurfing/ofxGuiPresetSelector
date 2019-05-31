#pragma once

#include "ofMain.h"

#include "ofxGuiPresetSelector.h"

//-

// DEFINE MODE:

// un-comment one of the two modes only! can't use both together:

// A. ofParameterGroup

#define USE_OF_PARAMETER_GROUP

//-

// B. custom DataGrid class

//#define USE_CUSTOM_DATAGRID

//-

#ifdef USE_CUSTOM_DATAGRID
#include "DataGrid.h"
#endif

//-

//--

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    //--

    // PRESET MANAGER

    ofxGuiPresetSelector PRESETS_manager;

    //-

    // CONTROL


    //-

    ofxGui gui;
    ofxGuiPanel* panel;
    ofxGuiGroup* group;

    void setup_group();

    //-

    // group

#ifdef USE_OF_PARAMETER_GROUP
    ofParameterGroup params;
    ofParameter<int> numSquares;
    ofParameter<int> separation;
    ofParameter<int> squareSide;
#endif

    //-

    // custom class

#ifdef USE_CUSTOM_DATAGRID
    DataGrid myDataGrid;
#endif

    //--

    // TODO: easy listener temp solution..
    void Changed_DONE_load(bool & DONE_load);
    void Changed_DONE_save(bool & DONE_save);

};
