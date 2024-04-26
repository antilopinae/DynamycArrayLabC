#include <time.h>
#include <string.h>
#include "dynamic_array.h"
#include <stdio.h>


typedef struct{
    int a;
    int b;
}square;



typedef struct{
    char name_a;
    int sum_a_b;
    int mult_a_b;
}new_square;



int RANDOM(

        int a,
        int b

)
{

    return (rand()%(b))+a;
}



void print_square(

        const char * element,
        const u_int8_t null_frame_size

)
{

    square * pointer = malloc(sizeof(square));

    if(null_frame_size == sizeof(square))
    {
        memcpy(pointer, element, null_frame_size);
        printf("Simple square: a = %d, b = %d\n", pointer -> a, pointer -> b);
    }
    else
    {
        printf("\nSomething went wrong\n");
    }

}



void print_new_square(

        const char * element,
        const u_int8_t null_frame_size

)
{

    new_square * pointer = malloc(sizeof(new_square));

    if(null_frame_size == sizeof(new_square))
    {
        memcpy(pointer, element, null_frame_size);
        printf("New square: name = %c, multiplication a and b = %d, sum a and b = %d\n", pointer -> name_a, pointer -> mult_a_b, pointer -> sum_a_b);
    }
    else
    {
        printf("\nSomething went wrong\n");
    }

}



square * init_random_square()
{

    square * sq = malloc(sizeof(square));

    sq -> a = RANDOM(1,100);
    sq -> b = RANDOM(1,100);

    return sq;
}



void init_random()
{

    long int ltime;
    ltime=time(NULL);
    srand((unsigned) ltime/2);

}



char * simple_init(

        const u_int8_t null_frame_size,
        const u_int64_t array_length

)
{

    char * pointer = malloc(null_frame_size * array_length);
    u_int64_t _array_length = array_length;

    square * sq;
    while(_array_length>0){
        sq = init_random_square();

        memcpy(pointer + (array_length - _array_length) * null_frame_size, sq, null_frame_size);
        --_array_length;
    }

    return pointer;
}



int simple_where(

        const char * pointer,
        const u_int8_t null_frame_size

)
{

    struct{
        int a;
        int b;
    }square_copy;

    memcpy(&square_copy, pointer, null_frame_size);

    if(square_copy.a > square_copy.b)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}



char * simple_map(

        const char * pointer,
        const u_int8_t null_frame_size,
        u_int8_t * new_frame_size

)
{

    *new_frame_size = sizeof(new_square);

    struct{
        int a;
        int b;
    }square_copy;

    struct{
        char name_a;
        int sum_a_b;
        int mult_a_b;
    }new_square_copy;

    memcpy(&square_copy, pointer, null_frame_size);

    new_square_copy.name_a = (int)(square_copy.a);
    new_square_copy.mult_a_b = (square_copy.a) * (square_copy.b);
    new_square_copy.sum_a_b = (square_copy.a) + (square_copy.b);

    char * _pointer = malloc(sizeof(new_square));

    memcpy(_pointer, &new_square_copy, sizeof(new_square));

    return _pointer;
}



void test(

        const u_int64_t length

)
{

    char * pointer = simple_init(sizeof(square), length);

    square * _null_frame = malloc(sizeof(char*));

    _null_frame -> a = 0;
    _null_frame -> b = 0;

    array example = {
            .array_length = length,
            .capacity = length*2,
            .null_frame = (const char *) _null_frame,
            .null_frame_size = sizeof(square),
            .array_pointer = pointer
    };

    printf("\nCREATING EXAMPLE ARRAY WITH SQUARES:\n\n");

    print_array(&example, &print_square);

    array * example_p = grow(&example, length*3);

    printf("\nSTARTING MAP ON EXAMPLE ARRAY: SQUARE -> NEW SQUARE:\n\n");

    array * map_array = map(example_p, &simple_map);
    print_array(map_array, &print_new_square);
    free_array(map_array);

    printf("\nSTARTING WHERE ON EXAMPLE ARRAY WITH CONDITION: SQUARE A > SQUARE B:\n\n");

    array * where_array = where(example_p, &simple_where);
    free_array(example_p);
    print_array(where_array, &print_square);
    free_array(where_array);

    printf("\nSTARTING DUBLICATE EXAMPLE ARRAY:\n\n");

    array * all_array = add_all(&example, &example);
    print_array(all_array, &print_square);
    free_array(all_array);

    printf("\nARRAYS FREE, TEST CLOSED\n\n");

}



void start_testing()
{

    init_random();

    for(int i =0; i < 1; ++i)
    {
        test(RANDOM(10,30));
    }
    printf("TESTING STOPPED. SUCCESS\n\n");

}