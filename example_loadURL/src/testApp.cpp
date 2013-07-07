#include "testApp.h"
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

void testApp::setup(){
	webTexWidth = ofGetWindowWidth();
	webTexHeight = ofGetWindowHeight();
    webTex.allocate(webTexWidth, webTexHeight, GL_RGBA);
    webPixels.allocate(webTexWidth,webTexHeight,OF_IMAGE_COLOR_ALPHA);
    
    // Disable scrollbars via the WebCoreConfig
    Awesomium::WebConfig config;
    //config.setCustomCSS("::-webkit-scrollbar { display: none; }");
    
    
    // Create the WebCore singleton with default configuration
    webCore = Awesomium::WebCore::Initialize(config);
    

	// Create a new WebView instance with a certain width and height, using the
	// WebCore we just created
	webView = webCore->CreateWebView(webTexWidth, webTexHeight);
	
    Awesomium::WebURL url(Awesomium::WSLit("http://www.google.com"));
	// Load a certain URL into our WebView instance
	webView->LoadURL(url);
	
	webView->Focus();
}


void testApp::exit(){
    // Destroy our WebView instance
	webView->Destroy();
    Awesomium::WebCore::Shutdown();
}


void testApp::update(){
    webCore->Update();
    // Call our display func when the WebView needs rendering
	//if (webView->isDirty()) {
        //const Awesomium::RenderBuffer* renderBuffer = webView->render();
        Awesomium::Surface* renderSurface = webView->surface();
        if (renderSurface) {
            renderSurface->Paint(webPixels.getPixels(),webTexWidth*4,Awesomium::Rect(0,0,webTexWidth,webTexHeight),Awesomium::Rect(0,0,webTexWidth,webTexHeight));
            webTex.loadData(webPixels.getPixels(), webTexWidth, webTexHeight, GL_BGRA);
        }
    //}
}


void testApp::draw(){
    ofSetColor(255);
	webTex.draw(0, 0);
	
    if (webView->IsLoading()) {
        ofSetColor(0);
        ofDrawBitmapString("Loading...", 10, ofGetHeight()-20);
    }
}


void testApp::keyPressed(int key){
    switch(key) {
        case 8: case 127:
            injectKey(Awesomium::KeyCodes::AK_BACK);
            return;
        case 9:
            injectKey(Awesomium::KeyCodes::AK_TAB);
            return;
        case OF_KEY_LEFT:
            injectKey(Awesomium::KeyCodes::AK_LEFT);
            return;
        case OF_KEY_UP:
            injectKey(Awesomium::KeyCodes::AK_UP);
            return;
        case OF_KEY_RIGHT:
            injectKey(Awesomium::KeyCodes::AK_RIGHT);
            return;
        case OF_KEY_DOWN:
            injectKey(Awesomium::KeyCodes::AK_DOWN);
            return;
        case OF_KEY_PAGE_UP:
            injectKey(Awesomium::KeyCodes::AK_PRIOR);
            return;
        case OF_KEY_PAGE_DOWN:
            injectKey(Awesomium::KeyCodes::AK_NEXT);
            return;
        case OF_KEY_HOME:
            injectKey(Awesomium::KeyCodes::AK_HOME);
            return;
        case OF_KEY_END:
            injectKey(Awesomium::KeyCodes::AK_END);
            return;
	}
    
	Awesomium::WebKeyboardEvent keyEvent;
	keyEvent.text[0] = key;
	keyEvent.unmodified_text[0] = key;
	keyEvent.type = Awesomium::WebKeyboardEvent::kTypeChar;
	keyEvent.virtual_key_code = key;
	keyEvent.native_key_code = key;
	webView->InjectKeyboardEvent(keyEvent);
}


void testApp::keyReleased(int key){

}


void testApp::injectKey(int keyCode) {
	Awesomium::WebKeyboardEvent keyEvent;
    
	char* buf = new char[20];
	keyEvent.virtual_key_code = keyCode;
	Awesomium::GetKeyIdentifierFromVirtualKeyCode(keyEvent.virtual_key_code, &buf);
	strcpy(keyEvent.key_identifier, buf);
	delete[] buf;
	
	keyEvent.modifiers = 0;
	keyEvent.native_key_code = 0;
	keyEvent.type = Awesomium::WebKeyboardEvent::kTypeKeyDown;
    
	webView->InjectKeyboardEvent(keyEvent);
    
	keyEvent.type = Awesomium::WebKeyboardEvent::kTypeKeyUp;
    
	webView->InjectKeyboardEvent(keyEvent);
}



void testApp::mouseMoved(int x, int y ){
    webView->InjectMouseMove(x, y);
}


void testApp::mouseDragged(int x, int y, int button){
    webView->InjectMouseMove(x, y);
}


void testApp::mousePressed(int x, int y, int button){
    webView->InjectMouseDown(Awesomium::kMouseButton_Left);
}


void testApp::mouseReleased(int x, int y, int button){
    webView->InjectMouseUp(Awesomium::kMouseButton_Left);
}


void testApp::windowResized(int w, int h){

}
