#include "contact.h"

int main() 
{
    AddressBook addressBook;
    initialize1(&addressBook);
    // loadDummyContacts(&addressBook); // Load dummy contacts initially

    int choice;
    do {
        printf("Contact Count: %d\n", addressBook.contactCount);
        printf("1. Add Contact\n2. Search Contact\n3. Edit Contact\n4. Delete Contact\n5. List Contacts\n6. Save Contact\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To handle the newline character left by scanf
        printf("\n");

        switch (choice)
         {
            case 1:
                addContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                saveContact(&addressBook);
                break;    
            case 7:
                printf("Exiting........\n      Thank you.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice != 7);

    return 0;
}