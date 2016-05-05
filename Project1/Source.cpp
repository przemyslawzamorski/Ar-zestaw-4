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

		/*counter = 0
			dla height 
				dla width
				ary[counter][0]=rgb
				ary[counter][1]= rgb
				ary[counter][2]= rgb
				przypisywanie do tablicy poprzez wskaŸnik 
				
				*/
		// dynamic allocation
		int** ary = new int*[pixel_count];
		for (int i = 0; i < pixel_count; ++i)
			ary[i] = new int[3];


	



		// fill
		for (int i = 0; i < pixel_count; ++i)
			for (int j = 0; j < 3; ++j)
				ary[i][j] = 5;

		// print
		for (int i = 0; i < pixel_count; ++i){
			cout << endl;
			for (int j = 0; j < 3; ++j)
				std::cout << i<<" "<<j<<" "<< ary[i][j] << "\n";

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