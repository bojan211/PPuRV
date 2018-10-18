#include "imageProcessing.h"
#include "bmp.h"

const uint_least8_t bwTreshold = 128;
const uint_least8_t darkenFactor = 192;
const int_least16_t brightnessMinimum = 20;
const int_least16_t brightnessMaximum = 220;


void darkenImage(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight)
{
	uint_least16_t i;
	uint_least16_t j;
	uint_least8_t* ptr = iData;
	
	for (i=0; i<iHeight; i++)
	{
		for (j=0; j<iWidth; j++)
		{
			*ptr = *ptr + darkenFactor;
			ptr++;
			*ptr = *ptr + darkenFactor;
			ptr += 1;
			*ptr = *ptr + darkenFactor;
			ptr += 1;
		}
	}
}

void adjustImageBrightness(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight,
		bool brighten, uint_least8_t adjustmentValue)
{
	uint_least32_t i;
	int_least16_t newValue;

	for (i=0; i<iWidth*iHeight*3; i++)
	{
		newValue = iData[i];
		if(brighten)
		{
			newValue += adjustmentValue;
		}
		else
		{
			newValue -= adjustmentValue;
		}

		if(newValue < brightnessMinimum)
		{
			newValue = brightnessMinimum;
		}
		else if(newValue > brightnessMaximum)
		{
			newValue = brightnessMaximum;
		}

		iData[i] = newValue;
	}
}

void effect(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight)
{
	uint_least8_t* ptr = iData;
	uint_least16_t i;
	uint_least16_t j;
	uint_least16_t k;
	
	for (i=0; i<iHeight; i++)
	{
		for (j=0; j<iWidth; j++)
		{
			uint_least16_t sum = 0;
			for (k=0; k<3; k++)
			{
				sum += *(ptr+k);
			}
			sum = sum/3;

			sum = (sum > bwTreshold)?255:0;

			for (k=0; k<3; k++)
			{
				*(ptr+k) = sum;
			}

			ptr += 3;
		}
	}
}


void meanFilter(uint_least8_t* iData, uint_least8_t* oData, uint_least16_t iWidth, uint_least16_t iHeight)
{
	uint_least16_t i;
	uint_least16_t j;
	uint_least16_t k;

	//
	// Set pointer to R component of pixel at position (1,1)
	//
	uint_least8_t* ptrIn = iData + 3*iWidth+3;
	uint_least8_t* ptrOut = oData + 3*iWidth+3;

	for(i=1; i<(iHeight-1); i++)
	{
		for(j=1; j<(iWidth-1); j++)
		{
			for(k=0; k<3; k++)
			{
				//
				// Calculate the sum
				//
				// Example: calculating for G component of pixel at position (1,1)
				//
				//  R00 | G00 | B00 | R01 | G01 | B01 | R02 | G02 | B02 |
				//  R10 | G10 | B10 | R11 | G11 | B11 | R12 | G12 | B12 |
				//  R20 | G20 | B20 | R21 | G21 | B21 | R22 | G22 | B22 |
				//
				uint_least16_t sum = 0;

				// sum += G10 + G11 + G12
				sum += *(ptrIn + k - 3) + *(ptrIn + k) + *(ptrIn + k + 3);
				// sum += G00 + G01 + G02
				sum += *(ptrIn + k - 3 - iWidth*3) + *(ptrIn + k - iWidth*3) + *(ptrIn + k + 3 - iWidth*3);
				// sum += G20 + G21 + G22
				sum += *(ptrIn + k - 3 + iWidth*3) + *(ptrIn + k + iWidth*3) + *(ptrIn + k + 3 + iWidth*3);

				// calculate average value
				sum = sum / 9;

				// store result
				*(ptrOut + k) = sum;
			}
			ptrIn += 3;
			ptrOut += 3;
		}
	}
}


void calculateLevels(uint_least8_t *iData, uint_least16_t iWidth, uint_least16_t iHeight, double* red, double* green, double* blue)
{
	uint_least8_t *ptr = iData;
	uint_least16_t i;
	uint_least16_t j;
	*red = *green = *blue =  0;
	for(i=0; i<iHeight; i++)
	{
		for(j=0; j<iWidth; j++)
		{
			*red   += *(ptr+0);
			*green += *(ptr+1);
			*blue  += *(ptr+2);
			ptr += 3;
		}
	}
	*red   /=(iWidth*iHeight);
	*green /=(iWidth*iHeight);
	*blue  /=(iWidth*iHeight);
}
