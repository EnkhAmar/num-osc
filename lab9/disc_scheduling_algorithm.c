/*  This program implements the following disck-scheduling algorithms:
FCFS, SSTF, SCAN, C-SCAN, LOOK, and C-LOOK
The program services a disk of 5,000 cylinders numbered 0 to 4999.
It generates a random series of 1000 cylinder requests and services 
them according to each of he algorithms listed above. The program
will be passed the initial position of the disk head (as a parameter
on the command line) and report the total amount of head movement 
required by each algorithm. 

To run:
gcc -o diskAlgorithms diskAlgorithms.c
./file_name followed by number from 0-4999 for index (see below for example)
./diskAlgorithms 423
*/

#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 5000
#define REQUESTS 1000

int start = 0;

int ran_array[REQUESTS];
int test_array[REQUESTS];

int *sort_array()
{

	int temp = 0, i = 0, j = 0;

	for (i = 0; i < REQUESTS; ++i)
	{

		for (j = i + 1; j < REQUESTS; ++j)
		{

			if (ran_array[i] > ran_array[j])
			{

				temp = ran_array[i];
				ran_array[i] = ran_array[j];
				ran_array[j] = temp;
			}
		}
	}

	return ran_array;
}

/* First-Come-First-Serve (fcfs) */
int fcfs(int *ran_array, int head)
{
	int i = 0, head_movement = 0;

	for (i = 0; i < REQUESTS; i++)
	{
		head_movement += abs(ran_array[i] - head);
		head = ran_array[i];
	}

	return head_movement;
}

/* Shortest-Seek-Time-First (SSTF) */
int sstf(int *ran_array, int head)
{
	int RQ[REQUESTS], count = 0, head_movement = 0, i;
	for (i = 0; i < REQUESTS; i++)
		RQ[i] = ran_array[i];

	while (count != REQUESTS)
	{
		int min = CYLINDERS, distance, index;
		for (i = 0; i < REQUESTS; i++)
		{
			distance = abs(RQ[i] - head);
			if (min > distance)
			{
				min = distance;
				index = i;
			}
		}
		head_movement = head_movement + min;
		head = RQ[index];
		RQ[index] = CYLINDERS;
		count++;
	}

	return head_movement;
}

/* SCAN ) */
int scan(int *ran_array, int head, int move)
{
	int RQ[REQUESTS], i, j, head_movement = 0;
	for (i = 0; i < REQUESTS; i++)
		RQ[i] = ran_array[i];

	for (i = 0; i < REQUESTS; i++)
	{
		for (j = 0; j < REQUESTS - i - 1; j++)
		{
			if (RQ[j] > RQ[j + 1])
			{
				int temp;
				temp = RQ[j];
				RQ[j] = RQ[j + 1];
				RQ[j + 1] = temp;
			}
		}
	}

	int index;
	for (i = 0; i < REQUESTS; i++)
	{
		if (head < RQ[i])
		{
			index = i;
			break;
		}
	}

	// if movement is towards high value
	if (move == 1)
	{
		for (i = index; i < REQUESTS; i++)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
		//  last movement for max size
		head_movement += abs(CYLINDERS - RQ[i - 1] - 1);
		head = CYLINDERS - 1;
		for (i = index - 1; i >= 0; i--)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
	}
	// if movement is towards low value
	else
	{
		for (i = index - 1; i >= 0; i--)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
		//  last movement for min size
		head_movement += abs(RQ[i + 1] - 0);
		head = 0;
		for (i = index; i < REQUESTS; i++)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
	}

	return head_movement;
}

/* Circular Scan (C-SCAN) */
int cscan(int *ran_array, int head, int move)
{
	int RQ[REQUESTS], i, j, n = REQUESTS, head_movement = 0;
	for (i = 0; i < REQUESTS; i++)
		RQ[i] = ran_array[i];

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (RQ[j] > RQ[j + 1])
			{
				int temp;
				temp = RQ[j];
				RQ[j] = RQ[j + 1];
				RQ[j + 1] = temp;
			}
		}
	}

	int index;
	for (i = 0; i < n; i++)
	{
		if (head < RQ[i])
		{
			index = i;
			break;
		}
	}

	// if movement is towards high value
	if (move == 1)
	{
		for (i = index; i < n; i++)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
		//  last movement for max size
		head_movement += abs(CYLINDERS - RQ[i - 1] - 1);
		/*movement max to min disk */
		head_movement += abs(CYLINDERS - 1 - 0);
		head = 0;
		for (i = 0; i < index; i++)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
	}
	// if movement is towards low value
	else
	{
		for (i = index - 1; i >= 0; i--)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
		//  last movement for min size
		head_movement += abs(RQ[i + 1] - 0);
		/*movement min to max disk */
		head_movement += abs(CYLINDERS - 1 - 0);
		head = CYLINDERS - 1;
		for (i = n - 1; i >= index; i--)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
	}

	return head_movement;
}

/* Look */
int look(int *ran_array, int head, int move)
{
	int RQ[REQUESTS],i,j,head_movement=0;
    for(i=0;i<REQUESTS;i++)
		RQ[i] = ran_array[i];

    for(i=0;i<REQUESTS;i++)
    {
        for(j=0;j<REQUESTS-i-1;j++)
        {
            if(RQ[j]>RQ[j+1])
            {
                int temp;
                temp=RQ[j];
                RQ[j]=RQ[j+1];
                RQ[j+1]=temp;
            }

        }
    }

    int index;
    for(i=0;i<REQUESTS;i++)
    {
        if(head<RQ[i])
        {
            index=i;
            break;
        }
    }
   
    // if movement is towards high value
    if(move==1)
    {
        for(i=index;i<REQUESTS;i++)
        {
            head_movement=head_movement+abs(RQ[i]-head);
            head=RQ[i];
        }
        
        for(i=index-1;i>=0;i--)
        {
             head_movement=head_movement+abs(RQ[i]-head);
             head=RQ[i];
            
        }
    }
    // if movement is towards low value
    else
    {
        for(i=index-1;i>=0;i--)
        {
            head_movement=head_movement+abs(RQ[i]-head);
            head=RQ[i];
        }
        
        for(i=index;i<REQUESTS;i++)
        {
             head_movement=head_movement+abs(RQ[i]-head);
             head=RQ[i];
            
        }
    }
    
    return head_movement;
}

/* C-Look */
int clook(int *ran_array, int head, int move)
{
	int RQ[REQUESTS],i,j,head_movement=0;
    for(i=0;i<REQUESTS;i++)
		RQ[i] = ran_array[i];
    
    // logic for C-look disk scheduling
    
        /*logic for sort the request array */
    for(i=0;i<REQUESTS;i++)
    {
        for( j=0;j<REQUESTS-i-1;j++)
        {
            if(RQ[j]>RQ[j+1])
            {
                int temp;
                temp=RQ[j];
                RQ[j]=RQ[j+1];
                RQ[j+1]=temp;
            }

        }
    }

    int index;
    for(i=0;i<REQUESTS;i++)
    {
        if(head<RQ[i])
        {
            index=i;
            break;
        }
    }
   
    // if movement is towards high value
    if(move==1)
    {
        for(i=index;i<REQUESTS;i++)
        {
            head_movement=head_movement+abs(RQ[i]-head);
            head=RQ[i];
        }
        
        for( i=0;i<index;i++)
        {
             head_movement=head_movement+abs(RQ[i]-head);
             head=RQ[i];
            
        }
    }
    // if movement is towards low value
    else
    {
        for(i=index-1;i>=0;i--)
        {
            head_movement=head_movement+abs(RQ[i]-head);
            head=RQ[i];
        }
        
        for(i=REQUESTS-1;i>=index;i--)
        {
             head_movement=head_movement+abs(RQ[i]-head);
             head=RQ[i];
        }
    }
    
    return head_movement;
}

int main()
{

	int i = 0, head = 0, start;
	
	printf("Enter initial head position:\n");
    scanf("%d", &start);

	for (i = 0; i < REQUESTS; i++)
	{
		ran_array[i] = rand() % CYLINDERS;
	}

	printf("FCFS head movements: %d\n", fcfs(ran_array, start));
	printf("SSTF head movements: %d\n", sstf(ran_array, start));
	printf("SCAN head movements (left): %d\n", scan(ran_array, start, 0));
	printf("SCAN head movements (right): %d\n", scan(ran_array, start, 1));
	printf("CSCAN head movements (left): %d\n", cscan(ran_array, start, 0));
	printf("CSCAN head movements (right): %d\n", cscan(ran_array, start, 1));
	printf("LOOK head movements (left): %d\n", look(ran_array, start, 0));
	printf("LOOK head movements (right): %d\n", look(ran_array, start, 1));
	printf("C-LOOK head movements (left): %d\n", clook(ran_array, start, 0));
	printf("C-LOOK head movements (right): %d\n\n", clook(ran_array, start, 1));

	return 0;
}
