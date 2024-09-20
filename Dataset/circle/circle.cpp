// #include <bits/stdc++.h>
// #include <stdio.h>

// #include <fstream>
// using namespace std;
// ofstream imagedata;
// ofstream imagedata2;

// int main() {
//     int data_size = 100;
//     // cout << " yes" << endl;
//     srand(time(0));
//     int height = 800;
//     int width = 800;
//     int radius;
//     int centrey = height / 2;
//     int centrex = width / 2;
//     int p;
//     int q;
//     int img2[50][50];
//     for (int i = 0; i < 50; i++) {
//         for (int j = 0; j < 50; j++) {
//             img2[i][j] = 0;
//         }
//     }

//     imagedata.open("input.txt");
//     imagedata2.open("output.txt");

//     for (int yo = 0; yo < data_size; yo++) {
//         centrey = height / 2 + (rand() % (height / 5) + 1) - height / 10;
//         centrex = width / 2 + (rand() % (height / 5) + 1) - height / 10;
//         radius = (height / 5) + (rand() % (height / 5) + 1) - height / 10;

//         for (int i = 0; i < width; i++) {
//             for (int j = 0; j < height; j++) {
//                 q = j / 16;
//                 p = i / 16;
//                 if ((double)((centrex - i) * (centrex - i) +
//                              (centrey - j) * (centrey - j)) < radius *
//                              radius) {
//                     img2[p][q] += 255;
//                 }
//             }
//         }
//         for (int i = 0; i < 50; i++) {
//             for (int j = 0; j < 50; j++) {
//                 img2[j][i] = img2[j][i] / 256;
//                 imagedata << img2[j][i] << " ";
//             }
//         }
//         imagedata2 << 1 << " " << 0 << " ";
//         imagedata << endl;
//         imagedata2 << endl;
//     }
// }

// #include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

ofstream imagedata;
ofstream imagedata2;

const int HEIGHT = 800;
const int WIDTH = 800;
const int IMG_SIZE = 50;
const int DATA_SIZE = 1000;

void initializeImage(vector<vector<int>>& img) {
    for (int i = 0; i < IMG_SIZE; ++i) {
        for (int j = 0; j < IMG_SIZE; ++j) {
            img[i][j] = 0;
        }
    }
}

void generateRandomCircle(int& centrex, int& centrey, int& radius,
                          mt19937& rng) {
    uniform_int_distribution<int> dist_height(HEIGHT / 2 - HEIGHT / 10,
                                              HEIGHT / 2 + HEIGHT / 10);
    uniform_int_distribution<int> dist_radius(HEIGHT / 5 - HEIGHT / 10,
                                              HEIGHT / 5 + HEIGHT / 10);

    centrey = dist_height(rng);
    centrex = dist_height(rng);
    radius = dist_radius(rng);
}

void drawCircle(vector<vector<int>>& img, int centrex, int centrey,
                int radius) {
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            int p = i / 16;
            int q = j / 16;
            if ((centrex - i) * (centrex - i) + (centrey - j) * (centrey - j) <
                radius * radius) {
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
    imagedata2 << 1 << " " << 0 << " " << endl;
}

int main() {
    srand(time(0));
    mt19937 rng(time(0));

    vector<vector<int>> img2(IMG_SIZE, vector<int>(IMG_SIZE, 0));

    imagedata.open("input.txt");
    imagedata2.open("output.txt");

    for (int yo = 0; yo < DATA_SIZE; ++yo) {
        int centrex, centrey, radius;
        generateRandomCircle(centrex, centrey, radius, rng);

        initializeImage(img2);
        drawCircle(img2, centrex, centrey, radius);
        normalizeAndWriteImage(img2, imagedata);
        writeOutput(imagedata2);
    }

    imagedata.close();
    imagedata2.close();

    return 0;
}