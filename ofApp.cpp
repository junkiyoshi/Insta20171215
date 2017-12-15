#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->photo.loadImage("photo2.png");

	for (int i = 0; i < 2048; i++) {
		this->particles.push_back(shared_ptr<Particle>(new Particle()));
	}

	this->fbo.allocate(720, 720);

}

//--------------------------------------------------------------
void ofApp::update() {
	ofPixels pixels = this->photo.getPixelsRef();
	ofColor pixel_color;

	for (int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->update();
	}

	this->fbo.begin();
	ofClear(0);

	for (int i = 0; i < this->particles.size(); i++) {
		pixel_color = pixels.getColor(this->particles[i]->get_location().x, this->particles[i]->get_location().y);
		this->particles[i]->set_color(pixel_color);
		if (pixel_color != ofColor(0, 0, 0, 0)) {
			this->particles[i]->draw(this->particles);

		}
	}
	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->fbo.draw(0, 0);
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}