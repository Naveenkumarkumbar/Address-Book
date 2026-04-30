/*
Name: Naveen Kumar.
Date: 3 November 2025.
Description:
The Address Book Project is a simple program designed to store, manage, and organize contact information efficiently. 
It allows users to create, List, search, edit, and delete contact details such as name, phone number, email.
*/
#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)    //function definition to savecntactstofile.
{
    FILE *fptr = fopen("contacts.txt", "w");          //opening the contact.txt file in the write mode.
    if(fptr == NULL)                                 
    {
        return;                                      //returns back where the function was called.
    } 
    fprintf(fptr, "#%d\n", addressBook->contactCount);    
    for(int i = 0; i < addressBook->contactCount; i++)      
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);                                 //close the files.
    printf("contacts saved successfully");
}

void loadContactsFromFile(AddressBook *addressBook)     //function definition to loadcontactsfromfile.
{
    FILE *fptr = fopen("contacts.txt", "r");            //opening the contact.txt file in read mode.
    if(fptr == NULL) 
    {
        return;                                         //returns back where the function was called.
    } 
    fscanf(fptr, "#%d\n", &addressBook->contactCount);
    for(int i = 0;i<addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
