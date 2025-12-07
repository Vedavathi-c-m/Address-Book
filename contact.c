#include "contact.h"     // Custom header file containing AddressBook and Contact struct definitions
#include <stdio.h>      // Standard I/O library for printf, scanf, etc.
#include <string.h>     // String handling functions: strlen, strcmp, strcpy, strstr, strchr
#include <ctype.h>      // Character handling: isdigit, isalpha, isupper
                        

// ---------------- Validation Functions ----------------
int validate_name(char Name[]) // Function to validate a name
{
    if (Name[0] == '\0' || isdigit(Name[0]) || Name[0] == ' ') // Name should not start with digit, space, or be empty
        return 0;

    for (int i = 0; Name[i] != '\0'; i++) // Check each character
        if (!(isalpha(Name[i]) || Name[i] == ' ')) // Allow only letters and spaces
            return 0;

    return 1; // Valid name
}

int validate_Phone(char Phone_number[]) // Function to validate a phone number
{
    if (strlen(Phone_number) != 10) // Phone number must be exactly 10 digits
        return 0;

    if (Phone_number[0] >= '0' && Phone_number[0] <= '5') // First digit must be 6-9
        return 0;

    for (int i = 0; Phone_number[i] != '\0'; i++)
        if (!isdigit(Phone_number[i])) // All characters must be digits
            return 0;

    return 1; // Valid phone
}

int validate_Mail(char Mail_ID[])// Function to validate email
{
    int len = strlen(Mail_ID);

    if (isdigit(Mail_ID[0])) // Email should not start with a digit
        return 0;

    for (int i = 0; Mail_ID[i] != '\0'; i++)
        if (isupper(Mail_ID[i])) // No uppercase letters allowed
            return 0;

    int at_count = 0;
    for (int i = 0; Mail_ID[i] != '\0'; i++)
        if (Mail_ID[i] == '@') // Count '@' symbols
            at_count++;
    if (at_count != 1) // Must have exactly one '@'
       return 0;

    char *ptr = Mail_ID;
    int dotcom_count = 0;
    while ((ptr = strstr(ptr, ".com")) != NULL) // Count ".com" occurrences 
    {
        dotcom_count++;
        ptr += 4;
    }
    if (dotcom_count != 1 || len < 4 || strcmp(Mail_ID + len - 4, ".com") != 0) // Only one ".com" at the end
       return 0;

    char *at_ptr = strchr(Mail_ID, '@'); // Pointer to '@'
    char *dotcom_ptr = strstr(Mail_ID, ".com"); // Pointer to ".com"
    if (at_ptr == NULL || dotcom_ptr == NULL || dotcom_ptr - at_ptr <= 1) // Ensure something before '.com' after '@' like any character
        return 0;

    return 1; // Valid email
    
}

// ---------------- Utility Functions ----------------
int is_unique(AddressBook *addressbook, char *Phone_no, char *eMailid) // Check if phone/email id already exists
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (Phone_no != NULL &&
            strcmp(addressbook->contact_details[i].Phone_number, Phone_no) == 0) // Phone number exists
            return 1;

        if (eMailid != NULL &&
            strcmp(addressbook->contact_details[i].Mail_ID, eMailid) == 0) // Email  ID exists
            return 1;
    }
    return 0; // Unique
}

void init_intitalization(AddressBook *addressbook) // Initialize AddressBook
{
    addressbook->contact_count = 0; // No contacts initially
}

// ---------------- Core Functions  to create a contanct ----------------
void create_contact(AddressBook *addressbook)
{
    char Name[50], Phone[15], eMailid[50];

    while (1)
    {
        printf("Enter Name: ");
        scanf(" %49[^\n]", Name);

        if (validate_name(Name))
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Name, Name);
            break;
        }
        else
            printf("Invalid name! Try again.\n");
    }

    while (1)
    {
        printf("Enter Phone: ");
        scanf(" %14s", Phone);

        if (validate_Phone(Phone) && !is_unique(addressbook, Phone, NULL))
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Phone_number, Phone);
            break;
        }
        else
            printf("Invalid phone! Try again.\n");
    }

    while (1)
    {
        printf("Enter Email: ");
        scanf(" %49s", eMailid);

        if (validate_Mail(eMailid) && !is_unique(addressbook, NULL, eMailid))
        {
            strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID, eMailid);
            break;
        }
        else
            printf("Invalid email! Try again.\n");
    }

    addressbook->contact_count++;
    printf("Contact created successfully!\n");
}

// Display all contacts in table format
void list_contacts(AddressBook *addressbook)
{
    if (addressbook->contact_count == 0)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    printf("\n+----------------+----------------+---------------------------+\n");
    printf("| %-14s | %-14s | %-25s |\n", "Name", "Phone", "Email");
    printf("+----------------+----------------+---------------------------+\n");

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf("| %-14s | %-14s | %-25s |\n",
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Phone_number,
               addressbook->contact_details[i].Mail_ID);
    }

    printf("+----------------+----------------+---------------------------+\n");
}



void search_contacts(AddressBook *addressbook) // Search a contact
{
    char keyword[30];
    int option;

    printf("Search by:\n");
    printf("1.Name:\n");
    printf("2.Phone Number:\n");
    printf("3.Email ID:\n");
    printf("4.Exit:\n");
    scanf("%d", &option);

    if (option == 1) // Search by Name
    {
        printf("Enter the Name which you want to search: ");
        scanf(" %[^\n]", keyword);

        if (validate_name(keyword))
        {
            int found = 0;
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Name, keyword) == 0)
                {
                    printf("\nContact found!!!\n");
                    printf("Name: %s\n", addressbook->contact_details[i].Name);
                    printf("Phone Number: %s\n", addressbook->contact_details[i].Phone_number);
                    printf("Email ID: %s\n", addressbook->contact_details[i].Mail_ID);
                    found = 1;
                }
            }
            if (!found)
                printf("No contact found with that name.\n");
        }
        else
            printf("Invalid name, Try again!\n");
    }
    else if (option == 2) // Search by Phone
    {
        printf("Enter the Phone number which you want to search: ");
        scanf(" %[^\n]", keyword);

        if (validate_Phone(keyword))
        {
            int found = 0;
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Phone_number, keyword) == 0)
                {
                    printf("\nContact found!!!\n");
                    printf("Name: %s\n", addressbook->contact_details[i].Name);
                    printf("Phone Number: %s\n", addressbook->contact_details[i].Phone_number);
                    printf("Email ID: %s\n", addressbook->contact_details[i].Mail_ID);
                    found = 1;
                }
            }
            if (!found)
                printf("No contact found with that Phone number.\n");
        }
        else
            printf("Invalid Phone number, Try again!\n");
    }
    else if (option == 3) // Search by Email
    {
        printf("Enter the Mail ID which you want to search: ");
        scanf(" %[^\n]", keyword);

        if (validate_Mail(keyword))
        {
            int found = 0;
            for (int i = 0; i < addressbook->contact_count; i++)
            {
                if (strcmp(addressbook->contact_details[i].Mail_ID, keyword) == 0)
                {
                    printf("\nContact found!!!\n");
                    printf("Name: %s\n", addressbook->contact_details[i].Name);
                    printf("Phone Number: %s\n", addressbook->contact_details[i].Phone_number);
                    printf("Email ID: %s\n", addressbook->contact_details[i].Mail_ID);
                    found = 1;
                }
            }
            if (!found)
                printf("No contact found with that Mail ID.\n");
        }
        else
            printf("Invalid Mail ID, Try again!\n");
    }
    else if (option == 4) // Exit search
        printf("Exit\n");
    else
        printf("Invalid option. Try again!\n");
}

// ---------------- Edit Contact ----------------
void edit_contact(AddressBook *addressbook) // Edit an existing contact
{
    char edit_keyword[30];
    int option;

    
    printf("Edit by:\n");
    printf("1.Name:\n");
    printf("2.Phone Number:\n");
    printf("3.Email ID:\n");
    printf("4.Exit:\n");
    scanf("%d", &option);

    if (option >= 1 && option <= 3) // If user wants to edit a field
    {
        char keyword[30];
        printf("Enter search keyword: ");
        scanf(" %[^\n]", keyword);

        int found_indexes[100], count = 0; // Store indexes of matching contacts

        for (int i = 0; i < addressbook->contact_count; i++) // Find all matching contacts
        // Loop through all contacts and check if they match keyword
        {
            if ((option == 1 && strcmp(addressbook->contact_details[i].Name, keyword) == 0) ||
                (option == 2 && strcmp(addressbook->contact_details[i].Phone_number, keyword) == 0) ||
                (option == 3 && strcmp(addressbook->contact_details[i].Mail_ID, keyword) == 0))
            {
                found_indexes[count++] = i; // u want search 
            }
        }

        if (count == 0) // No matching contact
        {
            printf("No matching contact found.\n");
            return;
        }
 // If only one match is found, use it
        int selected_index = (count == 1) ? found_indexes[0] : -1; // If only one match, select it
        if (selected_index == -1) // Multiple matches
        {
            printf("Multiple contacts found:\n");
            for (int j = 0; j < count; j++)
            {
                int i = found_indexes[j];
                printf("%d. Name: %s, Phone: %s, Email: %s\n",
                       j + 1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Phone_number,
                       addressbook->contact_details[i].Mail_ID);
            }
            int choice;
            printf("Select the contact number to edit (1 to %d): ", count);
            scanf("%d", &choice);

            if (choice < 1 || choice > count)
            {
                printf("Invalid selection.\n");
                return;
            }

            selected_index = found_indexes[choice - 1];
        }
    // Ask user what field they want to edit
        printf("What do you want to edit?\n");
        printf("1.Name:\n");
        printf("2.Phone Number:\n");
        printf("3.Email ID:\n");
        int edit_option;
        scanf("%d", &edit_option);

        if (edit_option == 1) // Edit name
        {
            printf("Enter New Name: ");
            scanf(" %[^\n]", edit_keyword);
            if (validate_name(edit_keyword))
                strcpy(addressbook->contact_details[selected_index].Name, edit_keyword);
            else
                printf("Invalid name. Try again....!\n");
        }
        else if (edit_option == 2) // Edit phone
        {
            printf("Enter New Phone number: ");
            scanf(" %[^\n]", edit_keyword);
            if (validate_Phone(edit_keyword))
                strcpy(addressbook->contact_details[selected_index].Phone_number, edit_keyword);
            else
                printf("Invalid Phone number. Try again....!\n");
        }
        else if (edit_option == 3) // Edit email
        {
            printf("Enter New Email ID: ");
            scanf(" %[^\n]", edit_keyword);
            if (validate_Mail(edit_keyword))
                strcpy(addressbook->contact_details[selected_index].Mail_ID, edit_keyword);
            else
                printf("Invalid email ID. Try again....!\n");
        }
        else
        {
            printf("Invalid edit option....\n");
            return;
        }

        printf("Contact updated successfully.\n");
    }
    else if (option == 4) // Exit edit
        printf("Exit\n");
        // If user entered invalid option
    else
        printf("Invalid option\n");
}

// ---------------- Delete Contact ----------------
void delete_contact(AddressBook *addressbook) // Delete a contact
{
    char delete_keyword[30];
    int option;

    // Keyword entered by user (Name/Phone/Email)
    printf("Delete by:\n");
    printf("1.Name:\n");
    printf("2.Phone Number:\n");
    printf("3.Email ID:\n");
    printf("4.Exit:\n");
    scanf("%d", &option);

    if (option >= 1 && option <= 3) // If delete by Name/Phone/Email
    {
        printf("Enter search keyword: ");
        scanf(" %[^\n]", delete_keyword);

        int found_indexes[100], count = 0; // Store matching contact indexes

        // Search all contacts for matches

        for (int i = 0; i < addressbook->contact_count; i++) 
        {
            if ((option == 1 && strcmp(addressbook->contact_details[i].Name, delete_keyword) == 0) ||
                (option == 2 && strcmp(addressbook->contact_details[i].Phone_number, delete_keyword) == 0) ||
                (option == 3 && strcmp(addressbook->contact_details[i].Mail_ID, delete_keyword) == 0))
                found_indexes[count++] = i;
        }

        if (count == 0) // No matches
        {
            printf("No matching contact found....!\n");
            return;
        }
// If only one contact matched, delete it directly
        int selected_index = (count == 1) ? found_indexes[0] : -1; 
        if (selected_index == -1) // Multiple matches
        {
            printf("Multiple contacts found:\n");
            for (int j = 0; j < count; j++)
            {
                int i = found_indexes[j];
                printf("%d. Name: %s, Phone: %s, Email: %s\n",
                       j + 1,
                       addressbook->contact_details[i].Name,
                       addressbook->contact_details[i].Phone_number,
                       addressbook->contact_details[i].Mail_ID);
            }
            int choice;
            printf("Select the choice to delete: ");
            scanf("%d", &choice);

            if (choice < 1 || choice > count)
            {
                printf("Invalid selection......\n");
                return;
            }

            selected_index = found_indexes[choice - 1];
        }

        for (int i = selected_index; i < addressbook->contact_count - 1; i++) // Shift contacts to remove
            addressbook->contact_details[i] = addressbook->contact_details[i + 1];

        addressbook->contact_count--; // Decrease count
        printf("Contact deleted successfully.\n");
    }
    else if (option == 4) // Exit delete
        printf("Exit\n");
    else
        printf("Invalid option\n");
}