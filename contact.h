#ifndef CONTACT_H
#define CONTACT_H

// Single contact structure
typedef struct
{
    char Name[50];
    char Phone_number[15];   // Changed from Mobile_number
    char Mail_ID[50];
} Contact;

// Address book structure
typedef struct
{
    Contact contact_details[100];
    int contact_count;
} AddressBook;


// Validation helpers
int validate_name(char Name[]);
int validate_Phone(char Phone_number[]);
int validate_Mail(char Mail_ID[]);


// Check uniqueness of phone/email
int is_unique(AddressBook *addressbook, char *Phone_no, char *eMailid); // Changed parameter name

// Initialize address book
void init_intitalization(AddressBook *addressbook);

// Create new contact
void create_contact(AddressBook *addressbook);

// List all contacts
void list_contacts(AddressBook *addressbook);

// Search contacts (by name, phone, or email)
void search_contacts(AddressBook *addressbook);

// Edit a contact
void edit_contact(AddressBook *addressbook);

// Delete a contact
void delete_contact(AddressBook *addressbook);
// save a contact
void save_contact(AddressBook *addressbook);

#endif