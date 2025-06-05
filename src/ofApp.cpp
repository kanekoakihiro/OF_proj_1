#include "ofApp.h"

void ofApp::setup(){
    video.load("video.mp4");
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();

    maskImage.load("mask.png");

    createAlphaMask(maskImage, originalMaskTexture);
    createInvertedMaskTexture(maskImage, invertedMaskTexture);

    ofEnableAlphaBlending();
}

void ofApp::update(){
    video.update();
}

void ofApp::draw(){
    // 動画を背景として描画
    video.draw(0, 0, ofGetWidth(), ofGetHeight());

    // マスクを反転状態に応じて描画
    if(isMouseInside){
        invertedMaskTexture.draw(0, 0, ofGetWidth(), ofGetHeight());
    } else {
        originalMaskTexture.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}

void ofApp::mouseEntered(int x, int y){
    isMouseInside = true;
}

void ofApp::mouseExited(int x, int y){
    isMouseInside = false;
}

// 黒を透明、その他は白不透明にして透過マスクを作成
void ofApp::createAlphaMask(const ofImage& src, ofTexture& dst){
    ofPixels pixels = src.getPixels();
    ofPixels rgbaPixels;
    rgbaPixels.allocate(pixels.getWidth(), pixels.getHeight(), OF_PIXELS_RGBA);

    for(int y=0; y<pixels.getHeight(); y++){
        for(int x=0; x<pixels.getWidth(); x++){
            ofColor c = pixels.getColor(x,y);
            bool isBlack = (c.r < 10 && c.g < 10 && c.b < 10);
            if(isBlack){
                rgbaPixels.setColor(x, y, ofColor(0,0,0,0)); // 透明
            } else {
                rgbaPixels.setColor(x, y, ofColor(255,255,255,255)); // 白不透明
            }
        }
    }
    dst.loadData(rgbaPixels);
}

// 反転マスク生成 黒→白不透明、白→透明に反転
void ofApp::createInvertedMaskTexture(const ofImage& src, ofTexture& dst){
    ofPixels pixels = src.getPixels();
    ofPixels rgbaPixels;
    rgbaPixels.allocate(pixels.getWidth(), pixels.getHeight(), OF_PIXELS_RGBA);

    for(int y=0; y<pixels.getHeight(); y++){
        for(int x=0; x<pixels.getWidth(); x++){
            ofColor c = pixels.getColor(x,y);
            bool isBlack = (c.r < 10 && c.g < 10 && c.b < 10);
            if(isBlack){
                rgbaPixels.setColor(x, y, ofColor(255,255,255,255)); // 黒部分を白不透明に反転
            } else {
                rgbaPixels.setColor(x, y, ofColor(0,0,0,0)); // 白部分を透明に反転
            }
        }
    }
    dst.loadData(rgbaPixels);
}
