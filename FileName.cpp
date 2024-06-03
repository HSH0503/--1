#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat img(500, 700, CV_8UC3, Scalar(255, 255, 255)); // Canvas for drawing and buttons
Point ptPrev(-1, -1);
Rect save(500, 0, 200, 100);
Rect load(500, 100, 200, 100);
Rect clear(500, 200, 200, 100);
Rect run(500, 300, 200, 100);
Rect exitt(500, 400, 200, 100);
void onMouse(int event, int x, int y, int flags, void*);
void Save();
void Load();
void Clear();
void Run();
void Exit();
int predictDigit(const Mat& image);
void drawButtons();
int main() 
{
    drawButtons();
    namedWindow("img");
    setMouseCallback("img", onMouse);
    imshow("img", img);
    waitKey(0);
    return 0;
}
void onMouse(int event, int x, int y, int flags, void*) 
{
    if (event == EVENT_LBUTTONDOWN) 
    {
        if (x < 500) 
        {
            ptPrev = Point(x, y);
        }
        else {
            Point clickPoint(x, y);
            if (save.contains(clickPoint)) {
                Save();
            }
            else if (load.contains(clickPoint)) {
                Load();
            }
            else if (clear.contains(clickPoint)) {
                Clear();
            }
            else if (run.contains(clickPoint)) {
                Run();
            }
            else if (exitt.contains(clickPoint)) {
                Exit();
            }
        }
    }
    else if (event == EVENT_LBUTTONUP) {
        ptPrev = Point(-1, -1);
    }
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
        if (x < 500 && x >= 0 && y < 500 && y >= 0) {
            line(img, ptPrev, Point(x, y), Scalar::all(0), 10);
            ptPrev = Point(x, y);
            imshow("img", img);
        }
    }
}
void drawButtons() 
{
    rectangle(img, save, Scalar(0, 0, 0), 2);
    putText(img, "Save", Point(save.x + 10, save.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, load, Scalar(0, 0, 0), 2);
    putText(img, "Load", Point(load.x + 10, load.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, clear, Scalar(0, 0, 0), 2);
    putText(img, "Clear", Point(clear.x + 10, clear.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, run, Scalar(0, 0, 0), 2);
    putText(img, "Run", Point(run.x + 10, run.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
    rectangle(img, exitt, Scalar(0, 0, 0), 2);
    putText(img, "Exit", Point(exitt.x + 10, exitt.y + 50), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(0, 0, 0), 2);
}
void Save() 
{
    string fileName;
    cout << "파일명 입력: ";
    cin >> fileName;
    Mat saveImg = img(Rect(0, 0, 500, 500)).clone();
    resize(saveImg, saveImg, Size(500, 500));
    imwrite(fileName, saveImg);
    cout << fileName + " 파일이 저장됨" << endl;
}
void Load() 
{
    string fileName;
    cout << "파일명 입력: ";
    cin >> fileName;
    Mat src = imread(fileName);
    if (!src.empty()) {
        src.copyTo(img(Rect(0, 0, 500, 500)));
        imshow("img", img);
        cout << fileName + " 파일을 불러옴" << endl;
    }
    else {
        cout << "파일을 불러올 수 없습니다." << endl;
    }
}
void Clear() 
{
    img(Rect(0, 0, 500, 500)) = Scalar(255, 255, 255);
    drawButtons();
    imshow("img", img);
    cout << "입력창 삭제됨" << endl;
}
void Run() 
{
    Mat gray, resized;
    cvtColor(img(Rect(0, 0, 500, 500)), gray, COLOR_BGR2GRAY);
    resize(gray, resized, Size(28, 28));
    int result = predictDigit(resized);
    cout << "인식결과: " << result << endl;
}
void Exit() 
{
    cout << "프로그램 종료" << endl;
    destroyAllWindows();
    exit(0);
}
int predictDigit(const Mat& image) 
{
    return rand() % 10;
}
