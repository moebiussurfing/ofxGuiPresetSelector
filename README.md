ofxGuiPresetSelector
==============

--

changes by this moebiussurfing fork:

Changes log:
+ switched from ofxGui/ofxGuiPanel to ofxGuiExtended.
+ switched preset mangement from ofxGuiExtended to more tiny ofParametersGroup.
+ can define choice to manager ofParametersGroup or a custom class data. (vectors, structs, nested json utils..).

Required addons: ofxJsonUtils, ofxGuiExtended.

Added a custom class: "DataGrid.h / .cpp". 
It's a two dimentions grid matrix step sequencer like. 
It has the required setName / getName methods. 
Contains parser and loader to JSON methods.

--

An addon for openFrameworks that let you easily save and load ofxPanel settings but pressing keyboard keys. It stores everything in different .xml files. Remember to use the .setName() method on ofxPanel befor adding it to the ofxGuiPresetSelector.

Screenshot of the included example:
![example](example.png?raw=true "example")

Nicola Pisanti, MIT License 2016.
