#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8

int read_bmp(FILE *f, unsigned char **image);
void write_bmp(FILE *f, unsigned char *image);
void rgb_to_yuv420(unsigned char rgb[16][48], unsigned char y[16][16], unsigned char u[8][8], unsigned char v[8][8]);
void yuv420_to_rgb(unsigned char y[16][16], unsigned char u[8][8], unsigned char v[8][8], unsigned char rgb[16][48]);

void convert_rgb_to_yuv420();
void convert_yuv420_to_rgb();
void extend_borders();
void perform_filtering();

int XSIZE, YSIZE;
unsigned char *rgb_pic;
unsigned char *y_pic;
unsigned char *y_pic2;
unsigned char *u_pic;
unsigned char *v_pic;
unsigned char rgb_buff[16][48];
unsigned char y_buff[16][16];
unsigned char y_buff11x11[11][11];
unsigned char y_buff8x8[8][8];
unsigned char u_buff[8][8];
unsigned char v_buff[8][8];
short dct_coefs[8][8];
short dct_coefs2[8][8];


int main(int argc, char **argv)
{
  FILE *f;

  if (argc != 3)
  {
    printf("You must specify input and output file\n");
    return -1;
  }

  f = fopen(argv[1], "rb");
  if (read_bmp(f, &rgb_pic) == 0)
  {
    printf("Error loading input file\n");
    return -1;
  }
  fclose(f);

  if ((XSIZE & 0xf) | (YSIZE & 0xf))
  {
    printf("Image size must be a multiple of 16x16\n");
    return -1;
  }

  y_pic = (unsigned char *)malloc((XSIZE+16)*(YSIZE+16));
  y_pic2 = (unsigned char *)malloc((XSIZE+16)*(YSIZE+16));
  u_pic = (unsigned char *)malloc((XSIZE+16)*(YSIZE+16)/4);
  v_pic = (unsigned char *)malloc((XSIZE+16)*(YSIZE+16)/4);

  convert_rgb_to_yuv420();
  extend_borders();
  perform_filtering();
  convert_yuv420_to_rgb();

  f = fopen(argv[2], "wb");
  write_bmp(f, rgb_pic);
  fclose(f);

  free(rgb_pic);
  free(y_pic);
  free(y_pic2);
  free(u_pic);
  free(v_pic);

  return 0;
}

void convert_rgb_to_yuv420()
{
  int x, y, i, j;

  for (y=0; y<YSIZE/16; y++)
  {
    for (x=0; x<XSIZE/16; x++)
    {
      for (j=0; j<16; j++)
      {
        for (i=0; i<48; i++)
        {
          rgb_buff[j][i] = rgb_pic[(16*y+j)*3*XSIZE+48*x+i];
        }
      }

      rgb_to_yuv420(rgb_buff, y_buff, u_buff, v_buff);

      for (j=0; j<8; j++)
      {
        for (i=0; i<8; i++)
        {
          y_pic[(16*y+2*j+8)*(XSIZE+16)+16*x+2*i+8] = y_buff[2*j][2*i];
          y_pic[(16*y+2*j+8)*(XSIZE+16)+16*x+2*i+9] = y_buff[2*j][2*i+1];
          y_pic[(16*y+2*j+9)*(XSIZE+16)+16*x+2*i+8] = y_buff[2*j+1][2*i];
          y_pic[(16*y+2*j+9)*(XSIZE+16)+16*x+2*i+9] = y_buff[2*j+1][2*i+1];
          u_pic[(8*y+j+4)*(XSIZE/2+8)+8*x+i+4] = u_buff[j][i];
          v_pic[(8*y+j+4)*(XSIZE/2+8)+8*x+i+4] = v_buff[j][i];
        }
      }
    }
  }
}

void convert_yuv420_to_rgb()
{
  int x, y, i, j;

  for (y=0; y<YSIZE/16; y++)
  {
    for (x=0; x<XSIZE/16; x++)
    {
      for (j=0; j<8; j++)
      {
        for (i=0; i<8; i++)
        {
          y_buff[2*j  ][2*i  ] = y_pic2[(16*y+2*j+8)*(XSIZE+16)+16*x+2*i+8];
          y_buff[2*j  ][2*i+1] = y_pic2[(16*y+2*j+8)*(XSIZE+16)+16*x+2*i+9];
          y_buff[2*j+1][2*i  ] = y_pic2[(16*y+2*j+9)*(XSIZE+16)+16*x+2*i+8];
          y_buff[2*j+1][2*i+1] = y_pic2[(16*y+2*j+9)*(XSIZE+16)+16*x+2*i+9];
          u_buff[j][i] = u_pic[(8*y+j+4)*(XSIZE/2+8)+8*x+i+4];
          v_buff[j][i] = v_pic[(8*y+j+4)*(XSIZE/2+8)+8*x+i+4];
        }
      }

      yuv420_to_rgb(y_buff, u_buff, v_buff, rgb_buff);

      for (j=0; j<16; j++)
      {
        for (i=0; i<48; i++)
        {
          rgb_pic[(16*y+j)*3*XSIZE+48*x+i] = rgb_buff[j][i];
        }
      }
    }
  }
}

void extend_borders()
{
  int i;

  for (i=0; i<8; i++)
  {
    memcpy(&y_pic[i*(XSIZE+16)+8], &y_pic[8*(XSIZE+16)+8], XSIZE);
    memcpy(&y_pic[(YSIZE+8+i)*(XSIZE+16)+8], &y_pic[(YSIZE+7)*(XSIZE+16)+8], XSIZE);
  }

  for (i=0; i<YSIZE+16; i++)
  {
    memset(&y_pic[i*(XSIZE+16)], y_pic[i*(XSIZE+16)+8], 8);
    memset(&y_pic[i*(XSIZE+16)+XSIZE+8], y_pic[i*(XSIZE+16)+XSIZE+7], 8);
  }

  for (i=0; i<4; i++)
  {
    memcpy(&u_pic[i*(XSIZE/2+8)+4], &u_pic[4*(XSIZE/2+8)+4], XSIZE/2);
    memcpy(&u_pic[(YSIZE/2+4+i)*(XSIZE/2+8)+4], &u_pic[(YSIZE/2+3)*(XSIZE/2+8)+4], XSIZE/2);
    memcpy(&v_pic[i*(XSIZE/2+8)+4], &v_pic[4*(XSIZE/2+8)+4], XSIZE/2);
    memcpy(&v_pic[(YSIZE/2+4+i)*(XSIZE/2+8)+4], &v_pic[(YSIZE/2+3)*(XSIZE/2+8)+4], XSIZE/2);
  }

  for (i=0; i<YSIZE/2+8; i++)
  {
    memset(&u_pic[i*(XSIZE/2+8)], u_pic[i*(XSIZE/2+8)+4], 4);
    memset(&u_pic[i*(XSIZE/2+8)+XSIZE/2+4], u_pic[i*(XSIZE/2+8)+XSIZE/2+3], 4);
    memset(&v_pic[i*(XSIZE/2+8)], v_pic[i*(XSIZE/2+8)+4], 4);
    memset(&v_pic[i*(XSIZE/2+8)+XSIZE/2+4], v_pic[i*(XSIZE/2+8)+XSIZE/2+3], 4);
  }
}

void perform_filtering_old()
{
  int x, y, dx, dy;
  int sum, avg, pixel;

  for (y=0; y<YSIZE; y+= N)
  {
    for (x=0; x<XSIZE; x+= N)
    {
        sum = 0;
        for( dy=0; dy<N; dy++)
        {
            for( dx=0; dx<N; dx++)
            {
                pixel = y_pic[(y + dy + 8)*(XSIZE + 16) + (x + dx + 8)];
                sum += pixel;
            }
        }

        avg = sum / (N * N);

            // Write new big pixel value
        for( dy=0; dy<N; dy++)
        {
            for( dx=0; dx<N; dx++)
            {
                y_pic2[(y + dy + 8)*(XSIZE + 16) + (x + dx + 8)] = avg;
            }
        }
    }
  }
}

void perform_filtering()
{
  int x, y;

  for (y=0; y<YSIZE; y+= N)
  {
    for (x=0; x<XSIZE; x+= N)
    {
    	pixelation(&y_pic[(y+8)*(XSIZE+16)+x+8],&y_pic2[(y+8)*(XSIZE+16)+x+8], XSIZE+16);
    }
  }
}

#pragma pack(2)
typedef struct
{
   short  bfType;  /* always 'BM' */
   int    bfSize;  /* size of bitmap file in bytes */
   short  bfReserved1; /* always 0 */
   short  bfReserved2; /* always 0 */
   int    bfOffBits;   /* offset to data for bitmap */
   int    biSize; 
   int    biWidth; 
   int    biHeight; 
   short  biPlanes; 
   short  biBitCount;
   int    biCompression;
   int    biSizeImage; 
   int    biXPelsPerMeter; 
   int    biYPelsPerMeter; 
   int    biClrUsed; 
   int    biClrImportant; 
} BITMAPFILEHEADER; 
#pragma pack(4)

int read_bmp(FILE *f, unsigned char **image)
{
  BITMAPFILEHEADER bmhdr;

  if (f == NULL)
    return 0;

  fread(&bmhdr, sizeof(bmhdr), 1, f);

  if (bmhdr.bfType != 0x4d42)
    return 0;

  XSIZE = bmhdr.biWidth;
  YSIZE = bmhdr.biHeight;
  if (YSIZE < 0)
    YSIZE = -YSIZE;

  *image = (unsigned char *)malloc(XSIZE*YSIZE*3);
  fread(*image, 1, XSIZE*YSIZE*3, f);

  return 1;
}

void write_bmp(FILE *f, unsigned char *image)
{
  BITMAPFILEHEADER bmhdr = { 0x4d42, 3*XSIZE*YSIZE+54, 0, 0, 54, 40, XSIZE, YSIZE, 1, 24, 0, 0, 100, 100, 0, 0};

	if (f)
	{
		fwrite(&bmhdr, 54, 1, f);
		fwrite(image, 1, 3*XSIZE*YSIZE, f);
	}
}

void rgb_to_yuv420(unsigned char rgb[16][48], unsigned char y[16][16], unsigned char u[8][8], unsigned char v[8][8])
{
  int i, j;
  int Y, U, V;

  for (j=0; j<8; j++)
  {
    for (i=0; i<8; i++)
    {
       Y =   66 * rgb[2*j][6*i+2] + 129 * rgb[2*j][6*i+1] +  25 * rgb[2*j][6*i];
       U = - 38 * rgb[2*j][6*i+2] -  74 * rgb[2*j][6*i+1] + 112 * rgb[2*j][6*i];
       V =  112 * rgb[2*j][6*i+2] -  94 * rgb[2*j][6*i+1] -  18 * rgb[2*j][6*i];

       Y = (Y + 128) >> 8;
       y[2*j][2*i] = Y + 16;

       Y  =   66 * rgb[2*j][6*i+5] + 129 * rgb[2*j][6*i+4] +  25 * rgb[2*j][6*i+3];
       U += - 38 * rgb[2*j][6*i+5] -  74 * rgb[2*j][6*i+4] + 112 * rgb[2*j][6*i+3];
       V +=  112 * rgb[2*j][6*i+5] -  94 * rgb[2*j][6*i+4] -  18 * rgb[2*j][6*i+3];

       Y = (Y + 128) >> 8;
       y[2*j][2*i+1] = Y + 16;

       Y  =   66 * rgb[2*j+1][6*i+2] + 129 * rgb[2*j+1][6*i+1] +  25 * rgb[2*j+1][6*i];
       U += - 38 * rgb[2*j+1][6*i+2] -  74 * rgb[2*j+1][6*i+1] + 112 * rgb[2*j+1][6*i];
       V +=  112 * rgb[2*j+1][6*i+2] -  94 * rgb[2*j+1][6*i+1] -  18 * rgb[2*j+1][6*i];

       Y = (Y + 128) >> 8;
       y[2*j+1][2*i] = Y + 16;

       Y  =   66 * rgb[2*j+1][6*i+5] + 129 * rgb[2*j+1][6*i+4] +  25 * rgb[2*j+1][6*i+3];
       U += - 38 * rgb[2*j+1][6*i+5] -  74 * rgb[2*j+1][6*i+4] + 112 * rgb[2*j+1][6*i+3];
       V +=  112 * rgb[2*j+1][6*i+5] -  94 * rgb[2*j+1][6*i+4] -  18 * rgb[2*j+1][6*i+3];

       Y = (Y + 128) >> 8;
       y[2*j+1][2*i+1] = Y + 16;

       U = (U + 512) >> 10;
       u[j][i] = U + 128;

       V = (V + 512) >> 10;
       v[j][i] = V + 128;
    }
  }
}

void yuv420_to_rgb(unsigned char y[16][16], unsigned char u[8][8], unsigned char v[8][8], unsigned char rgb[16][48])
{
  int i, j, Y, U, V, UV, r, g, b;
    
  for (j=0; j<8; j++)
  {
    for (i=0; i<8; i++)
    {
      U = u[j][i] - 128;
      V = v[j][i] - 128;

      UV = -6657 * U - 13424 * V;
      U = 33311 * U;
      V = 26355 * V;

      Y = 19077 * (y[2*j][2*i] - 16);

      r = (Y + V) >> 14;
      if (r < 0)
        r = 0;
      else if (r > 255)
        r = 255;
      g = (Y + UV) >> 14;
      if (g < 0)
        g = 0;
      else if (g > 255)
        g = 255;
      b = (Y + U) >> 14;
      if (b < 0)
        b = 0;
      else if (b > 255)
        b = 255;

      rgb[2*j][6*i  ] = b;
      rgb[2*j][6*i+1] = g;
      rgb[2*j][6*i+2] = r;

      Y = 19077 * (y[2*j][2*i+1] - 16);

      r = (Y + V) >> 14;
      if (r < 0)
        r = 0;
      else if (r > 255)
        r = 255;
      g = (Y + UV) >> 14;
      if (g < 0)
        g = 0;
      else if (g > 255)
        g = 255;
      b = (Y + U) >> 14;
      if (b < 0)
        b = 0;
      else if (b > 255)
        b = 255;

      rgb[2*j][6*i+3] = b;
      rgb[2*j][6*i+4] = g;
      rgb[2*j][6*i+5] = r;

      Y = 19077 * (y[2*j+1][2*i] - 16);

      r = (Y + V) >> 14;
      if (r < 0)
        r = 0;
      else if (r > 255)
        r = 255;
      g = (Y + UV) >> 14;
      if (g < 0)
        g = 0;
      else if (g > 255)
        g = 255;
      b = (Y + U) >> 14;
      if (b < 0)
        b = 0;
      else if (b > 255)
        b = 255;

      rgb[2*j+1][6*i  ] = b;
      rgb[2*j+1][6*i+1] = g;
      rgb[2*j+1][6*i+2] = r;

      Y = 19077 * (y[2*j+1][2*i+1] - 16);

      r = (Y + V) >> 14;
      if (r < 0)
        r = 0;
      else if (r > 255)
        r = 255;
      g = (Y + UV) >> 14;
      if (g < 0)
        g = 0;
      else if (g > 255)
        g = 255;
      b = (Y + U) >> 14;
      if (b < 0)
        b = 0;
      else if (b > 255)
        b = 255;

      rgb[2*j+1][6*i+3] = b;
      rgb[2*j+1][6*i+4] = g;
      rgb[2*j+1][6*i+5] = r;
    }
  }
}
