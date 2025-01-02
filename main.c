#include "contact.h"

int main()
{
    AddressBook addressBook;
    FILE *fp = fopen("contact.csv","r");
    initialize(&addressBook,fp);
    int i = 1;
    while(i)
    {
        printf("Menu:\n1. Add Contact\n2. Delete Contacts\n3. Search Contact\n4. Edit Contacts\n5. List all Conatacts\n");
        int opt;
        printf("Choose one option: ");
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                deleteContact(&addressBook);
                break;
            case 3:
                searchContact(&addressBook);
                break;
            case 4:
                editContact(&addressBook);
                break;
            case 5:
                listContact(&addressBook);
                break;
            default:
                printf("Enter the valid option!\n");
        }
        printf("\n\nDo you want to contine(Press-> 1. Yes | 0. No):\n");
        scanf("%d",&i);
    }
    saveContact(&addressBook,fp);
    printf("Thank you for spending your precious time on our services!\n");
    return 0;
}
