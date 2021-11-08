# Page Replacement Algorithm In Operating System

-----------------------------------------------------

In this situation, the operating system replaces an existing page from the main memory by bringing a new page from the secondary memory.

In such situations, the FIFO method is used, which is also refers to the First in First Out concept. This is the simplest page replacement method in which the operating system maintains all the pages in a queue. Oldest pages are kept in the front, while the newest is kept at the end. On a page fault, these pages from the front are removed first, and the pages in demand are added.

### Algorithm for FIFO Page Replacement

- Step 1. Start to traverse the pages.
- Step 2. If the memory holds fewer pages, then the capacity else goes to step 5.
- Step 3. Push pages in the queue one at a time until the queue reaches its maximum capacity or all page requests are fulfilled.
- Step 4. If the current page is present in the memory, do nothing.
- Step 5. Else, pop the topmost page from the queue as it was inserted first.
- Step 6. Replace the topmost page with the current page from the string.
- Step 7. Increment the page faults.
- Step 8. Stop

-----------------------------------------------------

In such a case, the operating system removes the unused pages from the main memory. It is based on the assumption that recent unused pages will remain unused for the next few instructions.

The concept is implemented through an algorithm to manage such a page fault. The algorithm retains a linked list of all the pages present in the memory retaining the most recently used page at high priority and the least recently used page at low priority. The priority is changed as per program executions.

### Algorithm for LRU Page Replacement

- Step 1. Start the process
- Step 2. Declare the page size
- Step 3. Determine the number of pages to be inserted.
- Step 4. Get the value.
- Step 5. Declare the counter and stack value.
- Step 6. Choose the least recently used page by the counter value.
- Step 7. Stack them as per the selection.
- Step 8. Display the values.
- Step 9. Terminate the process.

-----------------------------------------------------

To fulfill the demand of the most frequently used pages, the operating systems keep these pages in the primary memory. Pages that not have been used since a long time are replaced with the most frequently used pages under the method called as Optimal Page Replacement technique.
The approach can be best explained by the below reference string and the frame size.

### Algorithm for Optimal Page Replacement

- Step 1: Push the first page in the stack as per the memory demand.
- Step 2: Push the second page as per the memory demand.
- Step 3: Push the third page until the memory is full.
- Step 4: As the queue is full, the page which is least recently used is popped.
- Step 5: repeat step 4 until the page demand continues and until the processing is over.
- Step 6: Terminate the program.