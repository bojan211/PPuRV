/*
 ============================================================================
 Name        : e_bitmap.c
 Author      : rt-rk
 Version     :
 Copyright   : Your copyright notice
 Description : image processing example
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "imageProcessing.h"

#define __ARG_NUM__ 2

int main(int argc, char* argv[])
{
	int_least32_t err = 0;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	uint_least8_t* bitmapData;
	uint_least8_t* outputData;

	if ( argc != __ARG_NUM__ )
	{
		printf("Enter input file path");
		return 1;
	}

		printf("Applying brightness\n");	
	bitmapData = LoadBitmapFile(argv[1],&bitmapFileHeader, &bitmapInfoHeader);
	if(!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	// Apply image brightness to image
	adjustImageBrightness(bitmapData, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight, false, 70);
	err = SaveBitmapFile("out_brightness.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, bitmapData);
	if (err) 
	{
		printf("Error trying to save bitmap\n");
	}
	free(bitmapData);

	printf("Applying dark image\n");
	bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	if(!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	darkenImage(bitmapData, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight);
	err = SaveBitmapFile("out_dark.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, bitmapData);
	if (err)
	{
		printf("Error trying to save bitmap\n");
	}
	free(bitmapData);

	printf("Applying effect\n");
	bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	if(!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	effect(bitmapData, bitmapInfoHeader.biWidth,
		bitmapInfoHeader.biHeight);
	err = SaveBitmapFile("out_bw.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, bitmapData);
	if (err) 
	{
		printf("Error trying to save bitmap\n");
	}
	free(bitmapData);
	
	printf("Calculating average values\n");
	bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	if(!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	double levels[3];
	calculateLevels( bitmapData, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight,
					 &levels[0], &levels[1], &levels[2]
				   );

	printf("R = %f, G = %f, B = %f\n", levels[0], levels[1], levels[2]);
	free(bitmapData);

	printf("Applying mean filter\n");
	bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	if(!bitmapData)
	{
		printf("Error! Can't open input bitmap file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	outputData = (uint_least8_t*) malloc( bitmapInfoHeader.biSizeImage );

	// copy input buffer to output buffer
	memcpy( outputData, bitmapData, bitmapInfoHeader.biSizeImage );

	meanFilter( bitmapData, outputData,
			    bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight
			  );
	err = SaveBitmapFile("out_mean.bmp", &bitmapFileHeader,
		&bitmapInfoHeader, outputData);
	if (err)
	{
		printf("Error trying to save bitmap\n");
	}
	free(bitmapData);

	return EXIT_SUCCESS;
}
