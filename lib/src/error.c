#include <stdio.h>
#include <stdlib.h>

//char* arg[] = {"something went wrong", "sorry"};



void print_message(int argc, char * argv[])
{

    for (int i = 0; i < argc; i++)
    {
        printf("%s \n", argv[i]);
    }

}



void null_pointer_exception(int argc, char * argv[])
{

    print_message(argc, argv);
    printf("[NULL POINTER EXCEPTION]\n");

}



void error_pointer(char * pointer, int argc, char * argv[])
{
    if(!pointer)
    {
        null_pointer_exception(argc, argv);
    }
}



void malloc_exception(char * pointer, int argc, char * argv[])
{

    if(!pointer)
    {
        null_pointer_exception(argc, argv);
        printf("MALLOC EXCEPTION. APPLICATION WILL CLOSE.\n");
        exit(1);
    }

}



void something_went_wrong(int argc, char * argv[])
{

    print_message(argc, argv);
    printf("[EXCEPTION]\n");

}