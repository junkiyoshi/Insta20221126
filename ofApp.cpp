#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);
	ofNoFill();

	this->len = 250;
	ofColor color;
	for (int y = -this->len; y <= this->len; y += 5) {

		this->base_location_list.push_back(glm::vec2(this->len, y));
		color.setHsb(ofMap(y, -this->len, this->len, 0, 255), 255, 255);
		this->color_list.push_back(color);

		this->base_location_list.push_back(glm::vec2(-this->len, y));
		color.setHsb(ofMap(y, -this->len, this->len, 255, 0), 255, 255);
		this->color_list.push_back(color);

		this->base_location_list.push_back(glm::vec2(y, this->len));
		color.setHsb(ofMap(y, -this->len, this->len, 0, 255), 255, 255);
		this->color_list.push_back(color);

		this->base_location_list.push_back(glm::vec2(y, -this->len));
		color.setHsb(ofMap(y, -this->len, this->len, 255, 0), 255, 255);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	for (int i = 0; i < this->base_location_list.size(); i++) {

		vector<glm::vec2> log;
		log.push_back(this->base_location_list[i]);
		this->log_list.push_back(log);
	}

	int step = 1;
	for (int i = 0; i < this->log_list.size(); i++) {

		int k = 0;
		while (true) {

			auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.0015, ofGetFrameNum() * 0.004 + k * 0.001)), 0, 1, -720, 720);
			auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));

			if(abs(next.x) < this->len && abs(next.y) < this->len ){

				this->log_list[i].push_back(next);
			}
			else {

				break;
			}

			k++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int i = 0; i < this->log_list.size(); i++) {

		//ofSetColor(this->color_list[i]);
		ofSetColor(ofColor(200));

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}