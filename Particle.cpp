#include "Particle.h"

Particle::Particle() {
	this->location = ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	this->velocity = ofVec2f(ofRandom(-3, 3), ofRandom(-3, 3));
	this->acceleration = ofVec2f();
}

void Particle::apply_force(ofVec2f force) {
	this->acceleration += force;
}

void Particle::update() {
	this->acceleration += this->velocity;
	this->location += this->acceleration;
	this->acceleration *= 0;

	if (this->location.x < 0) {
		this->location.x = 0;
		this->velocity.x *= -1;
	}
	else if (this->location.x > ofGetWidth()) {
		this->location.x = ofGetWidth();
		this->velocity.x *= -1;
	}

	if (this->location.y < 0) {
		this->location.y = 0;
		this->velocity.y *= -1;
	}
	else if (this->location.y > ofGetHeight()) {
		this->location.y = ofGetHeight();
		this->velocity.y *= -1;
	}
}

void Particle::draw(vector<shared_ptr<Particle>> particles) {
	
	if (this->body_color != ofColor(0, 0, 0, 0)) {
		ofSetColor(this->body_color, 128);

		float distance;
		vector<ofVec2f> near_point;
		for (int i = 0; i < particles.size(); i++) {
			distance = this->location.squareDistance(particles[i]->get_location());
			if (distance > 0 && distance < 1000) {
				if (particles[i]->get_body_color() != ofColor(0, 0, 0)) {
					near_point.push_back(particles[i]->get_location());
				}
			}
		}

		if (near_point.size() < 2) {
			return;
		}
		ofBeginShape();
		for (int i = 0; i < near_point.size(); i++) {
			ofVertex(near_point[i].x, near_point[i].y);
		}
		ofEndShape(true);
	}
}

void Particle::set_color(ofColor body_color) {
	this->body_color = body_color;
}

ofVec2f Particle::get_location() {
	return this->location;
}

ofColor Particle::get_body_color() {
	return this->body_color;
}