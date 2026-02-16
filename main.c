/*NAME: ABINATH S
  DATE: 10/10/2025
  DESCRIPTION:To define adressbook project.
 	      1.Create the contact(name,phone number,mail id)
	      2.Search contact(search by name,phone number,mail id)
	      3.Edit contact(search contact and edit which fild we want to edit)
	      4.Delete contact(search contact then delete the contact)
	      5.List all contact
	      6.Save and exit.
*/ 
#include "contact.h"

int main() 
{
    int choice;

    struct AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do 
    {
	printf("\nAddress Book Menu:\n");
	printf("1. Create contact\n");
	printf("2. Search contact\n");
	printf("3. Edit contact\n");
	printf("4. Delete contact\n");
	printf("5. List all contacts\n");
	printf("6. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) 
	{
	    case 1:
		createContact(&addressBook);
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
		printf("Saving and Exiting...\n");
		saveAndExit(&addressBook);
		break;
	    default:
		printf("Invalid choice. Please try again.\n");
	}
    } while (choice != 6);

    return 0;
}
