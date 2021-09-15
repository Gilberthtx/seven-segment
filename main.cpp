#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <vector>

struct arguments
{
    int digit;
    int seg[7];

    void printOutput()
    {
        std::cout << digit << " = ";
        for (int i = 0; i < 7; i++)
        {
            std::cout << seg[i];
            if (i != 6)
            {
                std::cout << " ";
            }
        }
    }
};

void *myFunction(void *arg_void_ptr)
{
    struct arguments *arg_ptr = (struct arguments *)arg_void_ptr;
    int segments[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, //0
        {0, 1, 1, 0, 0, 0, 0}, //1
        {1, 1, 0, 1, 1, 0, 1}, //2
        {1, 1, 1, 1, 0, 0, 1}, //3
        {0, 1, 1, 0, 0, 1, 1}, //4
        {1, 0, 1, 1, 0, 1, 1}, //5
        {1, 0, 1, 1, 1, 1, 1}, //6
        {1, 1, 1, 0, 0, 0, 0}, //7
        {1, 1, 1, 1, 1, 1, 1}, //8
        {1, 1, 1, 1, 0, 1, 1}  //9
    };

    for (int i = 0; i < 7; i++)
    {
        arg_ptr->seg[i] = segments[arg_ptr->digit][i];
    }
    return nullptr;
}

int main()
{
    long num = 0;
    int numLength = 0;
    std::cin >> num;
    long numCopy = num;

    while (numCopy != 0)
    {
        numCopy /= 10;
        numLength++;
    }

    static int NTHREADS = numLength;
    pthread_t tid[NTHREADS];
    static std::vector<arguments> arg(NTHREADS);

    for (int i = 0; i < NTHREADS; i++)
    {
        arg[i].digit = num % 10;
        num /= 10;
        if (pthread_create(&tid[i], nullptr, myFunction, &arg[i]) != 0)
        {
            std::cerr << "Error creating thread" << std::endl;
            return 1;
        }
    }
    //Wait for threads to finish
    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(tid[i], nullptr);
    }
    for (int i = numLength - 1; i >= 0; i--)
    {
        arg[i].printOutput();
        if (i != 0)
        {
            std::cout << std::endl;
        }
    }
    return 0;
};
