#include <stdlib.h>
#include <string.h>
#include "error.h"

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
    char* debug[] = {"Exception in void GROW: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    u_int64_t _capacity = array_p -> capacity;
    const char * _null_frame = array_p -> null_frame;
    const u_int8_t _null_frame_size = array_p -> null_frame_size;

    const char * _new_pointer = malloc((array_p -> null_frame_size)*new_capacity);

    malloc_exception(_new_pointer, 1, debug);

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

    const char * pointer = malloc(sizeof(new_array));

    malloc_exception(pointer, 1, debug);

    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



typedef char * (*unary_operation)(const char *, const u_int8_t, u_int8_t *);



static array * map(

        const array * array_p,
        const unary_operation operation

)
{

    char* debug[] = {"Exception in void MAP: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    u_int64_t _array_length = array_p -> array_length;
    const u_int8_t _null_frame_size = array_p -> null_frame_size;

    const char * _old_pointer = malloc(_null_frame_size*(array_p -> capacity));

    memcpy(_old_pointer, array_p -> array_pointer, _null_frame_size*_array_length);

    u_int8_t _new_frame_size1;
    u_int8_t _new_frame_size2;

    operation(_old_pointer, _null_frame_size, &_new_frame_size1);

    char* debug2 = {"Error with size of elements in new array"};

    if(_new_frame_size1 <1 )
    {
        print_message(1, debug2);
        exit(0);
    }

    const char * _new_pointer = malloc((_new_frame_size1)*(array_p -> capacity));

    malloc_exception(_new_pointer, 1, debug);

    const char * result;
    u_int64_t _new_array_length = 0;

    char * __old_pointer = _old_pointer;


    while(_array_length > 0)
    {
        result = operation(__old_pointer, _null_frame_size, &_new_frame_size2);
        if(_new_frame_size2 != _new_frame_size1)
        {
            print_message(1, debug2);
            exit(0);
        }
        memcpy(_new_pointer + _new_array_length * _new_frame_size1, result, _new_frame_size1);
        --_array_length;
        ++_new_array_length;
        __old_pointer += (_null_frame_size);
    }

    const array new_array = {
            .array_length = array_p -> array_length,
            .array_pointer = _new_pointer,
            .capacity = array_p -> capacity,
            .null_frame = array_p -> null_frame,
            .null_frame_size = _new_frame_size1
    };

    const char * pointer = malloc(sizeof(new_array));

    malloc_exception(pointer, 1, debug);

    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



typedef int (*unary_condition)(const char *, const u_int8_t);



static array * where(

        const array * array_p,
        const unary_condition condition

)
{

    char* debug[] = {"Exception in void WHERE: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    u_int64_t _new_length = 0;
    u_int64_t _old_length = array_p -> array_length;
    const u_int8_t _null_frame_size = array_p -> null_frame_size;

    const char * _new_pointer = malloc((array_p -> null_frame_size)*(array_p -> array_length));

    const char * _old_pointer = malloc((array_p -> null_frame_size)*(array_p -> array_length));

    malloc_exception(_new_pointer, 1, debug);
    malloc_exception(_old_pointer, 1, debug);

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

    malloc_exception(pointer, 1, debug);

    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



static void free_array(

        const array * array_p

)
{
    char* debug[] = {"Exception in void FREE_ARRAY: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    free(array_p -> array_pointer);
    free(array_p);

}



static array * add_all(

        const array * array_first,
        const array * array_second

)
{

    char* debug[] = {"Exception in void ADD_ALL: DYNAMYC_ARRAY.C"};

    error_pointer(array_first, 1, debug);
    error_pointer(array_second, 1, debug);

    const u_int8_t _null_frame_size = array_first -> null_frame_size;
    const u_int64_t _length_first = array_first -> array_length;
    const u_int64_t _length_second = array_second -> array_length;


    if(_null_frame_size != array_second -> null_frame_size)
    {
        exit(0);
    }

    char * _new_pointer = malloc(_null_frame_size * (_length_first + _length_second));

    malloc_exception(_new_pointer, 1, debug);

    memcpy(_new_pointer, array_first -> array_pointer, _length_first * _null_frame_size);
    memcpy(_new_pointer + _length_first * _null_frame_size, array_second -> array_pointer, _length_second * _null_frame_size);


    array new_array = {
            .array_length = _length_first+_length_second,
            .array_pointer = _new_pointer,
            .capacity = array_first -> capacity + array_second -> capacity,
            .null_frame = array_first -> null_frame,
            .null_frame_size = _null_frame_size
    };

    char * pointer = malloc(sizeof(new_array));

    malloc_exception(pointer, 1, debug);

    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}




static array * add(

        const array * array_p,
        const char * el_p

)
{

    char* debug[] = {"Exception in void ADD: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    const u_int64_t _capacity = array_p -> capacity;
    const u_int64_t _length = array_p -> array_length;
    const u_int8_t _null_frame_size = array_p -> null_frame_size;

    const char * _array_pointer = malloc(_null_frame_size * (_length+1));

    memcpy(_array_pointer, array_p -> array_pointer, _null_frame_size * _length);
    memcpy(_array_pointer + _null_frame_size * _length, el_p, _null_frame_size);

    array new_array = {
            .array_length = _length + 1,
            .array_pointer = _array_pointer,
            .capacity = array_p -> capacity + 1,
            .null_frame = array_p -> null_frame,
            .null_frame_size = _null_frame_size
    };

    char * pointer = malloc(sizeof(new_array));

    malloc_exception(pointer, 1, debug);

    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



static char * get(

        const array * array_p,
        const int index

)
{

    char* debug[] = {"Exception in void GET: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    const char * element = array_p -> array_pointer + index * array_p -> null_frame_size;

    return element;
}



static array * delete(

        const array * array_p,
        const int index

)
{

    char* debug[] = {"Exception in void DELETE: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    const u_int64_t _length = array_p -> array_length;
    const u_int8_t _null_frame_size = array_p -> null_frame_size;
    const char * _pointer = array_p -> array_pointer;

    const u_int8_t _len = (index) * _null_frame_size;

    memcpy(_pointer + _len, _pointer + _len - _null_frame_size, (_length-_len-1)*_null_frame_size);

    array new_array = {
            .array_length = array_p -> array_length -1,
            .array_pointer = _pointer,
            .capacity = array_p -> capacity,
            .null_frame = array_p -> null_frame,
            .null_frame_size = array_p -> null_frame_size
    };

    char * pointer = malloc(sizeof(new_array));

    malloc_exception(pointer, 1, debug);

    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



static array * create_array(

        const u_int64_t array_length,
        const u_int64_t array_capacity,
        const char * null_frame,
        const u_int8_t null_frame_size

)
{

    char* debug[] = {"Exception in void CREATE_ARRAY: DYNAMYC_ARRAY.C"};

    error_pointer(null_frame, 1, debug);

    u_int64_t _old_length = array_length;
    const char * _new_pointer = malloc(null_frame_size * array_capacity);

    malloc_exception(_new_pointer, 1, debug);

    while(_old_length > 0){
        memcpy(_new_pointer + (array_length - _old_length) * null_frame_size, null_frame, null_frame_size);
        --_old_length;
    }

    array new_array = {
            .array_length = array_length,
            .array_pointer = _new_pointer,
            .capacity = array_capacity,
            .null_frame = null_frame,
            .null_frame_size = null_frame_size
    };

    char * pointer = malloc(sizeof(new_array));

    malloc_exception(pointer, 1, debug);

    memcpy(pointer, &new_array, sizeof(new_array));

    return (array *) pointer;
}



typedef void ( *print )( const char *, const u_int8_t);


static void print_array(

        const array * array_p,
        const print print_output

)
{

    char* debug[] = {"Exception in void PRINT_ARRAY: DYNAMYC_ARRAY.C"};

    error_pointer(array_p, 1, debug);

    const char * _pointer = array_p -> array_pointer;
    const u_int8_t _null_frame_size = array_p -> null_frame_size;
    const u_int64_t _length = array_p -> array_length;

    u_int64_t _old_length = array_p -> array_length;

    while(_old_length > 0){
        print_output(_pointer + (_length - _old_length) * _null_frame_size, _null_frame_size);
        --_old_length;
    }

}