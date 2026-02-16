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
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void listContacts(struct AddressBook *addressBook) 
{
	/* Define the logic for print the contacts */
	for(int i=0;i<(addressBook->contactCount);i++)
	{
		printf("NAME : %s\nPHONE NUMBER : %s\nEMAIL ID : %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		printf("---------------------------------------------------------\n");
	}
}

void initialize(struct AddressBook *addressBook)
{
	addressBook->contactCount = 0;
	//populateAddressBook(addressBook);

	//Load contacts from file during initialization (After files)
	loadContactsFromFile(addressBook);//when start the process load all contact from file to stack.
}

void saveAndExit(struct AddressBook *addressBook)
{
	saveContactsToFile(addressBook); // Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}

int my_num_check(struct AddressBook* addressBook,char* phone)//number validation.
{
	int count = 0;
	int len = strlen(phone);
	if(len == 10)//check for only 10 characters
	{
		for(int i=0;i<len;i++)//check for 10 characters are digits.
		{
			if(phone[i] >= '0' && phone[i] <= '9')
			{
				count++;
			}
			else
			{
				return 1;
			}
		}
		if(count == 10)
		{
			return 0;
		}	
	}
	else
	{
		return 1;
	}
}
int my_num_unique_check(struct AddressBook* addressBook,char* phone)//unique number validation.
{
	for(int i=0;i<(addressBook->contactCount);i++)
	{
		if(!(strcmp(addressBook->contacts[i].phone,phone)))//compare the number.
		{
			return 1;
		}
	}
	return 0;
}
int my_mail_check(struct AddressBook* addressBook,char* mail)//email validation.
{
	char ch = '@';
	char end[] = ".com";
	for(int i=0;i<strlen(mail);i++)//check for uppercase.
	{
		if(mail[i] >='A' && mail[i] <='Z')
		{
			return 1;
		}
	}
	if(!(strchr(mail,ch)))//check for '@'
	{
		return 1;
	}
	char* result = strchr(mail,ch);//check before and after of '@' as a character.
	{
		if(!(isalnum(*(result+1))) && isalnum(*(result-1)))
		{
			return 1;
		}
	}
	if(!(strstr(mail,end)))//check for ".com"
	{
		return 1;
	}
	char* res = strstr(mail,end);//check for ".com" at end of string.
	if(*(res+4) != '\0')
	{
		return 1;
	}
	return 0;
}
int my_mail_unique_check(struct AddressBook* addressBook,char* mail)//unique mail validation.
{
	for(int i=0;i<(addressBook->contactCount);i++)
	{
		if(!(strcmp(addressBook->contacts[i].email,mail)))//compare mail.
		{
			return 1;
		}
	}
	return 0;
}
void createContact(struct AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
	//name
	printf("Enter the name: ");
	scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
	//phone number
	char phone[20];
	int j;
	int flag;
	printf("Enter the phone number: ");
	do
	{
		flag = 0;
		j = 0;
		scanf(" %s",phone);
		int check = my_num_check(addressBook,phone);//check the number.
		if(check)
		{
			flag = 1;
			printf("Entered number is invalid !\nplease enter valid number:");
			j = 1;
		}
		if(flag == 0)
		{
			int ret = my_num_unique_check(addressBook,phone);//check the number for unique.
			if(ret)
			{
				printf("Entered number is invalid !\nplease enter valid number:");
				j = 1;
			}
		}
	}while(j);
	strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);//copy the number to the main address.
									     //email
	char mail[50];
	int m;
	printf("Enter the mail id: ");
	do
	{
		m = 0;
		flag = 0;
		scanf(" %[^\n]",mail);
		int check = my_mail_check(addressBook,mail);//check the mail.
		if(check)
		{
			flag = 1;
			printf("Entered mail is invalid !\nplease enter valid mail id:");
			m = 1;
		}
		if(flag == 0)
		{
			int res = my_mail_unique_check(addressBook,mail);//check the mail for unique.
			if(res)
			{
				printf("Entered mail is invalid !\nplease enter valid mail id:");
				m = 1;
			}
		}
	}while(m);
	strcpy(addressBook->contacts[addressBook->contactCount].email,mail);//cpy the mail to the main address.
	addressBook->contactCount++;//increase the contact count.
}
void searchContact(struct AddressBook *addressBook) 
{
	/* Define the logic for search */
	printf("Search menu:\n");
	printf("1.Search by name.\n2.Search by phone number.\n3.Search by email.\n");
	int opt;
	int flag;
	printf("Enter your choice : ");
	scanf("%d",&opt);
	switch(opt)
	{
		case 1://search by name.
			char str[20];
			flag = 0;
			printf("Enter the name: ");
			scanf(" %[^\n]",str);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(!(strcmp(addressBook->contacts[i].name,str)))//if found print all details.
				{
					flag = 1;
					printf("NAME : %s\n",addressBook->contacts[i].name);
					printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
					printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
					printf("--------------------------------------------------------\n");
				}
			}
			if(flag == 0)
			{
				printf("! Contact not found !\n");//if not found.
			}
			break;
		case 2:
			char phone[20];
			int j = 0;
			flag = 0;
			printf("Entre the phone number: ");
			do
			{
				scanf(" %s",phone);//search by phone.
				if(my_num_check(addressBook,phone))//number validation.
				{
					printf("Entered number is invalid !\nplease enter valid number:");
					j = 1;
				}
				else
				{
					j = 0;
				}
			}while(j);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(!(strcmp(addressBook->contacts[i].phone,phone)))//if found print all details.
				{
					flag = 1;
					printf("NAME : %s\n",addressBook->contacts[i].name);
					printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
					printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
					printf("--------------------------------------------------------\n");
					break;
				}
			}
			if(flag == 0)
			{
				printf("! Contact not found !\n");//if not found.
			}
			break;
		case 3:
			char mail[50];
			int m;
			printf("Enter the mail id: ");
			do
			{
				m = 0;
				flag = 0;
				scanf(" %[^\n]",mail);//search by mail id.
				int check = my_mail_check(addressBook,mail);//mail validation.
				if(check)
				{
					flag = 1;
					printf("Entered mail is invalid !\nplease enter valid mail id:");
					m = 1;
				}
			}while(m);
			for(int i=0;i<addressBook->contactCount;i++)
			{
				if(!(strcmp(addressBook->contacts[i].email,mail)))//if found print all details.
				{
					flag = 1;
					printf("NAME : %s\n",addressBook->contacts[i].name);
					printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
					printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
					printf("--------------------------------------------------------\n");
					break;
				}
			}
			if(flag == 0)
			{
				printf("! Contact not found !\n");//if not found.
			}
			break;
	}
}

void editContact(struct AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int opt;
	do
	{
		printf("Search menu:\n");
		printf("1.Search by name.\n2.Search by phone number.\n3.Search by email.\n4.Exit\n");
		int flag;
		int i;
		int ind_arr[addressBook->contactCount];
		printf("Enter your choice : ");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1://search by name for edit .
				char name[20];
				flag = 0;
				int count = 0;
				int num;
				printf("Enter the name: ");
				scanf(" %[^\n]",name);
				for(i=0;i<addressBook->contactCount;i++)
				{
					if(!(strcmp(addressBook->contacts[i].name,name)))
					{
						flag = 1;
						ind_arr[count] = i;
						count++;	
						printf("%d.NAME : %s\n",count,addressBook->contacts[i].name);
						printf("  PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
						printf("  EMAIL ID : %s\n",addressBook->contacts[i].email);
						printf("--------------------------------------------------------\n");
					}
				}
				if(flag == 0)
				{
					printf("! Contact not found !\n");
				}
				if(count>1)//if more contacts found by same name.
				{
					printf("Which contact you want to edit\nEnter the number: ");
					scanf("%d",&num);
					printf("NAME : %s\n",addressBook->contacts[ind_arr[num-1]].name);
					printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[num-1]].phone);
					printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[num-1]].email);
					printf("--------------------------------------------------------\n");
					int edit;
					do
					{
						printf("1.Name\n2.Phone\n3.Email id\n4.exit\n");
						printf("which field you want to edit\n");//menu fields for edit.
						char new_name[20];
						char new_phone[20];
						char new_mail[50];
						scanf("%d",&edit);
						switch(edit)
						{
							case 1:
								printf("Enter the new name:");
								scanf(" %[^\n]",new_name);
								strcpy(addressBook->contacts[ind_arr[num-1]].name,new_name);
								printf("NAME : %s\n",addressBook->contacts[ind_arr[num-1]].name);
								printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[num-1]].phone);
								printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[num-1]].email);
								printf("------------------------------------------------\n");
								break;
							case 2:
								char new_phone[20];
								int j;
								printf("Enter the new number:");
								do
								{
									flag = 0;
									j = 0;
									scanf(" %s",new_phone);
									int check = my_num_check(addressBook,new_phone);
									if(check)
									{
										flag = 1;
										printf("Entered number is invalid !\nplease enter valid number:");
										j = 1;
									}
									if(flag == 0)
									{
										int ret = my_num_unique_check(addressBook,new_phone);
										if(ret)
										{
											printf("Entered number is invalid !\nplease enter valid number:");
											j = 1;
										}
									}
								}while(j);
								strcpy(addressBook->contacts[ind_arr[num-1]].phone,new_phone);
								printf("NAME : %s\n",addressBook->contacts[ind_arr[num-1]].name);
								printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[num-1]].phone);
								printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[num-1]].email);
								printf("------------------------------------------------\n");
								break;
							case 3:
								char new_mail[60];
								int m;
								printf("Enter the new email:");
								do
								{
									m = 0;
									flag = 0;
									scanf(" %[^\n]",new_mail);
									int check = my_mail_check(addressBook,new_mail);
									if(check)
									{
										flag = 1;
										printf("Entered mail is invalid !\nplease enter valid mail id:");
										m = 1;
									}
									if(flag == 0)
									{
										int res = my_mail_unique_check(addressBook,new_mail);
										if(res)
										{
											printf("Entered mail is invalid !\nplease enter valid mail id:");
											m = 1;
										}
									}
								}while(m);
								strcpy(addressBook->contacts[ind_arr[num-1]].email,new_mail);
								printf("NAME : %s\n",addressBook->contacts[ind_arr[num-1]].name);
								printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[num-1]].phone);
								printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[num-1]].email);
								printf("------------------------------------------------\n");
								break;
							case 4:
								printf("! Exit !\n");
								break;
							default:
								printf("please enter valid option\n");
						}
					}while(edit != 4);
				}
				if(count == 1)
				{
					int edit;
					do
					{
						printf("1.Name\n2.Phone\n3.Email id\n4.exit\n");
						printf("which field you want to edit\n");
						char new_name[20];
						char new_phone[20];
						char new_mail[50];
						scanf("%d",&edit);
						switch(edit)
						{
							case 1:
								printf("Enter the new name:");
								scanf(" %[^\n]",new_name);
								strcpy(addressBook->contacts[ind_arr[0]].name,new_name);
								printf("NAME : %s\n",addressBook->contacts[ind_arr[0]].name);
								printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[0]].phone);
								printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[0]].email);
								printf("------------------------------------------------\n");
								break;
							case 2:
								char new_phone[20];
								int j;
								printf("Enter the new number:");
								do
								{
									flag = 0;
									j = 0;
									scanf(" %s",new_phone);
									int check = my_num_check(addressBook,new_phone);
									if(check)
									{
										flag = 1;
										printf("Entered number is invalid !\nplease enter valid number:");
										j = 1;
									}
									if(flag == 0)
									{
										int ret = my_num_unique_check(addressBook,new_phone);
										if(ret)
										{
											printf("Entered number is invalid !\nplease enter valid number:");
											j = 1;
										}
									}
								}while(j);
								strcpy(addressBook->contacts[ind_arr[0]].phone,new_phone);
								printf("NAME : %s\n",addressBook->contacts[ind_arr[0]].name);
								printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[0]].phone);
								printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[0]].email);
								printf("------------------------------------------------\n");
								break;
							case 3:
								char new_mail[60];
								int m;
								printf("Enter the new email:");
								do
								{
									m = 0;
									flag = 0;
									scanf(" %[^\n]",new_mail);
									int check = my_mail_check(addressBook,new_mail);
									if(check)
									{
										flag = 1;
										printf("Entered mail is invalid !\nplease enter valid mail id:");
										m = 1;
									}
									if(flag == 0)
									{
										int res = my_mail_unique_check(addressBook,new_mail);
										if(res)
										{
											printf("Entered mail is invalid !\nplease enter valid mail id:");
											m = 1;
										}
									}
								}while(m);
								strcpy(addressBook->contacts[ind_arr[0]].email,new_mail);
								printf("NAME : %s\n",addressBook->contacts[ind_arr[0]].name);
								printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[0]].phone);
								printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[0]].email);
								printf("------------------------------------------------\n");
								break;
							case 4:
								printf("! Exit !\n");
								break;
							default:
								printf("please enter valid option\n");
						}
					}while(edit != 4);
				}
				break;
			case 2:
				char phone[20];
				int j = 0;
				flag = 0;
				printf("Entre the phone number: ");
				do
				{
					scanf(" %s",phone);//search by phone number for edit.
					if(my_num_check(addressBook,phone))
					{
						printf("Entered number is invalid !\nplease enter valid number:");
						j = 1;
					}
					else
					{
						j = 0;
					}
				}while(j);
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(!(strcmp(addressBook->contacts[i].phone,phone)))
					{
						flag = 1;
						printf("NAME : %s\n",addressBook->contacts[i].name);
						printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
						printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
						printf("--------------------------------------------------------\n");
						int edit;
						do
						{
							printf("1.Name\n2.Phone\n3.Email id\n4.exit\n");
							printf("which field you want to edit\n");
							char new_name[20];
							char new_phone[20];
							char new_mail[50];
							scanf("%d",&edit);
							switch(edit)
							{
								case 1:
									printf("Enter the new name:");
									scanf(" %[^\n]",new_name);
									strcpy(addressBook->contacts[i].name,new_name);
									printf("NAME : %s\n",addressBook->contacts[i].name);
									printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
									printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
									printf("------------------------------------------------\n");
									break;
								case 2:
									char new_phone[20];
									int j;
									printf("Enter the new number:");
									do
									{
										flag = 0;
										j = 0;
										scanf(" %s",new_phone);
										int check = my_num_check(addressBook,new_phone);
										if(check)
										{
											flag = 1;
											printf("Entered number is invalid !\nplease enter valid number:");
											j = 1;
										}
										if(flag == 0)
										{
											int ret = my_num_unique_check(addressBook,new_phone);
											if(ret)
											{
												printf("Entered number is invalid !\nplease enter valid number:");
												j = 1;
											}
										}
									}while(j);
									strcpy(addressBook->contacts[i].phone,new_phone);
									printf("NAME : %s\n",addressBook->contacts[i].name);
									printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
									printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
									printf("------------------------------------------------\n");
									break;
								case 3:
									char new_mail[50];
									int m;
									printf("Enter the new email:");
									do
									{
										m = 0;
										flag = 0;
										scanf(" %[^\n]",new_mail);
										int check = my_mail_check(addressBook,new_mail);
										if(check)
										{
											flag = 1;
											printf("Entered mail is invalid !\nplease enter valid mail id:");
											m = 1;
										}
										if(flag == 0)
										{
											int res = my_mail_unique_check(addressBook,new_mail);
											if(res)
											{
												printf("Entered mail is invalid !\nplease enter valid mail id:");
												m = 1;
											}
										}
									}while(m);
									strcpy(addressBook->contacts[i].email,new_mail);
									printf("NAME : %s\n",addressBook->contacts[i].name);
									printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
									printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
									printf("------------------------------------------------\n");
									break;
								case 4:
									printf("! Exit !\n");
								default:
									printf("please enter valid option\n");
							}
						}while(edit != 4);
					}
				}
				if(flag == 0)
				{
					printf("! Contact not found !\n");
				}
				break;
			case 3:
				char mail[50];
				int m;
				printf("Enter the mail id: ");
				do
				{
					m = 0;
					flag = 0;
					scanf(" %[^\n]",mail);//search by mail id for edit.
					int check = my_mail_check(addressBook,mail);
					if(check)
					{
						flag = 1;
						printf("Entered mail is invalid !\nplease enter valid mail id:");
						m = 1;
					}
				}while(m);
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(!(strcmp(addressBook->contacts[i].email,mail)))
					{
						flag = 1;
						printf("NAME : %s\n",addressBook->contacts[i].name);
						printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
						printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
						printf("--------------------------------------------------------\n");
						int edit;
						do
						{
							printf("1.Name\n2.Phone\n3.Email id\n4.exit\n");
							printf("which field you want to edit\n");
							char new_name[20];
							char new_phone[20];
							char new_mail[50];
							scanf("%d",&edit);
							switch(edit)
							{
								case 1:
									printf("Enter the new name:");
									scanf(" %[^\n]",new_name);
									strcpy(addressBook->contacts[i].name,new_name);
									printf("NAME : %s\n",addressBook->contacts[i].name);
									printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
									printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
									printf("------------------------------------------------\n");
									break;
								case 2:
									char new_phone[20];
									int j;
									printf("Enter the new number:");
									do
									{
										flag = 0;
										j = 0;
										scanf(" %s",new_phone);
										int check = my_num_check(addressBook,new_phone);
										if(check)
										{
											flag = 1;
											printf("Entered number is invalid !\nplease enter valid number:");
											j = 1;
										}
										if(flag == 0)
										{
											int ret = my_num_unique_check(addressBook,new_phone);
											if(ret)
											{
												printf("Entered number is invalid !\nplease enter valid number:");
												j = 1;
											}
										}
									}while(j);
									strcpy(addressBook->contacts[i].phone,new_phone);
									printf("NAME : %s\n",addressBook->contacts[i].name);
									printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
									printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
									printf("------------------------------------------------\n");
									break;
								case 3:
									char new_mail[60];
									int m;
									printf("Enter the new email:");
									do
									{
										m = 0;
										flag = 0;
										scanf(" %[^\n]",mail);
										int check = my_mail_check(addressBook,new_mail);
										if(check)
										{
											flag = 1;
											printf("Entered mail is invalid !\nplease enter valid mail id:");
											m = 1;
										}
										if(flag == 0)
										{
											int res = my_mail_unique_check(addressBook,new_mail);
											if(res)
											{
												printf("Entered mail is invalid !\nplease enter valid mail id:");
												m = 1;
											}
										}
									}while(m);
									strcpy(addressBook->contacts[i].email,new_mail);
									printf("NAME : %s\n",addressBook->contacts[i].name);
									printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
									printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
									printf("------------------------------------------------\n");
									break;
								case 4:
									printf("! Exit !\n");
									break;
								default:
									printf("please enter valid option\n");
							}
						}while(edit != 4);
						break;
					}
				}
				if(flag == 0)
				{
					printf("! Contact not found !\n");
				}
				break;
			case 4:
				printf("! Exit !\n");
				break;
			default:
				printf("Enter the valid option\n");
		}
	}while(opt != 4);
}
void deleteContact(struct AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
	int opt;
	do
	{
		printf("Search menu:\n");
		printf("1.Search by name.\n2.Search by phone number.\n3.Search by email.\n4.Exit\n");
		int flag;
		int i;
		int ind_arr[addressBook->contactCount];
		printf("Enter your choice : ");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1://search by name for delete.
				char name[20];
				flag = 0;
				int count = 0;
				int num;
				printf("Enter the name: ");
				scanf(" %[^\n]",name);
				for(i=0;i<addressBook->contactCount;i++)
				{
					if(!(strcmp(addressBook->contacts[i].name,name)))
					{
						flag = 1;
						ind_arr[count] = i;
						count++;	
						printf("%d.NAME : %s\n",count,addressBook->contacts[i].name);
						printf("  PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
						printf("  EMAIL ID : %s\n",addressBook->contacts[i].email);
						printf("--------------------------------------------------------\n");
					}
				}
				if(flag == 0)
				{
					printf("! Contact not found !\n");
				}
				if(count>1)
				{
					printf("Which contact you want to delete\nEnter the number: ");
					scanf("%d",&num);
					printf("NAME : %s\n",addressBook->contacts[ind_arr[num-1]].name);
					printf("PHONE NUMBER : %s\n",addressBook->contacts[ind_arr[num-1]].phone);
					printf("EMAIL ID : %s\n",addressBook->contacts[ind_arr[num-1]].email);
					printf("--------------------------------------------------------\n");
					for(int i=ind_arr[num-1];i<addressBook->contactCount;i++)
					{
						strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
						strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
						strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
					}
				}
				else
				{
					for(int i=ind_arr[0];i<addressBook->contactCount;i++)
					{
						strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
						strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
						strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
					}
				}
				break;
			case 2:
				char phone[20];
				int j = 0;
				flag = 0;
				printf("Entre the phone number: ");
				do
				{
					scanf(" %s",phone);//search by phone to delete.
					if(my_num_check(addressBook,phone))
					{
						printf("Entered number is invalid !\nplease enter valid number:");
						j = 1;
					}
					else
					{
						j = 0;
					}
				}while(j);
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(!(strcmp(addressBook->contacts[i].phone,phone)))
					{
						flag = 1;
						printf("NAME : %s\n",addressBook->contacts[i].name);
						printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
						printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
						for(int j=i;j<addressBook->contactCount;j++)
						{
							strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
							strcpy(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
							strcpy(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
						}
						break;
					}
				}
				if(flag == 0)
				{
					printf("! Contact not found !\n");
				}
				break;
			case 3:
				char mail[50];
				int m;
				printf("Enter the mail id: ");
				do
				{
					m = 0;
					flag = 0;
					scanf(" %[^\n]",mail);//search by mail to delete.
					int check = my_mail_check(addressBook,mail);
					if(check)
					{
						flag = 1;
						printf("Entered mail is invalid !\nplease enter valid mail id:");
						m = 1;
					}
				}while(m);
				for(int i=0;i<addressBook->contactCount;i++)
				{
					if(!(strcmp(addressBook->contacts[i].email,mail)))
					{
						flag = 1;
						printf("NAME : %s\n",addressBook->contacts[i].name);
						printf("PHONE NUMBER : %s\n",addressBook->contacts[i].phone);
						printf("EMAIL ID : %s\n",addressBook->contacts[i].email);
						printf("--------------------------------------------------------\n");
						for(int j=i;j<addressBook->contactCount;j++)
						{
							strcpy(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
							strcpy(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
							strcpy(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
						}
						break;
					}
				}
				if(flag == 0)
				{
					printf("! Contact not found !\n");
				}
				break;
			case 4:
				printf("! Exit !\n");
				break;
			default:
				printf("Enter the valid option\n");
		}
	}while(opt != 4);
	addressBook->contactCount--;//decrement the contact count.
}
