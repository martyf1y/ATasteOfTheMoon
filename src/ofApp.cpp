#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // size(1280, 720);
    // println("New moon size: " + maskSize);
    // println("Full moon Size: " + moonAdjust);
    
    // fullScreen();
    // noCursor();
    // smooth();   MIGHT NEED THIS
    
    font.load("verdana.ttf", messageSize);
    
    /// LOAD TEXT INFO ///
    std::ostringstream localOSS;
    
    ofBuffer buffer = ofBufferFromFile("info.txt");
    int count = 0;
    string list[3];
  
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        list[count] = line;
        count ++;
    }

   /* if(buffer.size()) {
        while(buffer.isLastLine() == false) {
            string list[] = buffer.getLines();
            std::string line = buffer.getLines();
            cout << "HER " <<  line << endl;
            list[count] = line;
            count++;
        }
    }*/
    
    maskSize = ofToFloat(list[0]);
    changeMoon = ofToBool(list[1]);
    moonRotation = ofToInt(list[2]);
    heightPos = ofGetHeight()/2-ofGetHeight()/10;
    messagePositionX = ofGetWidth()/2;
    messagePositionY = ofGetHeight()-ofGetHeight()/17;
    
    //Fireflies
    // poop = new ArrayList();
    for (int i=0; i<50; i++) {
        fireFly P = fireFly(1);
        arrayFireFlies.push_back(P);
    }
    for (int i=0; i<45; i++) {
        fireFly P = fireFly(2);
        arrayFireFlies.push_back(P);
    }
    for (int i=0; i<10; i++) {
        fireFly P = fireFly(3);
        arrayFireFlies.push_back(P);
    }
    for (int i=0; i<6; i++) {
        fireFly P = fireFly(4);
        arrayFireFlies.push_back(P);
    }
    // Define colors for background
    b1 = ofColor(0);
    b2 = ofColor(0, 15, 50);
    //  b2 = color(0, 26, 38);
    c1 = ofColor(0, 15, 50);
    c2 = ofColor(102, 51, 0);
    
    
    QColor[0] = ofColor(250, 198, 0);
    QColor[1] = ofColor(113, 24, 196);
    QColor[2] = ofColor(255, 185, 15);
    QColor[3] = ofColor(124, 252, 0);
    QColor[4] = ofColor(156, 42, 200);
    QColor[5] = ofColor(255, 255, 255);
    QColor[6] = ofColor(235, 200, 131);
    
    BG.allocate(ofGetWidth(), ofGetHeight());
    //I have put it so you create the BG in the function
     setGradient(0, 400, ofGetWidth(), ofGetHeight(), c1, c2, Y_AXIS);
     setGradient(0, 0, ofGetWidth(), 400, b1, b2, Y_AXIS);
    BG.readToPixels(gradBackground);
    
    
    //twitter
   // ConfigurationBuilder cb = new ConfigurationBuilder();
   // cb.setOAuthConsumerKey("1kYoH9Jlh0RsYmNqiHU2ZQ");
  //  cb.setOAuthConsumerSecret("t07IeLHIZkEvWZpTGNXKEv7Oo12PrE52TcGz0jaPKs");
  //  cb.setOAuthAccessToken("108744696-PNDQdTj2O7Gq9hYyB5cf3xcLw7ZudXCUrrNKEpLC");
  //  cb.setOAuthAccessTokenSecret("Sk8yV38FrNWuzQHbF6QukpTZeSwi1rpCy1nGlGq5PEkRW");
    
    // Twitter twitter = new TwitterFactory(cb.build()).getInstance();
   // TwitterFactory tf = new TwitterFactory(cb.build());
   // twitter = tf.getInstance();
    //getNewTweets();
   // currentTweet = 0;
    // thread("refreshTweets");
    
    ////// Moon
    bigMoon = oneLargeMoon();
    bigMoon.moonSetup(fullMoonSize, moonAdjust);
    bigMoon.updateMoon(changeMoon, fullMoonSize);
    
    // font = createFont(fontName, messageSize);
    defaultMessage[0] = "Send a message to be displayed on screen right now! Just tweet using #web3d2017 and wait a minute or two.";

    minuteTimer = ofGetMinutes();
    //frameRate(30);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //background(244);
    ofBackground(0, 20, 40);
    // imageMode(CENTER); FIX THIS
    //tint(255, 255, 102);
    ofSetColor(255, 255, 102);
    gradBackground.draw(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth(), ofGetHeight());
    //noTint();
    ofSetColor(255, 255, 255);

    // These are the stars, not the moon dust!!
    for (int i=0; i<arrayFireFlies.size(); i++) {
        //Fireflies Pn1 = (Fireflies) poop.get(i);
        arrayFireFlies[i].display();
        // Pn1.update();
    }
    
    // If we ever need to shift the moon on the screen
    // pushMatrix();
    // translate(-moonShift, 0);
    
   moonRotation = bigMoon.drawMoon(changeMoon, fullMoonSize, moonRotation, heightPos, maskSize);
    
    
    updateMessage();     
    
    
    // CLEAR BACKGROUND
    
    
    // This takes away the moon!!
    if (removeMoonCounter >= 2) { // Change to default with addition moon
        removeMoon();
        removeMoonCounter = 0;
        bigMoon.updateMoon(changeMoon, fullMoonSize);
    }
    
    /////////////////// Particles Roll out ////////////////
    if (runAway && !waitType) {
        
        for (int x = arrayDustParticles.size() -1; x > -1; x--) {
            // Simulate and draw pixels
            //Particle particle = particles.get(x);
            // particle.target.x = width/2+fullMoonSize/2-15-moonTarget;
            if(!arrayDustParticles[x].isKilled){
                arrayDustParticles[x].move(moonShift, isOneDead);
                arrayDustParticles[x].draw(drawAsPoints);
            }
            // Remove any dead pixels out of bounds
            else {
                arrayDustParticles.erase(arrayDustParticles.begin()+x);
                if (!goFree) { // only take away when new
                    float pixelPercent = 1/sizepercent; // The amount one tweet will add in pixel amount
                    if (!changeMoon) {
                        float halfCircle = pixelPercent*(fullMoonSize/2); // The first half amount
                        float oneDay = halfCircle; // Adjust this based on how much is to fill in one day
                        maskSize -= oneDay/tweetPacket; // This is how much a tweet can do in one day
                        if (maskSize <= 1) {
                            maskSize = 0;
                            changeMoon = true;
                        }
                    } else {
                        if (maskSize >= moonAdjust) {
                            goFree = true;
                            maskSize = moonAdjust;
                        } else {
                            float halfCircle = pixelPercent*(moonAdjust);
                            float oneDay = halfCircle;
                            maskSize += oneDay/tweetPacket;
                        }
                    }
                }
                
            }
        }
        if(isOneDead && !goFree) {
            bigMoon.updateMoon(changeMoon, fullMoonSize);
            isOneDead = false;
            for (int x = arrayDustParticles.size() -1; x > -1; x--) {
                if(!arrayDustParticles[x].isKilled){
                    arrayDustParticles[x].updateParticles(maskSize, fullMoonSize, moonAdjust, changeMoon);
                }
            }
        }
        
        //Stop adding to only one per frame
        
        if (arrayDustParticles.size() == 0) {
            runAway = false;
            waitType = false;
            cycleTimer = ofGetElapsedTimeMillis(); // resets time
            //tweetCheckTimer = millis();
            string info = {ofToString(maskSize) + "\n" + ofToString(changeMoon)+"\n"+ofToString(moonRotation)};
            ofFile myTextFile;
            myTextFile.open("info.txt", ofFile::WriteOnly);
            myTextFile << info;
        }
    }
    ///////////////// END OF PARTICLES ///////////////////
    
    
    
    
    ////////// MESSAGE //////////
    ofSetColor(newColor);
    //textSize(messageSize);
    // textAlign(LEFT); FIX THIS
    
    // textFont(font);
    if (waitType) {
        
        font.drawString(message, messagePositionX-messageWidth/2, messagePositionY-messageHeight/2);
        
        // FIX BOUNDARIES
        
        if (!runAway) {
            cycleTimer = ofGetElapsedTimeMillis(); // resets timer
        }
    }
    //messageRadius = map(maskSize, 0, fullMoonSize/2, 0, moonAdjust/4 - 30);
    //int moonArcAdjust = int(map(moon.width, 250, 2500, 225, 2250));
    //int moonArcAdjustX = int(map(maskSize, 0, fullMoonSize/2, 0, moonArcAdjust));
    
    //  arc(width/2, heightPos,  moonArcAdjustX,moonArcAdjust, -HALF_PI, HALF_PI);
    
    //popMatrix();
    
    ofSetColor(0);
   // noStroke();
    // rect(0, 0, width/8-30, height);
    // rect(width-width/8 +50, 0, width/8, height);
    //  println("Frames: " + frameRate);
    /*  String timers = "Cycle " + str(millis()-cycleTimer) + " / " + cycleEndTime + "\n";
     timers += "TIMER Tweet " + str(millis()-tweetCheckTimer) + " / " + tweetCheckEndTimer + "\n";
     timers += "Default Message " + str(millis()-cycleTimer) + " / " + str(wordEndTime) + "\n";
     timers += "Old Tweet " + str(millis()-longTimer) + " / " + longEndTime + "\n";
     timers += "Removing Moon: "  + removeMoonCounter + "\n";
     timers += "New Tweet? " +  (newTweet?"YES":"NO") + "\n";
     timers += "Frame rate? " +  frameRate + "\n";
     fill(255);
     text(timers, width/2+width/4, 20);*/
    
    
}



// Makes all particles draw the next word
void ofApp::nextWord(string word) {
    // Draw word in memory
    pg.allocate(messageWidth, messageHeight);
    
    pg.begin();
    ofClear(0,0,0,0);
    ofSetColor(255, 255, 255);
    font.drawString(word, 0, 50); // YOU WiLL NEED TO ADD BOUNDARIES PLEASSSSSSSSE
    
    pg.end();
    
    ofPixels pixels;
    pg.readToPixels(pixels);
    
    for (int i = 0; i < messageWidth*messageHeight; i+=pixelSteps) {
        // Pick a random coordinate
        // Only continue if the pixel is not blank
        int x = i % pixels.getWidth();
        int y = i / pixels.getWidth();
        
        if (pixels.getColor(x, y) != ofColor(0,0,0,0)) { // times 4 because ofpixel takes in 4 values per pixel
            
            // Convert index to its coordinates
            
            int moonWidth = bigMoon.moon.getWidth();
            dustParticle newParticle = dustParticle();
            newParticle.particleSetup(newColor, moonWidth);
            newParticle.pos.x = x + messagePositionX-messageWidth/2;
            newParticle.pos.y = y + messagePositionY-messageHeight/2;
            
            if (!goFree) {
                newParticle.target.y = int(ofRandom(-newParticle.yRadius, newParticle.yRadius));
                // newParticle.target.x = random(width/2, width/2+rightMoonSize);
                newParticle.ySquared = newParticle.target.y * newParticle.target.y;
                newParticle.target.y += heightPos; // Add the screen position
                newParticle.updateParticles(maskSize, fullMoonSize, moonAdjust, changeMoon);
            } else {
                newParticle.target.x = ofRandom(moonShift, ofGetWidth()*1.5);
                newParticle.target.y = ofRandom(-ofGetHeight()/2, 0);
                ; // Add the screen position
            }
            newParticle.maxSpeed = ofRandom(3.0, 8.0);
            newParticle.maxForce = newParticle.maxSpeed*0.025;
            newParticle.particleSize = 2;
            newParticle.colorBlendRate = ofRandom(0.0025, 0.03);
            // Blend it from its current color
            newParticle.startColor = newParticle.startColor.lerp(newParticle.targetColor, newParticle.colorWeight);
            newParticle.targetColor = ofColor(235, 200, 131);
            newParticle.colorWeight = 0;
            
            arrayDustParticles.push_back(newParticle);
            
        }
    }
    
    sizepercent = arrayDustParticles.size();
    
    // MIGHT NEED THIS FOR DEBUGGING
    // Kill off any left over particles
    /*  if (particleIndex < particleCount) {
     for (int i = particleIndex; i < particleCount; i++) {
     // dustParticle particle = arrayDustParticles[i];
     arrayDustParticles[i].kill();
     //arrayDustParticles.erase(arrayDustParticles.begin()+i);
     // dustParticle particle = particles.get(i);
     // particle.kill();
     }
     }*/
}





void ofApp::setGradient(int x, int y, float w, float h, ofColor c1, ofColor c2, int axis ) {
    //noFill();
    BG.begin();
    if (axis == Y_AXIS) {  // Top to bottom gradient
        for (int i = y; i <= y+h; i++) {
            float inter = ofMap(i, y, y+h, 0, 1);
            ofColor c = c1.lerp(c2, inter);
            ofSetColor(c);
            ofDrawLine(x, i, x+w, i);
        }
    }
    BG.end();
}


void ofApp::removeMoon() {
    
    // println("Removing moon Now");
    goFree = false; // Will always be false if we subtract a bit
    if (!changeMoon) {
        float oneTweet = (fullMoonSize*0.5)/tweetPacket; // Adjust this based on how much is to fill in one day
        maskSize += oneTweet/8; // This is how much a tweet can do in one day
        if (maskSize >= 310) {
            maskSize = 310;
        }
    } else {
        float oneDay = moonAdjust/tweetPacket;
        maskSize -= oneDay/8;
        if (maskSize <= 0) {
            changeMoon = false;
            maskSize = 0;
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'r') {
        if(!changeMoon){
            float oneTweet = (fullMoonSize*0.5)/tweetPacket; // Adjust this based on how much is to fill in one day
            //  maskSize += oneTweet/10; // This is how much a tweet can do in one day
            if (maskSize >= 310) {
                maskSize = 310;
            }
        } else {
            float oneDay = moonAdjust/tweetPacket;
            //  maskSize -= oneDay/10;
            
            if (maskSize <= 0) {
                changeMoon = false;
                maskSize = 0;
            }
        }
        bigMoon.updateMoon(changeMoon, fullMoonSize);
        string info = {ofToString(maskSize) + "\n" + ofToString(changeMoon)+"\n"+ofToString(moonRotation)};
        ofFile myTextFile;
        myTextFile.open("info.txt", ofFile::WriteOnly);
        myTextFile << info;
    }
    if (key == 't') {
        if(!changeMoon){
            float oneTweet = (fullMoonSize*0.5)/tweetPacket; // Adjust this based on how much is to fill in one day
            //  maskSize -= oneTweet/10; // This is how much a tweet can do in one day
            if (maskSize <= 1) {
                maskSize = 0;
                changeMoon = true;
            }
        }
        else {
            float oneDay = moonAdjust/tweetPacket;
            //  maskSize += oneDay/10;
            
            if (maskSize >= moonAdjust) {
                goFree = true;
                maskSize = moonAdjust;
            }
        }
        bigMoon.updateMoon(changeMoon, fullMoonSize);
        string info = {ofToString(maskSize) + "\n" + ofToString(changeMoon)+"\n"+ofToString(moonRotation)};
        ofFile myTextFile;
        myTextFile.open("info.txt", ofFile::WriteOnly);
        myTextFile << info;
    }
    if (key == 'p') {
        drawAsPoints = (!drawAsPoints);
        if (drawAsPoints) {
            ofBackground(0);
            bgColor = ofColor(0, 20, 40, 40);
        } else {
            ofBackground(255);
            bgColor = ofColor(0, 20, 40, 100);
        }
    }
    if (key == 'w' ) {
        heightPos -=10;
    } else if (key == 's' ) {
        heightPos +=10;
    }
    if (key == ' ' || key == 'z' || key == 'x') {
        if (key == ' ' ) {
            leftMoonSize = 0;
            fullMoonSize = 430;
        } else if (key == 'z') {
            fullMoonSize +=10;
        } else {
            fullMoonSize -=10;
        }
        // moonAdjust = int(map(fullMoonSize, 150, 1500, 250, 2500));
        //arcAdjust = int(map(moonAdjust, 250, 2500, 225, 2250));
        ////// Moon
        bigMoon.moonSetup(fullMoonSize, moonAdjust);
        bigMoon.updateMoon(changeMoon, fullMoonSize);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
