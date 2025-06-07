#include <iostream>
#include <string>
#include "imageYUEE.h"
using namespace std;

int main() {
    string inputFile, outputFile;
    int mode;

    cout << "������ PGM ���� �̸��� �Է��ϼ��� (���ϸ�.pgm ���·� �Է�): ";
    cin >> inputFile;

    cout << "������ ��带 �����ϼ��� (0=����ȭ, 1=����, 2=��� ����, 3=������): ";
    cin >> mode;

    cout << "������ ���� �̸��� �Է��ϼ���: ";
    cin >> outputFile;

    imageYUEE img(inputFile);
    img.imageProc(mode);
    img.imageWrite(outputFile);

    cout << "�̹��� ó���� �Ϸ�Ǿ����ϴ�." << endl;
    return 0;
}