#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE averageByte;
    for (int i = 0; i < height; i++)
    {
        for (int j  = 0; j < width; j++)
        {
            // compute the average RGB values of each pixel and set them to all RGB values in that same pixel
            averageByte = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = averageByte;
            image[i][j].rgbtGreen = averageByte;
            image[i][j].rgbtRed = averageByte;
        }

    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j  = 0; j < width; j++)
        {
            // Compute and replace each pixel as instructed
            BYTE originalBlue, originalRed, originalGreen;
            originalBlue = image[i][j].rgbtBlue;
            originalGreen = image[i][j].rgbtGreen;
            originalRed = image[i][j].rgbtRed;

            // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            //   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            //   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
            image[i][j].rgbtRed = (BYTE)round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            image[i][j].rgbtGreen  = (BYTE)round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            image[i][j].rgbtBlue  = (BYTE)round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (image[i][j].rgbtRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            if (image[i][j].rgbtGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            if (image[i][j].rgbtBlue  > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else if (image[i][j].rgbtRed < 0)
            {
                image[i][j].rgbtRed = 0;
            }
            else if (image[i][j].rgbtGreen < 0)
            {
                image[i][j].rgbtGreen = 0;
            }
            else if (image[i][j].rgbtBlue  < 0)
            {
                image[i][j].rgbtBlue = 0;
            }
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE temp[width];
        // Create a temp array of RGBTRIPLE type that will
        // store the pixel of reversed order for each row
        for (int j  = 0; j < width; j++)
        {
            temp[j] = image[i][width - 1 - j];
        }
        // replace each elemement/pixel of that temp array to the the image[i] row.
        for (int k = 0; k < width; k++)
        {
            image[i][k] = temp[k];
        }
    }

    return;
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            tmpImage[row][col] = image[row][col];
        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // now we are on a current pixel of image[h][w]
            int reds = 0;
            int blues = 0;
            int greens = 0;
            int availablePixels = 0;
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // checks the boxes around the pixel by using [-1][-1], [-1][0], [-1][1], ... etc
                    // makes sure we don't go past width/height and 0
                    if ((row + i >= 0 && row + i < height) && (col + j >= 0 && col + j < width))
                    {
                        availablePixels++;
                        reds += tmpImage[row + i][col + j].rgbtRed;
                        greens +=  tmpImage[row + i][col + j].rgbtGreen;
                        blues +=  tmpImage[row + i][col + j].rgbtBlue;
                    }
                }
            }
            // set the current pixel we are on to the avg of the block
            image[row][col].rgbtRed = round(reds / (float) availablePixels);
            image[row][col].rgbtGreen = round(greens / (float)  availablePixels);
            image[row][col].rgbtBlue = round(blues / (float) availablePixels);
        }
    }
	return;
}