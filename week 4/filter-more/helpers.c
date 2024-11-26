#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = round(((float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE tmpB;
    BYTE tmpG;
    BYTE tmpR;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            tmpB = image[i][j].rgbtBlue;
            tmpG = image[i][j].rgbtGreen;
            tmpR = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = tmpB;
            image[i][width - j - 1].rgbtGreen = tmpG;
            image[i][width - j - 1].rgbtRed = tmpR;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            copy[a][b].rgbtBlue = image[a][b].rgbtBlue;
            copy[a][b].rgbtGreen = image[a][b].rgbtGreen;
            copy[a][b].rgbtRed = image[a][b].rgbtRed;
        }
    }


    float avgB;
    float avgG;
    float avgR;
    int pxlCount;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avgB = 0;
            avgG = 0;
            avgR = 0;
            pxlCount = 0;

            for (int k = -1; k <= 1; k++)
            {
                if (i + k < 0 || i + k > height - 1)
                {
                    continue;
                }

                for (int l = -1; l <= 1; l++)
                {
                    if (j + l < 0 || j + l > height - 1) {
                        continue;
                    }
                    avgB += copy[i + k][j + l].rgbtBlue;
                    avgG += copy[i + k][j + l].rgbtGreen;
                    avgR += copy[i + k][j + l].rgbtRed;
                    pxlCount++;
                }
            }

            image[i][j].rgbtBlue = round(avgB / pxlCount);
            image[i][j].rgbtGreen = round(avgG / pxlCount);
            image[i][j].rgbtRed = round(avgR / pxlCount);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            copy[a][b].rgbtBlue = image[a][b].rgbtBlue;
            copy[a][b].rgbtGreen = image[a][b].rgbtGreen;
            copy[a][b].rgbtRed = image[a][b].rgbtRed;
        }
    }

    float RedGx;
    float RedGy;
    float GreenGx;
    float GreenGy;
    float BlueGx;
    float BlueGy;

    float RedSum;
    float GreenSum;
    float BlueSum;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RedGx = 0;
            RedGy = 0;
            GreenGx = 0;
            GreenGy = 0;
            BlueGx = 0;
            BlueGy = 0;

            RedSum = 0;
            GreenSum = 0;
            BlueSum = 0;

            for (int k = -1; k <= 1; k++)
            {
                if (i + k < 0 || i + k > height - 1)
                {
                    continue; // if out of the edge, continue
                }

                for (int l = -1; l <= 1; l++)
                {
                    if (j + l < 0 || j + l > height - 1)
                    {
                        continue; // if out of the edge, continue
                    }

                    // Gx and Gy kernels
                    switch (l)
                    {
                        case -1:
                            RedGx += (k == 0) ? (copy[i + k][j + l].rgbtRed * -2) : (copy[i + k][j + l].rgbtRed * -1);
                            GreenGx += (k == 0) ? (copy[i + k][j + l].rgbtGreen * -2) : (copy[i + k][j + l].rgbtGreen * -1);
                            BlueGx += (k == 0) ? (copy[i + k][j + l].rgbtBlue * -2) : (copy[i + k][j + l].rgbtBlue * -1);
                            break;
                        case 0:
                            break;
                        case 1:
                            RedGx += (k == 0) ? (copy[i + k][j + l].rgbtRed * 2) : (copy[i + k][j + l].rgbtRed * 1);
                            GreenGx += (k == 0) ? (copy[i + k][j + l].rgbtGreen * 2) : (copy[i + k][j + l].rgbtGreen * 1);
                            BlueGx += (k == 0) ? (copy[i + k][j + l].rgbtBlue * 2) : (copy[i + k][j + l].rgbtBlue * 1);
                            break;
                    }

                    switch (k)
                    {
                        case -1:
                            RedGy += (l == 0) ? (copy[i + k][j + l].rgbtRed * -2) : (copy[i + k][j + l].rgbtRed * -1);
                            GreenGy += (l == 0) ? (copy[i + k][j + l].rgbtGreen * -2) : (copy[i + k][j + l].rgbtGreen * -1);
                            BlueGy += (l == 0) ? (copy[i + k][j + l].rgbtBlue * -2) : (copy[i + k][j + l].rgbtBlue * -1);
                            break;
                        case 0:
                            break;
                        case 1:
                            RedGy += (l == 0) ? (copy[i + k][j + l].rgbtRed * 2) : (copy[i + k][j + l].rgbtRed * 1);
                            GreenGy += (l == 0) ? (copy[i + k][j + l].rgbtGreen * 2) : (copy[i + k][j + l].rgbtGreen * 1);
                            BlueGy += (l == 0) ? (copy[i + k][j + l].rgbtBlue * 2) : (copy[i + k][j + l].rgbtBlue * 1);
                            break;
                    }
                }
            }

            // sum of each color
            BlueSum = round(sqrt(pow(BlueGx, 2) + pow(BlueGy, 2)));
            GreenSum = round(sqrt(pow(GreenGx, 2) + pow(GreenGy, 2)));
            RedSum = round(sqrt(pow(RedGx, 2) + pow(RedGy, 2)));

            // set new color
            image[i][j].rgbtBlue = (BlueSum <= 255) ? BlueSum : 255;
            image[i][j].rgbtGreen = (GreenSum <= 255) ? GreenSum : 255;
            image[i][j].rgbtRed = (RedSum <= 255) ? RedSum : 255;
        }
    }
    return;
}
