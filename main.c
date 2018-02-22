//Arlo Eardley 1108472
//Carel Ross 1106684
//Ryan Verpoort 1136745

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void ZeroSet(int* A[], int K, int N, int E)
{
//initialize array of pointers to other memory allocated arrays
//set all values in new memory array to 0
	for(int i = 0; i < N; i++) 
	{
		A[i] = malloc((E/N)*sizeof(*A[i]));
		for(int j = 0; j < E/N; j++) 
		{
			A[i][j] = 0;
		}
	}
}

void TenPercentSet(int* A[], int K, int N, int E)
{
//determine the number of elements
	int TenSize = E * 0.1;
	if (TenSize == 0) 
	{
		printf("0.10 of %d is 0\n", E);
		return;
	}
	int step = 0;
	int counter = 0;
//uniformly set 10 percent of the values to 1
	for(int i = 0; i < N; i++) 
	{
		for(int j = 0; j < E/N; j++) 
		{
			if(step == ((E - TenSize) / (TenSize + 1))) 
			{
				A[i][j] = 1;
				counter++;
				step = 0;
			} 
			else step++;
			if(counter == TenSize) break;
		}
	}
}

void FivePercentGet(int* A[], int K, int N, int E)
{
//determine the number of elements and initialize the random number function
	srand(time(NULL));
	int FiveSize = E * 0.05;
	if (FiveSize == 0) 
	{
		printf("0.05 of %d is 0\n", E);
		return;
	}
	int cache[FiveSize];
	int i = 0;
//initilize all values in the cache to -1 since an index cannot be negative
	for(int x = 0; x < FiveSize; x++) 
	{
		cache[x] = -1;
	}
//uniformly determine a random number from 5 percent of elements and display
	for(int counter = 0; counter < FiveSize; counter++) 
	{
		i = rand() % E;
		for(int x = 0; x < FiveSize; x++) 
		{
			if(i == cache[x]) 
			{
				printf("Duplicate detected \n");
				i = rand() % E;
				x = 0;
			}
		}
		cache[counter] = i;
		int indicies[K];
			for (int x = 0; x < K; x++)
			{
				indicies[x] = 0;
			}
		int y = 1;
		int imod = i%N;
		indicies[0] = imod;
		i -= imod;
		int idiv = i/N;
		while (i > 0)
		{
			i /= N;
			if (i >= 0) indicies[y] = i%N;
			else indicies[y] = N;
			y++;
		}
		for (int x = 0; x < K; x++)
		{
			printf("[ %d ]", indicies[x]);
		}
		printf("\n%d", (counter+1));
		printf(". Value %d \n \n", A[imod][idiv]);
	}
}

int main(int argc, char** argv)
{
//initialize the variables K and N
	int K = 0; // 2,3,4,5
	int N = 0; // 100,100,50,20
//get user input for variables K and N
	printf("Enter K Value: ");
	scanf("%d", &K);
	printf("Enter N Value: ");
	scanf("%d", &N);
	int* A[N];
	int E = pow(N,K);
//Run the dynamic array through all three procedures
	ZeroSet(A, K, N, E);
	TenPercentSet(A, K, N, E);
	FivePercentGet(A, K, N, E);
//free allocated memory to prevent memory leaks
	for(int i = 0; i < N; i++) 
	{
		free(A[i]);
	}
return 0;
}