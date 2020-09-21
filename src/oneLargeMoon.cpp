//
//  oneLargeMoon.cpp
//  ATasteOfTheMoon
//
//  Created by Matt Martin on 6/07/17.
//
//

#include "oneLargeMoon.h"

//------------------------------------------------------------------
oneLargeMoon::oneLargeMoon(){
}

void oneLargeMoon::moonSetup(int appfullMoonSize, const int appMoonAdjust){
    ofEnableAlphaBlending();
    
    localMoonAdjust = appMoonAdjust;
    moon.load("moonFest.png");
    // imageMode(CENTER); MIGHT NEED THIS
    moon.resize(appfullMoonSize,0);
    moon_Masking.allocate(moon.getWidth(), moon.getHeight());
    // moon_Masking.imageMode(CENTER);
    int moonArcAdjust = int(ofMap(moon.getWidth(), 250, 2500, 225, 2250));
    
    ofFbo rightArc;
    rightArc.allocate(localMoonAdjust, localMoonAdjust);
    rightArc.begin();
    ofClear(0,0,0,0);
    ofBackground(0, 0, 0);
    ofSetColor(255, 255);
    //  rightArc.ellipseMode(CENTER); FIX THIS
    ofDrawEllipse(rightArc.getWidth()/2, rightArc.getHeight()/2, moonArcAdjust, moonArcAdjust);
    // rightArc.filter(BLUR, 4); FIX THIS
    rightArc.end();
    rightArc.readToPixels(rightMoon);
    rightMoon.crop(localMoonAdjust/2, 0, localMoonAdjust/2, localMoonAdjust);
    
    ofFbo leftArc;
    leftArc.allocate(localMoonAdjust, localMoonAdjust);
    leftArc.begin();
    ofBackground(0, 0, 0);
    ofSetColor(255, 255);
    //     leftArc.ellipseMode(CENTER); FIX THIS
    ofDrawEllipse(leftArc.getWidth()/2, leftArc.getHeight()/2, moonArcAdjust, moonArcAdjust);
    //   leftArc.filter(BLUR, 4); FIX THIS
    leftArc.end();
    leftArc.readToPixels(leftMoon);
    leftMoon.crop(0, 0, localMoonAdjust, localMoonAdjust);
    
    ofFbo shade;
    int moonShadeAdjust = int(ofMap(appfullMoonSize, 150, 1500, 140, 1400));
    shade.allocate(appfullMoonSize, appfullMoonSize);
    shade.begin();
    ofBackground(0, 0, 0);
    ofSetColor(0, 255);
    //    shade.ellipseMode(CENTER); FIX THIS
    ofDrawEllipse(shade.getWidth()/2, shade.getHeight()/2, moonShadeAdjust, moonShadeAdjust);
    // shade.filter(BLUR, 4); FIX THIS
    shade.end();
    shade.readToPixels(moonShade);
    moonShade.crop(0, 0, appfullMoonSize, appfullMoonSize);
    
    ofFbo theMoon;
    theMoon.allocate(moon.getWidth(), moon.getHeight());
    // theMoon.imageMode(CENTER); FIX THIS
    //theMoon.ellipseMode(CENTER);
    theMoon.begin();
    ofClear(0, 0, 0, 0);
    ofTranslate(moon.getWidth()/2, moon.getHeight()/2);
    // theMoon.rotate(radians(millis())/100);
    // shader.begin();
    // shader.setUniformTexture("maskTex", moon_Masking.getTexture(), 1 );
    
    moon.draw(0, 0);
    
    theMoon.end();
}

void oneLargeMoon::updateMoon(bool appChangeMoon, int appfullMoonSize) {
    // DRAW FLASHLIGHT MASK
    moon_Masking.begin();
    ofBackground(0);
    // moon_Masking.imageMode(CENTER); FIX THIS
    if (appChangeMoon == true) {
        leftMoon.draw(moon.getWidth()/2, moon.getHeight()/2, appfullMoonSize, localMoonAdjust);
    }
    
    rightMoon.draw(moon.getWidth()/2+localMoonAdjust/4, moon.getHeight()/2, localMoonAdjust/2, localMoonAdjust);
    
    moon_Masking.end();
    // APPLY FLASHLIGHT MASK TO FRAME
    // mask(theMoon, moon_Masking);
    
    
    mask(theMoon, moon_Masking);
}

float oneLargeMoon::drawMoon(bool appChangeMoon, int appfullMoonSize, float appMoonRotation, int appheightPos, int appMaskSize) {
    // DRAW NEW FRAME
    
    if(ofGetSeconds() == 1 && !stopRotation){
        stopRotation = true;
        // println("YES " + second() + " : " + moonRotation);
        appMoonRotation += 0.2;
        if(appMoonRotation >= 360){
            appMoonRotation = 0;
        }
        theMoon.allocate(moon.getWidth(), moon.getHeight());
        // theMoon.imageMode(CENTER); FIX THIS
        theMoon.begin();
        ofBackground(0, 0, 0);
        ofTranslate(moon.getWidth()/2, moon.getHeight()/2);
        ofRotate(appMoonRotation);
        
        moon.draw(0, 0);
        theMoon.end();
        
        updateMoon(appChangeMoon, appfullMoonSize);
        string info = {ofToString(appMaskSize) + "\n" + ofToString(appChangeMoon)+"\n"+ofToString(appMoonRotation)};
        ofFile myTextFile;
        myTextFile.open("info.txt", ofFile::WriteOnly);
        myTextFile << info;
        // saveStrings("lib/info.txt", info);
    }
    else if(ofGetSeconds() != 1){
        stopRotation = false;
    }
    
    // imageMode(CENTER); FIX THIS
    // noStroke();
    ofSetColor(0, 255);
    moonShade.draw(ofGetWidth()/2, appheightPos); // The dark moon
    
    // tint(254, 252, 215, 255);
    ofSetColor(235,  200,  131);
    theMoon.draw(ofGetWidth()/2, appheightPos, appfullMoonSize, appfullMoonSize); // The Moon!!!
    ofSetColor(255,  255,  255);
    
    if(!appChangeMoon){
        ofSetColor(0);
        //  imageMode(CORNER); FIX THIS
        rightMoonShade.draw(ofGetWidth()/2, appheightPos - appfullMoonSize/2, appMaskSize, appfullMoonSize); // The dark moon
        //  arc(width/2, height/2-100, moonSize/2+8, 258, -HALF_PI, HALF_PI);
    }
    
    return appMoonRotation;
}

void oneLargeMoon::mask(ofFbo target, ofFbo mask) {
    // mask.loadPixels();
    ofPixels pTarget, pMask;
    mask.readToPixels(pMask);
    // target.loadPixels();
    target.readToPixels(pTarget);
    if (pMask.getHeight() != pTarget.getHeight() || pMask.getWidth() != pTarget.getWidth()) {
        cout << "Images are not the same size" << endl;;
    } else {
        for (int i=0; i<pTarget.getWidth()*pTarget.getHeight(); i++) {
            //   int x = i % pTarget.getWidth();
            //   int y = i / pTarget.getWidth();
            //   ofColor pTar = pTarget.getColor(x,y);
            //   ofColor pMas = pMask.getColor(x,y);
            //   pTarget.setColor(x, y, ((pMas & 0xff) << 24) | (pTar & 0xffffff));
            // target.pixels[i] = ((mask.pixels[i] & 0xff) << 24) | (target.pixels[i] & 0xffffff);
            
            ofColor pMaskColor = pMask.getColor(i); // yellow
            int pMaskHex = pMaskColor.getHex();
            ofColor pTargetColor = pTarget.getColor(i); // yellow
            int pTargetHex = pTargetColor.getHex();
            int colorChange = ((pMaskHex & 0xff) << 24) | (pTargetHex & 0xffffff);
            pTarget.setColor(i,ofColor::fromHex(colorChange));
            
        }
        ofImage moonIMG = pTarget;
        theMoon.begin();
        ofClear(0, 0, 0, 0);
        // theMoon.rotate(radians(millis())/100);
        // shader.begin();
        // shader.setUniformTexture("maskTex", moon_Masking.getTexture(), 1 );
        
        moonIMG.draw(0,0);
        
        
        theMoon.end();
    }
}
