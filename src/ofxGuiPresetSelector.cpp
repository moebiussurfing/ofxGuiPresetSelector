
// ofxGuiPresetSelector.h
// Nicola Pisanti, MIT License, 2016
//
// changes by moebiussurfing

#include "ofxGuiPresetSelector.h"

ofxGuiPresetSelector::~ofxGuiPresetSelector()
{
    save_ControlSettings();

    ofRemoveListener(params.parameterChangedE(), this, &ofxGuiPresetSelector::Changed_Gui);
}

ofxGuiPresetSelector::ofxGuiPresetSelector()
{
    // ofSetLogLevel("ofxGuiPresetSelector")
    ofSetLogLevel(OF_LOG_VERBOSE);

    modeKey = OF_KEY_CONTROL;
    bKeys = false;
    keysNotActivated = true;
    bKeySave = false;

    //-

    // A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
    groups.reserve(32);
#endif

    // B. custom DataGrid class
#ifdef USE_CUSTOM_DATAGRID
    grids.reserve(32);
#endif

    //-

    lastIndices.reserve(32);
    keys.reserve(32);

    lastMouseButtonState = false;
    bDelayedLoading = false;

    //-

    DONE_load.set("DONE LOAD", false);
    DONE_save.set("DONE SAVE", false);

    myTTF = "assets/fonts/PragmataProR_0822.ttf";
    sizeTTF = 10;
    myFont.load(myTTF, sizeTTF, true, true);

    //-

    // PRESETS OF DEVICE

    PRESET_selected.set("PRESETS", 1, 1, num_presets);

    params.setName("PRESETS");
    params.add(PRESET_selected);
    autoLoad.set("AUTO LOAD", false);
    autoSave.set("AUTO SAVE", false);
    cloneRight.set("CLONE >", false);
    params.add(autoLoad);
    params.add(autoSave);
    params.add(cloneRight);

    ofAddListener(params.parameterChangedE(), this, &ofxGuiPresetSelector::Changed_Gui);

    //-
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
        string myName = grids[i]->getName();
        if( myName == name ){
            return i;
        }
        return -1;
    }
}
#endif

string ofxGuiPresetSelector::presetName( string guiName, int presetIndex )
{
    string folder;
//    folder = "/patterns/"; //using subfolder
    folder = "/"; //without subfolder

#ifdef USE_OF_PARAMETER_GROUP
    return (folder + guiName + "_preset_" + ofToString(presetIndex) + ".xml" );
#endif

#ifdef USE_CUSTOM_DATAGRID
    return (folder + guiName + "_preset_" + ofToString(presetIndex) + ".json" );
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

void ofxGuiPresetSelector::add( DataGrid & grid, int numPresets ) {

    // add a gui for preset saving

    grids.push_back(&grid);

    lastIndices.push_back(0);
    newIndices.push_back(0);
    presets.push_back(numPresets);

    //-

    num_presets = numPresets;
    (group->getIntSlider("PRESETS"))->setMax(num_presets);

}

void ofxGuiPresetSelector::add( DataGrid & grid, initializer_list<int> keysList ) {
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

void ofxGuiPresetSelector::save( int presetIndex, int guiIndex )
{
    if(guiIndex>=0 && guiIndex<(int)grids.size())
    {
        ofLogNotice("ofxGuiPresetSelector") << "DONE_save";
        DONE_save = true;
        // will make in SEQ: get sequencer state before saving in preset manager
        //GRID_getFrom_Sequencer();

        std::string n = presetName( grids[guiIndex]->getName(), presetIndex);

        ofLogNotice("ofxGuiPresetSelector") << "> save( presetIndex, guiIndex): " << presetIndex <<", "<< guiIndex;
        ofLogNotice("ofxGuiPresetSelector") << "grids[guiIndex]->getName(): " << grids[guiIndex]->getName();
        ofLogNotice("ofxGuiPresetSelector") << "n: " << n;

        grids[guiIndex]->save_JSON(pathKitFolder + "/" + n);
    }
}

void ofxGuiPresetSelector::save( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>=0 && guiIndex<(int)grids.size())
    {
        ofLogNotice("ofxGuiPresetSelector") << "DONE_save";
        DONE_save = true;
        // will make in SEQ: get sequencer state before saving in preset manager
        //GRID_getFrom_Sequencer();

        ofLogNotice("ofxGuiPresetSelector") << "> save( presetIndex, guiName): " << presetIndex <<", "<< guiName;
        ofLogNotice("ofxGuiPresetSelector") << "guiIndex = getGuiIndex(guiName): " << guiIndex;

        string n = presetName( guiName, presetIndex);

        grids[guiIndex]->save_JSON(pathKitFolder + "/" + n);
    }
}

//-

void ofxGuiPresetSelector::load( int presetIndex, int guiIndex ) {
    if(guiIndex>=0 && guiIndex<(int)grids.size())
    {
        ofLogNotice("ofxGuiPresetSelector") << "> load( presetIndex, guiIndex): " << presetIndex <<", "<< guiIndex;

        string str = presetName( grids[guiIndex]->getName(), presetIndex);
        grids[guiIndex]->load_JSON( pathKitFolder + "/" + str );

        lastIndices[guiIndex] = presetIndex;

        // grids[guiIndex]->dump_grid();

        ofLogNotice("ofxGuiPresetSelector") << "DONE_load";

        DONE_load = true;
    }
}

void ofxGuiPresetSelector::load( int presetIndex, string guiName ) {
    int guiIndex = getGuiIndex(guiName);

    if(guiIndex>=0 && guiIndex<(int)grids.size()){

        ofLogNotice("ofxGuiPresetSelector") << "> load( presetIndex, guiName): " << presetIndex <<", "<< guiName;

        string n = presetName( guiName, presetIndex);
        grids[guiIndex]->load_JSON(pathKitFolder + "/" + n);

        lastIndices[guiIndex] = presetIndex;

        ofLogNotice("ofxGuiPresetSelector") << "DONE_load";

        DONE_load = true;
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

int ofxGuiPresetSelector::getPresetIndex( int guiIndex ) const
{
    if(guiIndex>0 && guiIndex<(int)grids.size()){
        return lastIndices[guiIndex];
    }else{
        return -1;
    }
}

int ofxGuiPresetSelector::getPresetIndex( string guiName )const
{
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

void ofxGuiPresetSelector::keyPressed( ofKeyEventArgs& eventArgs )
{
    if( bKeys && ENABLE_shortcuts){
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
//                            newIndices[i] = k;
//                            ofLogNotice("ofxGuiPresetSelector") << "newIndices[i] = k;" <<  k << ", " << i;
//                            PRESET_selected = 1 + k;
                        }
                        else{
//                            load( k, i );
//                            ofLogNotice("ofxGuiPresetSelector") << "load( k, i ):" <<  k << ", " << i;

                            PRESET_selected = 1 + k;
                        }
                    }
                    return;
                }
            }
        }
    }
}


void ofxGuiPresetSelector::keyReleased( ofKeyEventArgs& eventArgs ) {
    if( eventArgs.key == modeKey && ENABLE_shortcuts) bKeySave = false;
}


void ofxGuiPresetSelector::addKeysListeners(){
    ofAddListener( ofEvents().keyPressed, this, &ofxGuiPresetSelector::keyPressed );
    ofAddListener( ofEvents().keyReleased, this, &ofxGuiPresetSelector::keyReleased );
    keysNotActivated = false;
    bKeys = true;
}


void ofxGuiPresetSelector::setPosition_CLICKER( int x, int y, int cellSize ) {
    this->x = x;
    this->y = y;
    this->cellSize = cellSize;
}


void ofxGuiPresetSelector::draw( int x, int y, int cellSize ) {
    setPosition_CLICKER(x, y, cellSize);
    draw();
}


void ofxGuiPresetSelector::draw( ) {

    if (SHOW_ClickPanel) {
        if (!lastMouseButtonState && ofGetMousePressed()) {
            mousePressed(ofGetMouseX(), ofGetMouseY());
        }
        lastMouseButtonState = ofGetMousePressed();

        ofPushMatrix();
        ofPushStyle();
        ofNoFill();
        ofTranslate(x, y);

        for (size_t i = 0; i < keys.size(); ++i) {
            size_t k = 0;
            for (; k < keys[i].size(); ++k) {
                ofDrawRectangle(cellSize * k, cellSize * i, cellSize, cellSize);

                //ofDrawBitmapString( ofToString((char)keys[i][k]), cellSize*k+8, cellSize*i+18 );
                myFont.drawString(ofToString((char) keys[i][k]),
                        cellSize * k + 0.5 * cellSize - 0.25 * sizeTTF,
                        cellSize * i + 0.5 * cellSize + 0.5 * sizeTTF);

                if (lastIndices[i] == k) ofDrawRectangle(cellSize * k + 4, cellSize * i + 4, cellSize - 8, cellSize - 8);
            }
            for (; k < presets[i]; ++k) {
                ofDrawRectangle(cellSize * k, cellSize * i, cellSize, cellSize);
                if (lastIndices[i] == k) ofDrawRectangle(cellSize * k + 4, cellSize * i + 4, cellSize - 8, cellSize - 8);
            }

            // save button
            ofDrawRectangle(cellSize * k, cellSize * i, cellSize, cellSize);
            ofDrawCircle(cellSize * k + cellSize / 2, cellSize * i + cellSize / 2, cellSize * 0.1f);
            ofDrawRectangle(cellSize * k + cellSize * 0.24f, cellSize * i, cellSize * 0.09f, cellSize * 0.20f);
            ofDrawRectangle(cellSize * k + cellSize * 0.18f, cellSize * i, cellSize * 0.55f, cellSize * 0.25f);


            k++;

            //-

            // kit name

//            // A. ofParameterGroup
//            #ifdef USE_OF_PARAMETER_GROUP
//            ofDrawBitmapString( groups[i].getName(), cellSize*k+8, cellSize*i+18 );
//            #endif
//
//            // B. custom DataGrid class
//            #ifdef USE_CUSTOM_DATAGRID
//            ofDrawBitmapString( grids[i]->getName(), cellSize*k+8, cellSize*i+18 );
//            #endif

            //-
        }
        ofPopStyle();
        ofPopMatrix();
    }
}


void ofxGuiPresetSelector::mousePressed( int x, int y ) {

    x -= this->x;
    y -= this->y;

    int xIndex = x/cellSize;
    int yIndex = y/cellSize;

    xIndex = (x>0) ? xIndex : -1;
    yIndex = (y>0) ? yIndex : -1;

    ofLogNotice("ofxGuiPresetSelector") << "> mousePressed - xIndex, yIndex: " << xIndex <<", "<< yIndex;

    //-

    // A. ofParameterGroup
#ifdef USE_OF_PARAMETER_GROUP
    if( yIndex >=0 &&  yIndex < (int)groups.size() )
    {
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

    if( yIndex >=0 &&  yIndex < (int)grids.size() )
    {
        // row buttons, preset selctors
        if(xIndex>=0 && xIndex< presets[yIndex] ){
            //load
            if(bDelayedLoading)
            {
//                newIndices[yIndex] = xIndex;
//                ofLogNotice("ofxGuiPresetSelector") << "newIndices[yIndex] = xIndex:" <<  yIndex << " = " << xIndex;
            }
            else
            {
//                load( xIndex, yIndex);
//                ofLogNotice("ofxGuiPresetSelector") << "load( xIndex, yIndex):" <<  xIndex << ", " << yIndex;

                PRESET_selected = 1 + xIndex;
            }
        }

        // last button (save button)
        else if( xIndex == presets[yIndex])
        {
            // save
            save( lastIndices[yIndex], yIndex );

//            PRESET_selected = 1 + yIndex;
        }
    }

#endif

    //-
}


void ofxGuiPresetSelector::setDelayedLoading( bool active )
{
    bDelayedLoading = active;
}

//-

void ofxGuiPresetSelector::delayedLoad( int presetIndex, int guiIndex )
{

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

void ofxGuiPresetSelector::delayedLoad( int presetIndex, string guiName )
{
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

//--

// PRESET GUI MANAGER

void ofxGuiPresetSelector::Changed_Gui(ofAbstractParameter &e)
{
    string WIDGET = e.getName();

    ofLogNotice("ofxGuiPresetSelector") << "Changed_Gui '" << WIDGET << "': " << e;

    if ( WIDGET == "CLONE >" && (cloneRight) )
    {
        ofLogNotice("ofxGuiPresetSelector") << "CLONE >: " << e;
        doCloneRight(PRESET_selected - 1);
    }

    if ( WIDGET == "PRESETS" && (PRESET_selected != PRESET_selected_PRE) )
    {
        ofLogNotice("ofxGuiPresetSelector") << "PRESETS: " << e;

        //load
        if(bDelayedLoading)
        {
            //byKey
            //newIndices[i] = k;
            //ofLogNotice("ofxGuiPresetSelector") << "newIndices[i] = k;" <<  k << ", " << i;

            //byMousePressed
            //ofLogNotice("ofxGuiPresetSelector") << "newIndices[yIndex] = xIndex:" <<  yIndex << " = " << xIndex;
        }

        else
        {
            //byKey
//            load( k, i );
//            ofLogNotice("ofxGuiPresetSelector") << "load( k, i ):" <<  k << ", " << i;

            //byMousePressed
//            load( xIndex, yIndex);
//            ofLogNotice("ofxGuiPresetSelector") << "load( xIndex, yIndex):" <<  xIndex << ", " << yIndex;

            //-

////            if (autoSave)
////            {
//                DONE_save = true;// get sequencer state before saving in preset manager
//                save( lastIndices[PRESET_selected_PRE], 0 );//save on back from ofxSEQlistener
////            }

            //-

//            if (autoLoad)
//            {

                int xIndex = PRESET_selected - 1;

                PRESET_selected_PRE = PRESET_selected;

                int yIndex = 0;
                //this should handle when using multiple kits together
                // yIndex = ?

                //-

                load( xIndex, yIndex);
                ofLogNotice("ofxGuiPresetSelector") << "load( xIndex, yIndex): " <<  xIndex << ", " << yIndex;

                DONE_load = true;
//            }
        }
    }
}

void ofxGuiPresetSelector::setup_Gui()
{
    gui_w = 200;
    gui_slider_h = 14;
    gui_slider_big_h = 18;
    gui_button_h = 22;

    //-

    confCont = //container
            {
                    {"direction", "vertical"},
                    {"width", gui_w},
                    {"padding", 0},
                    {"margin", 0},
            };

    confItem_toggle = //toggle
            {
                    {"height", gui_slider_h},
            };

    confItem = //sliders
            {
                    {"type", "fullsize"},
                    {"height", gui_slider_h},
            };

    confItem_Big = //big sliders
            {
                    {"type", "fullsize"},
                    {"height", gui_slider_big_h},
            };

    confItem_Fat = //big buttons
            {
                    {"type", "fullsize"},
                    {"height", gui_button_h},
                    {"text-align", "center"},
            };

    //-

    group = gui.addGroup("PATTERNS", confCont);
    group->add<ofxGuiIntSlider>(PRESET_selected, confItem_Big);
//    group->add<ofxGuiToggle>(autoLoad, confItem_toggle);
//    group->add<ofxGuiToggle>(autoSave, confItem_toggle);
    group->add<ofxGuiButton>(cloneRight, confItem_toggle);

    //-

    group->setPosition(600, 550);
}

void ofxGuiPresetSelector::set_GUI_position(int x, int y)
{
    group->setPosition(x, y);
}

void ofxGuiPresetSelector::setVisible_Gui(bool visible)
{
    SHOW_Gui = visible;
    gui.getVisible().set(SHOW_Gui);
}

void ofxGuiPresetSelector::setVisible_ClickPanel(bool visible)
{
    SHOW_ClickPanel = visible;
}

void ofxGuiPresetSelector::load_ControlSettings()
{
    ofXml settings;
    settings.load(pathControl);
    ofDeserialize(settings, params);

    cout << "load_ControlSettings > PRESET_selected: " << PRESET_selected << endl;
}

void ofxGuiPresetSelector::save_ControlSettings() {
    ofXml settings;
    ofSerialize(settings, params);
    settings.save(pathControl);
}

void ofxGuiPresetSelector::set_pathKit_Folder(string folder)
{
    pathKitFolder = folder;
}

void ofxGuiPresetSelector::doCloneRight(int patternNum)
{
    ofLogNotice("ofxGuiPresetSelector") << "doCloneRight: patternNum: " << patternNum;
    for (int i = patternNum+1; i<num_presets; i++)
    {
        save( i, 0 );//only 1 row (gui) / data content
    }
}