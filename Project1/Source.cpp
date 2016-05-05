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

	/*allokacja tablicy na ile na kazdy proces */
	int* per_process = new int[size];


	if (rank == 0){
		/*wczytanie na bitmapy */
		char *BITMAP_SCR = "test.BMP";
		BMP Input;

		Input.ReadFromFile(BITMAP_SCR);
		int width = Input.TellWidth();
		int height = Input.TellHeight();

		int pixel_count = width*height;

		Color* buffer = (Color*)malloc(sizeof(Color)*pixel_count);

		int counter = 0;

		/*wczytanie bitmapy do tablicy struktor*/
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

		int default_for_process = pixel_count / size;
		int rest = pixel_count % size;

		/*obliczenie ile na ka¿dy proces*/

		for (int i = 0; i < size; i++){

			per_process[i] = default_for_process;
			if (i < rest){
				per_process[i]++;
			}

		}

		
	}

	/*rozeslanie po ile dla kazdego procesu */
	MPI_Bcast(per_process, size, MPI_INT, 0, MPI_COMM_WORLD);
	cout << rank << " " << per_process[rank] << endl;

	/*stworzenie tablicy pikseli przydzielonych po podziale  */
	Color* pixel_per_process = (Color*)malloc(sizeof(Color)*per_process[rank]);
	
	

	
	MPI_Finalize();
	return 0;

}
