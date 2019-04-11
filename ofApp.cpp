#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->locations.size() - 1; i >= 0; i--) {

		this->locations[i] += this->directions[i];
		if (glm::distance(this->bases[i], this->locations[i]) > 100) {

			this->locations.erase(this->locations.begin() + i);
			this->bases.erase(this->bases.begin() + i);
			this->directions.erase(this->directions.begin() + i);
		}
	}

	for (int x = -240; x <= 240; x += 240) {

		for (int y = -240; y <= 240; y += 240) {

			if (ofRandom(100) < 50) {

				auto direction = glm::vec2(ofRandom(-1, 1), ofRandom(-1, 1));
				direction = glm::normalize(direction) * ofRandom(1, 3);

				this->locations.push_back(glm::vec2(x, y));
				this->bases.push_back(glm::vec2(x, y));
				this->directions.push_back(direction);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (auto& location : this->locations) {

		ofSetColor(39);
		ofDrawCircle(location, 3);
		for (auto& other : this->locations) {

			if (location == other) { continue; }
			float distance = glm::distance(location, other);
			if (distance < 30) {
				
				ofSetColor(39, ofMap(distance, 0, 30, 255, 64));
				ofDrawLine(location, other);
			}
		}

	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}