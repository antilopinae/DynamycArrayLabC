#ifndef ERROR
#define ERROR


//TODO: Prints some definitions to user: (count rows of message, message).
extern void print_message(const int, char *[]);


//TODO: Check: if pointer is null throws message to user: (nullable pointer, count rows of message, message).
void error_pointer(const char *, const int, const char *[]);


//TODO: Close application and print error if pointer is null: (nullable malloc pointer, count rows of message, message).
extern void malloc_exception(const char *, const int, const char *[]);


//TODO: Close enable task and print error: (count rows of message, message).
extern void something_went_wrong(const int, const char *[]);


#endif