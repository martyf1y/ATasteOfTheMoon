//
//  fireFlies.cpp
//  ATasteOfTheMoon
//
//  Created by Matt Martin on 6/07/17.
//
//
#include "dustParticles.h"

#include "fireFlies.h"

//------------------------------------------------------------------

fireFly::fireFly(int rX)
    {
        x = ofRandom(0, ofGetWidth());
        y = ofRandom(0, ofGetHeight()-100);
        r = rX;
        fx = ofRandom(-0.9, 0.9);
        fy = ofRandom(-0.9, 0.9);
    }
    
void fireFly::display()
    {
        
        //color t = color(0,0,0);
        int ik = (int)ofRandom(0, 60*r);
        if (ik==1*r) t= ofColor(255, 201, 201, 255);
        if (ik==2*r) t= ofColor(192, 209, 255, 255);
        if (ik==3*r) t= ofColor(237, 238, 255, 255);
        if (ik==4*r) t= ofColor(255, 249, 249, 255);
        if (ik==5*r) t= ofColor(255, 241, 223, 255);
        if (ik==6*r) t= ofColor(255, 215, 224, 255);
        if (ik==7*r) t= ofColor(255, 221, 197, 255);
        if (ik==8*r) t= ofColor(240, 230, 140, 255);
        if (ik==8*r) t= ofColor(255, 255, 102, 255);
        
        //---------------blur/glow ----------
        float h = 3;
        for (float r1 = r*4; r1 > 0; --r1) {
            ofSetColor(t, h);
            //noStroke();
            ofDrawEllipse(x, y, r1, r1);
            h=(h+2);
        }
        //noStroke();
        
        ofSetColor(t);
        ofDrawEllipse(x, y, r, r);
    }
    
    /*void update() {
     if (r>3) {
     x = x + j*fx;
     y = y + i*fy;
     }
     if (y > height-200-r) i=-1;
     if (y < 0+r) i=1;
     if (x > width-r) j=-1;
     if (x < 0+r) j=1;
     }*/
