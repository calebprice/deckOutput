#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	soundPlayer.load("Under The Sun-001-Mark Pritchard-.mp3");
	//soundPlayer.setMultiPlay(true);
	trackPos = soundPlayer.getPosition();
	soundVol = soundPlayer.getVolume();
	trackSpeed = soundPlayer.getSpeed();

	myfont.loadFont("arial.ttf", 18); //requires this to be in bin/data/

	receive.setup(PORT);

	cout << "deckOutput app" << endl;
}

//--------------------------------------------------------------
void ofApp::update(){

	if (soundPlayer.isPlaying())
	{
		trackPos = soundPlayer.getPosition();
	}

	while (receive.hasWaitingMessages()) {
		ofxOscMessage m;
		receive.getNextMessage(&m);

		if (m.getAddress() == "/wek/outputs") {
			std::cout << "number of arguments: " << m.getNumArgs() << endl;

			string msgString;
			msgString = m.getAddress();
			msgString += ":";
			for (size_t i = 0; i < m.getNumArgs(); i++) {

				// get the argument type
				msgString += " ";
				msgString += m.getArgTypeName(i);
				msgString += ":";

				// display the argument - make sure we get the right type
				if (m.getArgType(i) == OFXOSC_TYPE_INT32) {
					msgString += ofToString(m.getArgAsInt32(i));
				}
				else if (m.getArgType(i) == OFXOSC_TYPE_FLOAT) {
					msgString += ofToString(m.getArgAsFloat(i));
				}
				else if (m.getArgType(i) == OFXOSC_TYPE_STRING) {
					msgString += m.getArgAsString(i);
				}
				else {
					msgString += "argument type: " + m.getArgTypeName(i);
				}
			}
			cout << "message: " << msgString << endl;

			// test for play forward gesture
			if (m.getArgAsFloat(0) < threshold) {
				soundPlayer.play();
				soundPlayer.setPosition(trackPos);
				trackSpeed = abs(trackSpeed);
				soundPlayer.setSpeed(trackSpeed);
			}
			// test for play bakwards gesture
			else if (m.getArgAsFloat(1) < threshold) {
				soundPlayer.play();
				soundPlayer.setPosition(trackPos);
				trackSpeed = -abs(trackSpeed);
				soundPlayer.setSpeed(trackSpeed);
			}
			// est for stop gesture
			else if (m.getArgAsFloat(2) < threshold) {
				soundPlayer.stop();
			}

			// test for speed increase gesture
			if (m.getArgAsFloat(3) < threshold) {
				trackSpeed = trackSpeed * 1.2;
				soundPlayer.setSpeed(trackSpeed);
			}
			// test for speed decrease gesture
			else if (m.getArgAsFloat(4) < threshold) {
				trackSpeed = trackSpeed * 0.8;
				soundPlayer.setSpeed(trackSpeed);
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	float textPos = 100;
	float textLeft = 30;
	char textString[255];

	sprintf(textString, "track position: %.4f", trackPos);
	myfont.drawString(textString, textLeft, textPos);

	textPos += 50;
	sprintf(textString, "track speed: %.1f", trackSpeed);
	myfont.drawString(textString, textLeft, textPos);

	textPos += 50;
	sprintf(textString, "volume: %.1f", soundVol);
	myfont.drawString(textString, textLeft, textPos);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// play
	if (key == '1') { 
		soundPlayer.play();
		soundPlayer.setPosition(trackPos);
	}

	// stop
	else if (key == '2')
	{
		//trackPos = soundPlayer.getPosition();
		soundPlayer.stop();
	}

	// reduce volume by 1dB
	else if (key == '3')
	{
		soundVol = soundVol * minus_1dB;
		soundPlayer.setVolume(soundVol);
	}

	// increase volume by 1dB
	else if (key == '4')
	{
		soundVol = soundVol * plus_1dB;
		soundPlayer.setVolume(soundVol);
	}

	// decrease speed by 20%
	else if (key == 'z')
	{
		trackSpeed = trackSpeed * 0.8;
		soundPlayer.setSpeed(trackSpeed);
	}

	// increase speed by 20%
	else if (key == 'x')
	{
		trackSpeed = trackSpeed * 1.2;
		soundPlayer.setSpeed(trackSpeed);
	}

	// reverse play direction
	else if (key == 'q')
	{
		trackSpeed = trackSpeed * (-1.0);
		soundPlayer.setSpeed(trackSpeed);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
