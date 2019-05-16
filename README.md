ofxGuiPresetSelector
==============

//--

changes by moebiussurfing:

(+ switched from ofxGui/ofxGuiPanel to ofxGuiExtended)
(+ switched preset mangement from ofxGuiExtended to ofParametersGroup)
 + can define choice to manager ofParametersGroup or a custom class data. (vectors, structs, json utils..)

//--

An addon for openFrameworks that let you easily save and load ofxPanel settings but pressing keyboard keys. It stores everything in different .xml files. Remember to use the .setName() method on ofxPanel befor adding it to the ofxGuiPresetSelector.

Screenshot of the included example:
![example](example.png?raw=true "example")

Nicola Pisanti, MIT License 2016.
