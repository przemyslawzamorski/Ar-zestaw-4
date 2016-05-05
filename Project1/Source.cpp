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

	/*inicjalizacja procesu  ile na proces */
	int* per_process = new int[size];

	for (int i = 0; i < size; i++){
			per_process[i] = 0;
		}

	if (rank == 0){
		

		for (int i = 0; i < size; i++){
			int default_for_process = 12 / size;
			int rest = 12 % size;

			if (i < rest){
				default_for_process++;
				
			}
			per_process[i] = default_for_process;
		}

	}


	MPI_Bcast(per_process, size, MPI_INT, 0, MPI_COMM_WORLD);


	
		cout << rank << " " << per_process[rank] << endl;
	
	cout << endl;
	
	MPI_Finalize();
	return 0;
}