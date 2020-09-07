#include "helpers.h"
#include <math.h>

BYTE cap_color(float color)
{
    //if the color is higher than 255
    if (color > 255)
    {
        //return 255
        return 255;
    }
    //return roounded color
    return round(color);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE avg = round((float)(image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3);
            image[h][w].rgbtRed = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE invertedImage[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {

            int trade_position = width - w - 1;
            //keep swap pixel
            RGBTRIPLE temp = image[h][trade_position];

            //set original pixel to swap position
            image[h][trade_position] = image[h][w];

            //set swap pixel to original position
            image[h][w] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //pixel atual >> 6 = image[h][w]
            //h-1
            //1 => 0,0 , w - 1
            //2 => 0,1 , w - 0
            //3 => 0,2 , w + 1

            //h
            //5 => 1,0 , w - 1
            //6 => 1,1 , w - 0
            //7 => 1,2 , w + 1

            //h+1
            // 9 => 2,0 , w - 1
            //10 => 2,1 , w - 0
            //11 => 2,2 , w + 1

            int count = 0, red = 0, green = 0, blue = 0;

            for (int aux_h = h - 1; aux_h <= h + 1 ; aux_h++)
            {
                if (aux_h < 0 || aux_h > height - 1)
                {
                    continue;
                }

                for (int aux_w = w - 1; aux_w  <= w + 1; aux_w++)
                {
                    if (aux_w < 0 || aux_w > width - 1)
                    {
                        continue;
                    }

                    red += image[aux_h][aux_w].rgbtRed;
                    green += image[aux_h][aux_w].rgbtGreen;
                    blue += image[aux_h][aux_w].rgbtBlue;
                    count++;
                }
                new_image[h][w].rgbtRed = cap_color((float) red / count);
                new_image[h][w].rgbtGreen = cap_color((float) green / count);
                new_image[h][w].rgbtBlue = cap_color((float) blue / count);
            }
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = new_image[h][w];
        }
    }
    return;
}

int EDGE_GX[3][3] =
{
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

int EDGE_GY[3][3] =
{
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //pixel atual >> 6 = image[h][w]
            //h-1
            //1 => 0,0 , w - 1
            //2 => 0,1 , w - 0
            //3 => 0,2 , w + 1

            //h
            //5 => 1,0 , w - 1
            //6 => 1,1 , w - 0
            //7 => 1,2 , w + 1

            //h+1
            // 9 => 2,0 , w - 1
            //10 => 2,1 , w - 0
            //11 => 2,2 , w + 1

            int red_gx = 0, green_gx = 0, blue_gx = 0, red_gy = 0, green_gy = 0, blue_gy = 0;

            int edge_h = 0;
            for (int aux_h = h - 1; aux_h <= h + 1 ; aux_h++)
            {
                if (aux_h < 0 || aux_h > height - 1)
                {
                    edge_h++;
                    continue;
                }
                int edge_w = 0;
                for (int aux_w = w - 1; aux_w  <= w + 1; aux_w++)
                {
                    if (aux_w < 0 || aux_w > width - 1)
                    {
                        edge_w++;
                        continue;
                    }
                    
                    red_gx += image[aux_h][aux_w].rgbtRed * EDGE_GX[edge_h][edge_w];
                    red_gy += image[aux_h][aux_w].rgbtRed * EDGE_GY[edge_h][edge_w];
                    green_gx += image[aux_h][aux_w].rgbtGreen * EDGE_GX[edge_h][edge_w];
                    green_gy += image[aux_h][aux_w].rgbtGreen * EDGE_GY[edge_h][edge_w];
                    blue_gx += image[aux_h][aux_w].rgbtBlue * EDGE_GX[edge_h][edge_w];
                    blue_gy += image[aux_h][aux_w].rgbtBlue * EDGE_GY[edge_h][edge_w];
                    
                    edge_w++;

                  
                }
                
                edge_h++;
                
            }
            
            new_image[h][w].rgbtRed = cap_color((float) sqrt(red_gx * red_gx + red_gy * red_gy));
            new_image[h][w].rgbtGreen = cap_color((float) sqrt(green_gx * green_gx + green_gy * green_gy));
            new_image[h][w].rgbtBlue = cap_color((float) sqrt(blue_gx * blue_gx + blue_gy * blue_gy));
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = new_image[h][w];
        }
    }
    return;
}
