#include <time.h>
#include <string.h>
#include "dynamic_array.c"
#include <stdio.h>


typedef struct{
    int name;
}simple_people;



typedef struct{
    char name;
}simple_men;



int RANDOM(int a, int b){
    return (rand()%(b))+a;
}



void initRandom()
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

    initRandom();

    while(_array_length>0){
        simple_people * people = malloc(sizeof(*people));
        people -> name = RANDOM(1,100);
        memcpy(pointer + (array_length - _array_length) * null_frame_size, people, null_frame_size);
        --_array_length;
    }

    return pointer;
}



size_t size_simple_men = sizeof(simple_men);



char * simple_map(

        const char * pointer,
        const u_int8_t null_frame_size,
        u_int8_t * new_frame_size

)
{

    struct{
        int name;
    }simple_copy;

    struct{
        char name;
    }simple_men_copy;

    *new_frame_size = size_simple_men;

    memcpy(&simple_copy, pointer, null_frame_size);

    if(simple_copy.name % 2 == 0)
    {
        simple_men_copy.name = 'A';
        printf("Oy men A \n");
    }
    else
    {
        simple_men_copy.name = 'B';
        printf("Oy men B \n");
    }
    char * _pointer = malloc(size_simple_men);
    memcpy(_pointer, &simple_men_copy, size_simple_men);

    return _pointer;
}



int start_testing()
{

    char * pointer = simple_init(sizeof(simple_people), 16);

    simple_people * _null_frame = malloc(sizeof(char*));
    _null_frame -> name = 0;

    array example = {
            .array_length = 16,
            .capacity = 20,
            .null_frame = (const char *) _null_frame,
            .null_frame_size = sizeof(simple_people),
            .array_pointer = pointer
    };

    grow(&example, 200);

    array * new_array = map(&example, &simple_map);

    free_array(new_array);
    printf("Array free\n");

    return 1;
}