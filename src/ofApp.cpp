#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// Resize and initialize left and right history buffers...
	leftHistory.resize(1, left);
	//rightHistory.resize(MY_BUFFERHISTORY, right);

	ofSetVerticalSync(true);
	ofSetFullscreen(true);
	ofEnableDepthTest();
	ofBackground(0); // Black Background 
	cigarette.set(30, 700);

	sound_stream.printDeviceList();

	left.assign(buffersize, 0.0);
	right.assign(buffersize, 0.0);

	sound_stream.setup(this, 0, 1, 48000, buffersize, 4);
    
	sphere.setRadius(100);
	big_sphere.setRadius(250);
	texture.loadImage(ofToDataPath("world3.jpg"));
	big_sphere.mapTexCoords(0, 0, texture.getWidth(), texture.getHeight());

	earth.loadImage(ofToDataPath("mars.jpg"));
	sphere.mapTexCoords(0, 0, earth.getWidth(), earth.getHeight());

	moon.loadImage(ofToDataPath("mars.jpg"));
	sphere.mapTexCoords(0, 0, moon.getWidth(), moon.getHeight());

	cigar.loadImage(ofToDataPath("cigar.jpg"));
	cigarette.mapTexCoords(0, 0, cigar.getWidth(), cigar.getHeight());








}

void ofApp::audioIn(float * input, int bufferSize, int nChannels) {

	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++) {
		left[i] = input[i];
		curVol += left[i] * left[i];
		
		numCounted += 1;
	}

	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	cout << " " << curVol<< endl;
	// this is how we get the root of rms :) 
	curVol = sqrt(curVol);

	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;

	
    bufferCounter++;
	

}


//--------------------------------------------------------------
void ofApp::update(){

	leftHistory.push_back(left);
//	rightHistory.push_back(right);
	// Remove oldest buffers
	leftHistory.erase(leftHistory.begin(), leftHistory.begin() + 1);
	//rightHistory.erase(rightHistory.begin(), rightHistory.begin() + 1);

	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);

	cylinder_rotation_angle_Y += scaledVol*0.7;
	cylinder_rotation_angle_Z += scaledVol*0.7;

	signal_rot_x += scaledVol * 0.5;
	signal_rot_y += scaledVol * 0.5;
//	signal_rot_z += scaledVol * 3;


	ball_rotation_angle += scaledVol*0.9;
	



}

//--------------------------------------------------------------
void ofApp::draw(){
	ofColor cylinder_color;
	cylinder_color.r = 0;
	cylinder_color.g = 255;
	cylinder_color.b = 0;

	ofColor caps;
	caps.r = 255;
	caps.g = 120;
	caps.b = 200;

	ofPushMatrix();
		ofTranslate(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.5);

		ofPushMatrix();
			ofRotateY(cylinder_rotation_angle_Y);
			ofRotateZ(cylinder_rotation_angle_Z);
			
			ofPushStyle();

			// ofSetColor(255, 0, 0);

			    texture.getTextureReference().bind();
				big_sphere.draw();
				texture.unbind();

			ofPopStyle();

			ofPushMatrix();
				ofRotateY(ball_rotation_angle);
				ofTranslate(400, 0, 0);
				ofRotateZ(ball_rotation_angle);

				ofPushStyle();

					//ofSetColor(0, 0, 256);
				    earth.getTextureReference().bind();
					sphere.draw();
					earth.unbind();

				ofPopStyle();
			ofPopMatrix();
			
		

		

		ofPushStyle();
		ofPushMatrix();
			
			ofRotateY(signal_rot_y);
			ofTranslate(0, -650, 0);
 			ofSetLineWidth(7);

			ofSetColor(200,250,200);
			ofNoFill();
			
				ofBeginShape();
				
			
			// Make a vertex for each sample value
				
				for (unsigned int i = 0; i < buffersize; i++) {
					ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0); 
					
				}
			// End line. False == Don't connect first and last points.
				ofEndShape(false);


				
				
		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(0, -650, -20);
		ofSetLineWidth(5);

		ofSetColor(255, 0, 0);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(0, -650, 20);
		ofSetLineWidth(5);

		ofSetColor(255, 255, 0);

		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {

			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();
		

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(20, -650, 0);
		ofSetLineWidth(5);

		ofSetColor(0, 0, 255);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(-20, -650, 0);
		ofSetLineWidth(5);

		ofSetColor(0, 255, 0);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(20/sqrt(2), -650, 20/sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(200, 150, 50);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(-20/sqrt(2), -650, -20/sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(150, 150, 150);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();


		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(+20 / sqrt(2), -650, -20 / sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(100, 200, 150);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(-20 / sqrt(2), -650, +20 / sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(0, 200, 200);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPopMatrix();

		//
		//
		//
		//
		//
		//
		//


		
		moon.loadImage(ofToDataPath("moon.jpg"));
		sphere.mapTexCoords(0, 0, moon.getWidth(), moon.getHeight());




		ofPushMatrix();
		ofRotateY(cylinder_rotation_angle_Y+120);
		ofRotateZ(cylinder_rotation_angle_Z+60);
		ofPushStyle();
		cigarette.setResolution(20, 13, 4);

		/*cigarette.setCylinderColor(cylinder_color);
		cigarette.setBottomCapColor(caps);
		cigarette.setTopCapColor(caps);*/
		cigar.getTextureReference().bind();
		cigarette.draw();
		cigar.unbind();
		ofPopStyle();

		ofPushMatrix();
		ofRotateY(ball_rotation_angle);
		ofTranslate(400, 0, 0);
		ofRotateZ(ball_rotation_angle);

		ofPushStyle();

		//ofSetColor(100, 100, 100);
		moon.getTextureReference().bind();
		sphere.draw();
		moon.unbind();

		ofPopStyle();
		ofPopMatrix();



		float waveform_amp = 400;
		float waveform_width = 1200;

		ofPushStyle();
		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(0, -650, 0);
		ofSetLineWidth(7);

		ofSetColor(200, 250, 200);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(0, -650, -20);
		ofSetLineWidth(5);

		ofSetColor(255, 0, 0);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(0, -650, 20);
		ofSetLineWidth(5);

		ofSetColor(255, 255, 0);

		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {

			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();


		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(20, -650, 0);
		ofSetLineWidth(5);

		ofSetColor(0, 0, 255);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(-20, -650, 0);
		ofSetLineWidth(5);

		ofSetColor(0, 255, 0);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(20 / sqrt(2), -650, 20 / sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(200, 150, 50);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(-20 / sqrt(2), -650, -20 / sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(150, 150, 150);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();


		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(+20 / sqrt(2), -650, -20 / sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(100, 200, 150);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPushStyle();

		ofPushMatrix();

		ofRotateY(signal_rot_y);
		ofTranslate(-20 / sqrt(2), -650, +20 / sqrt(2));
		ofSetLineWidth(5);

		ofSetColor(0, 200, 200);
		ofNoFill();

		ofBeginShape();


		// Make a vertex for each sample value

		for (unsigned int i = 0; i < buffersize; i++) {
			ofVertex(waveform_amp * leftHistory[0][i], i*waveform_width / (float)buffersize, 0);

		}
		// End line. False == Don't connect first and last points.
		ofEndShape(false);




		ofPopMatrix();
		ofPopStyle();

		ofPopMatrix();

		
	ofPopMatrix();

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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