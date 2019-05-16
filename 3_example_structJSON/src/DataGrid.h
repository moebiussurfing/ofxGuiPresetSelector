//
// Created by moebiussurfing on 5/15/19.
//

#pragma once

#include "ofMain.h"
#include "ofxJsonUtils.h"

#define NUM_SEQ_NOTES 12//max & fixed size
#define NUM_SEQ_BEATS 16//max & fixed size


class DataGrid {

public:
    DataGrid();

    std::string name;
    int	id;

    int grid [NUM_SEQ_NOTES][NUM_SEQ_BEATS];
    //    vector < vector<int> > grid;

    void save_JSON(string path);
    void load_JSON(string path);
    void dump_grid();

    string subTag;

//    void setName(string n);
    virtual std::string getName();

    virtual void setName(const std::string name);
//    virtual void setName(const std::string& name);
//    virtual std::string getName();
};

