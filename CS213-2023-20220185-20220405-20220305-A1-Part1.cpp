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


void loadImage (unsigned char image[SIZE][SIZE]);
void saveImage (unsigned char image[SIZE][SIZE]);
void flipImage(string flipType);
void adjustDarkeningAndLightening();
void doSomethingForImage();
void BW();
void InvertImage();
void Merge();
void RotateImage();
void ninetydegree();
void enlargeQuarter(int x, int y, int newSIZE);
void shuffleQuarters();
void skewRight();
void skewImageHorizontally();
void SkewVertically();
void detect_edge();
void shrink();
void mirror();
void leftMirror();
void rightMirror();
void upperMirror() ;
void lowerMirror();
void blur();
void cut_square();

int main() {
  loadImage(image);
  doSomethingForImage();
  saveImage(image);
  return 0;
}


void loadImage (unsigned char image[SIZE][SIZE]) {
  char imageFileName[100];

  // Get gray scale image file name
  cout << "Enter the source image file name: ";
  cin >> imageFileName;

  // Add to it .bmp extension and load image
  strcat(imageFileName, ".bmp");
  readGSBMP(imageFileName, image);
}

void saveImage (unsigned char image[SIZE][SIZE]){
 
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
  }


void doSomethingForImage() {
 bool state = true;
 while (state) {
  // Choosing the filter by number
  cout << "Choose the filter you want to use \n";
  cout << "1- Black and White\n"
          "2- InvertImage\n"
          "3- Merge\n"
          "4- FlipImage \n"
          "5- RotateImage\n"
          "6- Darken and Lighten Image \n"
          "7- Detect Image Edges \n"
          "8- Enlarge Image \n"
          "9- Shrink Image \n"
          "a- Mirror Image \n"
          "b- Shuffle Image \n"
          "c- Blur Image \n"
          "d- CropImage \n"
          "e- Skew Image Horizontally\n"
          "f- Skew Image Vertically\n"
          "0- Exit \n";


  char filterNumber; cin >> filterNumber;
  string flipType = "";

  switch (filterNumber) {

  default:
    state = false;
    break;

  case '1':
    BW();
    break;
    
  case '2':
    InvertImage();
    break;

  case '3':
    Merge();
    break;

  case '4':
    cout << "Choose the flipType (h) or (v) \n";
    cin >> flipType;
    flipImage(flipType);
    break;


  case '5':
    RotateImage();
    break;

  case '6':
    adjustDarkeningAndLightening();
    break;

  case '7':
    detect_edge();
    break;

  case '8':
    enlargeQuarter(10 , 20 , 30);
    break;

  case '9':
    shrink();
    break;
  
  case 'a':
    mirror();
    break;
  
  case 'b':
    shuffleQuarters();
    break;
  
  case 'c':
    blur();
    break;

  case 'd':
    cut_square();
    break;

  case 'e':
    skewImageHorizontally();
    break;

  case 'f':
    SkewVertically();
    break;
}

}

}


void BW() { // function to turn image to black and white

  for (int i = 0; i < SIZE; i++)
  {

    for (int j = 0; j < SIZE; j++)
    {

      if (int(image[i][j]) > 127)
      {
        image[i][j] = char(255);
      } // if the pixel gray level is bigger than the average gray level
        //: set the pixel to black

      else
      {
        image[i][j] = char(0);
      } // else : set it to white
    }
  }
}


void InvertImage() { // function to invert an image

  for (int i = 0; i < SIZE; i++)
  {

    for (int j = 0; j < SIZE; j++)
    {

      image[i][j] = char(255 - int(image[i][j])); // subtract 255 from the pixel gray level to invert it ( if the pixel is white it will turn to black
                                                  // and the opposite)
    }
  }
}


void Merge(){

  unsigned char image2[SIZE][SIZE];
  loadImage(image2);

  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image[i][j] = (image[i][j] + image2[i][j]) / 2;
    }
  }
}


void flipImage(string flipType) {
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



void RotateImage() {

  int rotation;
  cout << "please enter rotation \n"
          "1- 90 degree\n"
          "2- 180 degree\n"
          "3- 270 degree\n";

  cin >> rotation;

  while (rotation--)
  {

    ninetydegree();
  }
}

void ninetydegree() {

  unsigned char image3[SIZE][SIZE];

  for (int i = 0; i < SIZE; i++) {

    for (int j = 0; j < SIZE; j++)
    {

      image3[i][j] = image[SIZE - 1 - j][i];
    }
  }

  swap(image3, image);
}


void adjustDarkeningAndLightening() {
  // Brightness is a user input that if negative darkens the image while if positive lightens it with the amount that user entered
  int Brightness;

  cout << "Enter the brightness adjustment value (positive for lighten, negative for darken): ";
  cin >> Brightness;

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      // Adjust the pixel intensity
      int newIntensity = static_cast<int>(image[i][j]) + Brightness;
      // Ensure the intensity stays within the valid range [0, 255]
      newIntensity = max(0, min(255, newIntensity));
      // Update the pixel intensity
      image[i][j] = static_cast<unsigned char>(newIntensity);
    }
  }
}


void detect_edge(){
    unsigned char arr[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            arr[i][j] = image[i][j];
        }
    }

    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            int x = 2*arr[i][j-1] - 2*arr[i][j+1] + arr[i-1][j-1] - arr[i-1][j+1] + arr[i+1][j-1] - arr[i+1][j+1];
            int y = 2*arr[i+1][j] - 2*arr[i-1][j] + arr[i+1][j-1] - arr[i-1][j-1] + arr[i+1][j+1] - arr[i-1][j+1];

            if (abs(x) > 100 || abs(y) > 100) {
                image[i][j] = 0;
            }
            else {
                image[i][j] = 255;      
        } 
    }

  }
}


void enlargeQuarter(int x, int y, int newSIZE) {
  unsigned char enlargedQuarter[SIZE][SIZE];

  // Calculate scaling factor
  int scale = SIZE / newSIZE;

  // Iterate over each pixel in the new image
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      // Calculate corresponding position in the original quarter
      int quarterI = i / scale;
      int quarterJ = j / scale;

      // Copy pixel values from the chosen quarter to the new image
      enlargedQuarter[i][j] = image[x + quarterI][y + quarterJ];
    }
  }

  // Copy the enlarged quarter to the original image
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image[i][j] = enlargedQuarter[i][j];
    }
  }
}

void shrink() {

unsigned char image2 [SIZE][SIZE] ;

for ( int i = 0 ; i < SIZE ; i++ ) {
  for ( int j = 0 ; j <  SIZE ; j++) {
     image2[i][j] = 255;
  }
}

  string target_size ;  int block;
  cout << "enter shrink size : (1/2 , 1/3 , 1/4)";
  cin >> target_size;
  
  if ( target_size == "1/2") block = 2; // when shrinking the image to 1/2 its dimensions 
  //: the average of every 2 x 2 blocks  = 1 pixel in the new image 

  else if (target_size == "1/3") block = 3;// when shrinking the image to 1/3 its dimensions 
  //: the average of every 3 x 3 blocks  = 1 pixel in the new image 

  else if (target_size == "1/4") block = 4;// when shrinking the image to 1/4 its dimensions 
  //: the average of every 4 x 4 blocks  = 1 pixel in the new image 

  else  cout << "invalid number. please choose again";
    
   

  for ( int i = 0 ; i < SIZE ; i += block ) {  //looping on the original image by block * block , every time increase the index by block 
      for ( int j = 0 ; j < SIZE ; j += block) {

          int sum = 0 ;

          for (int x = i ; x < i + block ; x++) {
            for ( int y = j ; y < j + block ; y++) {
                 
                 sum += image[x][y];   //calculating the sum  of every block x block (4 x 4 or 2x2 or 3x3)
            } 

          }

          // calculating the average of every block x block and dividing 
          //it by the number of pixels then assigning the result to the new pixel in the new image 
          int average = sum / (block * block) ;
          image2[ i / block][ j / block] = char(average); 
          
      }
  }

  swap (image2, image);
}


void mirror(){
    int choice;
    cout<<"Mirror 1-left, 2-right, 3-upper, 4-Down ?"<<endl;
    cin>>choice;
    if (choice==1)
        leftMirror();
    else if(choice==2)
        rightMirror();
    else if(choice==3)
        upperMirror();
    else if(choice==4)
        lowerMirror();
}


void leftMirror(){
    for (int i=0;i<SIZE;i++){

          for (int j=0;j<SIZE/2;j++){
                image[i][SIZE-j-1]=image[i][j];
          }
    }
}


void rightMirror(){
    for (int i=0;i<SIZE;i++){

        for (int j=0;j<SIZE/2;j++){
              image[i][j]=image[i][SIZE-j-1];
        }
    }
}


void upperMirror() {

  for (int i=0;i<SIZE/2;i++) {

        for (int j=0;j<SIZE;j++) {
            image[SIZE-i-1][j]=image[i][j];
        }
  }
 
}



void lowerMirror(){

     for (int i=0;i<SIZE/2;i++){
        for (int j=0;j<SIZE;j++){
            image[i][j]=image[SIZE-i-1][j];
        }
     }
}




void chooseQuarter() {
  // Enlarge one of the four quarters into a new image
  int quarter;
  cout << "Choose a quarter to enlarge (1, 2, 3, or 4): ";
  cin >> quarter;

  // Enlarge the specified quarter into a new image
  if (quarter == 1)
  {
    enlargeQuarter(0, 0, SIZE / 2);
  }
  else if (quarter == 2)
  {
    enlargeQuarter(0, SIZE / 2, SIZE / 2);
  }
  else if (quarter == 3)
  {
    enlargeQuarter(SIZE / 2, 0, SIZE / 2);
  }
  else if (quarter == 4)
  {
    enlargeQuarter(SIZE / 2, SIZE / 2, SIZE / 2);
  }
  else
  {
    cout << "Invalid quarter choice.\n";
  }
}


void shuffleQuarters() {
  // Quarters order based on user input
  int order[] = {0, 0, 0, 0};

  // Get user input for quarter order
  cout << "Enter the order of quarters (1, 2, 3, 4): ";
  for (int i = 0; i < 4; ++i)
  {
    cin >> order[i];
  }

  // Validate user input
  bool validOrder = true;
  for (int i = 1; i <= 4; ++i)
  {
    if (find(begin(order), end(order), i) == end(order))
    {
      cout << "Invalid order. Please enter each quarter number exactly once.\n";
      validOrder = false;
      break;
    }
  }

  if (!validOrder)
  {
    return;
  }

  // Create a copy of the original image for shuffling
  unsigned char shuffledImage[SIZE][SIZE];
  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      shuffledImage[i][j] = image[i][j];
    }
  }

  // Shuffle the quarters based on user input
  for (int i = 0; i < 4; ++i)
  {
    int newRow = i / 2;
    int newCol = i % 2;

    int originalRow = (order[i] - 1) / 2;
    int originalCol = (order[i] - 1) % 2;

    for (int x = 0; x < SIZE / 2; ++x)
    {
      for (int y = 0; y < SIZE / 2; ++y)
      {
        image[newRow * (SIZE / 2) + x][newCol * (SIZE / 2) + y] = shuffledImage[originalRow * (SIZE / 2) + x][originalCol * (SIZE / 2) + y];
      }
    }
  }
}



void blur() {

// applying box blur
int kernal_size = 5 ; // the size of the box blur matrix

double kernal_value = 1.0 / (kernal_size * kernal_size); // the value of each element in the box blur matrix

  unsigned char blurred_matrix[SIZE][SIZE];
 
  for ( int i = 0 ; i < SIZE ; i++) {
      
    for( int j = 0 ; j < SIZE ; j++) {
      double sum = 0.0;
      int count = 0 ;

      for (int ki = 0 ; ki < kernal_size ; ki++) {
        for ( int kj = 0 ; kj < kernal_size ; kj++) { 
          
          // multiplying every element in the original matrix by the corresponding element in the box blur matrix 
          //and summing every neighbor element
          
          if( i > 0 && i < SIZE && j > 0 && j < SIZE){
              int ni = i + ki - (kernal_size / 2) ;
              int nj = j + kj - (kernal_size / 2);
              sum += image[ni][nj];
              count ++ ;
            }
        }

     }

      blurred_matrix[i][j] = sum / count;

  }
 }
   saveImage(blurred_matrix);
}


void cut_square() {
  
  int x , y , l , w;
  cout << "enter position x and y :\n";
  cin >> x >> y;
  cout << "enter the length and width of the square to keep :";
  cin >> l >> w;

  unsigned char image2[SIZE][SIZE];

  for (int i = 0; i < SIZE; i++) {

    for (int j = 0; j < SIZE; j++) {

        if (i >= x && i < x + l && j >= y && j < y + w) {
            image2[i][j] = image[i][j];
        }

        else {
            image2[i][j] = 255;
        }
    }

  }   
    swap(image2,image);
}




void skewImageHorizontally()
{

  unsigned char shrunkImage[SIZE][SIZE];

  double angle;
  cout << "Enter the angle: ";
  cin >> angle;
  angle = (angle * 22) / (180 * 7);
  double scaleFactor = (1 + (1 / tan(angle)));

  // Calculate the dimensions of the shrunk image
  int newWidth = SIZE / scaleFactor;
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      shrunkImage[i][j] = 255;

  // Iterate over each pixel in the shrunk image
  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = 0; j < newWidth; ++j)
    {
      // Calculate the corresponding position in the original image
      int originalJ = j * scaleFactor;

      // Copy pixel values from the original image to the shrunk image
      shrunkImage[i][j] = image[i][originalJ];
    }
  }

  // Copy the shrunk image to the original image
  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      image[i][j] = shrunkImage[i][j];
    }
  }

  double mov = SIZE - (SIZE / scaleFactor); // calculate the number of pixels to move
  double step = mov / SIZE; // calculate the step to move each pixel
  unsigned char img_in[SIZE][SIZE + (int)mov]; 
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      img_in[i][j] = 255;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      img_in[i][j + (int)mov] = image[i][j]; 
    }
    mov -= step;
  }
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      image[i][j] = img_in[i][j]; // copy the image to the original image
    }
  }
}


void SkewVertically() {


    unsigned char shrunkImage[SIZE][SIZE];
    double angle;    cout << "Enter the angle: ";
    cin >> angle;
    angle = ( angle * 22 ) / ( 180 * 7 );
    double scaleFactor = (1+(1/tan(angle)));

    // Calculate the dimensions of the shrunk image
    int newHeight = SIZE / scaleFactor;
        for ( int i = 0 ; i < SIZE ; i++ )
          for ( int j = 0 ; j < SIZE ; j++ )
            shrunkImage[i][j] = 255 ;

    // Iterate over each pixel in the shrunk image
    for (int i = 0; i < newHeight; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // Calculate the corresponding position in the original image
            int originalI = i * scaleFactor;

            // Copy pixel values from the original image to the shrunk image
            shrunkImage[i][j] = image[originalI][j];
        }
    }


    for ( int i = 0 ; i < SIZE ; i++ ) {

        for ( int j = 0 ; j < SIZE ; j++ ) {
            image[i][j] = shrunkImage[i][j] ;
        }
}


    double mov = SIZE -(SIZE / scaleFactor) ;
    double step = mov / SIZE ; 
    unsigned char img_in[SIZE + (int)mov][SIZE];

    for ( int i = 0 ; i < SIZE ; i++ ) {
        for ( int j = 0 ; j < SIZE ; j++ ) {
            img_in[i][j] = 255 ;
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ) {
        mov = SIZE -(SIZE / scaleFactor) ;
        for ( int j = 0 ; j < SIZE ; j++ ) {
            img_in[i +(int)mov][j] =  image[i][j];
            mov-=step;
        }
    
}
      for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            image[i][j] = img_in[i][j];
}
    }

}

