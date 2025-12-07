#include <stdio.h>                 // Standard I/O header for printf, scanf
#include "contact.h"                // Header file containing contact-related structures and function declarations
#include "file.h"                   // Header file for file handling functions (save/load)

int main()
{
    char option;                    
    AddressBook addressbook;        // AddressBook type variable (typedef used, so no 'struct')

    init_intitalization(&addressbook);      // Initialize the address book (set contact_count = 0 etc.)
    loadContactsFromFile(&addressbook);    

    while (1)                                 // Infinite loop for menu until user chooses Exit
    {
        printf("\n===========================Address book menu===============================\n");                     
        // Display menu heading
        printf("1.Add contact\n2.Edit contact\n3.Delete contact\n4.Search contact\n5.Display contact\n6.Save contact\n7.Exit"); 
        printf("\n===========================================================================\n");
        // Show all available options
        printf("Enter the option : ");                       
        scanf(" %c", &option);                               // Read one character choice from user (with space before %c to ignore whitespace)

        switch (option)                                      // Switch statement to handle user choice
        {
            case '1':                                        
                create_contact(&addressbook);  
                break;              // Call function to add a new contact

            case '2':                                        
                edit_contact(&addressbook);                  // Call function to edit an existing contact
                break;

            case '3':                                       
                delete_contact(&addressbook);                // Call function to delete a contact
                break;

            case '4':                                       
                search_contacts(&addressbook);               // Call function to search for contacts
                break;

            case '5':                                        
                list_contacts(&addressbook);                 // Call function to display all contacts
                break;

            case '6':                                        
                saveContactsToFile(&addressbook);             // Call function to save contacts to a file
                break;

            case '7':                                        
                printf("INFO : Save and Exit...\n");          // Inform user that program will exit
                return 0;                                     

            default:                                          // If user enters invalid option
                printf("Invalid option \n");                  
        }
    }                                                        
}
