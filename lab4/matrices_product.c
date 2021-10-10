// C Program to multiply two matrix using pthreads without
// use of global variables
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 4


void getMatrixElements(int matrix[][10], int row, int column);
void display(int result[][10], int row, int column);

//Each thread computes single element in the resultant matrix
void *mult(void* arg)
{
	int *data = (int *)arg;
	int k = 0, i = 0;
	
	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];
	
	int *p = (int*)malloc(sizeof(int));
		*p = k;
	
//Used to terminate a thread and the return value is passed as a pointer
	pthread_exit(p);
}

//Driver code
int main()
{
	int first[10][10], second[10][10], result[10][10], r1, c1, r2, c2;
	printf("Enter rows and column for the first matrix: ");
	scanf("%d %d", &r1, &c1);
	printf("Enter rows and column for the second matrix: ");
	scanf("%d %d", &r2, &c2);

	// Taking input until
	// 1st matrix columns is not equal to 2nd matrix row
	while (c1 != r2) {
		printf("Error! Enter rows and columns again.\n");
		printf("Enter rows and columns for the first matrix: ");
		scanf("%d%d", &r1, &c1);
		printf("Enter rows and columns for the second matrix: ");
		scanf("%d%d", &r2, &c2);
	}

	// get elements of the first matrix
	getMatrixElements(first, r1, c1);

	// get elements of the second matrix
	getMatrixElements(second, r2, c2);
	
	int i, j, k;
	int max = r1*c2;
	
	
	//declaring array of threads of size r1*c2	
	pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));
	
	int count = 0;
	int* data = NULL;
	for (i = 0; i < r1; i++)
		for (j = 0; j < c2; j++)
			{
				
			//storing row and column elements in data
			data = (int *)malloc((20)*sizeof(int));
			data[0] = c1;
	
			for (k = 0; k < c1; k++)
				data[k+1] = first[i][k];
	
			for (k = 0; k < r2; k++)
				data[k+c1+1] = second[k][j];
			
			//creating threads
				pthread_create(&threads[count++], NULL,
							mult, (void*)(data));
				
					}
	
	printf("RESULTANT MATRIX IS :- \n");
	for (i = 0; i < max; i++)
	{
	void *k;
	
	//Joining all threads and collecting return value
	pthread_join(threads[i], &k);
			
		
		int *p = (int *)k;
	printf("%d ",*p);
	if ((i + 1) % c2 == 0)
		printf("\n");
	}

	
	free(threads);
	free(data);
return 0;
}

void getMatrixElements(int matrix[][10], int row, int column) {
	printf("\nEnter elements: \n");
	
	for (int i=0; i < row; ++i)
		for (int j=0; j < column; ++j) {
			printf("Enter matrix[%d]{%d]: ", i+1, j+1);
			scanf("%d", &matrix[i][j]);
		}
}

void display(int result[][10], int row, int column) {
	printf("\nOutput Matrix:\n");
	for (int i=0; i<row; ++i)
		for(int j=0; j<column; ++j) {
			printf("%d ", result[i][j]);
			if (j == column - 1)
				printf("\n");
		}
}