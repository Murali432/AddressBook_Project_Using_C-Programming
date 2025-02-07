#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct 
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct 
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);
void initialize1(AddressBook *addressBook);
void loadDummyContacts(AddressBook *addressBook);
void addContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveContact(AddressBook *addressBook);
bool isValidName(const char *name);
bool isValidPhone(const char *phone);
bool isValidEmail(const char *email);

#endif