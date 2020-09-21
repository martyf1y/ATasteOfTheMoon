//
//  dustParticles.h
//  particlesForOF
//
//  Created by Matt Martin on 2/07/17.
//
//
#pragma once
#include "ofMain.h"

//bool drawAsPoints;

class dustParticle {
    
public:
    dustParticle();
    
    void particleSetup(ofColor appNewColor, int appMoonWidth);
    
    bool move(int appMoonShift, bool appIsOneDead);
    void draw(int appDrawAsPoints);
    void updateParticles(int appMaskSize, int appFullMoonSize, int appMoonAdjust, bool appChangeMoon);

    ofPoint generateRandomPos(int x, int y, float mag);
    
    bool isKilled;
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    ofVec2f target;
    
    float closeEnoughTarget;
    float maxSpeed;
    float maxForce;
    float particleSize;
    
    
    ofColor startColor;
    ofColor targetColor;
    float colorWeight;
    float colorBlendRate;
    
    // This stuff has been moved to here because it only needs to be set once
    int yRadius;
    float yRadiusSquared;
    float ySquared;
};
