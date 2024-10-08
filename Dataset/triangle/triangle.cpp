#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

const int HEIGHT = 400;
const int WIDTH = 400;
const int IMG_SIZE = 25;
const int DATA_SIZE = 100;

ofstream imagedata;
ofstream imagedata2;

void initializeImage(vector<vector<int>>& img) {
    for (int i = 0; i < IMG_SIZE; ++i) {
        for (int j = 0; j < IMG_SIZE; ++j) {
            img[i][j] = 0;
        }
    }
}

void generateRandomTriangle(int& x1, int& y1, int& x2, int& y2, int& x3,
                            int& y3, mt19937& rng) {
    uniform_int_distribution<int> dist_height(HEIGHT * 7 / 20 - HEIGHT / 4,
                                              HEIGHT * 7 / 20 + HEIGHT / 4);
    uniform_int_distribution<int> dist_width(WIDTH * 7 / 20 - WIDTH / 4,
                                             WIDTH * 7 / 20 + WIDTH / 4);

    y1 = dist_height(rng);
    x1 = dist_width(rng);
    y2 = dist_height(rng);
    x2 = dist_width(rng);
    y3 = dist_height(rng);
    x3 = dist_width(rng);
}

bool isInsideTriangle(int x, int y, int x1, int y1, int x2, int y2, int x3,
                      int y3) {
    float denominator = ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));
    float a = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / denominator;
    float b = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / denominator;
    float c = 1 - a - b;
    return 0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1;
}

void drawTriangle(vector<vector<int>>& img, int x1, int y1, int x2, int y2,
                  int x3, int y3) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            int p = i / 16;
            int q = j / 16;
            if (isInsideTriangle(i, j, x1, y1, x2, y2, x3, y3)) {
                img[p][q] += 255;
            }
        }
    }
}

void normalizeAndWriteImage(const vector<vector<int>>& img,
                            ofstream& imagedata) {
    for (int i = 0; i < IMG_SIZE; ++i) {
        for (int j = 0; j < IMG_SIZE; ++j) {
            imagedata << img[j][i] / 256 << " ";
        }
    }
    imagedata << endl;
}

void writeOutput(ofstream& imagedata2) {
    imagedata2 << 0 << " " << 0 << " " << 1 << " " << endl;
}

int main() {
    srand(time(0));
    mt19937 rng(time(0));

    vector<vector<int>> img2(IMG_SIZE, vector<int>(IMG_SIZE, 0));

    imagedata.open("input.txt");
    imagedata2.open("output.txt");

    for (int yo = 0; yo < DATA_SIZE; ++yo) {
        int x1, y1, x2, y2, x3, y3;
        generateRandomTriangle(x1, y1, x2, y2, x3, y3, rng);

        initializeImage(img2);
        drawTriangle(img2, x1, y1, x2, y2, x3, y3);
        normalizeAndWriteImage(img2, imagedata);
        writeOutput(imagedata2);
    }

    imagedata.close();
    imagedata2.close();

    return 0;
}