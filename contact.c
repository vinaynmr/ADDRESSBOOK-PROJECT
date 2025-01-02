#include "contact.h"

void initialize(AddressBook *addressBook,FILE *fp)
{
    fscanf(fp,"#%d#\n",&addressBook->contactCount);
    addressBook -> contacts  = malloc(addressBook->contactCount*sizeof(Contact));
    for(int i = 0; i < addressBook->contactCount; i++)
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
}

void listContact(AddressBook *addressBook) 
{
    printf("\t\t\t:::::LISTING ALL DATA:::::\n");
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        printf("Name: %s  Contact: %s   Email: %s\n",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
    }
    printf("\t\t\t:::::LISTING ALL DATA COMPLETED:::::\n");
}

void createContact(AddressBook *addressBook) 
{
    printf("\t\t\t:::::ADD DATA:::::\n");
    printf("\nHow many contacts do you wann'a add?: ");
    int size;
    scanf("%d",&size);
    for(int i = 0; i < size; i++)
    {
        char name[20],contact[15],email_id[30];
    label:
        printf("Enter the name: ");
        getchar();
        scanf("%[^\n]",name);
        int res = add_contact_check(addressBook,contact,1);
        if(res == 0)
            goto label;
    label1:
        printf("Enter the Contact Number: ");
        getchar();
        scanf("%[^\n]",contact);
        res = contact_no_check(contact);
        if(res == 0)
        {
            printf("Enter the valid contact number!\n");
            goto label1;
        }
        res = add_contact_check(addressBook,contact,1);
        if(res == 0)
            goto label1;
    label2:
        printf("Enter the Email ID: ");
        getchar();
        scanf("%[^\n]",email_id);
        res = gmail_check(email_id);
        if(res == 0)
        {
            printf("Enter the valid email which has no uppercase letters and extension of '@gmail.com'\n");
            goto label2;
        }
        res = add_contact_check(addressBook,email_id,2);
        if(res == 0)
            goto label2;
        addressBook->contactCount++;
        addressBook -> contacts  = realloc(addressBook->contacts,addressBook->contactCount * sizeof(Contact));
        int j;
        int len = strlen(name);
        int len1 = strlen(contact);
        int len2 = strlen(email_id);
        for(j = 0; j <= len; j++)
            addressBook->contacts[addressBook->contactCount - 1].name[j] = name[j];
        for(j = 0; j <= len1; j++)
            addressBook->contacts[addressBook->contactCount - 1].phone[j] = contact[j];
        for(j = 0; j <= len2; j++)
            addressBook->contacts[addressBook->contactCount - 1].email[j] = email_id[j];
    }
    printf("\t\t\t:::::ADDING DATA COMPLETED:::::\n");
}
int add_contact_check(AddressBook *addressBook,char *input,int opt)
{
    switch(opt)
    {
        case 0:
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].name,input)))
                {
                    printf("Entered Name is already found in the contact!\n\n");
                    return 0;
                }
            }
            return 1;
        case 1:
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].phone,input)))
                {
                    printf("Entered Contact Number is already found in the contact!\n\n");
                    return 0;
                }
            }
            return 1;
        case 2:
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(!(strcmp(addressBook->contacts[i].email,input)))
                {
                    printf("Entered Email ID is already found in the contact!\n\n");
                    return 0;
                }
            }
            return 1;
    }

}
void searchContact(AddressBook *addressBook) 
{
    printf("\t\t\t:::::SEARCH SPECIFIC DATA:::::\n");
    printf("\n\nDo you wanna search by: \n");
    printf("1. Name\n2. Contact Number\n3. Email ID\n");
    int opt,i;
    printf("Choose one option: ");
    scanf("%d",&opt);
    switch(opt)
    {
        case 1:
            i = search_name(addressBook);
            printf("Name: %s Contact number: %s Email ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            break;
        case 2:
            i = search_contact_no(addressBook);  
            printf("Name: %s Contact number: %s Email ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            break;
        case 3:
            i = search_email(addressBook);
            printf("Name: %s Contact number: %s Email ID: %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            break;
    }
    printf("\t\t\t:::::SEARCHING SPECIFIC DATA COMPLETED:::::\n");
}
int search_name(AddressBook *addressBook)
{
    char s[100];
label:
    printf("\nEnter the name to search: ");
    getchar();
    scanf("%[^\n]",s);
    int i;
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(!(strcmp(addressBook->contacts[i].name,s)))
            return i;
    }
    if(i == addressBook->contactCount)
    {
        printf("Please Enter a valid name or entered name is not found\n");
        goto label;
    }
}
int search_contact_no(AddressBook *addressBook)
{
    char s[100];
label:
    printf("Enter the contact number to search: ");
    getchar();
    scanf("%[^\n]",s);
    int res = contact_no_check(s);
    if(res == 0)
    {
        printf("Enter the valid contact number!\n");
        goto label;
    }
    int i;
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(strstr(addressBook->contacts[i].phone,s))
            return i;
    }
    if(i == addressBook->contactCount)
    {
        printf("Please Enter a valid Contact Number or Entered Contact Number is not found\n");
        goto label;
    }
}
int search_email(AddressBook *addressBook)
{
    char s[100]; 
label1:
    printf("Enter the Email ID to search: ");
    getchar();
    scanf("%[^\n]",s);
    int res1 = gmail_check(s);
    if(res1 == 0)
    {
        printf("Enter the valid email which has no uppercase letters and extension of '@gmail.com'\n");
        goto label1;
    }
    int i;
    for(i = 0; i < addressBook->contactCount; i++)
    {
        if(!(strcmp(addressBook->contacts[i].email,s)))
            return i;
    }
    if(i == addressBook->contactCount)
    {
        printf("Please Enter a valid name or entered name is not found\n");
        goto label1;
    }
}
int contact_no_check(char *s)
{
    int len = strlen(s);
    if(len != 10)
        return 0;
    int count = 0;
    for(int i = 0; i < len; i++)
    {
        if(s[i] >= 48 && s[i] <= 57)
            count++;
        else
            return 0;
    }
    if(count == len)
        return 1;
}

int gmail_check(char *s)
{
    char email_id[13] = "@gmail.com";
    char *p = strstr(s,email_id);
    if(p != NULL)
    {
        for(int i = 0; s[i] != '@'; i++)
        {
           if((s[i] >= 97 && s[i] <= 122) || (s[i] >= 48 && s[i] <= 57))
               continue;
           else
               return 0;
        }
        return 1;
    }else    
        return 0;
}

void editContact(AddressBook *addressBook) 
{
    printf("\t\t\t:::::EDIT SPECIFIC DATA:::::\n");
    char s[100];
    printf("What do you want to edit choose the option below: \n1. name\n2. contact number\n3. email id\n");
    int opt,i;
    printf("Choose one option: ");
    scanf("%d",&opt);
    switch(opt)
    {
        case 1:
            i = search_name(addressBook);
            printf("Enter the name to update?\n");
            getchar();
            scanf("%[^\n]",addressBook->contacts[i].name);
            printf("\t\t\t:::::Contact is updated!:::::\n");
            break;
        case 2:
            i = search_contact_no(addressBook);
            printf("Enter the Contact Number to update?\n");
            getchar();
            scanf("%[^\n]",addressBook->contacts[i].phone);
            printf("\t\t\t:::::Contact is updated!:::::\n");
            break;
        case 3:
            i = search_email(addressBook);
            printf("Enter the Email ID to update?\n");
            getchar();
            scanf("%[^\n]",addressBook->contacts[i].email);
            printf("\t\t\t:::::Contact is updated!:::::\n");
            break;
    }
    printf("\t\t\t:::::EDITING SPECIFIC DATA COMPLETED:::::\n");
}

void deleteContact(AddressBook *addressBook) 
{
    printf("\t\t\t:::::DELETE FUNCTION:::::\n");      
    int opt,i,opt1,opt2;
    printf("Do you want to delete:\n1.All Data\n2.Specific Data\nChoose one option: ");
    scanf("%d",&opt2);
    switch(opt2)
    {
        case 1:
            addressBook->contactCount = 0;
            printf("All Data Deleted!\n");
            break;
        case 2:
            printf("\n\nHow many contacts do you wanna delete: ");
            scanf("%d",&opt1);
            for(int l = 0; l < opt1; l++)
            {
                printf("Do you wanna Delete by:\n1. Name\n2.Contact Number\n3.Eamil ID\n");
                printf("Choose one option: ");
                scanf("%d",&opt);
                printf("\n");
                switch(opt)
                {
                    case 1:
                        i = search_name(addressBook);
                        break;
                    case 2:
                        i = search_contact_no(addressBook);
                        break;
                    case 3:
                        i = search_email(addressBook);
                        break;
                }
                int k = 0;
                for(int j = 0; j < addressBook->contactCount; j++)
                {
                    if(j == i)
                        continue;
                    else
                    {
                        addressBook->contacts[k] = addressBook->contacts[j];
                        k++;
                    }
                }
                addressBook->contactCount--;
                addressBook -> contacts  = realloc(addressBook->contacts,addressBook->contactCount * sizeof(Contact));
                printf("%d Contact Deleted!\n\n\n",l+1);
            }
            break;
    }   
    printf("\t\t\t:::::DELETING PROCESS COMPLETED!:::::\n");

}
void saveContact(AddressBook *addressBook,FILE *fp)
{
    fp = fopen("contact.csv","w");
    fprintf(fp,"#%d#\n",addressBook->contactCount);
    for(int i = 0;i < addressBook->contactCount; i++)
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    free(addressBook->contacts);
}
