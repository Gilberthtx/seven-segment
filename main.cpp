#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>

struct arguments
{
    int digit;
    int segVals[10][7] =
        {{1, 1, 1, 1, 1, 1, 0},
         {0, 1, 1, 0, 0, 0, 0},
         {1, 1, 0, 1, 1, 0, 1},
         {1, 1, 1, 1, 0, 0, 1},
         {0, 1, 1, 0, 0, 1, 1},
         {1, 0, 1, 1, 0, 1, 1},
         {1, 0, 1, 1, 1, 1, 1},
         {1, 1, 1, 0, 0, 0, 0},
         {1, 1, 1, 1, 1, 1, 1},
         {1, 1, 1, 1, 0, 1, 1}};
};

void *myFunction(void *params)
{
    int threadNumber = *((int *)params);
    std::cout << threadNumber << std::endl;
    return nullptr;
}

int main()
{
    long num = 0;
    int numLength = 0;

    std::cout << "Enter an integer: " << std::endl;
    std::cin >> num;
    long numCopy = num;

    std::cout << "numcopy init: " << numCopy << std::endl;

    while (numCopy != 0)
    {
        numCopy /= 10;
        numLength++;
        std::cout << "numcopy: " << numCopy << std::endl;
    }

    static int NTHREADS = numLength;
    pthread_t tid[NTHREADS];
    static struct arguments arg[10];

    for (int i = 0; i < NTHREADS; i++)
    {
        arg[i].digit = i;
        if (pthread_create(&tid[i], nullptr, myFunction, &arg[i]) != 0)
        {
            std::cerr << "Error creating thread" << std::endl;
            return 1;
        }
    }

    //Wait for threads to finish
    for (int i = 0; i < NTHREADS; i++)
        pthread_join(tid[i], nullptr);
    std::cout << "Child threads ends" << std::endl;
    std::cout << "number of digits: " << numLength << std::endl;

    return 0;
};