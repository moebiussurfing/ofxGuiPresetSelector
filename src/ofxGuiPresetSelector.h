
// ofxGuiPresetSelector.h
// Nicola Pisanti, MIT License, 2016
//
// changes by moebiussurfing:
// + switched from ofxGui to ofxGuiExtended
// + switched preset mangement from ofxGuiPanel to ofParametersGroup
// TODO: add vectors, structs, json utils..

#pragma once

#include "ofMain.h"
#include "ofxGuiExtended.h"
#include "DataGrid.h"

class ofxGuiPresetSelector {
    
public:
    ofxGuiPresetSelector();

    // add a gui for preset saving
    void add( ofParameterGroup group, int numPresets=8 );

    // adds and activate key switch
    void add( ofParameterGroup group, initializer_list<int> keysList );

    // save to a preset
    void save( int presetIndex, int guiIndex=0 );
    void save( int presetIndex, string guiName );
    
    // loads an already saved preset
    void load( int presetIndex, int guiIndex=0 );
    void load( int presetIndex, string guiName );
    
    // get the last loaded preset
    int getPresetIndex( int guiIndex ) const;
    int getPresetIndex( string guiName ) const;
    
    // set the key you have to hold for saving, default is OF_KEY_CONTROL
    void setModeKey( int key );

    // set graphics position
    // cellsize is the size of each preset button
    void setPosition( int x, int y, int cellSize );

    // draw some info, when the gui is drawn you can also click on the button to change / save presets
    void draw();
    void draw( int x, int y, int cellSize );
    
    // if you set it to true the preset will be loaded only when you call (false is the default behavior)
    void setDelayedLoading( bool active );
    // make preset change effective when setDelayedLoading() is set to true
    void delayedUpdate();
    // if setDelayedLoading() is set to true stages a load action
    void delayedLoad( int presetIndex, int guiIndex=0 );
    void delayedLoad( int presetIndex, string guiName );
    
    // switch on or off the control with the keys
    void toggleKeysControl( bool active );
    
private:
    int getGuiIndex(string name ) const;
    string presetName( string guiName, int presetIndex );

    //-

    vector<ofParameterGroup> groups;

    //-

    vector<int> lastIndices;
    vector<int> presets;

    void addKeysListeners();
    void keyPressed( ofKeyEventArgs& eventArgs);
    void keyReleased( ofKeyEventArgs& eventArgs );
    
    bool bKeys;
    vector<vector<int>> keys;
    bool keysNotActivated;
    int modeKey;
    bool bKeySave;
    
    int x;
    int y;
    int cellSize;
    
    bool lastMouseButtonState;
    void mousePressed( int x, int y );
    
    bool bDelayedLoading;
    vector<int> newIndices;
};
