#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <math.h>
#include <windows.h>
#include <fstream>

using namespace std;
using namespace cv;

void setCursor(int x, int y) {
    COORD p = { x, y };
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(out, p );
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void setFont(int w, int h){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.dwFontSize.X = w;
    cfi.dwFontSize.Y = h;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Monocraft");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

string matToAscii(Mat *image, char *chars, size_t arraySize, float wScale, float hScale){
    string output = "";

    float value = 255.0f / arraySize;
    resize(*image, *image, Size((int)(image->cols/wScale), (int)(image->rows/hScale)), INTER_LINEAR);
    
    for (int y = 0; y < image->rows; y++) {
        for (int x = 0; x < image->cols; x++) {
            Vec3b rgb = image->at<Vec3b>(y, x);
            float gray = (rgb[0]+rgb[1]+rgb[2])/3.0f;
            int index = (int)floor( min(gray, 254.0f) / value );
            output += *(chars + index);
        }
        output += "\n";
    }

    return output;
}

void webcamLoop(char *chars, size_t arraySize, float wScale, float hScale) {
    Mat frame;
    VideoCapture camera(0);
    namedWindow("Frame", cv::WINDOW_AUTOSIZE);
    
    while (1) {
        camera >> frame;
        imshow("Frame", frame);
        
        string image = matToAscii(&frame, chars, arraySize, wScale, hScale);

        cout << image;
        setCursor(0, 0);

        if (cv::waitKey(10) == 27){
            break;
        }
    }
}

int main() {
    setCursor(0, 0);
    setFont(6, 12); //setting font size.

    //characters used to display feed in ascending order of brightness.
    char chars[] = {' ', '.', ',', '*', '-', '+', '=', '%', '?', 'C', 'O', '0', '8', '@', 'X'};
    
    float wScale = 2.5f; //width scale edit both if image doesnt fit in cmd window.
    float hScale = 6.0f; //height scale (higher than wScale because cmd font is not monospace)

    webcamLoop(&chars[0], size(chars), wScale, hScale);

    //string image = matToAscii(&imread("image.jpg"), &chars[0], size(chars), wScale, hScale);
    
    //ofstream file("image.txt", ofstream::out);
    //file << image;
    //cout << image;
    //cin >> image; //keep console open

    //!Comment webcamLoop() and uncomment all of the above to use the program with image files instead
}