#include <iostream>
#include <string>
#include "imageYUEE.h"
using namespace std;

int main() {
    string inputFile, outputFile;
    int mode;

    cout << "적용할 PGM 파일 이름을 입력하세요 (파일명.pgm 형태로 입력): ";
    cin >> inputFile;

    cout << "적용할 모드를 선택하세요 (0=이진화, 1=반전, 2=밝기 증가, 3=샤프닝): ";
    cin >> mode;

    cout << "저장할 파일 이름을 입력하세요: ";
    cin >> outputFile;

    imageYUEE img(inputFile);
    img.imageProc(mode);
    img.imageWrite(outputFile);

    cout << "이미지 처리가 완료되었습니다." << endl;
    return 0;
}