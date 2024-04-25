#include <stdlib.h>
#include <string.h>

//dynamic array
typedef struct Array{
    u_int64_t array_length;
    const char * array_pointer;
    const u_int64_t capacity;
    const char * null_frame;
    const u_int8_t null_frame_size;
}array;



static array * grow(

        const array * array_p,
        const u_int64_t new_capacity

        )
{

    u_int64_t _capacity = array_p -> capacity;
    const char * _null_frame = array_p -> null_frame;
    u_int8_t _null_frame_size = array_p -> null_frame_size;

    char * _new_pointer = malloc((array_p -> null_frame_size)*new_capacity);

    memcpy(_new_pointer, array_p -> array_pointer, (array_p -> null_frame_size)*(array_p -> array_length));

    while(new_capacity-_capacity>0){
        memcpy(_new_pointer+_capacity * _null_frame_size, _null_frame, _null_frame_size);
        ++_capacity;
    }

    array new_array = {
            .array_length = array_p -> array_length,
            .array_pointer = _new_pointer,
            .capacity = new_capacity,
            .null_frame = array_p -> null_frame,
            .null_frame_size = array_p -> null_frame_size
    };

    char * pointer = malloc(sizeof(new_array));
    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



typedef char * (*unary_operation)(const char *, const u_int8_t, u_int8_t *);



static array * map(

        const array * array_p,
        unary_operation operation

        )
{

    u_int64_t _array_length = array_p -> array_length;
    u_int8_t _null_frame_size = array_p -> null_frame_size;

    char * _old_pointer = malloc((array_p -> null_frame_size)*(array_p -> capacity));

    memcpy(_old_pointer, array_p -> array_pointer, (array_p -> null_frame_size)*(array_p -> array_length));

    u_int8_t _new_frame_size1;
    u_int8_t _new_frame_size2;

    operation(_old_pointer, _null_frame_size, &_new_frame_size1);

    if(_new_frame_size1 <1 )
    {
        exit(0);
    }

    char * _new_pointer = malloc((_new_frame_size1)*(array_p -> capacity));

    char * result;
    u_int64_t _new_array_length = 0;

    while(_array_length > 0)
    {
        result = operation(_old_pointer, _null_frame_size, &_new_frame_size2);
        if(_new_frame_size2 != _new_frame_size1)
        {
            exit(0);
        }
        memcpy(_new_pointer+_new_array_length * _new_frame_size1, result, _new_frame_size1);
        --_array_length;
    }

    array new_array = {
            .array_length = array_p -> array_length,
            .array_pointer = _new_pointer,
            .capacity = array_p -> capacity,
            .null_frame = array_p -> null_frame,
            .null_frame_size = _new_frame_size1
    };

    char * pointer = malloc(sizeof(new_array));
    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



typedef int (*unary_condition)(const char *, const u_int8_t null_frame_size);



static array * where(

        const array * array_p,
        const unary_condition condition

        )
{

    u_int64_t _new_length = 0;
    u_int64_t _old_length = array_p -> array_length;
    u_int8_t _null_frame_size = array_p -> null_frame_size;

    char * _new_pointer = malloc((array_p -> null_frame_size)*(array_p -> array_length));

    char * _old_pointer = malloc((array_p -> null_frame_size)*(array_p -> array_length));

    memcpy(_old_pointer, array_p -> array_pointer, (array_p -> null_frame_size)*(array_p -> array_length));

    while(_old_length>0)
    {
        if(condition(_old_pointer, _null_frame_size))
        {
            memcpy(_new_pointer + _new_length * _null_frame_size, _old_pointer, _null_frame_size);
            ++_new_length;
        }
        --_old_length;
        _old_pointer += _null_frame_size;
    }

    array new_array = {
            .array_length = _new_length,
            .array_pointer = _new_pointer,
            .capacity = array_p -> capacity,
            .null_frame = array_p -> null_frame,
            .null_frame_size = array_p -> null_frame_size
    };

    char * pointer = malloc(sizeof(new_array));
    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



static void free_array( const array * array_p)
{
    free(array_p -> array_pointer);
    free(array_p);
}



static array * add_all(

        const array * array_first,
        const array * array_second

)
{

}




static array * add( const array *, const char * );
{

}



static char * get( const array *, const int );
{

}



static array * delete( const array *, const int );
{

}



static array * create_array( u_int64_t, const u_int64_t, const char *, const u_int8_t );
{

}



typedef void ( *print )( const char *, const u_int8_t );


static void print_array( const array *, print );
{

}