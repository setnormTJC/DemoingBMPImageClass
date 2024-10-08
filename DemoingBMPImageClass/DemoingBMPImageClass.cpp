// DemoingBMPImageClass.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include"BMPImage.h"
//#include"C:/Users/Work/Downloads/ImageFileGeneration/BMPImage.h"
//#include"C:/Users/Work/Downloads/ImageFileGeneration/BMPImage.cpp"

int main()
{
    int height = 256; //unit: pixels 
    int width = 128;  

    BMPImage mySpecialImage{ width, height };


    for (int row = 0; row < height; ++row)
    {
        for (int col = 0; col < width; ++col)
        {
            if (col % 3 == 0)
            {
                mySpecialImage.setColor(Color{ 1.0f, 0.0f, 0.0f }, col, row);
            }

            else if (col % 3 == 1)
            {
                mySpecialImage.setColor(Color{ 0.0f, 1.0f, 0.0f }, col, row);
            }

            else
            {
                mySpecialImage.setColor(Color{ 0.0f, 0.0f, 1.0f }, col, row);
            }
    }
}
    //for (int currentRow = 0; currentRow < height; ++currentRow)
    //{
    //    for (int currentCol = 0; currentCol < width; ++currentCol)
    //    {
    //        mySpecialImage.setColor(Color{ 1.0, 0.0, 0.0 }, 0, 0);
    //    }
    //}

    mySpecialImage.ExportBMPFile("mySpecialImage.bmp");


    //int width = 50; 
    //int height = 100; 

    //BMPImage image(width, height);

    //for (int row = 0; row < height; ++row)
    //{
    //    for (int col = 0; col < width; ++col)
    //    {
    //        if (col % 3 == 0)
    //        {
    //            image.setColor(Color{ 1.0f, 0.0f, 0.0f }, col, row);
    //        }

    //        else if (col % 3 == 1)
    //        {
    //            image.setColor(Color{ 0.0f, 1.0f, 0.0f }, col, row);
    //        }

    //        else
    //        {
    //            image.setColor(Color{ 0.0f, 0.0f, 1.0f }, col, row);
    //        }
    //    }
    //}

    //image.ExportBMPFile("out_image.bmp");
}
