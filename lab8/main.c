#include <stdio.h>
#define MAX 100;

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
        printf("\n");
        for (n = 0; n < frames; n++)
            printf("%d\t", temp[n]);
        return pageFaults;
    }
}

int LeastRecentlyUsed() {
    return 0;
}

int main()
{
    int referenceString[MAX], pageFaultsFIFO = 0, pageFaultsLRU = 0, pageFaultsOPTIMAL = 0, m, pages, frames;
    printf("\nEnter the number of Pages:\t");
    scanf("%d", &pages);
    printf("\nEnter reference string values:\n");
    for (m = 0; m < pages; m++)
    {
        printf("Value No. [%d]:\t", m + 1);
        scanf("%d", &referenceString[m]);
    }
    printf("\n What are the total number of frames:\t");
    {
        scanf("%d", &frames);
    }

    pageFaultsFIFO = FirstInFirstOut(referenceString, pages, frames);
    printf("TOTAL FAULTS\n");
    printf("FIFO: %d\n", pageFaults);

    return 0;
}
