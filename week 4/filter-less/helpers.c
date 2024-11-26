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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            sepiaRed = (sepiaRed < 255) ? round(sepiaRed) : 255;
            sepiaGreen = (sepiaGreen < 255) ? round(sepiaGreen) : 255;
            sepiaBlue = (sepiaBlue < 255) ? round(sepiaBlue) : 255;

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmpBlue;
    int tmpGreen;
    int tmpRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            tmpBlue = image[i][j].rgbtBlue;
            tmpGreen = image[i][j].rgbtGreen;
            tmpRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = tmpBlue;
            image[i][width - j - 1].rgbtGreen = tmpGreen;
            image[i][width - j - 1].rgbtRed = tmpRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    float avgB;
    float avgG;
    float avgR;
    int pxlCount;
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            avgB = 0;
            avgG = 0;
            avgR = 0;
            pxlCount = 0;
            for (int m = -1; m <= 1; m++)
            {
                if (k + m < 0 || k + m >= height)
                {
                    continue;
                }
                for (int n = -1; n <= 1; n++)
                {
                    if (l + n < 0 || l + n >= width)
                    {
                        continue;
                    }
                    avgB += copy[k+m][l+n].rgbtBlue;
                    avgG += copy[k+m][l+n].rgbtGreen;
                    avgR += copy[k+m][l+n].rgbtRed;
                    pxlCount++;
                }
            }
            image[k][l].rgbtBlue = round(avgB / pxlCount);
            image[k][l].rgbtGreen = round(avgG / pxlCount);
            image[k][l].rgbtRed = round(avgR / pxlCount);
        }
    }
    return;
}
