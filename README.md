ofxGuiPresetSelector
==============

--

changes by this moebiussurfing fork:

Changes log:
+ switched from ofxGui/ofxGuiPanel to ofxGuiExtended.
+ switched preset management from ofxGuiExtended to more tiny ofParametersGroup.
+ can define choice to manager presets of 'ofParametersGroup' or a 'custom class data'. (vectors, structs, nested json utils..).

Required addons: ofxJsonUtils, ofxGuiExtended.

Added a custom class: "DataGrid.h / .cpp". 
It's a two dimentions int array grid matrix step sequencer like:
''int grid [NUM_SEQ_NOTES][NUM_SEQ_BEATS];''
It has the required setName / getName methods. 
Contains parser and loader to JSON methods.

--

An addon for openFrameworks that let you easily save and load ofxPanel settings but pressing keyboard keys. It stores everything in different .xml files. Remember to use the .setName() method on ofxPanel befor adding it to the ofxGuiPresetSelector.

Screenshot of the included example:
![example](example.png?raw=true "example")

Nicola Pisanti, MIT License 2016.
