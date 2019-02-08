#include "pch.h"
#include <iostream>
#include <cstring>

using namespace std;

struct BookType
{
	int bookID;
	char title[256];
	char author[256];
	int year;
	float price;
};

void BookFunc(const BookType& book);

int main6()
{
	BookType book;
	strcpy(book.author, "Mark Twain");
	book.bookID = 12345;
	strcpy(book.title, "The book title");
	book.year = 1950;
	book.price = 23.5f;

	BookType* bookPtr = &book;
	BookType* newBookPtr = new BookType;
	(*bookPtr).year = 2000;
	bookPtr->year = 2018;

	delete bookPtr;

	return 0;
}

void BookFunc(const BookType& book)
{

}