/*
Name: Naveen Kumar.
Date: 3 November 2025
Description:
The Address Book Project is a simple program designed to store, manage, and organize contact information efficiently.
 It allows users to create, List, search, edit, and delete contact details such as name, phone number, email.
*/
#include <stdio.h>
#include "contact.h"

int main() {
    int choice,index;                                                 //declaration of choice and index variables. 
    AddressBook addressBook;
    initialize(&addressBook);            // Initialize the address book.

    do {
        printf("\nAddress Book Menu:\n");          //Display Menu options to the user.
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);                         //read the choice from the user.
        
        switch (choice) {
            case 1:
                createContact(&addressBook);              //function call to create a new contact.
                break;
            case 2:
                searchContact(&addressBook,&index);       //function call to search contact.
                break;
            case 3:
                editContact(&addressBook);               //function call to edit contact.
                break;
            case 4:
                deleteContact(&addressBook);                //function call to delete contact.
                break;
            case 5:
              //  printf("Select sort criteria:\n");
               // printf("1. Sort by name\n");
               // printf("2. Sort by phone\n");
               // printf("3. Sort by email\n");
               // printf("Enter your choice: ");
                int sortChoice;
               // scanf("%d", &sortChoice);
                listContacts(&addressBook, sortChoice);             //function call to list contact.
                break;
            case 6:
                printf("Saving and Exiting...\n");                   
                saveContactsToFile(&addressBook);                 //function call to saving and exiting.
                break;
            default:
                printf("Invalid choice. Please try again.\n");        //if users give invalid input.
        }
    } while (choice != 6);                                           //continue until user chooses to exit.
    
       return 0;                
}
