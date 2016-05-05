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

	/*inicjalizacja procesu  ile na proces i zerowanie */
	int* per_process = new int[size];

	for (int i = 0; i < size; i++){
			per_process[i] = 0;
		}






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

		/*allokacja 3 elementowej tablicy*/
		int ***old_bitmap = new int**[height];
		for (int i = 0; i<height; i++){
			old_bitmap[i] = new int*[width];
			for (int j = 0; j<width; j++){
				old_bitmap[i][j] = new int[3];
				old_bitmap[i][j][0] = (int)Input(width, height)->Red;
				old_bitmap[i][j][1] = (int)Input(width, height)->Green;
				old_bitmap[i][j][2] = (int)Input(width, height)->Blue;


			}
		}
		

		/*for (int i = 0; i < size; i++){
			int default_for_process = 12 / size;
			int rest = 12 % size;

			if (i < rest){
				default_for_process++;
				
			}
			per_process[i] = default_for_process;
		}*/

	}


	/*MPI_Bcast(per_process, size, MPI_INT, 0, MPI_COMM_WORLD);


	
		cout << rank << " " << per_process[rank] << endl;
	
	cout << endl;*/
	
	MPI_Finalize();
	return 0;
}