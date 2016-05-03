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
	int* per_process = new int[size];
	if (rank == 0){
		int from = 0;
		int to = 0;
		int array_size = 12;
		int sum = 0;

		int default_for_process = 12 / size;
		int rest = 12 % size;
		
		int** from_to_proces = new int*[size]; /*ile od do którego */
		
	
		int *displs = new int[size]; /*przesuniecie*/
			

		for (int i = 0; i < size; i++){
			from_to_proces[i] = new int[2];
			from = to;
			to = from + default_for_process;
			if (i < rest){
				to++;
			}
			from_to_proces[i][0] = from;
			from_to_proces[i][1] = to;
			per_process[i] = to - from;
			displs[i] = sum;
			sum += to - from;

		}

		for (int i = 0; i < size; i++){
			cout << per_process[i] << endl;
		}


	}
	MPI_Bcast(&per_process, size, MPI_INT, 1, MPI_COMM_WORLD);

	
	
	
	if (rank == 3){
	for (int i = 0; i < size; i++){
		cout <<rank<<"proces    "<< per_process[i] << endl;

	}
	}
		






	MPI_Finalize();
	return 0;
}