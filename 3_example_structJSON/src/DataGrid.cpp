//
// Created by moebiussurfing on 5/15/19.
//

#include "DataGrid.h"

DataGrid::DataGrid()
{
    ofLogNotice("DataGrid") << "CONSTRUCTOR";
    name = "";
    id = 0;
    subTag = "row";//text tag for any row (aka subjson) into json file

    //    grid.resize(32);
}

//------------------------------------------------
void DataGrid::save_JSON(string path)
{
    ofLogNotice("DataGrid") << "save_JSON";

    //    int steps[NUM_SEQ_BEATS];
    //    //    vector<int> steps;
    //    //    steps.resize(NUM_SEQ_BEATS);

    ofJson JSON_row;//for the slow mode parser
    ofJson JSON_grid;

    //-

    // slow mode with tags

    // create one json for each row aka note:
    for (int note = 0;  note < NUM_SEQ_NOTES; note++)
    {
        string name = subTag + ofToString(note);

        // JSON_row = ofxJsonUtils::create( kv( grid[note] ) );
        JSON_row = ofxJsonUtils::create( name, grid[note] );

        ofLogNotice("DataGrid") << " > DUMP: " + name + " " << JSON_row.dump();

        //-

        JSON_grid.push_back(JSON_row);
    }

    //-

    // fast mode without tags
    //    JSON_grid = ofxJsonUtils::create( kv( grid ) );

    //-

    ofSavePrettyJson(path, JSON_grid);
}


//------------------------------------------------
void DataGrid::dump_grid(string path)
{
    ofLogNotice("DataGrid") << "dump_grid";

    for (int note = 0;  note < NUM_SEQ_NOTES; note++) {

        string str;
        for (int s = 0; s < NUM_SEQ_BEATS ; s++)
        {
            str += ofToString( grid[note][s] ) + " ";
        }
        ofLogNotice("DataGrid") << "NOTE: " << note << " BEATS: " + str;
    }
}


//------------------------------------------------
void DataGrid::load_JSON(string path)
{
    ofLogNotice("DataGrid") << "load_JSON";

    //-

    // fast mode do not works. maybe because using array not vectors..

    //    ofJson js = ofxJsonUtils::loadFromFile(path);
    //    ofLogNotice("DataGrid") << "DUMP GRID: " << js.dump();
    //    ofxJsonUtils::load( json, kv( grid[][] ) );

    //-

    ofJson js;
    ofFile file( path );
    if(file.exists())
    {
        file >> js;
        ofLogNotice("DataGrid") << " > DUMP GRID: ";

        int n = 0;
        for (auto &js_Row: js) {
            if (!js_Row.empty()) {
                string js_Tag = subTag + ofToString(n);
                ofLogNotice("DataGrid") << "subJSON:" + js_Tag + ": " << js_Row.dump();

                std::vector<int> steps = js_Row[js_Tag]; //load json array to vector
                int b = 0;
                for (auto i : steps) {
                    grid[n][b] = i;
                    b++;
                }
                n++;
            }
        }
    }
}