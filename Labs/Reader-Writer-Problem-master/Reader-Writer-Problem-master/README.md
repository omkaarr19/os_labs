# Reader-Writer-Problem
C Code for readers-writers problem in OS.

## Operating Systems Assignment-3
(Group No.-32)
Sneha Sinha: 2016098
Ritu Kumari: 2016078

### 1. Description Of Code

##### - Main function :
        1. Creates a new Queue.
        2. Initialises 2 semaphores, namely mutex and wrt. "mutex" is used for keeping track of the no, of readers, whereas "wrt" can be regarded as lock on the queue.
        3. Pthreads are then created according to the user input.

##### - Reader function : Serves the reading purpose of multiple readers via menu.
        1. The reader first tries to get "mutex" via "sem_wait", in order to tell that first reader has arrived.
        2. If it gets it, the readercount is incremented by that process only.
        3. If the process is the first process to read from the shared queue, then "wrt" semaphore is also acquired so as to prevent the writers from updating the contents of the queue at that time.
        4. Reader menu provides (based upon the choice of the user):
                i) Printing entire queue elements, except the current written one. (Call to the PrintPrevQ() function).
                ii) Printing an element based upon the index entered by the user, except the current written one. (1-based indexing is followed, Call to the PrintQElement() functiom).
                iii) Reader can quit anytime.
        5. "sem_post" on "mutex" allows other reader process to read from the queue.
        6. Again the "mutex" is acquired so as to now decrement the readercount.
        7. If no readers are left, "wrt" lock on the shared queue is lifted to allow writers to write.
        8. Lock on "mutex" is also lifted as no readers are left now.
        9. Above procedure also maitains atomicity among the readers.

##### - Writer function : Serves the writing purpose of multiple writers via menu.
        1. First the lock on "wrt" is acquired, signalling that a writer process has arrived and only 1 writer at a time can do the updation.
        2. Writer menu provides (based upon the choice of the user):
                i) Proper message is received from the user and enQueue() function is called.
                ii) Writer can quit anytime.
        3. Lock on "wrt" is lifted, signalling that now the lock on shared queue can be acquired by other writer processes.

##### - PrintPrevQ function :
        Prints the contents of the shared queue, except the last written one. (Performs reading)

##### - enQueue function :
        Enqueues a new message by a writer into the shared queue.

##### - PrintQ function :
        Prints all the contents of the shared queue.

##### - PrintQElement function :
        Prints an element from the queue based upon its index.

### 2. Compiling And Testing

- Ensure that the Makefile and the source code are in the same directory.
- In the terminal, type:
####
        1. make
        2. ./rw
- To terminate the program, quit from all the reader-writer threads. (Option is provided in the menu).

### 3. Inputs To Give

The code is user-friendly (No need to give arguments at command line).
- Enter the no. of reader and writer threads (Must be between 1 and 100 [inclusive]).
- Provide proper messages when asked.
- Provide proper choice for menus as is asked.
- Provide proper index while printing a specific element. 1-based indexing is followed. Since the reader cannot access the current written element, do not provide the index equal to queue size (will give Element Access Error).

### 4. Expected Output

- Only 1 writer should write to the shared queue at a time.
- Multiple readers should read from the shared queue.
- Messages read by the readers should not be the current written message, irrespective of the writer.
- Specific messages that readers want to read from the queue.
- Menu-driven functionality is provided.
- Pthreads may generate random outputs (Outputs need not be same after each run), but above rules should follow.

### 5. Error Value And Interpretation

##### - Scanf Error:- 
        If argument provided by the user is
                1. Not a number
                2. A number < 1 or > 100 (when providing No. of reader/writers)

##### - Message Error:- 
        If the message provided by the user is newline.

##### - Index Error:- 
        If the index entered while seeking a message at a specific index in the shared queue is < 1 or > the queue size.

##### - Element Access Error:- 
        If the index entered while seeking a message at a specific index in the shared queue is equal to the queue size since seeking current written elements is not allowed.

##### - Input Error:- 
        If the choice entered is not what is expected.
