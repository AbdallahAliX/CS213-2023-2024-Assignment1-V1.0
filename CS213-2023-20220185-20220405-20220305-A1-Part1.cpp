// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				CS213-2023-20220185-20220405-20220305-A1.cpp
// Author1 and ID and Email and Group:	Abdallah Mohamed / 20220185 / abdallahali0004@gmail.com
// Author2 and ID and Email and Group:	Youssef Mohamed / 20220405 / Safottanew2@gmail.com
// Author3 and ID and Email and Group:	Mohamed Maged / 20220305 / medomaged01000@gmail.com
// Purpose: Adding filters to a gray scale image

#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];

void loadImage();
void saveImage();
void flipImage(string flipType);
void adjustDarkeningAndLightening();
void doSomethingForImage();
void BW();
void InvertImage();
void mer();
void RotateImage();
void ninetydegree();
void enlargeQuarter(int x, int y, int newSIZE);
void shuffleQuarters();
int filterNumber;

int main()
{
  loadImage();
  doSomethingForImage();
  saveImage();
  return 0;
}

void loadImage()
{
  char imageFileName[100];

  // Get gray scale image file name
  cout << "Enter the source image file name: ";
  cin >> imageFileName;

  // Add to it .bmp extension and load image
  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, image);
}

void saveImage()
{
  if (filterNumber != 0)
  {
     char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
  }
  
 
}

void flipImage(string flipType)
{
  // Flipping image both horizontally and vertically
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE / 2; j++)
    {
      if (flipType == "h")
      {
        // Swap pixels horizontally across the middle column
        swap(image[i][j], image[i][SIZE - 1 - j]);
      }
      else if (flipType == "v")
      {
        // Swap pixels horizontally across the middle row
        swap(image[j][i], image[SIZE - 1 - j][i]);
      }
    }
  }
}

void adjustDarkeningAndLightening(){
  //Brightness is a user input that if negative darkens the image while if positive lightens it with the amount that user entered
  int Brightness;

  cout << "Enter the brightness adjustment value (positive for lighten, negative for darken): ";
  cin >> Brightness;

  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      // Adjust the pixel intensity
      int newIntensity = static_cast<int>(image[i][j]) + Brightness;
      // Ensure the intensity stays within the valid range [0, 255]
      newIntensity = max(0, min(255, newIntensity));
      // Update the pixel intensity
      image[i][j] = static_cast<unsigned char>(newIntensity);
    }
  }
}


void BW() { // function to turn image to black and white


for (int i = 0; i < SIZE; i++) {

    for (int j = 0; j< SIZE; j++) {

        if(int(image[i][j]) > 127) {image[i][j] = char(255);} // if the pixel gray level is bigger than the average gray level 
                                                              //: set the pixel to black

        else {image[i][j] = char(0);} // else : set it to white
    }

  }

}



void InvertImage() { // function to invert an image

  
  for (int i = 0; i < SIZE; i++) {

    for (int j = 0; j< SIZE; j++) {

       image[i][j] = char(255 - int(image[i][j])); // subtract 255 from the pixel gray level to invert it ( if the pixel is white it will turn to black 
                                                   //and the opposite)
    }
  }
}

void mer() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE ; j++)
        {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;


        }

    }
}

void ninetydegree() {

    unsigned char image3[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            image3[i][j] = image[SIZE - 1 - j][i];
        }
    }

    swap(image3, image);
}

void RotateImage() {

    int rotation;
    cout << "please enter rotation \n"
        "1- 90 degree\n"
        "2- 180 degree\n"
        "3- 270 degree\n";

    cin >> rotation;


    while (rotation--) {

        ninetydegree();
    }
    
}

void enlargeQuarter(int x, int y, int newSIZE) {
    unsigned char enlargedQuarter[SIZE][SIZE];

    // Calculate scaling factor
    int scale = SIZE / newSIZE;

    // Iterate over each pixel in the new image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // Calculate corresponding position in the original quarter
            int quarterI = i / scale;
            int quarterJ = j / scale;

            // Copy pixel values from the chosen quarter to the new image
            enlargedQuarter[i][j] = image[x + quarterI][y + quarterJ];
        }
    }

    // Copy the enlarged quarter to the original image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = enlargedQuarter[i][j];
        }
    }
}

void chooseQuarter(){
        // Enlarge one of the four quarters into a new image
        int quarter;
        cout << "Choose a quarter to enlarge (1, 2, 3, or 4): ";
        cin >> quarter;

        // Enlarge the specified quarter into a new image
        if (quarter == 1) {
            enlargeQuarter(0, 0, SIZE / 2);
        } else if (quarter == 2) {
            enlargeQuarter(0, SIZE / 2, SIZE / 2);
        } else if (quarter == 3) {
            enlargeQuarter(SIZE / 2, 0, SIZE / 2);
        } else if (quarter == 4) {
            enlargeQuarter(SIZE / 2, SIZE / 2, SIZE / 2);
        } else {
            cout << "Invalid quarter choice.\n";
        }
}

void shuffleQuarters() {
    // Quarters order based on user input
    int order[] = {0, 0, 0, 0};

    // Get user input for quarter order
    cout << "Enter the order of quarters (1, 2, 3, 4): ";
    for (int i = 0; i < 4; ++i) {
        cin >> order[i];
    }

    // Validate user input
    bool validOrder = true;
    for (int i = 1; i <= 4; ++i) {
        if (find(begin(order), end(order), i) == end(order)) {
            cout << "Invalid order. Please enter each quarter number exactly once.\n";
            validOrder = false;
            break;
        }
    }

    if (!validOrder) {
        return;
    }

    // Create a copy of the original image for shuffling
    unsigned char shuffledImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            shuffledImage[i][j] = image[i][j];
        }
    }

    // Shuffle the quarters based on user input
    for (int i = 0; i < 4; ++i) {
        int newRow = i / 2;
        int newCol = i % 2;

        int originalRow = (order[i] - 1) / 2;
        int originalCol = (order[i] - 1) % 2;

        for (int x = 0; x < SIZE / 2; ++x) {
            for (int y = 0; y < SIZE / 2; ++y) {
                image[newRow * (SIZE / 2) + x][newCol * (SIZE / 2) + y] = shuffledImage[originalRow * (SIZE / 2) + x][originalCol * (SIZE / 2) + y];
            }
        }
    }
}



void doSomethingForImage() {
  // Choosing the filter by number
  
  cout << "Choose the filter you want to use \n";
  cout << "1- Flip Horizontally or vertically\n"
          "2- Darken or Lighten the image\n"
          "3- black and white\n"
          "4- Invert Image \n"
          "5- Merge image \n"
          "6- Rotate image \n"
          "7- Enlarge quarter \n"
          "8- Shuffle \n"
          "0- Exit \n";

  cin >> filterNumber;
  string flipType = "";
  
  switch(filterNumber) {
  
    case 1:
      cout << "Choose the flipType (h) or (v) \n";
      cin >> flipType;
      flipImage(flipType);
      break;


    case 2:
      adjustDarkeningAndLightening();
      break;


    case 3:
      BW();
      break;
    

    case 4:
      InvertImage();
      break;


    case 5:
      mer();
      break;


    case 6:
      RotateImage();
      break;

    case 7:
      chooseQuarter();
      break;

    case 8:
      shuffleQuarters();
      break;
  }
}



