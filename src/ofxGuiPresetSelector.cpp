
// ofxGuiPresetSelector.h
// Nicola Pisanti, MIT License, 2016
//
// changes by moebiussurfing:
// + switched from ofxGui to ofxGuiExtended
// + switched preset mangement from ofxGuiPanel to ofParametersGroup
// TODO: add vectors, structs, json utils..

#include "ofxGuiPresetSelector.h"

ofxGuiPresetSelector::ofxGuiPresetSelector(){
        
    modeKey = OF_KEY_CONTROL;
    bKeys = false;
    keysNotActivated = true;
    bKeySave = false;

    // groups
#ifdef USE_OF_PARAMETER_GROUP
    groups.reserve(32);
#endif

    // B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
    grids.reserve(32);
#endif

    lastIndices.reserve(32);
    keys.reserve(32);
    
    lastMouseButtonState = false;

    bDelayedLoading = false;
}

// A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
int ofxGuiPresetSelector::getGuiIndex( string name ) const {

    for( size_t i = 0; i<groups.size(); ++i ){
        if( groups[i].getName() == name ){
            return i;
        }
        return -1;
    }
}
#endif

// B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
int ofxGuiPresetSelector::getGuiIndex( string name ) const {

    for( size_t i = 0; i<grids.size(); ++i ){

        string myName = grids[i].getName();

        if( myName == name ){
        // if( grids[i].getName() == name ){

            return i;
        }
        return -1;
    }
}
#endif


string ofxGuiPresetSelector::presetName( string guiName, int presetIndex ) {

#ifdef USE_OF_PARAMETER_GROUP
    return (guiName + "_preset_" + ofToString(presetIndex) + ".xml" );
#endif

#ifdef USE_CUSTOM_DATAGRID
    return (guiName + "_preset_" + ofToString(presetIndex) + ".json" );
#endif

}

//-

// A. ofParameterGroup

#ifdef USE_OF_PARAMETER_GROUP
void ofxGuiPresetSelector::add( ofParameterGroup group, int numPresets ) {

    // add a gui for preset saving

    groups.push_back(group);

    lastIndices.push_back(0);
    newIndices.push_back(0);
    presets.push_back(numPresets);
}
void ofxGuiPresetSelector::add( ofParameterGroup group, initializer_list<int> keysList ) {

    add( group, keysList.size() );

    keys.resize(groups.size());
    int i = groups.size() - 1;

    keys[i].reserve(keysList.size());

    for (const int & key : keysList) keys[i].push_back( key );

    if(keysNotActivated) addKeysListeners();
}
#endif

//-

// B. custom DataGrid class

#ifdef USE_CUSTOM_DATAGRID
void ofxGuiPresetSelector::add( DataGrid grid, int numPresets ) {

    // add a gui for preset saving

    grids.push_back(grid);

    lastIndices.push_back(0);
    newIndices.push_back(0);
    presets.push_back(numPresets);
}
void ofxGuiPresetSelector::add( DataGrid grid, initializer_list<int> keysList ) {

    add( grid, keysList.size() );

    keys.resize(grids.size());
    int i = grids.size() - 1;

    keys[i].reserve(keysList.size());

    for (const int & key : keysList) keys[i].push_back( key );

    if(keysNotActivated) addKeysListeners();
}
#endif

//-

// A. ofParameterGroup

#ifdef USE_OF_PARAMETER_GROUP
void ofxGuiPresetSelector::save( int presetIndex, int guiIndex ) {
    if(guiIndex>=0 && guiIndex<(int)groups.size()){

        ofXml settings;
        std::string n = presetName( groups[guiIndex].getName(), presetIndex);
        ofSerialize( settings, groups[guiIndex] );
        settings.save( n );
    }
}
void ofxGuiPresetSelector::load( int presetIndex, int guiIndex ) {
    if(guiIndex>=0 && guiIndex<(int)groups.size()){

        ofXml settings;
        settings.load(  presetName( groups[guiIndex].getName(), presetIndex) );
        ofDeserialize(settings, groups[guiIndex] );

        lastIndices[guiIndex] = presetIndex;
    }
}
void ofxGuiPresetSelector::save( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>=0 && guiIndex<(int)groups.size()){
        ofXml settings;
        string n = presetName( guiName, presetIndex);
        ofSerialize( settings, groups[guiIndex] );
        settings.save( n );
    }
}
void ofxGuiPresetSelector::load( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>=0 && guiIndex<(int)groups.size()){

        ofXml settings;
        settings.load( presetName( guiName, presetIndex) );
        ofDeserialize(settings, groups[guiIndex]);

        lastIndices[guiIndex] = presetIndex;
    }
}
#endif

//-

// B. custom DataGrid class

#ifdef USE_CUSTOM_DATAGRID
void ofxGuiPresetSelector::save( int presetIndex, int guiIndex ) {
    if(guiIndex>=0 && guiIndex<(int)grids.size()){

        std::string n = presetName( grids[guiIndex].getName(), presetIndex);
        grids[guiIndex].save_JSON(n);

    }
}
void ofxGuiPresetSelector::load( int presetIndex, int guiIndex ) {
    if(guiIndex>=0 && guiIndex<(int)grids.size()){
        string str = presetName( grids[guiIndex].getName(), presetIndex);
        grids[guiIndex].load_JSON( str );

        lastIndices[guiIndex] = presetIndex;

        grids[guiIndex].dump_grid();
    }
}
void ofxGuiPresetSelector::save( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>=0 && guiIndex<(int)grids.size()){

        string n = presetName( guiName, presetIndex);
        grids[guiIndex].save_JSON(n);
    }
}
void ofxGuiPresetSelector::load( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>=0 && guiIndex<(int)grids.size()){

        string n = presetName( guiName, presetIndex);
        grids[guiIndex].load_JSON(n);

        lastIndices[guiIndex] = presetIndex;

        grids[guiIndex].dump_grid();
    }
}
#endif

//-

// A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
int ofxGuiPresetSelector::getPresetIndex( int guiIndex ) const {
    if(guiIndex>0 && guiIndex<(int)groups.size()){
        return lastIndices[guiIndex];
    }else{
        return -1;
    }
}
int ofxGuiPresetSelector::getPresetIndex( string guiName )const {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>0 && guiIndex<(int)groups.size()){
        return lastIndices[guiIndex];
    }else{
        return -1;
    }
}
#endif

// B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
int ofxGuiPresetSelector::getPresetIndex( int guiIndex ) const {
    if(guiIndex>0 && guiIndex<(int)grids.size()){
        return lastIndices[guiIndex];
    }else{
        return -1;
    }
}
int ofxGuiPresetSelector::getPresetIndex( string guiName )const {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>0 && guiIndex<(int)grids.size()){
        return lastIndices[guiIndex];
    }else{
        return -1;
    }
}
#endif

//-

void ofxGuiPresetSelector::setModeKey( int key ){
    modeKey = key;
}


void ofxGuiPresetSelector::keyPressed( ofKeyEventArgs& eventArgs ) {    
    if( bKeys ){
		const int & key = eventArgs.key;
		
		if(key == modeKey){
			bKeySave = true;
			return;
		} 
		
		for(size_t i=0; i<keys.size(); ++i){
			for(size_t k=0; k<keys[i].size(); ++k){
				if(key == keys[i][k]){
					
					if(bKeySave){
						save( k, i);
					}else{
						if(bDelayedLoading){
							newIndices[i] = k;
						}else{
							load( k, i );
						}
					}
					
					return;
				}
			}   
		}
    }
}


void ofxGuiPresetSelector::keyReleased( ofKeyEventArgs& eventArgs ) {
    if( eventArgs.key == modeKey) bKeySave = false;
}


void ofxGuiPresetSelector::addKeysListeners(){
    ofAddListener( ofEvents().keyPressed, this, &ofxGuiPresetSelector::keyPressed );
    ofAddListener( ofEvents().keyReleased, this, &ofxGuiPresetSelector::keyReleased );
    keysNotActivated = false;
	bKeys = true;
}


void ofxGuiPresetSelector::setPosition( int x, int y, int cellSize ) {
    this->x = x;
    this->y = y;
    this->cellSize = cellSize;
}


void ofxGuiPresetSelector::draw( int x, int y, int cellSize ) {
    setPosition(x, y, cellSize);    
    draw();
}


void ofxGuiPresetSelector::draw( ) {
    
    if( !lastMouseButtonState && ofGetMousePressed() ){
        mousePressed( ofGetMouseX(), ofGetMouseY() );
    }
    lastMouseButtonState = ofGetMousePressed();
    
    ofPushMatrix();
    ofPushStyle();
        ofNoFill();
        ofTranslate(x, y);
        for(size_t i=0; i<keys.size(); ++i){
            size_t k=0;
            for(; k<keys[i].size(); ++k){
                ofDrawRectangle( cellSize*k, cellSize*i, cellSize, cellSize );
                ofDrawBitmapString( ofToString((char)keys[i][k]), cellSize*k+8, cellSize*i+18 );
                if( lastIndices[i]==k ) ofDrawRectangle( cellSize*k+4, cellSize*i+4, cellSize-8, cellSize-8 );
            }
            for(; k<presets[i]; ++k){
                ofDrawRectangle( cellSize*k, cellSize*i, cellSize, cellSize );
                if( lastIndices[i]==k ) ofDrawRectangle( cellSize*k+4, cellSize*i+4, cellSize-8, cellSize-8 );
            }
            
            
            ofDrawRectangle( cellSize*k, cellSize*i, cellSize, cellSize );
            ofDrawCircle ( cellSize*k + cellSize/2, cellSize*i + cellSize/2, cellSize * 0.1f );
            ofDrawRectangle( cellSize*k + cellSize*0.24f, cellSize*i, cellSize*0.09f, cellSize*0.20f );
            ofDrawRectangle( cellSize*k + cellSize*0.18f, cellSize*i, cellSize*0.55f, cellSize*0.25f );
            
            
            k++;

            // A. ofParameterGroup
            #ifdef USE_OF_PARAMETER_GROUP
            ofDrawBitmapString( groups[i].getName(), cellSize*k+8, cellSize*i+18 );
            #endif

            // B. custom DataGrid class
            #ifdef USE_CUSTOM_DATAGRID
            ofDrawBitmapString( grids[i].getName(), cellSize*k+8, cellSize*i+18 );
            #endif

        }
    ofPopStyle();
    ofPopMatrix();
}


void ofxGuiPresetSelector::mousePressed( int x, int y ) {

    x -= this->x;
    y -= this->y;

    int xIndex = x/cellSize;
    int yIndex = y/cellSize;

    xIndex = (x>0) ? xIndex : -1;
    yIndex = (y>0) ? yIndex : -1;

    //-

    // A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
    if( yIndex >=0 &&  yIndex < (int)groups.size() ){
        if(xIndex>=0 && xIndex< presets[yIndex] ){
            //load
            if(bDelayedLoading){
                newIndices[yIndex] = xIndex;
            }else{
                load( xIndex, yIndex);
            }
        }else if( xIndex == presets[yIndex]){
            // save
            save( lastIndices[yIndex], yIndex );
        }
    }
#endif

    // B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
    if( yIndex >=0 &&  yIndex < (int)grids.size() ){
        if(xIndex>=0 && xIndex< presets[yIndex] ){
            //load
            if(bDelayedLoading){
                newIndices[yIndex] = xIndex;
            }else{
                load( xIndex, yIndex);
            }
        }else if( xIndex == presets[yIndex]){
            // save
            save( lastIndices[yIndex], yIndex );
        }
    }
#endif

    //-
}  


void ofxGuiPresetSelector::setDelayedLoading( bool active ) {
    bDelayedLoading = active;
}

//-

void ofxGuiPresetSelector::delayedLoad( int presetIndex, int guiIndex ) {

    // A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
    if(guiIndex>=0 && guiIndex<(int)groups.size()){
        newIndices[guiIndex] = presetIndex;
    }
#endif

    // B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
    if(guiIndex>=0 && guiIndex<(int)grids.size()){
        newIndices[guiIndex] = presetIndex;
    }
#endif
}

void ofxGuiPresetSelector::delayedLoad( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);

    // A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
    if(guiIndex>=0 && guiIndex<(int)groups.size()){
        newIndices[guiIndex] = presetIndex;
    }
#endif

    // B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
    if(guiIndex>=0 && guiIndex<(int)grids.size()){
        newIndices[guiIndex] = presetIndex;
    }
#endif

}

void ofxGuiPresetSelector::delayedUpdate() {

    // A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
    for(size_t i=0; i<groups.size(); ++i){
        if(newIndices[i]!=lastIndices[i]){
            load( newIndices[i], i);
        }
    }
#endif

    // B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
    for(size_t i=0; i<grids.size(); ++i){
        if(newIndices[i]!=lastIndices[i]){
            load( newIndices[i], i);
        }
    }
#endif

}

//-

void ofxGuiPresetSelector::toggleKeysControl( bool active ) {
	bKeys = active;
}
