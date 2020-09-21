#pragma once

#include "ofMain.h"
#include "dustParticles.h"
#include "fireFlies.h"
#include "oneLargeMoon.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void nextWord(string word);
        void removeMoon();
        void setGradient(int x, int y, float w, float h, ofColor c1, ofColor c2, int axis);
        void updateMessage();
        string retrieveAllLines(int rand, vector <string> Tlines, string incoming);
        bool printMessage();
    
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
    
    vector <dustParticle> arrayDustParticles;
    vector <fireFly> arrayFireFlies; // ArrayList poop; // Star Particles
    oneLargeMoon bigMoon;
    
    //Twitter twitter;
    string searchString = "#web3d2017";
   // List<Status> tweets;
    //status status;

    
    // tweets
    bool newTweet = false;
    // particles
    bool isOneDead = false;
    bool drawAsPoints = false;
    bool runAway = false;
    bool goFree = false; // This is the variable saying if the particles should be added
    
    bool changeMoon = false;

    // words
    bool waitType = false;

    // tweet
    int tweetCounter = 0;
    int tweetPacket = 12;
    int currentTweet;

    //// Moon sizes
    int fullMoonSize = 620;
    const int moonAdjust = int(ofMap(fullMoonSize, 150, 1500, 250, 2500));
    const int moonShift = 0;
    int leftMoonSize = 0;
    int heightPos;
    
    float maskSize = fullMoonSize/2;
    float moonRotation = 0;
   
    // Word particle variables
    int pixelSteps = 1; // Amount of pixels to skip
    int wordIndex = 0;
    int messageWidth = 580;
    int messageHeight = 200;
    int messagePositionX;
    int messagePositionY;
    int messageSize = 22;
    float sizepercent = 0;

    ///// Word timers
    int tweetCheckEndTimer = 11000;
    int tweetCheckTimer;
    int cycleEndTime = 11000; // This IS THE MAIN end TIME
    int cycleTimer; // This is the main timer
    int wordEndTime = 31000; // This IS THE MAIN end TIME
    int longTimer;
    int stringCount = 0;
    int minuteTimer = 0;
    int removeMoonCounter = 0;
    float longEndTime = 65000;
    
    
    // Tweets
    string theTweets[30];
    string thisTwit;
    
    // Messages
    string message;
    string defaultMessage[6];
    
    ofColor bgColor = ofColor(0, 20, 40, 40);
    ofColor newColor;
    ofColor QColor[7];
    /// BG
    ofColor b1, b2, c1, c2;

    ofTrueTypeFont font;
    
    ofFbo BG;
    ofFbo pg;
    const int Y_AXIS = 1;

    ofImage gradBackground;
};
