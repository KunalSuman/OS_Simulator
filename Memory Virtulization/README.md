This readme constains the assumptions made and details regarding how each program is working
        1. BS_pipes we implement merge sort by break ing a array into 2 halfs which in turn are broken into smaller arrays until we have 1 elemeent in each array now we merge them back together thorugh merge function in a sorted way, here in our code we break into child which creates an independent process which will work on broken half of the array and we recive back the data from these child using open pipes
                Refrence : lecture notes
        2. Memory_Segmentation we have taken the following assumptions:
                Code(00): starts at 32Kb and grows towards end(64kb) i.e. offset is added to base. Goes from 32Kb to 34kb.
                Heap(01): starts at 34Kb and grows towards end(64kb) i.e. offset is added to base. Goes from 34Kb to 37Kb.
                Stack(01): starts at 28Kb and grows towards 0Kb i.e. offset is substracted from base. Goes from 28Kb to 26Kb.
                Code will gice a segment fault in 3 cases:
                        Invalid segment is selected
                        Invalid Input (that is length of Hexadecimal input is not 4)
                        Bounds of a segment are violated
                Note: All the charecters of input should be in CAPITAL LETTERS.
                for eg.  12AB is a Valid Input,         but,    12ab is Invalid. 


        3. Virtual_Memory_TLB we simulate a TLB give hit if present on memroy or a miss if not present
                Assumptions : all the index starts form 1 and ends at 16 and size of tlb is 4 so it can hold 4 entries

        4. Paging_PTE_PD our page directory is of 1024 pages ande each pd is mapped to 1024 pt and each pt has a corrosponding physical_addr a
                Assumptions : all indexing starts form 0 to 1023 and 999 enties are already mapped from pde table and 24 enties are empty to simulate a miss
                              each page table is in the format of page_table_array[page_directory_int][page_table_index_integer] = page_directory_int*1000 + page_table_index_integer;
                              so that no to page tables point to same phy_addr which is calulated by the formula (PFN << offset) | offset due to this the physical addr recived is a lrge value of string.

        5. Page_replacement_clock_algo we have taken the following assumptions:
                An extra output is also being printed, to make it clearer for the TA, about what our program is doing.
                I am also taking a few extra inputs, apart from number of page frames, page requests.
                They are:
                        Number of Page Requests
                        Dirty Bit info, User can tell the program whether the dirty bit is 0 or 1
                Other assumption is that if all pages have dirty bit as 1, then i replace a page by first storing it in memory (It shows like that).

                In the end we get the standard output hits, faults and hit rate
