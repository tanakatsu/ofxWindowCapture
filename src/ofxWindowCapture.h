#include "ofMain.h"

class ofxWindowCapture
{
public:
	ofxWindowCapture();
	~ofxWindowCapture();

	void capture();
	void capture(HWND hWnd);
	HWND getSelectedWindow();
	bool isButtonPressed(int key);

	ofImage captureImage;

private:
	void allocate(HWND hWnd);

};
