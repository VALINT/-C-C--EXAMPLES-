// TestTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "FIR_II_174_Int16_2_5KHz.h"
#include <fstream>
#include <iostream>
#include <string>

void readFile(std::ifstream* inWAV, short* input, int lengh);

typedef struct WAV
{
	char			chunkID[4];
	unsigned int	chunkSize;
	char			format[4];
	char			subchunk1Id[4];
	unsigned int	subchunk1Size;
	unsigned short  audioFormat;
	unsigned short  numChannels;
	unsigned int	sampleRate;
	unsigned int	byteRate;
	unsigned short  blockAlign;
	unsigned short  bitsPerSample;
	unsigned int	subchunk2Size;
	unsigned int	WAVOffset;

}WAV;

int main()
{
	char test[512];
	WAV testSound;
	char* WAVPtr = &testSound.chunkID[0];

	//std::string name = "Test_32f";
	std::string name = "Test_16Int";

	std::ifstream inWAV (name+".wav", std::ifstream::binary);				//Input file
	std::ofstream outWAV(name + "_out" + ".wav", std::ifstream::binary);	//Output file (input_name + _out)
	if(inWAV)	//Read WAV file header.
	{
		std::cout << "File open successfuly" << std::endl;
		inWAV.read(test, 512);
		for (int j = 0; j < 36; j++)
			*(WAVPtr + j) = test[j];
		//Search the start of sound data
		for (int j = 36; j < 508; j++)
			if (test[j] == 'd' && test[j + 1] == 'a' && test[j + 2] == 't' && test[j + 3] == 'a')
			{
				testSound.WAVOffset = j + 8;
				*(WAVPtr + 36 + 0) = test[j + 4];
				*(WAVPtr + 36 + 1) = test[j + 5];
				*(WAVPtr + 36 + 2) = test[j + 6];
				*(WAVPtr + 36 + 3) = test[j + 7];
				break;
			}
		outWAV.write(test, testSound.WAVOffset);
		inWAV.close();
	}
	// Open file and go to the sound data start
	inWAV.open(name+".wav", std::ifstream::binary);
	inWAV.read(test, testSound.WAVOffset);

	short* input = new short[2 * BL];	//filter buffer (2x core lenght)

	for (int i = 0; i < BL; i++)		//fill the half of buffer by zeros
	{
		input[i] = 0;
	}
	
	short sample;
	int   filter;
	//process all sound data
	for (int cb_int = 0; cb_int < testSound.subchunk2Size / (testSound.bitsPerSample / 8); cb_int++)
	{
		if (!(cb_int % 44100))//Some service data
			std::cout << cb_int / 44100 << "c\n";

		if (cb_int % BL == 0)
		{
			// Read second part if pointer in the start of first part
			if (cb_int % (2 * BL) == 0)
			{
				readFile(&inWAV, &input[BL], BL);
			}
			// Read first part if pointer in the start of second part
			else
			{
				readFile(&inWAV, &input[0], BL);
			}
		}

		//Convolution
		filter = 0;
		for (int a = 0; a < BL; a++)	// Go along FIR core
		{	
			// Looping of the buffer
			sample = (cb_int % (2 * BL)) + a;	
			if(sample >= (2 * BL)) sample -= (2 * BL);
			// (In[x] * FIR[x]) + (In[x+1] * FIR[x+1]) + ...
			filter += input[sample] * B[a];
		}
		// Back to 16bit signed int
		filter = (short)(filter / 32768);

		//Write filtered value to output file. 
		outWAV.put(char(filter));
		outWAV.put(char(filter >> 8));
	}

	// Clear memory and close files.
	delete[] input;
	outWAV.close();
	inWAV.close();
}

void readFile(std::ifstream* inWAV, short* input, int lengh)
{
	short buff;
	for (int i = 0; i < lengh; i++)
	{
		buff = 0;
		buff |= inWAV->get();
		buff |= (short int)inWAV->get() << 8;
		input[i] = buff;
	}
}