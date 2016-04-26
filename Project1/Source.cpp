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

	BMP Input;
	Input.ReadFromFile(BITMAP_SCR);
	int width = Input.TellWidth();
	int height = Input.TellHeight();

	cout << width << endl;
	cout << height << endl;





	MPI_Finalize();
	return 0;
}