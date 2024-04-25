#include <string.h>
#include <stdio.h>
#include "dynamic_array.h"



typedef struct Person{
    char* firstName;
    char* lastName;
}person;



static void print_element(

        const char * element,
        const u_int8_t null_frame_size

        )
{

    person* pointer = malloc(sizeof(person));

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



static void _print_array(


        const array * array_p

        )
{

    printf("\nPrinting array..\n");
    printf("Array size: %d\n", array_p -> array_length);


    print_array(array_p, &print_element);
    printf("\n");
}



static array ** init_array()
{

    person person1 = {
            .firstName = "Admin",
            .lastName = "Tester"
    };
    char * pointer = malloc(sizeof(person));

    memcpy(pointer, &person1, sizeof(person));

    array * array_p = create_array(4, 20, pointer, sizeof(person));

    _print_array(array_p);

    return &array_p;
}



void start_debug_example()
{

    printf("HELLO! There is a debug menu to test dynamic arrays. Wait a little..\n");
    printf("\n");

}



enum menu
{
    STANDART_MENU,
    CHOOSE_PERSON_MENU,
    CREATE_PERSON_MENU,
    CHANGE_PERSON_MENU,
    DELETE_PERSON_MENU,
    EXIT_MENU
};



static void print_person(

        int index,
        const array * array_p

        )
{

    char * element = get(array_p, index);

    person* pointer = malloc(sizeof(person));

    memcpy(pointer, element, array_p -> null_frame_size);

    printf("Person first name: %s, last name: %s\n", pointer -> firstName, pointer -> lastName);
    printf("\n");

}




static void create_person(

        const array * array_p

        )
{
    person person1 = {
            .firstName = "Admin",
            .lastName = "Tester"
    };

    char * pointer = malloc(sizeof(person));

    memcpy(pointer, &person1, sizeof(person));

    array * _array_p = add(array_p, pointer);
    free_array(array_p);


}


static enum menu delete_person_menu(

        int input,
        const array ** array_p

)
{

}



static enum menu change_person_menu(

        int input,
        const array ** array_p

)
{

    printf("Okay, you selected the person, now I'm print him...\n");
    print_person(index, array_p);
    printf("Please enter numbers: \'1\' to change new Person;\n\'0\' to to exit from this menu.\n");

    char c;
    scanf("%c", &c);
    while(c!='0'){
        if( c == '1')
        {
            printf("Go to change this person..\n");
            change_person(index, array_p);
            return;
        }
        scanf("%c", &c);
    }

}



static enum menu create_person_menu(

        int input,
        const array ** array_p

)
{

    printf("Please enter numbers: \'y\' to create new Person;\n\'n\' to to exit from this menu.\n");



    while(c!='n'){
        if( c == 'y')
        {
            create_person(array_p);
            printf("New person created. Do you want to change his params now?\n");
            printf("Please enter symbols: \'y\' to change params;\n\'n\' to to exit from this menu.\n");

            scanf("%c", &c);

            while(c!='n'){
                if( c == 'y')
                {
                    printf("\nChange person..\n");
                    open_person(array_p -> array_length - 1, array_p);
                }
                scanf("%c", &c);
            }
            return;
        }
    }

}



static enum menu choose_person_menu(

        int input,
        const array ** array_p

)
{

    _print_array(array_p);

    printf("Please input correct number of person:\n");

}



static enum menu standart_menu(

        int input,
        const array ** array_p

)
{

    enum menu _menu;

    if(input == 0)
    {
        printf("\n Creating new Person...\n");
        _menu = CREATE_PERSON_MENU;
        return _menu;
    }
    else if( input == 1 )
    {
        _menu = CHOOSE_PERSON_MENU;
        return _menu;
    }
    else if( input == 2 )
    {
        printf("You didn't select person.\n");
    }
    else if( input == 3 )
    {
        _print_array(*array_p);
        _menu = STANDART_MENU;
        return _menu;
    }
    else
    {
        printf("MENU selected, please enter numbers to edit person:\n");
        printf("\'0\' to create new Person;\n\'1\' to select person from array;\n\'2\' to change selected person params;\n\'3'\ to print your dynamic array;\n\'i\' to get info for debug mode.\n'q\' to exit from debug mode.\n");
    }

}



typedef enum menu (*open_menu)(int, array **);



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
        case DELETE_PERSON_MENU: return &delete_person_menu;
        case EXIT_MENU: return &standart_menu;
    }
}



static int get_input()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    read = getline(&line, &len, stdin);

    while(read == -1){
        read = getline(&line, &len, stdin);
    }

    int c = strtol(line, NULL, 10);

    free(line);

    return c;
}



void start_debugging()
{

    printf("...Debug program started, please enter the numbers from the keyboard for testing..\n");

    const array ** array_p = init_array();

    enum menu _menu = STANDART_MENU;

    while(1){
        if(_menu == EXIT_MENU)
        {
            return;
        }
        _menu = get_menu(_menu)(get_input(), array_p);
    }

}