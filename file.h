#ifndef FILE_H
#define FILE_H

#include "contact.h"

// Save all contacts to CSV file
void saveContactsToFile(AddressBook *addressBook);

// Load all contacts from CSV file
void loadContactsFromFile(AddressBook *addressBook);

#endif