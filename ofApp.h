#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 12000

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

		const float minus_1dB = 0.891251;
		const float plus_1dB = 1.122018;
		const float threshold = 500.0;

		ofSoundPlayer soundPlayer;
		float trackPos;
		float soundVol;
		float trackSpeed;

		ofTrueTypeFont myfont;

		ofxOscReceiver receive;

};
