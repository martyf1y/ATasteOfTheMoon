//
//  fireFlies.h
//  ATasteOfTheMoon
//
//  Created by Matt Martin on 6/07/17.
//
//

#pragma once
#include "ofMain.h"

class fireFly {
    
public:
    
    fireFly(int rX);
    
    void move();
    void display();
    
    float x, y, r, fx, fy;
    ofColor c;
    //  int i=1, j=1;
    ofColor t = ofColor(0, 0, 0, 255);

    
};






