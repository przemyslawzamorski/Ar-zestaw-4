#include <stdio.h>          // printf
#include <mpi.h>
#include <stdlib.h>         
#include <time.h>  
#include <iostream>
#include "EasyBMP.h"

using namespace std;

int main(int argc, char **argv) {



	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0){
		/*wczytanie pliku do tablicy i znalezienie get width and height */
		char *BITMAP_SCR = "test.BMP";
		BMP Input;

		Input.ReadFromFile(BITMAP_SCR);
		int width = Input.TellWidth();
		int height = Input.TellHeight();

		cout << width << endl;
		cout << height << endl;

		int pixel_count = width*height;

		int ** ary = (int**)malloc(pixel_count * sizeof(int*));
		for (int i = 0; i < pixel_count; ++i)
			ary[i] = (int*)malloc(3 * sizeof(int));


		// fill
		for (int i = 0; i < pixel_count; ++i){
				ary[i][1] = 5;
				ary[i][0] = 5;
				ary[i][2] = 5;
		}

		// print
		for (int i = 0; i < pixel_count; ++i){
			cout << endl;
			for (int j = 0; j < 3; ++j)
				cout << i << " " << j << " " << ary[i][j] << "\n";

		}
		
		


	}
		MPI_Finalize();
		return 0;
	}
