
#include "ofxWindowCapture.h"

ofxWindowCapture::ofxWindowCapture() {
}

ofxWindowCapture::~ofxWindowCapture() {
}

void ofxWindowCapture::capture() {
	capture(GetDesktopWindow());
}

void ofxWindowCapture::capture(HWND hWnd) {
	if (hWnd == NULL) {
		return;
	} 	
	allocate(hWnd);

	HDC hScreen = GetDC(hWnd);
	HDC hdcMem = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, captureImage.width, captureImage.height);
	HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
	BitBlt(hdcMem, 0, 0, captureImage.width, captureImage.height, hScreen, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hOld);

	BITMAPINFOHEADER bmi = {0};
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = captureImage.width;
	bmi.biHeight = -captureImage.height;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;

	GetDIBits(hdcMem, hBitmap, 0, captureImage.height, captureImage.getPixels(), (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	ReleaseDC(hWnd, hScreen);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);

	unsigned char *p = captureImage.getPixels();
	unsigned char tmpVal;
	for (int j = 0; j < captureImage.height; j++) {
		for (int i = 0; i < captureImage.width; i++) {
			tmpVal = p[((j * captureImage.width) + i) * 4 + 0];
			p[((j * captureImage.width) + i) * 4 + 0] = p[((j * captureImage.width) + i) * 4 + 2];
			p[((j * captureImage.width) + i) * 4 + 2] = tmpVal; 
			p[((j * captureImage.width) + i) * 4 + 3] = 255; 
		}
	}

	captureImage.update(); 
}

HWND ofxWindowCapture::getSelectedWindow() {
	POINT p;
	GetCursorPos(&p);
  
    return WindowFromPoint(p);
}

bool ofxWindowCapture::isButtonPressed(int key) {
	bool button_pressed = false;
	
	while(GetAsyncKeyState(key))
		button_pressed = true;
	
	return button_pressed;
}

void ofxWindowCapture::allocate(HWND hWnd) {
	if (hWnd != NULL) {
		RECT winRect;
        GetWindowRect(hWnd, &winRect);

		int width = winRect.right - winRect.left;
		int height = winRect.bottom - winRect.top;

		if (captureImage.isAllocated() && (captureImage.width != width || captureImage.height != height)) {
			captureImage.resize(width, height);
		} else {
			captureImage.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
		}
	}
}

