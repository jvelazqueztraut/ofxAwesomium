#pragma once

#include "ofMain.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

class ofxAwesomium {
public:
	void setup(int width, int height);
	void update();
	void draw();
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);
	void exit();
	void keyPressed(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void focus();
	void loadURL(string URL);
	bool isLoading();

	Awesomium::WebView* webView;
    
private:
	void injectKey(int keyCode);

	Awesomium::WebSession* webSession;
	Awesomium::WebCore* webCore;
	
	int webTexWidth;
	int webTexHeight;
	ofTexture webTex;
};
