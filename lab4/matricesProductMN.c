// gcc matricesProduct.c -pthread
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void getMatrixElements(int matrix[][10], int row, int column);
void display(int result[][10], int row, int column);

// Thread bur ene function-g heregjuulne
void *mult(void* arg)
{
	int *data = (int *)arg;
	int k = 0, i = 0;
	
	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];
	
	int *p = (int*)malloc(sizeof(int));
		*p = k;
	
	// threading haaj, pointer-eer urjveriin utgiig butsaana
	pthread_exit(p);
}

int main()
{
	int first[10][10], second[10][10], result[10][10], r1, c1, r2, c2;
	printf("Ehnii matrix-iin mor bagana too oruul: ");
	scanf("%d %d", &r1, &c1);
	printf("Hoyor dahi matrix-iin mor bagan too oruul: ");
	scanf("%d %d", &r2, &c2);

    // ehnii matrix-iin baganiin too, hoyor dahi matrix-iin
    // moriin too-toi tentseh yostoi !!!
	while (c1 != r2) {
		printf("Error! Mor baganiin toog dahiad oruulna uu.\n");
		printf("Ehnii matrix-iin mor bagana too oruul: ");
		scanf("%d%d", &r1, &c1);
		printf("Hoyor dahi matrix-iin mor bagan too oruul: ");
		scanf("%d%d", &r2, &c2);
	}

	getMatrixElements(first, r1, c1);
	getMatrixElements(second, r2, c2);
	
	int i, j, k;
	int max = r1*c2;
	
	
	// threadiin r1*c2 hemjeetei array zarlana	
    pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));
	
	int count = 0;
	int* data = NULL;
	for (i = 0; i < r1; i++)
		for (j = 0; j < c2; j++) {
				
			// data dotor mor baganiin elementiig huulna
			data = (int *)malloc((20)*sizeof(int));
			data[0] = c1;
	
			for (k = 0; k < c1; k++)
				data[k+1] = first[i][k];
	
			for (k = 0; k < r2; k++)
				data[k+c1+1] = second[k][j];
			
			pthread_create(&threads[count++], NULL, mult, (void*)(data));	
		}
	
	printf("RESULT: \n");
	for (i = 0; i < max; i++) {
		void *k;
	
        // Threaduudee join hiij, butsaah utgiig tsugluulna
		pthread_join(threads[i], &k);
			
		int *p = (int *)k;
		printf("%d ",*p);
        free(k);
		if ((i + 1) % c2 == 0)
			printf("\n");
	}

	free(threads);
	free(data);
return 0;
}

void getMatrixElements(int matrix[][10], int row, int column) {
	printf("\nElementuudee oruulna uu: \n");
	
	for (int i=0; i < row; ++i)
		for (int j=0; j < column; ++j) {
			printf("matrix[%d]{%d]: ", i+1, j+1);
			scanf("%d", &matrix[i][j]);
		}
}