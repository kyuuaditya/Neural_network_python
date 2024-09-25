#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

ofstream imagedata;
ofstream imagedata2;

const int HEIGHT = 400;
const int WIDTH = 400;
const int IMG_SIZE = 25;
const int DATA_SIZE = 10000;

void initializeImage(vector<vector<int>>& img) {
    for (int i = 0; i < IMG_SIZE; ++i) {
        for (int j = 0; j < IMG_SIZE; ++j) {
            img[i][j] = 0;
        }
    }
}

void generateRandomSquare(int& x, int& y, int& side, mt19937& rng) {
    uniform_int_distribution<int> dist_height(HEIGHT * 7 / 20 - HEIGHT / 4,
                                              HEIGHT * 7 / 20 + HEIGHT / 4);
    uniform_int_distribution<int> dist_side(HEIGHT / 5 - HEIGHT / 10,
                                            HEIGHT / 5 + HEIGHT / 10);

    y = dist_height(rng);
    x = dist_height(rng);
    side = dist_side(rng);
}

void drawSquare(vector<vector<int>>& img, int x, int y, int side) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            int p = i / 16;
            int q = j / 16;
            if (i > x && j > y && i < (x + side) && j < (y + side)) {
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
    imagedata2 << 0 << " " << 1 << " " << 0 << " " << endl;
}

int main() {
    srand(time(0));
    mt19937 rng(time(0));

    vector<vector<int>> img2(IMG_SIZE, vector<int>(IMG_SIZE, 0));

    imagedata.open("input.txt");
    imagedata2.open("output.txt");

    for (int yo = 0; yo < DATA_SIZE; ++yo) {
        int x, y, side;
        generateRandomSquare(x, y, side, rng);

        initializeImage(img2);
        drawSquare(img2, x, y, side);
        normalizeAndWriteImage(img2, imagedata);
        writeOutput(imagedata2);
    }

    imagedata.close();
    imagedata2.close();

    return 0;
}