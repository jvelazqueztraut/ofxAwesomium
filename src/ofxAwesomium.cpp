#include "ofxAwesomium.h"

void ofxAwesomium::setup(int width, int height){
	webTexWidth = width;
	webTexHeight = height;
    webTex.allocate(webTexWidth, webTexHeight, GL_RGBA);
    
    // Disable scrollbars via the WebCoreConfig
    Awesomium::WebConfig config;
	//Awesomium::WebStringArray configStrings;
	//configStrings.Push(Awesomium::WSLit("::-webkit-user-select { display: none; }"));
	//configStrings.Push(Awesomium::WSLit("::-webkit-scrollbar { display: none; }"));
	//config.additional_options=configStrings;
    
	// Create the WebCore singleton with default configuration
    webCore = Awesomium::WebCore::Initialize(config);
    
	Awesomium::WebPreferences prefs;
	prefs.enable_web_security = false;

	string path = ofToDataPath("WebSession/",true);
	// Create the WebSession
    webSession = webCore->CreateWebSession(Awesomium::WebString(Awesomium::WSLit(path.c_str())),prefs);

	// Create a new WebView instance with a certain width and height, using the
	// WebCore we just created
	webView = webCore->CreateWebView(webTexWidth, webTexHeight, webSession);

}
void ofxAwesomium::focus(){
    webView->Focus();
}

void ofxAwesomium::loadURL(string URL){
	Awesomium::WebURL url(Awesomium::WSLit(URL.c_str()));
	// Load a certain URL into our WebView instance
	webView->LoadURL(url);
}

bool ofxAwesomium::isLoading(){
	return webView->IsLoading();
}

void ofxAwesomium::exit(){
    // Destroy our WebView instance
	webView->Destroy();
	webSession->Release();
    Awesomium::WebCore::Shutdown();
}

void ofxAwesomium::update(){
    webCore->Update();
    // Call our display func when the WebView needs rendering
	//if (webView->isDirty()) {
        //const Awesomium::RenderBuffer* renderBuffer = webView->render()
        Awesomium::BitmapSurface* surface = (Awesomium::BitmapSurface*)webView->surface();
        if (surface) {
            webTex.loadData(surface->buffer(), webTexWidth, webTexHeight, GL_BGRA);
        }
    //}
}


void ofxAwesomium::draw(){
	webTex.draw(0, 0);
}

void ofxAwesomium::draw(float x, float y){
	webTex.draw(x, y);
}

void ofxAwesomium::draw(float x, float y, float w, float h){
	webTex.draw(x, y, w, h);
}


void ofxAwesomium::keyPressed(int key){
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

void ofxAwesomium::injectKey(int keyCode) {
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



void ofxAwesomium::mouseMoved(int x, int y ){
    webView->InjectMouseMove(x, y);
}


void ofxAwesomium::mouseDragged(int x, int y, int button){
    webView->InjectMouseMove(x, y);
}


void ofxAwesomium::mousePressed(int x, int y, int button){
    webView->InjectMouseDown(Awesomium::kMouseButton_Left);
}


void ofxAwesomium::mouseReleased(int x, int y, int button){
    webView->InjectMouseUp(Awesomium::kMouseButton_Left);
}
