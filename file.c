#include <stdio.h> 
#include <string.h>                // Standard I/O library for file operations (fopen, fprintf, fscanf, etc.)
#include "contact.h"               // Custom header containing definition of AddressBook structure
#include "file.h"                  // Custom header declaring these file-related functions

// Function to save all contacts from AddressBook to a CSV file
void saveContactsToFile(AddressBook *addressBook)          
{
    FILE *fp = fopen("contacts.csv", "w");                 // Open file in write mode (will overwrite existing file)
    if (fp == NULL)                                        
    {
        printf("Unable to open file for writing.\n");      
        return;                                            
    }

    fprintf(fp, "#%d\n", addressBook->contact_count);       // Write total contact count as the first line (with a # marker)

    for (int i = 0; i < addressBook->contact_count; i++)    
    {
        fprintf(fp, "%s,%s,%s\n",                           // Write contact details in CSV format (Name,Mobile,Email)
                addressBook->contact_details[i].Name,       
                addressBook->contact_details[i].Phone_number, 
                addressBook->contact_details[i].Mail_ID);   
    }

    fclose(fp);                                             
    printf("Contacts saved successfully\n");                // Inform user that contacts were saved
}

// Function to load contacts from a CSV file into AddressBook
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.csv", "r");
    if (fp == NULL)
    {
        printf("No saved contact found\n");
        return;
    }

    addressBook->contact_count = 0;  // Reset contact count

    char line[150];
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0'; // Remove newline
        if (line[0] == '\0') continue;    // Skip empty lines

        char *token = strtok(line, ",");
        if (!token) continue;
        strcpy(addressBook->contact_details[addressBook->contact_count].Name, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(addressBook->contact_details[addressBook->contact_count].Phone_number, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(addressBook->contact_details[addressBook->contact_count].Mail_ID, token);

        addressBook->contact_count++;  // Increment AFTER filling
    }

    fclose(fp);
    printf("Contacts loaded successfully\n");
}
