#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#define TEMP_SIZE 8
#define M 8
#define N 8

int** createMatrix(int m, int n)
{
	int i;
	int j;
	int k = 0;
	int** mat = (int**)malloc(m * sizeof(int*));
	int* p_mat;
	
	
	for(i = 0; i< m; i++)
	{
		mat[i] = malloc(n*sizeof(int));
		for( p_mat = mat[i]; p_mat< mat[i]+n; p_mat++)
			*p_mat = k++;
	}		
	
	return mat;
}

void printMatrix(int** mat, int m, int n)
{
	int i;
	int j;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j<n; j++)
		{
			printf("%d ", (*mat)[i*n+j]);
		}
		printf("\n");
	}
}


void main()
{
	int** mat1;
	
	////////////////////////////////////////////////////////////////////////////
	// Blok koda koji sluzi da manifestaciju problema ucini verovatnijom
	// Otkomentarisati ukoliko se ne javi problem  prilikom pokretanja primera
	//int* temp1 = (int*)malloc(TEMP_SIZE*sizeof(int));
	//int* temp2 = (int*)malloc(TEMP_SIZE*sizeof(int));
	//int i;
	//for(i = 0; i<TEMP_SIZE; i++)
	//{
	//	temp2[i] = 0xdedababa;
	//}
	//
	//free(temp1);
	///////////////////////////////////////////////////////////////////////////
	
	mat1 = createMatrix(M, N);
	printMatrix(mat1, M, N);
	
	free(mat1);
}
