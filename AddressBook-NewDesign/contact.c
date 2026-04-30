/*
Name: Naveen Kumar.
Date: 3 November 2025.
Description:
The Address Book Project is a simple program designed to store, manage, and organize contact information efficiently. 
It allows users to create, List, search, edit, and delete contact details such as name, phone number, email.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria)         //function definition to list contacts.
{
    // Sort contacts based on the chosen criteria
    for(int i = 0; i < addressBook->contactCount; i++)     //running loop for contact count times to list all the contacts.
    {
        printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook)                   //function definition to initialize.
 {
    addressBook->contactCount = 0;                         
   // populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);        //function call.
}

void saveAndExit(AddressBook *addressBook)            //function definition to saveAndexit.
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int validate_name(char *buffer)           //function definition to validate name.
{
    for(int i = 0; buffer[i] != '\0'; i++)                 //running loop upto null character to read all the elements in buffer.
    {
        if(!(buffer[i] >= 'A' && buffer[i] <= 'Z'|| buffer[i] >= 'a' && buffer[i] <= 'z'|| buffer[i] == ' ')) //condition to check if the entered name has these characters or not.
        {
            return 0;                   //returns 0 if the entered name has other characters.

        }
    }
    return 1;                            //else it returns 1.
}
int validate_phone(AddressBook *addressBook,char *buffer)     //function definition to validate phone number.
{
    int len = strlen(buffer);                 //finding the length of the buffer using strlen standard library function and storing it in len.
    if(len != 10)                             //condition to check the phone number has 10 digits or not.
    {
        return 0;                             //if phone number doesnt have 10 digits it will return zero.
    }
    for(int i = 0; buffer[i] != '\0'; i++)      //running loop upto null character to read all the elements in buffer.
    {
        if(buffer[i] <'0' || buffer[i] > '9')    //condition to check weather given phone numbers have only digit or not.
        {
            return 0;                              //returns 0 if it contains characters other than digits.
        }
    }
    for(int i = 0; i < addressBook->contactCount; i++)               //running loop upto contactcount times
    {
        if(strcmp(buffer, addressBook->contacts[i].phone) == 0)        //to check weather the given phone number already exists or not.
        {
            return 0;                                               //if already exists it will return zero.
        }
    }
    return 1;                                         //else it will return 1.
}
int validate_email(AddressBook *addressBook, char *buffer)          //function definition to validate email.
{
    int i, at_position = -1, dot_position = -1;                     //declaration of i varible ,at _position and dot_position.
    int at_count =0, dot_count = 0;                                 //declaration of variable at_count and dot_count and initializing it to zero.
    int len = strlen(buffer);                                      //finding the buffer length using strlen and storing it in len.
    for (i = 0; i < len; i++)                                      //running loop upto len times.
    {
        char ch = buffer[i];                                      //taking each character one by one and storing it in ch variable.               
        // Allow only small letters, numbers, '@', '.', and '_'
        if (!((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') ||     ch == '@' || ch == '.' || ch == '_'))
        {
            return 0; // invalid character found
        }
        // Find positions of '@' and incrementing '@' count.
        if (ch == '@')
        {
            at_count++;                                   
            at_position = i;                  
        }
        //finding position of'.' and incrementing dot_count.
        if (ch == '.')
        {
            dot_count++;
            dot_position = i;
        }
    }
    if(at_count != 1 || dot_count != 1)           //to check if the entered email has '@' and '.' only one or not.        
    {
        return 0;                                 //returns zero if they are not found and if they are found multiple times.
    }
    if (at_position == -1 || dot_position == -1)  // must contain both
    {
        return 0;                                  //returns zero if it doesnt have these two characters.
    }
    if (at_position > dot_position)  // '@' must come before '.'
    {
        return 0;
    }
    if (at_position == 0 || dot_position == len - 1) // cannot be first or last
    {
        return 0;
    }
    if(i - dot_position <= 1)                       //to check weather character is present after the '.' or not.
    {
        return 0;
    }
    if(dot_position - at_position <= 1)            //to check weather character is present after the '@' or not.
    {
        return 0;
    }
    // Duplicate email check
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(buffer, addressBook->contacts[i].email) == 0)
        {
            return 0; // duplicate found
        }
    }
    return 1; // valid email
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    int res;                                   //declaring res variable.
    char buffer[60];                           //declaration of buffer string.
    do
    {
        printf("Enter the name : ");               //it asks to enter the name.
        scanf(" %[^\n]", buffer);                 //it reads the buffer from the user.
        res = validate_name(buffer);              //function call to validate name and return value is stored in res variable.
        if(res == 1)                              //if res value is 1 then it will store the contacts.
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name, buffer);               //sting copy from buffer to contacts.
        }
    } while (res == 0);                           //This loop is terminated when the condition is true.
    do
    {
        printf("Enter the phone_no : ");         //it asks to enter the phone no.
        scanf(" %[^\n]", buffer);                //it reads the buffer from the user.
        res = validate_phone(addressBook, buffer);        //function call to validate phone no and return value is stored in res variable.
        if(res == 1)                                      //if res value is 1 then it will store the contacts.
        {
            strcpy(addressBook->contacts[addressBook->contactCount].phone, buffer);          //sting copy from buffer to contacts.
                  
        }
    } while (res == 0);                              //This loop is terminated when the condition is true.
    do
    {
        printf("Enter the email : ");                //it asks to enter the email.
        scanf(" %[^\n]", buffer);                    //it reads the buffer from the user.
        res = validate_email(addressBook, buffer);     //function call to validate email and return value is stored in res variable.
        if(res == 1)                                  //if res value is 1 then it will store the contacts.
        {
            strcpy(addressBook->contacts[addressBook->contactCount].email, buffer);           //sting copy from buffer to contacts.
        }
    } while (res == 0);                                  //This loop is terminated when the condition is true.
    addressBook->contactCount++;                         //increment of contact count.
}

int searchContact(AddressBook *addressBook, int *index)             //function definiton to search contact.
{
    /* Define the logic for search */
    printf("1. search contact by using name : ");
    printf("2. search contact by using phone : ");
    printf("3. search contact by using email : ");
    int choice;                                       //declartion of choice variable.
    printf("Enter your choice : ");                   //it asks the user to enter the choice.
    scanf("%d", &choice);                             //it reads the choice value from the user.
    char buffer[50];                                  //declaration of buffer string.
    int flag = 0;                                     //declaration of flag variable and assigning it to zero.
    switch (choice)                                   //it is used to choose the particular choice based on above options.
    {
        case 1:                                       //this case is used to search based on name.
        printf("Enter the name : ");                  //it asks to enter the name.
        scanf(" %[^\n]", buffer);                     //it reads the name from the user.
        for(int i = 0; i < addressBook->contactCount; i++)           //running the loop upto contactcount times.
        {
            if(strcmp(buffer, addressBook->contacts[i].name) == 0)    //condition to check if there exists entered name.
            {
                *index = i;                                        //storing index value.
                printf("%d %s %s %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);   //prints the entire contact.
                flag++;                                              //increment the flag variable.
             }
        } 
         break;
         case 2:                                         //this case is used to search based on phone.
         printf("Enter the phone : ");                   //it asks to enter the phone.
         scanf(" %[^\n]", buffer);                        //it reads the phone from the user.
         for(int i = 0; i < addressBook->contactCount; i++)            //running the loop upto contactcount times.
        {
            if(strcmp(buffer, addressBook->contacts[i].phone) == 0)        //condition to check if there exists entered phone no.
            {
                 *index = i;                                              //storing index value
                 printf("%d %s %s %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);  //prints the entire contact.
                 flag++;                                         //increment the flag variable.
            }
        }
        break;
        case 3:                                                   //this case is used to search based on email.
        printf("Enter the email : ");                             //it asks to enter the email.
        scanf(" %[^\n]", buffer);                                 //it reads the email from the user.
        for(int i = 0; i < addressBook->contactCount; i++)         //running the loop upto contactcount times.
        {
            if(strcmp(buffer, addressBook->contacts[i].email) == 0)          //condition to check if there exists entered email.
            {
                *index = i;                                                //storing index value
                 printf("%d %s %s %s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);  //prints the entire contact.
                 flag++;                                            //increment the flag variable.
            }
        }
        break;
        default:
        printf("Invalid choice. Please try again.\n");              //it tells user to enter valid choice.
    }
    if(flag == 0)                                                //if flag value is zero contact is not found.
    {
        printf("contact not found\n");
        return flag;
    } 
    else if(flag == 1)                                      //if flag value equal to 1 contact is found.
    {
        return flag;
    }
    else if(flag > 1)                                   //if flag value greater than 1 multiple contacts are found.
    {
        return flag;
    }
}
int editContact(AddressBook *addressBook)                 //function definition to edit contact.
{
    /* Define the logic for Editcontact */
    int index;                          //declaration of index variable.
    int res = searchContact(addressBook, &index);      ////function call and returning the result in res. 
    if(res == 0)             //this condition implies that contact is not found.
    {
        return 0;
    }
    else if(res > 1)         //this condition implies that more than one contact is found so it asks to enter index value of which contact you want to edit.
    {
        printf("Enter index to edit : ");       //it asks to enter index value.
        scanf("%d", &index);                    //it reads the index value from the user.
    }
    printf("\n1.Edit Name\n");
    printf("2.Edit Phone\n");
    printf("3.Edit Email_Id\n");
    int option;                              //declration of option variable.
    printf("Enter your option : ");         //it asks to enter the option.
    scanf("%d", &option);                   //it reads the option from the user.
    char buffer[50];                        //declaration of buffer string.
    int valid;                              //declaration of valid variable.
    switch(option)                          //This is used to choose the particular case based on options.
    {
        case 1:                              //this case is used to edit name.
        do
        {
            scanf(" %[^\n]", buffer);         //reads the buffer from the user.
            valid = validate_name(buffer);       //function call it validates the given name is correct or not.
            if(valid == 1)                       //condition to check weather the given name is valid or not.
            {
                strcpy(addressBook->contacts[index].name, buffer);
                printf("%d %s %s %s\n",index, addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
            }
            else
            {
                printf("Enter Valid name\n");       // if the given name is invalid name then it will print this.
            }
        }while(valid == 0);                      //This loop is terminated when the condition is true.
        break;
        case 2:                                  // this case is used to edit phone_number.
            do
            {
                scanf(" %[^\n]", buffer);            //reads the buffer from the user.
                valid = validate_phone(addressBook, buffer);            //function call it validates the given phone_number is correct or not.
                if(valid == 1)                             //condition to check weather the given phone number is valid or not.
                {
                    strcpy(addressBook->contacts[index].phone, buffer);
                    printf("%d %s %s %s\n", index,addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
                }
                else
                {
                    printf("Enter Valid Phone number\n");          // if the given phone no is invalid name then it will print this.
                }
            }while(valid == 0);                                  //This loop is terminated when the condition os true.
            break;
        case 3:                                               // this case is used to edit email.
            do
            {
                 scanf(" %[^\n]", buffer);                          //reads the buffer from the user.
                 valid = validate_email(addressBook, buffer);       //function call it validates the given email is correct or not.
                if(valid == 1)                                    //condition to check weather the given email is valid or not.
                {
                    strcpy(addressBook->contacts[index].email, buffer);
                    printf("%d %s %s %s\n", index, addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
                 }
                else
                { 
                     printf("Enter Valid Email Id\n");                 //if the given email is invalid name then it will print this.
                }
            }while(valid == 0);                                        //This loop is terminated when the condition os true.
        break;
        default:                                               //if the entered option is not valid then it will print the below statement.
        printf("enter valid option\n");
   }
}
void deleteContact(AddressBook *addressBook)        //function definition to delete contact.
{
	/* Define the logic for deletecontact */
    int index = 0;               //declaration of index variable and assigning it to zero.
    int res = searchContact(addressBook, &index);    //function call and returning the result in res. 
    if(res == 0)           //Based on res value it means that contact is not found.
    {
        return;
    }
    else if(res > 1)      //It means that there are two contacts with same name so it asks the index value.
    {
        printf("Enter the index : ");      //it asks to enter the index.
        scanf("%d", &index);                //reading the index value from the user.
    }
    else if(res == 1)              //It means that contact is found which you want to delete.
    {
        for(int i = index; i < addressBook->contactCount; i++)        //running the loop upto contact count times.
        {
             addressBook->contacts[i] = addressBook->contacts[i+1];    //shifting operation.
        } 
    } 
    addressBook->contactCount--;        //decrementing contactcount.
}
