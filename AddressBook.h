//AddressBook.h
/*
파일이름 : AddressBook.h
기    능 :
작 성 자 : 이병도
작성일자 : 2017년 6월 12일
*/
#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H

//매크로 선언
#define NAME 11
#define ADDRESS 128
#define TELEPHONENUMBER 12
#define EMAILADDRESS 128


//자료형 설계
typedef signed long int Long;
typedef struct _personal {
	char name[NAME];
	char address[ADDRESS];
	char telephoneNumber[TELEPHONENUMBER];
	char emailAddress[EMAILADDRESS];
} Personal;
typedef struct _addressBook {
	Personal (*personals);
	Long capacity;
	Long length;
} AddressBook;

//함수 선언
void Create(AddressBook *addressBook, Long capacity);
Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress));
void Find(AddressBook *addressBook, char(*name), Long *(*indexes), Long *count);
Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress));
Long Erase(AddressBook *addressBook, Long index);
void Arrange(AddressBook *addressBook);
void Destroy(AddressBook *addressBook);

#endif //_ADDRESSBOOK_H