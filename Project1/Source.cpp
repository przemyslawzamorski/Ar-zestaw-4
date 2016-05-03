#include <stdio.h>          // printf
#include <mpi.h>
#include <stdlib.h>         
#include <time.h>  
#include <iostream>
#include "EasyBMP.h"

using namespace std;

int main(int argc, char **argv) {

	char *BITMAP_SCR = "MARBLES.BMP";

	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int probna[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11};
	

	/*BMP Input;
	Input.ReadFromFile(BITMAP_SCR);
	int width = Input.TellWidth();
	int height = Input.TellHeight();*/


	/*dekompozycja*/
	if (rank == 0){
		int from = 0;
		int to = 0;
		int array_size = 12;

		int default_for_process = 12 / size;
		int rest = 12 % size;
		
		int** per_proces = new int*[size]; /*ile od do którego */
	
		int *numbers_pixels = new int[size]; /*iloœæ pikseli na proces*/
			

		for (int i = 0; i < size; i++){
			per_proces[i] = new int[2];
			from = to;
			to = from + default_for_process;
			if (i < rest){
				to++;
			}
			per_proces[i][0] = from;
			per_proces[i][1] = to;
			numbers_pixels[i] = to - from;

		}


		for (int i = 0; i < size; i++){
			cout << per_proces[i][0] << " " << per_proces[i][1] << " " << numbers_pixels[i] << endl;
		}
	}
	else{

	}





	MPI_Finalize();
	return 0;
}