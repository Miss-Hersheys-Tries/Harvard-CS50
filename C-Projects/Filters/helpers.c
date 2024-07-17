#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (int) round((image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Helper function clamp for sepia function
int clamp(int value)
{
    if (value > 255)
    {
        return 255;
    }
    else if (value < 0)
    {
        return 0;
    }
    else
    {
        return value;
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = (int) round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = (int) round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = (int) round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            image[i][j].rgbtRed = clamp(sepiaRed);
            image[i][j].rgbtGreen = clamp(sepiaGreen);
            image[i][j].rgbtBlue = clamp(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width-j-1] = tmp;
        }
    }
}

// Helper function to calculate total around pixels for blur function
void total(int height, int width, RGBTRIPLE copy[height][width], int i, int j, int *sumRed, int *sumGreen, int *sumBlue, int *count)
{
    *sumRed = 0;
    *sumGreen = 0;
    *sumBlue = 0;
    *count = 0;

    // Looping around the pixel i [i,j]
    for (int li = -1; li <= 1; li++)
    {
        for (int lj = -1; lj <= 1; lj++)
        {
            // Assigning Neighbouring pixels
            int ni = li + i;
            int nj = lj + j;

            // Checking if neighbouring pixels is in the boundaries
            if (ni >= 0  && ni < height && nj >= 0 && nj < width)
            {
                *sumRed += copy[ni][nj].rgbtRed;
                *sumGreen += copy[ni][nj].rgbtGreen;
                *sumBlue += copy[ni][nj].rgbtBlue;
                (*count)++;
            }
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed, sumGreen, sumBlue, count;
            total(height, width, copy, i, j, &sumRed, &sumGreen, &sumBlue, &count);

            // Averaging the colours
            if (count != 0)
            {
                image[i][j].rgbtRed = (int) round(sumRed / (float) count);
                image[i][j].rgbtGreen = (int) round(sumGreen / (float) count);
                image[i][j].rgbtBlue = (int) round(sumBlue / (float) count);
            }
        }
    }
}
