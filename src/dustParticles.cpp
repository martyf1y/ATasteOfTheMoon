//
//  dustParticles.cpp
//  particlesForOF
//
//  Created by Matt Martin on 2/07/17.
//
//

#include "dustParticles.h"

//------------------------------------------------------------------
dustParticle::dustParticle(){
    
}
void dustParticle::particleSetup(ofColor appNewColor, int appMoonWidth){
    pos.set(0, 0);
    vel.set(0, 0);
    target.set(0, 0);
    acc.set(0, 0);
    
    closeEnoughTarget = 30;
    maxSpeed = 4.0;
    maxForce = 0.1;
    particleSize = 5;
    isKilled = false;
    
    startColor = ofColor(appNewColor);
    targetColor = ofColor(0);
    colorWeight = 0;
    colorBlendRate = 0.025;
    
    yRadius = int(ofMap(appMoonWidth, 2.5, 2500, 2.2, 2250))/2;
    yRadiusSquared = yRadius * yRadius;
}

bool dustParticle::move(int appMoonShift, bool appIsOneDead) {
    
    // Check if particle is close enough to its target to slow down
    float proximityMult = 1.0;
    float easing = 0.05;
    float distance = ofDist(pos.x, pos.y, target.x, target.y);
    
    maxSpeed = distance*easing;
    
    // Add force towards target
    ofVec2f towardsTarget(target.x, target.y);
    towardsTarget -= pos;
    towardsTarget.normalize();
    towardsTarget *= (maxSpeed*proximityMult);
    
    ofVec2f steer(towardsTarget.x, towardsTarget.y);
    steer -= vel;
    steer.normalize();
    steer *= maxForce;
    acc += steer;
    
    // Move particle
    vel += acc;
    pos += vel;
    acc *= 0;
    
    if (distance <= 8 || pos.x >= ofGetWidth()+appMoonShift || pos.x <= 0-appMoonShift || pos.y <= 0-300 || pos.y >= ofGetHeight()) {
        if (! isKilled) {
            // Begin blending its color to black
            startColor = startColor.lerp(targetColor, colorWeight);
            targetColor = ofColor(0);
            colorWeight = 0;
            
            isKilled = true;
            appIsOneDead = true;
        }
    }
    return appIsOneDead;
}

void dustParticle::draw(int appDrawAsPoints) {
    // Draw particle
    
    
    ofColor currentColor = startColor.lerp(targetColor, colorWeight);
    if (appDrawAsPoints) {
    ofSetColor(currentColor);
    ofDrawCircle(pos.x, pos.y, 1);
    } else {
    ofSetColor(currentColor);
    ofDrawEllipse(pos.x, pos.y, particleSize, particleSize);
    }
    
    // Blend towards its target color
    if (colorWeight < 1.0) {
        colorWeight = MIN(colorWeight+colorBlendRate, 1.0);
    }
}

void dustParticle::updateParticles(int appMaskSize, int appFullMoonSize, int appMoonAdjust, bool appChangeMoon) {
    float messageRadius;

    if (!appChangeMoon) {
        messageRadius = int(ofMap(appMaskSize, 0, appFullMoonSize/2, 0, yRadius*2));
        messageRadius = int(messageRadius/2);
    } else {
        messageRadius = int(ofMap(appMaskSize, 0, appMoonAdjust, 0, yRadius*2));
        messageRadius = int(messageRadius/2);
    }
    // I put the constrain in to stop going past the middle point
    float xRadiusSquared = messageRadius * messageRadius;
    
    float xValue = sqrt((1 - ySquared/yRadiusSquared)*xRadiusSquared);
    if (appChangeMoon) {
        xValue *= -1;
    }
    target.x = xValue;
    target.x += ofGetWidth()/2;
}
