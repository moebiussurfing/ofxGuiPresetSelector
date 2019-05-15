#pragma once

#include "ofMain.h"

#include "ofxGuiPresetSelector.h"

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

    ofxGuiPresetSelector selector;

    ofxGui gui;
    ofxGuiPanel* panel;
    ofxGuiGroup* group;
    void setup_group();

    // group
    ofParameterGroup params;

    // int parameters
    ofParameter<int> numSquares;
    ofParameter<int> separation;
    ofParameter<int> squareSide;

    // array bool steps
    ofParameter<bool> step[16];

    //-

    // NOTES:

    // pointer / no-pointer

    // ofParameterGroup * params;
    // ofParameterGroup params;

    // void add( ofParameterGroup & group, initializer_list<int> keysList );
    // void ofxGuiPresetSelector::add( ofParameterGroup & group, int numPresets ) {

    // void add( ofParameterGroup group, initializer_list<int> keysList );
    // void ofxGuiPresetSelector::add( ofParameterGroup group, int numPresets ) {

    // vector<ofParameterGroup> groups;
    // groups.push_back( &group );

    //-

    };