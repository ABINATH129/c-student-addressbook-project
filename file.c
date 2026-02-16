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
#include <stdio.h>
#include "file.h"

void saveContactsToFile(struct AddressBook *addressBook)
{
	FILE* fp = fopen("addressbook.csv","w");
	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	fclose(fp);  
}

void loadContactsFromFile(struct AddressBook *addressBook)
{
	FILE* fp = fopen("addressbook.csv","r");
	int i = 0;
	while((!(feof(fp))))
	{
		fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		i++;
	}
	addressBook->contactCount = i;
	fclose(fp);
}
