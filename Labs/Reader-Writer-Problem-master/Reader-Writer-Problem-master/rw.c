#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t mutex, wrt;
int readcount;

void *Reader(void *arguments);
void *Writer(void *arguments);
char prevdata[500];

struct SharedQNode
{
        char msg[500];
        struct SharedQ *link;
};

struct SharedQ
{
        struct SharedQNode *front;
        struct SharedQNode *rear;
        int size;
};


struct SharedQ *createNewQ()
{
        struct SharedQ *q = (struct SharedQ*)malloc(sizeof(struct SharedQ));
        q->front = q->rear = NULL;
        q->size = 0;
        return q;
}

void enQueue(struct SharedQ *q, char data[500])
{
        struct SharedQNode *temp = (struct SharedQNode*)malloc(sizeof(struct SharedQNode));
        strcpy(temp->msg, data);
        temp->link = NULL;
        if (q->rear == NULL)
        {
                q->front = q->rear = temp;
                q->size = q->size + 1;
                PrintQ(q);
                return;
        }

        q->rear->link = temp;
        q->rear = temp;
        q->size = q->size + 1;
        PrintQ(q);
}

void PrintPrevQ(struct SharedQ *q)
{
        struct SharedQNode *temp = q->front;
        printf("\nQueue contains :\n");
        while (temp != NULL && strcmp(temp->msg, prevdata)!=0)
        {
                printf("%s", temp->msg);
                temp = temp->link;
        }
}

void PrintQ(struct SharedQ *q)
{
        struct SharedQNode *temp = q->front;
        printf("\nWriting to queue successfull. Queue contains :\n");
        while (temp != NULL)
        {
                printf("%s", temp->msg);
                temp = temp->link;
        }
}

void PrintQElement(struct SharedQ *q, int index)
{
        struct SharedQNode *temp = q->front;
        printf("\nElement %d is : ", index);
        int ctr = 1;
        while (temp != NULL && ctr < index)
        {
                temp = temp->link;
                ctr = ctr + 1;
        }
        printf("%s\n", temp->msg);
}

struct SharedQ *q;
int main()
{
        q = createNewQ();
        int i = 0, ReaderCount = 0, WriterCount = 0;
        sem_init(&mutex, 0, 1);
        sem_init(&wrt, 0, 1);

        pthread_t Readers[100], Writers[100];

        printf("\nEnter number of Readers thread (Max 100) : ");
        if (scanf("%d", &ReaderCount) <= 0 || ReaderCount < 1 || ReaderCount > 100)
        {
                printf("Scanf error: Only positive numbers expected\n");
                return 0;
        }

        printf("\nEnter number of Writers thread (Max 100) : ");
        if (scanf("%d", &WriterCount) <= 0 || WriterCount < 1 || WriterCount > 100)
        {
                printf("Scanf error: Only positive numbers expected\n");
                return 0;
        }
        getchar();

        for(i = 0; i < ReaderCount; i++)
                pthread_create(&Readers[i], NULL, Reader, (void *)i);

        for(i = 0; i < WriterCount; i++)
                pthread_create(&Writers[i], NULL, Writer, (void *)i);

        for(i = 0; i < WriterCount; i++)
                pthread_join(Writers[i], NULL);

        for(i = 0; i < ReaderCount; i++)
                pthread_join(Readers[i], NULL);

        sem_destroy(&wrt);
        sem_destroy(&mutex);
        printf("\n");
        return 0;
}

void *Reader(void *arguments)
{
        do
        {
                sleep(1);
                int readerid = (int)arguments;
                sem_wait(&mutex);
                readcount++;
                if(readcount == 1)
                {
                        sem_wait(&wrt);
                        int choice;
                        printf("\nReader %d Menu: ", readerid);
                        printf("\n1. Print Queue contents.");
                        printf("\n2. Print a Queue entry.");
                        printf("\n3. Quit");
                        printf("\nEnter your choice (1-3) : ");
                        if (scanf("%d", &choice) <= 0)
                        {
                                printf("Scanf error: Only numbers expected\n");
                                exit(0);
                        }
                        if (choice == 1)
                                PrintPrevQ(q);
                        else if (choice == 2)
                        {
                                int index;
                                printf("\nQueue size is = %d", q->size);
                                if (q->size == 0)
                                {
                                        printf("\nQueue does not contain any element yet.\n");
                                }
                                else
                                {
                                        printf("\nEnter Index (1-%d) : ", q->size);
                                        scanf("%d", &index);
                                        if (index < 1 || index > q->size)
                                        {
                                                printf("\nIndex Error: Index out of bounds.\n");
                                                exit(0);
                                        }
                                        else if (index == q->size)
                                        {
                                                printf("\nElement Access Error: Cannot access this element.\n");
                                                exit(0);
                                        }
                                        PrintQElement(q, index);
                                }
                        }
                        else if (choice == 3)
                        {
                                printf("\nReader %d quitted\n", readerid);
                                pthread_cancel(pthread_self());
                        }
                        else
                        {
                                printf("\nInput Error: Invalid choice input.\n");
                                exit(0);
                        }
                }

                sem_post(&mutex);
                sem_wait(&mutex);
                readcount--;
                if(readcount == 0)
                        sem_post(&wrt);
                sem_post(&mutex);

        } while(1);
}

void *Writer(void *arguments)
{
        do
        {
                sleep(1);
                int writerid = (int)arguments;
                sem_wait(&wrt);
                char msg[100];
                int choice;
                printf("\n\nWriter %d Menu : ", writerid);
                printf("\n1. Write to Queue.");
                printf("\n2. Quit");
                printf("\nEnter your choice (1 or 2) : ");
                if (scanf("%d", &choice) <= 0)
                {
                        printf("Scanf error: Only numbers expected\n");
                        exit(0);
                }
                getchar();
                if (choice == 1)
                {
                        printf("\nEnter message : ");
                        fgets(msg, sizeof(msg), stdin);
                        if (strcmp(msg, "\n")==0)
                        {
                                printf("\nMessgae error: Proper text message expected\n");
                                exit(0);
                        }
                        enQueue(q, msg);
                        strcpy(prevdata, msg);
                }
                else if (choice == 2)
                {
                        printf("\nWriter %d quitted\n", writerid);
                        pthread_cancel(pthread_self());
                }
                else
                {
                        printf("\nInput Error: Invalid choice input.\n");
                        exit(0);
                }
                sem_post(&wrt);

        } while(1);
}
