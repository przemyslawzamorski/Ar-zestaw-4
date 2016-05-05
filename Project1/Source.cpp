#include <stdio.h>          // printf
#include <mpi.h>
#include <stdlib.h>         
#include <time.h>  
#include <iostream>
#include "EasyBMP.h"

using namespace std;

struct Color
{
	int r, g, b;
};


int main(int argc, char **argv) {

	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if (rank == 0){
		char *BITMAP_SCR = "test.BMP";
		BMP Input;

		Input.ReadFromFile(BITMAP_SCR);
		int width = Input.TellWidth();
		int height = Input.TellHeight();

		cout << width << endl;
		cout << height << endl;

		int pixel_count = width*height;

		Color* buffer = (Color*)malloc(sizeof(Color)*pixel_count);

		int counter = 0;

		for (int i = 0; i<width; ++i)
		{
			for (int j = 0; j<height; ++j)
			{
				buffer[counter].r = 255;
				buffer[counter].g = 0;
				buffer[counter].b = 255;
				counter++;
			}
		}

		counter = 0;
		for (int i = 0; i<width; ++i)
		{
			for (int j = 0; j<height; ++j)
			{
				cout << buffer[counter].r << "\n";
				cout << buffer[counter].g << "\n";
				cout << buffer[counter].b << "\n";
				counter++;
			}
		}


	}

	

	
	MPI_Finalize();
	return 0;

}
