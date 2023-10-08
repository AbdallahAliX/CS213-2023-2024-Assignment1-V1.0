// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				CS213-2023-20220185-20220405-20220305-A1.cpp
// Author1 and ID and Group:	Abdallah Mohamed 20220185
// Author2 and ID and Group:	Youssef Mohamed 20220405
// Author3 and ID and Group:	Mohamed Maged 20220305
// Purpose: Adding filters to a gray scale image

#include <iostream>
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
void nineteydegree();
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




<<<<<<< HEAD
void doSomethingForImage()
{

=======
void doSomethingForImage() {
>>>>>>> 1070c0104724fb141fb3ab90115ace3ac87d3931
  // Choosing the filter by number
  cout << "Choose the filter you want to use \n";
  cout << "1- Flip Horizontally or vertically\n"
          "2- Darken or Lighten the image\n"
          "3- black and white\n"
          "4- Invert Image \n"
          "5- Merge image \n"
          "6- Rotate image \n"
          "0- Exit \n";

  cin >> filterNumber;
  string flipType = "";
  
  switch(filterNumber) {
  
    case 0:
      break;

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
<<<<<<< HEAD
  }
=======


    case 5:
        mer();
        break;
>>>>>>> 1070c0104724fb141fb3ab90115ace3ac87d3931


    case 6:
        void RotateImage();
        break;

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