#include <stdlib.h>
#include "dynamic_array.c"

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY


////dynamic array
//typedef struct Array{
//    u_int64_t array_length;
//    const char * array_pointer;
//    const u_int64_t capacity;
//    const char * null_frame;
//    const u_int8_t null_frame_size;
//}array;


//TODO: Update dynamic array: ( previous pointer to array, new array capacity ) -> new array with new capacity.
static array * grow ( const array *, const u_int64_t );


//TODO: Operation for Map-Function: ( pointer to previous element, size of previous element, pointer to size of new element from Map-Function ) -> pointer to new element.
typedef char * ( *unary_operation )( const char *, const u_int8_t, u_int8_t * );

//TODO: Return new dynamic array: (previous pointer to array, function for map-func) -> new array with new elements.
static array * map( const array *, unary_operation );


//TODO: Condition for Where-Function: ( pointer to previous element, size of previous element from array ) -> '1' (true) or '0' (false).
typedef int ( *unary_condition )( const char *, const u_int8_t null_frame_size );

//TODO: Return new dynamic array: (previous pointer to array, condition for where-func) -> new array with new elements, which implement condition with '1' (true).
static array * where( const array *, unary_condition );


//TODO: Return new dynamic array: (previous pointer to array first, previous pointer to array last) -> new array with both of arrays: array first + array last. Do nothing if elements are different in both arrays.
static array * add_all( const array *, const array * );


//TODO: Return new dynamic array: (previous pointer to array first, previous pointer to new element) -> new array with this array plus new element. Do nothing if elements are different.
static array * add( const array *, const char * );


//TODO: Return element from dynamic array: (previous pointer to array, index of element) -> pointer to this element. Do nothing if index are incorrect.
static char * get( const array *, const int );


//TODO: Return new dynamic array without element: (previous pointer to array first, index of element for remove) -> new array without this element. Do nothing if index are incorrect.
static array * delete( const array *, const int );


//TODO: Return new dynamic array: ( length of new array, length of capacity of new array, pointer to data of nullable array element, size of this element) -> new array witch all elemnts were copied from nullable element.
static array * create_array( const u_int64_t, const u_int64_t, const char *, const u_int8_t );


//TODO: Free dynamic array from the pointer, also free all pointers in it.
static void free_array( const array * );


//TODO: Print one element from array: (pointer to this element, size of this element) -> print element.
typedef void ( *print )( const char *, const u_int8_t );

//TODO: Prints array and nothing else.
static void print_array( const array *, const print );



#endif