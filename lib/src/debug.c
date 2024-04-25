#include <time.h>
#include <string.h>
#include "dynamic_array.h"
#include <stdio.h>


typedef struct PERSON_ID {
    int series;
    int number;
}person_id;



typedef struct Person{
    person_id id;
    char* firstName;
    char* lastName;
}person;



static array * array_p;



void print_element(

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



static void _print_array()
{
    print_array(array_p, &print_element);
}



static void init_array()
{

    person_id person_id1 = {
            .number = 0,
            .series = 0
    };
    person person1 = {
            .id = person_id1,
            .firstName = "Admin",
            .lastName = "Tester"
    };
    char * pointer = malloc(sizeof(person));

    memcpy(pointer, &person1, sizeof(person));

    array_p = create_array(1, 20, pointer, sizeof(person));

    _print_array();

}



static int start_debug_example()
{
    printf("HELLO! There is a debug menu to test dynamic arrays. Wait a little..\n");
    return 0;
}



static void print_person(int index)
{

    char * element = get(array_p, index);

    person* pointer = malloc(sizeof(person));

    memcpy(pointer, element, array_p -> null_frame_size);

    printf("Person first name: %s, last name: %s\n", pointer -> firstName, pointer -> lastName);

}



static void change_person(int index)
{

    char * first_name;
    char * last_name;

    printf("Please input first name of person:\n");

    scanf("%s", first_name);

    printf("Please input last name of person:\n");

    scanf("%s", last_name);

    person_id person_id1 = {
            .number = 0,
            .series = 0
    };
    person person1 = {
            .id = person_id1,
            .firstName = first_name,
            .lastName = last_name
    };
    char * pointer = malloc(sizeof(person));

    memcpy(pointer, &person1, sizeof(person));

    array_p = delete(array_p, index);
    array_p = add(array_p, pointer);

    printf("Sorry passport id is a secret information!\n");

    _print_array();

}



static void create_person()
{

    person_id person_id1 = {
            .number = 0,
            .series = 0
    };
    person person1 = {
            .id = person_id1,
            .firstName = "Tester",
            .lastName = "Tester"
    };
    char * pointer = malloc(sizeof(person));

    memcpy(pointer, &person1, sizeof(person));

    array_p = add(array_p, pointer);

    change_person(array_p -> array_length -1);

}

static void open_person(int index)
{

    printf("Okay, you selected the person, now I'm print him...\n");
    print_person(index);
    printf("Please enter numbers: \'1\' to change new Person;\n\'0\' to to exit from this menu.\n");

    char c;
    while(c=getchar()!='0'){
        if( c == '1')
        {
            printf("Go to change this person..\n");
            change_person(index);
            return;
        }
    }

}

static void person_menu()
{

    printf("Please enter numbers: \'y\' to create new Person;\n\'n\' to to exit from this menu.\n");

    char c;

    while(c=getchar()!='n'){
        if( c == 'y')
        {
            create_person();
            printf("New person created. Do you want to change his params now?\n");
            printf("Please enter symbols: \'y\' to change params;\n\'n\' to to exit from this menu.\n");

            while(c=getchar()!='n'){
                if( c == 'y')
                {
                    printf("\nChange person..\n");
                    open_person(array_p -> array_length -1);
                }
            }
            return;
        }
    }

}


static void select_person()
{

    _print_array();

    printf("Please input correct number of person:\n");

    char c;
    c=(int)getchar();
    while(c<0 || c > array_p -> array_length){
        printf("Please input correct number of person:\n");

        c=(int)getchar();
    }
    open_person(c);

}


static void print_menu(char c)
{

    if(c=='0')
    {
        printf("\n Creating new Person...\n");
        person_menu();
    }
    else if( c == '1' )
    {
        select_person();
    }
    else if( c == '2' )
    {
        printf("You didn't select person.\n");
    }
    else if( c == '3' )
    {
        _print_array();
    }
    else
    {
        printf("MENU selected, please enter numbers to edit person:\n");
        printf("\'0\' to create new Person;\n\'1\' to select person from array;\n\'2\' to change selected person params;\n\'3'\ to print your dynamic array;\n\'i\' to get info for debug mode.\n'q\' to exit from debug mode.\n");
    }

}


static int start_debugging()
{

    printf("...Debug program started, please enter the numbers from the keyboard for testing..\n");

    init_array();

    print_menu('c');

    char c;

    while(c=getchar()!='q'){
        if(c=='i' || c=='0' || c=='1' || c == '2' || c == '3')
        {
            print_menu(c);
        }
    }

    return 0;
}