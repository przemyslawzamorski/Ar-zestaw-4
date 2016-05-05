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

	/*allokacja tablicy na ile na kazdy proces */
	int* per_process = new int[size];




	/*tworzenie nowego typu zmiennych*/
	int count = 4;
	int lengths[4] = { 1, 1, 1, 1 };
	MPI_Aint offsets[4] = { 0, sizeof(int), sizeof(int) + sizeof(int), sizeof(int) + sizeof(int) + sizeof(int) };
	MPI_Datatype types[4] = { MPI_INT, MPI_INT, MPI_INT, MPI_INT };

	MPI_Datatype barDatatype;
	MPI_Type_struct(count, lengths, offsets, types, &barDatatype);
	MPI_Type_commit(&barDatatype);



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

		/*obliczenie ile na ka¿dy proces oraz przesuniecia */

		int default_for_process = pixel_count / size; /*domyslnie na proces*/
		int rest = pixel_count % size; /*reszta do podzielenia miedzy procesy*/
		int* displs = new int[size]; /* tablica przesuniecia */
		int sum = 0; // suma zliczen. uzywana to obliczenia przesuniecia


		for (int i = 0; i < size; i++){
			per_process[i] = default_for_process;
			if (i < rest){
				per_process[i]++;
			}
			displs[i] = sum;/*uzupelnienie przesuniecia */
			sum += per_process[i];
		}

		/*rozeslanie po ile dla kazdego procesu */
		MPI_Bcast(per_process, size, MPI_INT, 0, MPI_COMM_WORLD);
		cout << rank << " " << per_process[rank] << endl;


	}
	else{

		/*rozeslanie po ile dla kazdego procesu */
		MPI_Bcast(per_process, size, MPI_INT, 0, MPI_COMM_WORLD);
		cout << rank << " " << per_process[rank] << endl;
		Color* buffer = (Color*)malloc(sizeof(Color)*10);


	}


	/*stworzenie tablicy pikseli przydzielonych po podziale  */
	Color* pixel_per_process = (Color*)malloc(sizeof(Color)*per_process[rank]);

	MPI_Scatterv(&buffer, per_process, displs, barDatatype, pixel_per_process, per_process[rank], barDatatype, 0, MPI_COMM_WORLD);


	for(int i = 0; i < per_process[rank]; i++) {
		cout << " Proces" << rank << " otrzymal " << pixel_per_process[i].r << " " << pixel_per_process[i].g << " " << pixel_per_process[i].b << " " << endl;
	}
	





	/*obliczenie luminacji kazdego pixelu*/
	int lumination_sum = 0;

	for (int i = 0; i < per_process[rank]; i++) {

		pixel_per_process[i].i = 0, 299 * pixel_per_process[i].r + 0, 587 * pixel_per_process[i].g + 0, 114 * pixel_per_process[i].b;
		lumination_sum += pixel_per_process[i].i;
	}

	/*obliczenie sr luminacji i rozeslanie do procesow*/
	int sr_lumination = 0;

	MPI_Reduce(&lumination_sum, &sr_lumination, 1, MPI_INT, MPI_SUM, 0 /*root*/, MPI_COMM_WORLD);

	sr_lumination = sr_lumination / pixel_count;

	MPI_Bcast(&sr_lumination, 1, MPI_INT, 0, MPI_COMM_WORLD);

	/*zmienianie koloru*/

	for (int i = 0; i < per_process[rank]; i++) {

		if (pixel_per_process[i].i > sr_lumination){
			pixel_per_process[i].r = 255;
			pixel_per_process[i].g = 255;
			pixel_per_process[i].b = 255;

		}
		else{
			pixel_per_process[i].r = 0;
			pixel_per_process[i].g = 0;
			pixel_per_process[i].b = 0;
		}
	}

	/*zebranie wszystkich zamienionych*/

	Color* buffer_recv = (Color*)malloc(sizeof(Color)*pixel_count);

	MPI_Gatherv(pixel_per_process, per_process[rank], barDatatype, buffer_recv, pixel_count, displs, barDatatype,
		0, MPI_COMM_WORLD);




	
	MPI_Finalize();
	return 0;

}
