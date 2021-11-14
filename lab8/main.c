#include <stdio.h>
#define MAX 100


int FirstInFirstOut(int referenceString[], int pages, int frames) {
    int temp[frames], m, s, n, pageFaults = 0;
    for (m = 0; m < frames; m++)
        temp[m] = -1;
    
    for (m = 0; m < pages; m++) {
        s = 0;
        for (n = 0; n < frames; n++)
            if (referenceString[m] == temp[n]) {
                s++;
                pageFaults--;
            }
        pageFaults++;
        if ((pageFaults <= frames) && (s == 0))
            temp[m] = referenceString[m];
        else if (s == 0)
            temp[(pageFaults - 1) % frames] = referenceString[m];
        // printf("\n");
        // for (n = 0; n < frames; n++)
        //     printf("%d\t", temp[n]);
    }
    return pageFaults;
}


int findLRU(int time[], int n){
    int i, minimum = time[0], pos = 0;
 
    for(i = 1; i < n; ++i)
        if(time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    return pos;
}
int LeastRecentlyUsed(int referenceString[], int pages, int frames) {
    int temp[pages], time[pages], m, n, pageFaults = 0, flag1, flag2, count = 0, pos;
    for (m = 0; m < pages; m++)
        temp[m] = -1;
    
    for (m = 0; m < pages; m++) {
        flag1 = flag2 = 0;
        for (n = 0; n < frames; n++)
            if (referenceString[m] == temp[n]) {
                time[n] = ++count;
                flag1 = flag2 = 1;
                break;
            }

        if (flag1 == 0)
            for (n = 0; n < frames; n++)
                if (temp[n] == -1) {
                    pageFaults++;
                    temp[n] = referenceString[m];
                    time[n] = ++count;
                    flag2 = 1;
                    break;
                }
        
        if (flag2 == 0) {
            pos = findLRU(time, frames);
            pageFaults++;
            temp[pos] = referenceString[m];
            time[pos] = ++count; 
        }
    }
    return pageFaults;
}


int Optimal(int referenceString[], int pages, int frames) {
    int temp[frames], time[frames], m, n, pageFaults = 0, flag1, flag2, flag3, pos, k, max;
    for (m = 0; m < frames; m++)
        temp[m] = -1;
    
    for (m = 0; m < pages; m++) {
        flag1 = flag2 = 0;
        for (n = 0; n < frames; n++)
            if (referenceString[m] == temp[n]) {
                flag1 = flag2 = 1;
                break;
            }
        
        if (flag1 == 0)
            for (n = 0; n < frames; n++)
                if (referenceString[n] == -1) {
                    pageFaults++;
                    temp[n] = referenceString[m];
                    flag2 = 1;
                    break;
                }
        
        if (flag2 == 0) {
            flag3 = 0;

            for (n = 0; n < frames; n++) {
                time[n] = -1;
                
                for (k = m+1; k < pages; k++)
                    if (referenceString[k] == temp[n]) {
                        time[n] = k;
                        break;
                    }
            }

            for (n = 0; n < frames; n++) {
                if (time[n] == -1) {
                    pos = n;
                    flag3 = 1;
                    break;
                }
            }

            if (flag3 == 0) {
                max = time[0];
                pos = 0;

                for (n = 1; n < frames; n++)
                    if (time[n] > max) {
                        max = time[n];
                        pos = n;
                    }
            }
            temp[pos] = referenceString[m];
            pageFaults++;
        }
    }
    return pageFaults;
}

int main()
{
    int referenceString[MAX], pageFaultsFIFO = 0, pageFaultsLRU = 0, pageFaultsOPTIMAL = 0, m, pages, frames;
    printf("\nEnter number of frames: ");
    scanf("%d", &frames);
    printf("\nEnter number of pages: ");
    scanf("%d", &pages);
    printf("\nEnter reference string values:\n");
    for (m = 0; m < pages; m++)
    {
        // printf("Value No. [%d]:  ", m + 1);
        scanf("%d", &referenceString[m]);
    }

    pageFaultsLRU = LeastRecentlyUsed(referenceString, pages, frames);
    pageFaultsFIFO = FirstInFirstOut(referenceString, pages, frames);
    pageFaultsOPTIMAL = Optimal(referenceString, pages, frames);
    printf("\nTOTAL FAULTS\n");
    printf("LRU: %d\n", pageFaultsLRU);
    printf("FIFO: %d\n", pageFaultsFIFO);
    printf("OPTIMAL: %d\n", pageFaultsOPTIMAL);

    return 0;
}
