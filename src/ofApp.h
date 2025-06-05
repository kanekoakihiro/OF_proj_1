#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
    void setup() override;
    void update() override;
    void draw() override;

    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;

private:
    void createAlphaMask(const ofImage& src, ofTexture& dst);
    void createInvertedMaskTexture(const ofImage& src, ofTexture& dst);

    ofVideoPlayer video;
    ofImage maskImage;

    ofTexture originalMaskTexture;   // 黒→透明マスク
    ofTexture invertedMaskTexture;   // 反転マスク（黒→白、不透明、白→透明）

    bool isMouseInside = false;
};
