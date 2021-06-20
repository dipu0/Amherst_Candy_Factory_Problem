/*Amherst Candy Factory Problem
Group no-03
Group Members:
Md Asad Chowdhury Dipu _ ID:2019-1-60-093
Md Mizanur Rahman Riad Khan _ ID: 2019-1-60-094
Kazi Mostaq Hridoy _ ID:2019-1-60-098
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MaxItems 100
#define BufferSize 100
int empty;
sem_t semEmpty;
sem_t semFull;
int full=0,nCandy=0;
int in = 0, out = 0;
int i=0, j=0, ci=0;
int packi=0,packj=0;
int buffer[BufferSize];
int item, bs;
int Maxcandy=100;
int pack[100][100];
int packflag=0;
char CandyList[BufferSize][BufferSize];
pthread_mutex_t mutex;

void input_candy()
{
    int cx;

    printf("Enter number of candy producer want to produce: ");
    scanf("%d",&nCandy);
    for(cx=1;cx<=nCandy;cx++)
    {
        printf("Candy %d: ",cx);
        scanf("%s",&CandyList[cx]);
    }

}

int candy()
{
    int c;
    int cd;
    for(cd=1;cd<=nCandy;cd++)
    {
        printf("%d. %s \n",cd,&CandyList[cd]);
    }
    CandyList[c];
    printf("Which Candy Producer want to produce: ");
    scanf("%d",&c);
        return c;
}
void printcandy(int c)
{
   printf(" %s ",&CandyList[c]);

}

void printpacket()
{
    int q=0;
    for(int t=0; t<packi; t++)
    {
        if(pack[t][q]==-1)
        {
            break;
        }
        printf("Package %d : ",t+1);
        for(;;)
        {

            printf(" ");
            printcandy(pack[t][q]);
            printf(" , ");
            q++;
            if(pack[t][q]==-1)
            {
                q=0;
                break;
            }
        }
        printf("\n");
    }
}

void *producer(void *pno)
{

    empty--;
    sem_wait(&semEmpty);
    pthread_mutex_lock(&mutex);

    buffer[in]=item;

    in = (in+1)%bs;

    pthread_mutex_unlock(&mutex);
    full++;
    i++;
    sem_post(&semFull);
    pthread_exit(NULL);
}
void *consumer(void *cno)
{
    full--;
    sem_wait(&semFull);
    pthread_mutex_lock(&mutex);

    pack[packi][packj]=buffer[out];
    packj++;
    if(packj==Maxcandy)
    {
        packi++;
        packj=0;
    }

    buffer[out]=-1;
    packflag++;

    out = (out+1)%bs;
    pthread_mutex_unlock(&mutex);
    //empty++;
    j++;
    //sem_wait(&semFull);
    sem_post(&semEmpty);
    pthread_exit(NULL);

}

int main()
{
    printf("Enter Buffer Size (1-100) :");
    scanf("%d",&bs);
    empty=bs;
    int n;
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);

    for(int k=0; k<bs; k++)
    {
        buffer[k]=-1;
    }
    printf("Enter max candy in a package: ");
    scanf("%d",&Maxcandy);

    input_candy();


    for(int t=0; t<100; t++)
    {
        for(int q=0; q<100; q++)
        {
            pack[t][q]=-1;
        }
    }

    pthread_t pro[MaxItems],con[MaxItems];
    pthread_mutex_init(&mutex, NULL);

    while(1)
    {
        printf("\n1. Producer\n2. Consumer\n3. Show Candy in Package\n4. Exit\n");
        printf("\nEnter your choice:");
        scanf("%d",&n);

        if(n==1)
        {
            int h,pPro;
            printf("How many candy you want to produce: ");
            scanf("%d",&pPro);
            for(h=0; h<pPro; h++)
            {
                if(empty>=1)
                {
                    item=candy();
                    pthread_create(&pro[i], NULL, (void *)producer, NULL);
                    printf("Producer %d: produce candy ", i+1);
                    printcandy(item);
                    printf(" in buffer %d\n",in);


                }
                else
                {
                    printf("Buffer is full. Producer cannot produce candy now.\n");
                }

            }

        }
        else if(n==2)
        {
            int v,pCon;
            printf("How many candy you want to consume: ");
            scanf("%d",&pCon);
            for(v=0; v<pCon; v++)
            {
                if(full>0)
                {

                    pthread_create(&con[j], NULL, (void *)consumer, NULL);
                    printf("Consumer %d: consume candy ", j+1);
                    printcandy(buffer[out]);
                    printf(" from buffer %d\n",ci);
                    ci = (ci+1)%bs;
                }


                else
                {
                    printf("Buffer is empty. consumer cannot consume candy now.\n");
                }
            }

        }
        else if(n==3)
        {
            if(packflag!=0)
            {
                printpacket();
            }
            else
            {
                printf("Candies hasn't packed yet\n");
            }

        }
        else if(n=4)
        {
            exit(0);
        }
        else
        printf("Wrong Choice.\n");

    }
    pthread_mutex_destroy(&mutex);
    return 0;
}



