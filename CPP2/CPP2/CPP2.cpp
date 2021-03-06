// CPP2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "Utils.h"

using namespace std;

const int MAX_NAME_SIZE = 256;
const char * INPUT_ERROR_STRING = "Input error!";

struct Contact
{
	char firstName[MAX_NAME_SIZE];
	char lastName[MAX_NAME_SIZE];
	int phoneNumber;
};

struct ContactsDB
{
	Contact* ownerPtrContacts;
	int numOfContacts;
	int capacity;
};

char GetOptionFromUser();
void ExecuteOption(char option, ContactsDB& contactsDB);
bool LoadContacts(ContactsDB& contactsDB);
void AddOption(ContactsDB& contactsDB);
void DisplayOption(const ContactsDB& contactsDB);

int main()
{
	char option;
	ContactsDB contactsDB;
	contactsDB.ownerPtrContacts = nullptr;
	contactsDB.numOfContacts = 0;
	contactsDB.capacity = 0;

	LoadContacts(contactsDB);

	do
	{
		option = GetOptionFromUser();
		ExecuteOption(option, contactsDB);
	} while (option != 'q');

	return 0;
}

char GetOptionFromUser()
{
	const char options[] = { 'd', 'a', 'q' };
	return GetCharacter("Please choose an option:\n\n(d) Display Contacts\n(a) Add Contact\n(q)Quit\n\nWhat is your choice: ", INPUT_ERROR_STRING, options, 3, CC_LOWER_CASE);
}

void ExecuteOption(char option, ContactsDB& contactsDB)
{
	switch (option)
	{
	case 'a':
		AddOption(contactsDB);
		break;
	case 'd':
		DisplayOption(contactsDB);
		break;
	default:
		break;
	}
}

bool LoadContacts(ContactsDB& contactsDB)
{

}
void AddOption(ContactsDB& contactsDB)
{
	if (contactsDB.numOfContacts == contactsDB.capacity)
	{
		ResizeContactsDB(contactsDB, contactsDB.capacity * 2 + 10);
	}
}

void DisplayOption(const ContactsDB& contactsDB)
{
	for (int i = 0; i < contactsDB.numOfContacts; i++)
	{
		cout << "First Name: " << contactsDB.ownerPtrContacts[i].firstName << "Last Name: " << contactsDB.ownerPtrContacts[i].lastName << "Phone Number: " << contactsDB.ownerPtrContacts[i].phoneNumber << endl;
	}
}
