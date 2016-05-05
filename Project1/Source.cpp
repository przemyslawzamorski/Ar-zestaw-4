#include <stdio.h>          // printf
#include <mpi.h>
#include <stdlib.h>         
#include <time.h>  
#include <iostream>
#include "EasyBMP.h"

using namespace std;

struct Color
{
	int r, g, b, i;
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

		for (int i = 0; i<height; ++i)
		{
			for (int j = 0; j<width; ++j)
			{
				buffer[counter].r = Input(j, i)->Red;
				buffer[counter].g = Input(j, i)->Green;
				buffer[counter].b = Input(j, i)->Blue;
				buffer[counter].i = 0;
				counter++;
			}
		}

		for (int i = 0; i < pixel_count; i++){
				cout << i << "\n ";
				cout << buffer[i].r << " ";
				cout << buffer[i].g << " ";
				cout << buffer[i].b << " ";
				cout << buffer[i].i << "\n";
				
		}
	
	}

	

	
	MPI_Finalize();
	return 0;

}
