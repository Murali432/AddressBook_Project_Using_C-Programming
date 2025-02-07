#include "contact.h"

void initialize1(AddressBook *addressBook)
{
    FILE *fp;
    fp=fopen("Contact.txt","r");
    if(fp==NULL)
    {
        printf("File not found\n");
    }
    addressBook->contactCount=0;
    int i=0;
    while((fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email))==3)
    {
        i++;
        addressBook->contactCount++;
        if(addressBook->contactCount>=MAX_CONTACTS)
        {
            printf("Reached maximum contacts. No more contacts can be added.\n");
            break;
        }
    }
    fclose(fp);
}

bool isValidName(const char *name) 
{
    if (strlen(name) == 0 || strspn(name, " ") == strlen(name)) 
    {
        return false;
    }

    for (int i = 0; name[i] != '\0'; i++) 
    {
        if (!isalpha(name[i]) && name[i] != ' ') 
        {
            return false;
        }
    }
    return true;
}

bool isValidPhone(const char *phone) 
{
    if (strlen(phone) != 10) 
    {
        return false;
    }

    for (int i = 0; phone[i] != '\0'; i++) 
    {
        if (!isdigit(phone[i])) 
        {
            return false;
        }
    }

    // Reject sequential or repeated digits
    bool allSame = true;
    bool sequential = true;
    for (int i = 1; i < 10; i++) 
    {
        if (phone[i] != phone[i - 1]) 
        {
            allSame = false;
        }

        if (phone[i] != phone[i - 1] + 1) 
        {
            sequential = false;
        }
    }

    // Explicitly reject "1234567890" and similar sequences
    if (strcmp(phone, "1234567890") == 0 || strcmp(phone, "0987654321") == 0) 
    {
        return false;
    }

    return !(allSame || sequential);
}


bool isValidEmail(const char *email) 
{
    const char *gmailDomain = "@gmail.com";
    size_t len = strlen(email);
    size_t domainLen = strlen(gmailDomain);

    if (len < domainLen) 
    {
        return false;
    }

    // Check for only spaces before @gmail.com
    for (int i = 0; i < len - domainLen; i++) 
    {
        if (!isspace(email[i]))
         {
            return strcmp(email + len - domainLen, gmailDomain) == 0;
        }
    }
    return false;
}

void addContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount >= MAX_CONTACTS) 
    {
        printf("Address book is full. Cannot add more contacts.\n");
        return;
    }

    Contact newContact;

    // Validate Name
    do {
        printf("Enter Name: ");
        fgets(newContact.name, sizeof(newContact.name), stdin);
        newContact.name[strcspn(newContact.name, "\n")] = 0; // Remove newline
        if (!isValidName(newContact.name)) 
        {
            printf("Invalid name. Please enter only alphabetic characters and spaces.\n");
        }
    } 
    while (!isValidName(newContact.name));

    // Validate Phone
    do {
        printf("Enter Phone (10 digits): ");
        fgets(newContact.phone, sizeof(newContact.phone), stdin);
        newContact.phone[strcspn(newContact.phone, "\n")] = 0; // Remove newline
        if (!isValidPhone(newContact.phone)) 
        {
            printf("Invalid phone number. Please enter exactly 10 digits (not all same or sequential).\n");
        }
    } 
    while (!isValidPhone(newContact.phone));

    // Validate Email
    do {
        printf("Enter Email (must end with @gmail.com): ");
        fgets(newContact.email, sizeof(newContact.email), stdin);
        newContact.email[strcspn(newContact.email, "\n")] = 0; // Remove newline
        if (!isValidEmail(newContact.email)) 
        {
            printf("Invalid email. Please enter an email ending with @gmail.com and no leading spaces.\n");
        }
    }
     while (!isValidEmail(newContact.email));

    addressBook->contacts[addressBook->contactCount++] = newContact;
    printf("Contact added successfully!\n");
}

void searchContact(AddressBook *addressBook)
 {
    int searchChoice;
    char input[50];
    int found = 0;

    printf("Search by:\n1. Name\n2. Phone\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);
    getchar();  // To handle the newline character left by scanf

    switch (searchChoice) 
    {
        case 1:
            do {
                printf("Enter Name to Search: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // Remove newline
                if (!isValidName(input)) 
                {
                    printf("Invalid name. Please enter only alphabetic characters and spaces.\n");
                }
            } while (!isValidName(input));

            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].name, input) == 0) 
                {
                    printf("Contact Found: \nName: %s\nPhone: %s\nEmail: %s\n",
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            break;

        case 2:
            do {
                printf("Enter Phone to Search: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // Remove newline
                if (!isValidPhone(input)) 
                {
                    printf("Invalid phone number. Please enter exactly 10 numeric digits.\n");
                }
            } 
            while (!isValidPhone(input));

            for (int i = 0; i < addressBook->contactCount; i++)
             {
                if (strcmp(addressBook->contacts[i].phone, input) == 0) 
                {
                    printf("Contact Found: \nName: %s\nPhone: %s\nEmail: %s\n",
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            break;

        case 3:
            do {
                printf("Enter Email to Search: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // Remove newline
                if (!isValidEmail(input)) 
                {
                    printf("Invalid email. Please enter an email ending with @gmail.com.\n");
                }
            }
             while (!isValidEmail(input));

            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].email, input) == 0) 
                {
                    printf("Contact Found: \nName: %s\nPhone: %s\nEmail: %s\n",
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            break;

        default:
            printf("Invalid choice. Please choose 1, 2, or 3.\n");
            return;
    }

    if (!found) 
    {
        printf("No contact found matching the given details.\n");
    }
}

void editContact(AddressBook *addressBook) 
{
    char searchName[50];
    printf("Enter Name to Edit: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0; // Remove newline

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, searchName) == 0) 
        {
            printf("Editing Contact: %s\n", addressBook->contacts[i].name);

            do {
                printf("Enter New Phone (10 digits): ");
                fgets(addressBook->contacts[i].phone, sizeof(addressBook->contacts[i].phone), stdin);
                addressBook->contacts[i].phone[strcspn(addressBook->contacts[i].phone, "\n")] = 0; // Remove newline
                if (!isValidPhone(addressBook->contacts[i].phone)) 
                {
                    printf("Invalid phone number. Please enter exactly 10 numeric digits.\n");
                }
            }
             while (!isValidPhone(addressBook->contacts[i].phone));

            do {
                printf("Enter New Email (must end with @gmail.com): ");
                fgets(addressBook->contacts[i].email, sizeof(addressBook->contacts[i].email), stdin);
                addressBook->contacts[i].email[strcspn(addressBook->contacts[i].email, "\n")] = 0; // Remove newline
                if (!isValidEmail(addressBook->contacts[i].email)) 
                {
                    printf("Invalid email. Please enter an email ending with @gmail.com.\n");
                }
            } 
            while (!isValidEmail(addressBook->contacts[i].email));

            printf("Contact updated successfully!\n");
            return;
        }
    }

    printf("Contact not found.\n");
}

void deleteContact(AddressBook *addressBook)
 {
    char searchName[50];
    printf("Enter Name to Delete: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0; // Remove newline

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, searchName) == 0) 
        {
            for (int j = i; j < addressBook->contactCount - 1; j++)
             {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }
            addressBook->contactCount--;
            printf("Contact deleted successfully!\n");
            return;
        }
    }

    printf("Contact not found.\n");
}

void listContacts(AddressBook *addressBook)
 {
    if (addressBook->contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }

    printf("Listing All Contacts:\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Sl.No\tNAME\t\t\tPhone No\t\tEmail ID\n");
    printf("----------------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {    
         printf("%d\t%s\t\t%s\t\t%s\n",i+1,
         addressBook->contacts[i].name,
         addressBook->contacts[i].phone,
         addressBook->contacts[i].email);   
    }
}


void saveContact(AddressBook *addressBook)
{
    FILE *fp;
    fp=fopen("Contact.txt","w");
    int i=0;
    while(i!=addressBook->contactCount)
    {
        fputs(addressBook->contacts[i].name,fp);
        fputc(',',fp);

        fputs(addressBook->contacts[i].phone,fp);
        fputc(',',fp);

        fputs(addressBook->contacts[i].email,fp);
        fputc('\n',fp);

        i++;
    }
    fclose(fp);
}


