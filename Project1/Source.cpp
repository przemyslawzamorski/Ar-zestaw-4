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

	int pixec_count = width*height;

	width = 4;
	height = 3;

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


	cout << old_bitmap[66][2][0] << endl;
	cout << old_bitmap[66][2][1] << endl;
	cout << old_bitmap[66][2][2] << endl; 



	/*int ***arr3D = new int**[height];
	for (int i = 0; i<height; i++){
		arr3D[i] = new int*[width];
		for (int j = 0; j<width; j++){
			arr3D[i][j] = new int[1];
			for (int k = 0; k<1; k++){
				arr3D[i][j][k] = 0;
			}
		}
	}

	for (int i = 0; i<height; i++){
		for (int j = 0; j<width; j++){

			cout << arr3D[i][j][0] << " ";
			
		}
		cout << endl;
	}*/



	

	/*int** old_bitmap = new int*[pixec_count];
	for (int i = 0; i < pixec_count; ++i){
		old_bitmap[i] = new int[3];
		old_bitmap[i][0] = (int)Input(1419, 1001)->Red;
		old_bitmap[i][0] = (int)Input(1419, 1001)->Red;
		old_bitmap[i][0] = (int)Input(1419, 1001)->Red;

		
	}

	cout << "(" << (int)Input(1419, 1001)->Red << ","
		<< (int)Input(1419, 1001)->Green << ","
		<< (int)Input(1419, 1001)->Blue << ","
		<< (int)Input(1419, 1001)->Alpha << ")" << endl;
		*/




	MPI_Finalize();
	return 0;
}