#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include <stdint.h>
#include <stdbool.h>

void darkenImage(uint_least8_t* imageData, uint_least16_t imageWidth, uint_least16_t imageHeight);

void adjustImageBrightness(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight,
		bool brighten, uint_least8_t adjustmentValue);

void effect(uint_least8_t* iData, uint_least16_t iWidth, uint_least16_t iHeight);


void meanFilter( uint_least8_t* iData, uint_least8_t* oData,
				 uint_least16_t iWidth, uint_least16_t iHeight
			   );

void calculateLevels( uint_least8_t *iData, uint_least16_t iWidth, uint_least16_t iHeight,
					  double* red, double* green, double* blue
					);


#endif /* IMAGEPROCESSING_H_ */
