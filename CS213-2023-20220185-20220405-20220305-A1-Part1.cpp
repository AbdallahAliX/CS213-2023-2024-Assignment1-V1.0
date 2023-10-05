// FCAI – OOP Programming – 2023 - Assignment 1 
// Program Name:				CS213-2023-20220185-20220405-20220305-A1.cpp
// Last Modification Date:	xx/xx/xxxx
// Author1 and ID and Group:	Abdallah Ali 20220185
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

void loadImage ();
void saveImage ();
void doSomethingForImage ();

int main()
{
  loadImage();
  doSomethingForImage();
  saveImage();
  return 0;
}


void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}


void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}


void doSomethingForImage() {
  //Choosing the filter by number
  string filterNumber ="";
  cout << "Choose the filter you want to use";
  cout << "1- \n" 
          "2- \n"
          "3- \n"
          "4- \n"
          "5- \n"
          "6- \n";
  cin >> filterNumber;
  
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {

    }
  }
}
