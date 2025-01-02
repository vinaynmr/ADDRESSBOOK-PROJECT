#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact *contacts;
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
int search_name(AddressBook *addressBook);
int search_contact_no(AddressBook *addressBook);
int search_email(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContact(AddressBook *addressBook);
void initialize(AddressBook *addressBook,FILE *fp);
void saveContact(AddressBook *addressBook,FILE *fp);
int contact_no_check(char *);
int gmail_check(char *);
int add_contact_check(AddressBook *addressBook,char *,int);
#endif
