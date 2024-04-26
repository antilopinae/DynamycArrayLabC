#include <string.h>
#include <stdio.h>
#include "dynamic_array.h"



typedef struct Person{
    char* firstName;
    char* lastName;
}person;



enum menu
{
    STANDART_MENU,
    CHOOSE_PERSON_MENU,
    CREATE_PERSON_MENU,
    CHANGE_PERSON_MENU,
    CHANGE_PERSON_NAME_MENU,
    CHANGE_PERSON_LAST_NAME_MENU,
    DELETE_PERSON_MENU,
    EXIT_MENU
};



static int str_to_input(const char * str)
{

    int c = strtol(str, NULL, 10);

    return c;
}



void start_debug_example()
{

    printf("HELLO! There is a debug menu to test dynamic arrays. Wait a little..\n");
    printf("\n");

}



static void print_element(

        const char * element,
        const u_int8_t null_frame_size

)
{

    person * pointer = malloc(sizeof(person));

    if(null_frame_size == sizeof(person))
    {
        memcpy(pointer, element, null_frame_size);
        printf("Person first name: %s, last name: %s\n", pointer -> firstName, pointer -> lastName);
    }
    else
    {
        printf("\nSomething went wrong\n");
    }

}



static array ** init_array()
{

    person person1 = {
            .firstName = "ADMIN",
            .lastName = "ADMIN"
    };
    char * pointer = malloc(sizeof(person));

    memcpy(pointer, &person1, sizeof(person));

    array * array_p = create_array(2, 20, pointer, sizeof(person));

    array ** _pointer = malloc(sizeof(array **));

    memcpy(_pointer, &array_p, sizeof(array *));

    return _pointer;
}



static void __print_array(

        const array ** array_p

)
{

    printf("\nPrinting array..\n");
    printf("Array size: %d\n", (*array_p) -> array_length);
    if((*array_p) -> array_length <= 0)
    {
        *array_p = *init_array();
    }

    print_array((*array_p), &print_element);

    printf("\n");
}



static void print_person(

        const int index,
        const array * array_p

)
{

    char * element = get(array_p, index);

    person* pointer = malloc(sizeof(person));

    memcpy(pointer, element, (array_p) -> null_frame_size);

    printf("\nPerson first name: %s, last name: %s\n", pointer -> firstName, pointer -> lastName);
    printf("\n");

}



static void create_person(

        const array ** array_p,
        const char * first_name,
        const char * last_name
)
{
    person person1 = {
            .firstName = first_name,
            .lastName = last_name
    };

    char * pointer = malloc(sizeof(person));

    memcpy(pointer, &person1, sizeof(person));

    array * _array_p = add(*array_p, pointer);

    *array_p = _array_p;

}



static void delete_person(

        const array ** array_p,
        const int index

)
{

    array * _array_p = delete(*array_p, index);
    *array_p = _array_p;

}



const char * person_name;



static enum menu change_person_name_menu(

        const char * str,
        const array ** array_p,
        int * person

)
{

    enum menu _menu;

    person_name = str;

    printf("Please enter last name:\n");

    _menu = CHANGE_PERSON_LAST_NAME_MENU;

    return _menu;

}



static enum menu change_person_last_name_menu(

        const char * person_last_name,
        const array ** array_p,
        int * person

)
{

    printf("Changing person...\n");

    delete_person(array_p, *person);
    create_person(array_p, person_name, person_last_name);

    __print_array(array_p);

    printf("\nGo to menu..\n");
    enum menu _menu = STANDART_MENU;

    return  _menu;
}



static enum menu delete_person_menu(

        const char * str,
        const array ** array_p,
        int * person

)
{

    enum menu _menu;

    int input = str_to_input(str);

    if(input<0 || input > (* array_p) -> array_length - 1)
    {
        printf("Please input correct index:\n");
        _menu = DELETE_PERSON_MENU;
        return _menu;
    }
    else if(input == 0)
    {
        printf("\nGo to menu..\n");
        _menu = STANDART_MENU;
        return _menu;
    }

    delete_person(array_p, input);
    __print_array(array_p);

    printf("\nGo to menu..\n");
    _menu = STANDART_MENU;
    return _menu;
}



static enum menu change_person_menu(

        const char * str,
        const array ** array_p,
        int * person

)
{

    int input = str_to_input(str);

    enum menu _menu;

    if(input < 0 || input > 2)
    {
        printf("Please input correct number: 1 or 0:\n");
        _menu = CHANGE_PERSON_MENU;
        return _menu;
    }
    else if(input == 0)
    {
        printf("\nGo to menu..\n");
        _menu = STANDART_MENU;
        return _menu;
    }
    else if(input == 2)
    {
        printf("Input index of person to delete..\n");
        _menu = DELETE_PERSON_MENU;
        return _menu;
    }

    printf("Go to change this person..\nPlease enter first name:\n");
    _menu = CHANGE_PERSON_NAME_MENU;

    return _menu;
}



static enum menu create_person_menu(

        const char * str,
        const array ** array_p,
        int * person

)
{

    enum menu _menu;

    int input = str_to_input(str);

    if(input < 0 || input > 1)
    {
        printf("Please input correct number: 1 or 0:\n");
        _menu = CREATE_PERSON_MENU;
        return _menu;
    }
    else if(input == 0)
    {
        printf("\nGo to menu..\n");
        _menu = STANDART_MENU;
        return _menu;
    }

    printf("New person creating..\n");

    create_person(array_p, "TEST", "TEST");

    * person = (* array_p) -> array_length -1;

    printf("Please input correct number: 2 to delete new person, 1 to change, 0 to choose menu\n");

    _menu = CHANGE_PERSON_MENU;

    return _menu;
}



static enum menu choose_person_menu(

        const char * str,
        const array ** array_p,
        int * person

)
{

    int input = str_to_input(str);

    enum menu _menu;

    if(input < 0 || input > (* array_p) -> array_length)
    {
        printf("Please input correct number of person:\n");
        _menu = CHOOSE_PERSON_MENU;
        return _menu;
    }

    _menu = CHANGE_PERSON_MENU;

    *person = input;

    printf("Okay, you selected the person, now I'm print him...\n");
    print_person(*person, *array_p);
    printf("Please enter numbers: \'1\' to change new Person;\n\'0\' to to exit from this menu.\n");

    return _menu;
}



static enum menu standart_menu(

        const char * str,
        const array ** array_p,
        int * person

)
{

    enum menu _menu;

    if(*str == 'q')
    {
        _menu = EXIT_MENU;
        return _menu;
    }

    int input = str_to_input(str);

    if(input == 0)
    {
        printf("Please enter numbers: \'1\' to create new Person;\n\'0\' to to exit from this menu.\n");
        _menu = CREATE_PERSON_MENU;
        return _menu;
    }
    else if( input == 1 )
    {
        printf("Please input correct number of person:\n");
        _menu = CHOOSE_PERSON_MENU;
        return _menu;
    }
    else if( input == 2 )
    {
        printf("You didn't select person.\n");
        _menu = STANDART_MENU;
        return _menu;
    }
    else if( input == 3 )
    {
        __print_array(array_p);
        printf("\nGo to menu..\n");
        _menu = STANDART_MENU;
        return _menu;
    }
    else if( input == 4)
    {
        printf("Input index of person to delete..\n");
        _menu = DELETE_PERSON_MENU;
        return _menu;
    }
    else
    {
        printf("MENU selected, please enter numbers to edit person:\n");
        printf("\'0\' to create new Person;\n\'1\' to select person from array;\n\'2\' to change selected person params;\n\'3'\ to print your dynamic array;\n\'4'\ to delete some people;\n\'q\' to exit from debug mode.\n");

        _menu = STANDART_MENU;
        return _menu;
    }

}



typedef enum menu (*open_menu)(const char *, const array **, int* person);



static open_menu get_menu(

        enum menu _menu

)
{
    switch (_menu)
    {
        case STANDART_MENU: return &standart_menu;
        case CHOOSE_PERSON_MENU: return &choose_person_menu;
        case CREATE_PERSON_MENU: return &create_person_menu;
        case CHANGE_PERSON_MENU: return &change_person_menu;
        case CHANGE_PERSON_NAME_MENU: return &change_person_name_menu;
        case CHANGE_PERSON_LAST_NAME_MENU: return &change_person_last_name_menu;
        case DELETE_PERSON_MENU: return &delete_person_menu;
        case EXIT_MENU: return &standart_menu;
    }
}



static char* get_input()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);

    while(read == -1){
        read = getline(&line, &len, stdin);
    }

    line[strlen(line) - 1] = 0;

    char * pointer = malloc(sizeof(char)*len);

    memcpy(pointer, line, (strlen(line))*sizeof(char));


    free(line);

    return pointer;
}



void start_debugging()
{

    printf("...Debug program started, please enter the numbers from the keyboard for testing..\n");

    const array ** array_p = init_array();

    __print_array(array_p);

    enum menu _menu = STANDART_MENU;

    int * person = malloc(sizeof(int));

    printf("\nGo to menu..\n");

    printf("MENU selected, please enter numbers to edit person:\n");
    printf("\'0\' to create new Person;\n\'1\' to select person from array;\n\'2\' to change selected person params;\n\'3'\ to print your dynamic array;\n\'4'\ to delete some people;\n\'q\' to exit from debug mode.\n");

    while(1){
        if(_menu == EXIT_MENU)
        {
            return;
        }
        _menu = get_menu(_menu)(get_input(), array_p, person);
    }

}