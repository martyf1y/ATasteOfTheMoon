//
//  oneLargeMoon.h
//  ATasteOfTheMoon
//
//  Created by Matt Martin on 6/07/17.
//
//

#pragma once
#include "ofMain.h"

//bool drawAsPoints;

class oneLargeMoon {
    public:
    oneLargeMoon();
    void moonSetup(int appfullMoonSize, const int appMoonAdjust);
    void updateMoon(bool appChangeMoon, int appfullMoonSize);
    float drawMoon(bool appChangeMoon, int appfullMoonSize, float appMoonRotation, int appheightPos, int appMaskSize);
    void mask(ofFbo target, ofFbo mask);
    ofImage moon, rightMoon, leftMoon, cropLeftMoon, moonShade, rightMoonShade;

    //// Moon masking
    ofFbo moon_Masking, theMoon;
    
    int localMoonAdjust;
        
    bool stopRotation = false;


};
