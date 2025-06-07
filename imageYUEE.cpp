#include "imageYUEE.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

imageYUEE::imageYUEE(string fname) {
    ifstream file(fname, ios::binary);
    if (!file) {
        cerr << "파일을 열 수 없습니다: " << fname << endl;
        exit(1);
    }

    string magic;
    file >> magic;
    if (magic != "P5") {
        cerr << "지원되지 않는 PGM 포맷입니다." << endl;
        exit(1);
    }

    file >> cols >> rows;
    int maxVal;
    file >> maxVal;
    file.ignore(); 

    pixelValues = new unsigned char[rows * cols];
    pixelProcessed = new unsigned char[rows * cols];
    file.read(reinterpret_cast<char*>(pixelValues), rows * cols);
    memcpy(pixelProcessed, pixelValues, rows * cols);
    file.close();
}

int imageYUEE::imageProc(int Mode) {
    if (Mode == 0) {                         // 이진화
        int threshold = 128;
        for (int i = 0; i < rows * cols; i++) {
            pixelProcessed[i] = (pixelValues[i] > threshold) ? 255 : 0;
        }
    }
    else if (Mode == 1) {                    // 반전
        for (int i = 0; i < rows * cols; i++) {
            pixelProcessed[i] = 255 - pixelValues[i];
        }
    }
    else if (Mode == 2) {                    // 밝기 증가
        int boost = 50;
        for (int i = 0; i < rows * cols; i++) {
            int temp = pixelValues[i] + boost;
            pixelProcessed[i] = (temp > 255) ? 255 : temp;
        }
    }
    else if (Mode == 3) {                   // 샤프닝
        memcpy(pixelProcessed, pixelValues, rows * cols);
        for (int y = 1; y < rows - 1; y++) {
            for (int x = 1; x < cols - 1; x++) {
                int sum = 0;
                int kernel[3][3] = {
                    { 0, -2,  0},
                    {-2, 10, -2},
                    { 0, -2,  0}
                };                          // 더 강한 샤프닝
                for (int j = -1; j <= 1; j++) {
                    for (int i = -1; i <= 1; i++) {
                        int val = pixelValues[(y + j) * cols + (x + i)];
                        sum += val * kernel[j + 1][i + 1];
                    }
                }
                sum = max(0, min(255, sum));
                pixelProcessed[y * cols + x] = static_cast<unsigned char>(sum);
            }
        }
    }
    else {
        cerr << "알 수 없는 모드입니다." << endl;
        return -1;
    }
    return 0;
}

int imageYUEE::imageWrite(string fname) {
    ofstream file(fname, ios::binary);
    if (!file) {
        cerr << "파일을 저장할 수 없습니다: " << fname << endl;
        return -1;
    }
    file << "P5\n" << cols << " " << rows << "\n255\n";
    file.write(reinterpret_cast<char*>(pixelProcessed), rows * cols);
    file.close();
    return 0;
}

imageYUEE::~imageYUEE() {
    delete[] pixelValues;
    delete[] pixelProcessed;
}