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
} bar;


int main(int argc, char **argv) {

	MPI_Init(&argc, &argv);
	int rank, size;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int* per_process = new int[size];/*allokacja tablicy na ile na kazdy proces */

	/*tworzenie nowego typu zmiennych*/
	int count = 4;
	int lengths[4] = { 1, 1, 1, 1 };
	MPI_Aint offsets[4] = { 0, sizeof(int), sizeof(int) + sizeof(int), sizeof(int) + sizeof(int) + sizeof(int) };
	MPI_Datatype types[4] = { MPI_INT, MPI_INT, MPI_INT, MPI_INT };

	MPI_Datatype barDatatype;
	MPI_Type_struct(count, lengths, offsets, types, &barDatatype);
	MPI_Type_commit(&barDatatype);


	int pixel_count; /*liczba pikseli*/
	int arr_dimensions[2]; /*wymiary bitmapy height x width*/
	BMP Input;

	int* displs = new int[size]; /* tablica przesuniecia */

	if (rank == 0){
		/*wczytanie na bitmapy i rozeslanie wymiarow */
		char *BITMAP_SCR = "test.BMP";
		Input.ReadFromFile(BITMAP_SCR);

		arr_dimensions[0] = Input.TellHeight();
		arr_dimensions[1] = Input.TellWidth();
		MPI_Bcast(arr_dimensions, 2, MPI_INT, 0, MPI_COMM_WORLD);
	}
	else{
		MPI_Bcast(arr_dimensions, 2, MPI_INT, 0, MPI_COMM_WORLD);
	}


	pixel_count = arr_dimensions[1] * arr_dimensions[0];/*obliczanie liczby pixli*/
		
	Color* buffer = (Color*)malloc(sizeof(Color)*pixel_count);/*allokacja tablicy struktor na pixele */


	if (rank == 0){
		/*wczytanie bitmapy do tablicy struktor*/
		int counter = 0;
		for (int i = 0; i<arr_dimensions[0]; ++i)
		{
			for (int j = 0; j<arr_dimensions[1]; ++j)
			{
				buffer[counter].r = Input(j, i)->Red;
				buffer[counter].g = Input(j, i)->Green;
				buffer[counter].b = Input(j, i)->Blue;
				buffer[counter].i = 0;
				counter++;
			}
		}

		/*obliczenie ile na ka¿dy proces oraz przesuniecia */

		int default_for_process = pixel_count / size; /*domyslnie na proces*/
		int rest = pixel_count % size; /*reszta do podzielenia miedzy procesy*/
		
		int sum = 0; // suma zliczen. uzywana to obliczenia przesuniecia


		for (int i = 0; i < size; i++){
			per_process[i] = default_for_process;
			if (i < rest){
				per_process[i]++;
			}
			displs[i] = sum;/*uzupelnienie przesuniecia */
			sum += per_process[i];
		}
		/*rozeslanie po ile dla kazdego procesu oraz przesuniecie dla gathera*/
		MPI_Bcast(per_process, size, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(displs, size, MPI_INT, 0, MPI_COMM_WORLD);

	}
	else{

		/*pobranie po ile dla ka¿dego procesu   */
		MPI_Bcast(per_process, size, MPI_INT, 0, MPI_COMM_WORLD);
		cout << rank << " " << per_process[rank] << endl;
		MPI_Bcast(displs, size, MPI_INT, 0, MPI_COMM_WORLD);


	}


	/*stworzenie tablicy pikseli przydzielonych po podziale  */
	Color* pixel_per_process = (Color*)malloc(sizeof(Color)*per_process[rank]);

	MPI_Scatterv(buffer, per_process, displs, barDatatype, pixel_per_process, per_process[rank], barDatatype, 0, MPI_COMM_WORLD);


	
	cout << "-----------------" << endl;
	for(int i = 0; i < per_process[rank]; i++) {
		cout << " Proces" << rank << " otrzymal " << pixel_per_process[i].r << " " << pixel_per_process[i].g << " " << pixel_per_process[i].b << " " << endl;
	}
	cout << "-----------------" << endl;
	








	
	MPI_Finalize();
	return 0;

}
