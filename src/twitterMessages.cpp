#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::updateMessage() {
    
    if (ofGetElapsedTimeMillis()-cycleTimer > cycleEndTime || (ofGetElapsedTimeMillis()-tweetCheckTimer > tweetCheckEndTimer && !waitType)) {
        
        if (!waitType && !runAway) { //  When we are not typing message or filling moon
            newColor = QColor[int(ofRandom(0, 7))];
            thisTwit = defaultMessage[int(ofRandom(0, 6))];
            
            if (tweetCheckTimer < ofGetElapsedTimeMillis()-tweetCheckEndTimer) {
                // We dont want the program looping the search,
                // it only resets (or searches again) after a message has played
                cout << "We have made it" << endl;
                
            }
            if (newTweet) {
                
                string finalTwit = theTweets[currentTweet];
                //currentTweet = currentTweet + 1;
                if (finalTwit.empty()) {
                    thisTwit = defaultMessage[int(ofRandom(0, 6))];
                } else {
                    thisTwit = finalTwit;
                    goFree = false;
                    tweetCounter ++;
                    if (maskSize >= moonAdjust && changeMoon) {
                        goFree = true;
                    }
                }
                nextWord(thisTwit);
            } else {
                goFree = true;
                // We check many things here. If no new tweet then we grab a default message,
                // After a while we will grab an old message
                // After an hour we see if there is a new message already sent. If not add a bit of moon.
                if (cycleTimer < ofGetElapsedTimeMillis()-wordEndTime) { // Show default message
                    thisTwit = defaultMessage[int(ofRandom(0, 6))];
                    removeMoonCounter ++;
                } else if (longTimer < ofGetElapsedTimeMillis()-longEndTime) {
                    ofBuffer buffer = ofBufferFromFile("tweets.txt");

                    vector <string> Tlines;
                    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
                        string line = *it;
                        Tlines.push_back(line);
                    }
                    // Change to old message
                    if (Tlines.size() >= 1) {
                        int rand = ofRandom(0, Tlines.size());
                    
                        //choose random line with @ symbol to start the tweet
                        int breakCounter = 0;
                        while (Tlines[rand].find("@")) { // JENNA THIS WAS YOUR CODE I CHANGED IT SLIGHTLY MAY BE WRONG
                            rand = ofRandom(0, Tlines.size()-1);
                            breakCounter ++;
                            if(breakCounter >50){
                                return;
                            }
                        }
                        string retrievedFromFile = Tlines[rand];
                        //recursive function / retrieve all lines before the next @
                        thisTwit = retrieveAllLines(rand, Tlines, retrievedFromFile);
                        cout << "Retrieved " << retrievedFromFile << endl;
                    }
                    longTimer = ofGetElapsedTimeMillis();
                }  else {
                    return;
                }
                nextWord(thisTwit);
            }
            stringCount = 0;
            //nextWord(thisTwit);
            waitType = true;
        } else {
            waitType = false;
        }
    }
    if (waitType && !runAway) {    
        runAway = printMessage();
    }
}


bool ofApp::printMessage() {
    if (stringCount < thisTwit.length() && ofGetFrameNum()%2 == 0) {
        stringCount ++;
        string typeTwit = thisTwit.substr(0, stringCount);
        message = typeTwit;
    } else if (stringCount >= thisTwit.length()) {
        return true;
    }
    //delay(40);
    return false;
}



// * * * * * * * * * * * * * * * * * *
// Retrieve function

string ofApp::retrieveAllLines(int rand, vector <string> Tlines, string incoming) {
    
    string output = incoming;
    
    if (rand+1 < Tlines.size()) {
        
        if (Tlines[rand+1].find("@")) {
            
            output = output + "\n" + Tlines[rand+1];
            retrieveAllLines(rand+1, Tlines, output);
        } else {
            return output ;
        }
    }
    return output;
}
