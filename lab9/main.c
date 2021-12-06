#include <stdio.h>
#include <stdlib.h>

#define CYLINDERS 5000
#define REQUESTS 1000

int ran_array[REQUESTS];

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

	if (move == 1)
	{
		for (i = index; i < REQUESTS; i++)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
		head_movement += abs(CYLINDERS - RQ[i - 1] - 1);
		head = CYLINDERS - 1;
		for (i = index - 1; i >= 0; i--)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
	}
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

	if (move == 1)
	{
		for (i = index; i < n; i++)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
		head_movement += abs(CYLINDERS - RQ[i - 1] - 1);
		head_movement += abs(CYLINDERS - 1 - 0);
		head = 0;
		for (i = 0; i < index; i++)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
	}
	else
	{
		for (i = index - 1; i >= 0; i--)
		{
			head_movement += abs(RQ[i] - head);
			head = RQ[i];
		}
		head_movement += abs(RQ[i + 1] - 0);
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
	
	printf("Enter head position: ");
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
	printf("C-LOOK head movements (right): %d\n", clook(ran_array, start, 1));

	return 0;
}
