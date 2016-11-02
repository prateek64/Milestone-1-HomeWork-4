#pragma once

#include "ofMain.h"

 

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void audioIn(float * input, int bufferSize, int nChannels);

    private:

		ofCylinderPrimitive cigarette;
		ofSpherePrimitive sphere,big_sphere;
		ofImage texture,cigar,earth,moon;
		ofTexture image_texture;


		float cylinder_rotation_angle_Y=0;
		float cylinder_rotation_angle_Z=0;
		float ball_rotation_angle = 0;

		float signal_rot_x = 0;
		float signal_rot_y = 0;
		float signal_rot_z = 90;
		float waveform_amp = 400;
		float waveform_width = 1200;

		ofSoundPlayer sound_player;
		ofSoundStream sound_stream;

		vector <float> left;
		vector <float> right;

		int buffersize = 512;
		int bufferCounter = 0;
		int buffer_history = 50;
		float smoothedVol=0;
		float scaledVol=0;

		vector< vector<float> > leftHistory;
		// vector< vector<float> > rightHistory;

	
};
