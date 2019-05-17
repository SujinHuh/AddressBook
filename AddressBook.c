//AddressBook.c
/*
파일이름 : AddressBook.c
기    능 : 이름, 주소, 전화번호, 이메일주소를 기재하여 주소록을 만들고 찾기, 고치기, 지우기, 정리하기의 기능을 제공한다.
작 성 자 : 이병도
작성일자 : 2017년 6월 12일
*/

//매크로 선언
#include "AddressBook.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdafx.h"
#pragma warning (disable : 4996)

//함수 정의
/*int main(int argc, char *argv[])
{
	AddressBook addressBook;
	Long menu;

	Create(&addressBook, 60000);
	DisplayMenu(); rewind(stdin);  scanf("%d", &menu);
	while (menu != 0)
	{
		switch (menu)
		{
		case 1:FormForRecording(&addressBook); break;
        case 2:FormForFinding(&addressBook); break;
		case 3:FormForCorrecting(&addressBook); break;
		case 4:FormForErasing(&addressBook); break;
		case 5:FormForArranging(&addressBook); break;
		case 6:FormForViewAll(&addressBook); break;
		default:break;
		}
		DisplayMenu(); rewind(stdin); scanf("%d", &menu);
	}
	Destroy(&addressBook);
	return 0;
}
*/

/*
함수이름 : Create
기    능 : 할당량을 입력받아 할당량만큼 사람들을 준비한다.
입    력 : 할당량
출    력 : 없음
*/

void Create(AddressBook *addressBook, Long capacity)
{
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}


/*
함수이름 : Record
기    능 : 주소록에 개인을 저장한다.
입    력 : 이름, 주소, 전화번호, 이메일주소
출    력 : 첨자
*/

Long Record(AddressBook *addressBook, char(*name), char(*address), char(*telephoneNumber), char(*emailAddress))
{
	Long i = 0;
	Long j = 0;
	Long index;
	Personal(*temp);
	
	while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0)
	{
		i++;
	}
	if (i >= addressBook->capacity)
	{
		temp = (Personal(*))calloc(addressBook->capacity + 1, sizeof(Personal));
		while (j < addressBook->length)
		{
			temp[j] = addressBook->personals[j];
			j++;
		}
		if (addressBook->personals != NULL)
		{
			free(addressBook->personals);

		}
		addressBook->personals = temp;
		(addressBook->capacity)++;
	}
	index = i;
	strcpy(addressBook->personals[index].name, name);
	strcpy(addressBook->personals[index].address,address);
	strcpy(addressBook->personals[index].telephoneNumber,telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress,emailAddress);
	(addressBook->length)++;
	
	return index;
}


/*
함수이름 : Find
기    능 : 입력받은 이름과 같은 이름을 찾고 찾은 줄의 위치들과 찾은 줄의 개수를 찾는다.
입    력 : 이름
출    력 : 줄의 위치들, 줄의 개수
*/

void Find(AddressBook *addressBook, char(*name), Long*(*indexes), Long *count)
{
	Long i = 0;
	Long j = 0;
	
	*count = 0;
	if (addressBook->length > 0)
	{
		*indexes = (Long(*))calloc(addressBook->length, sizeof(Long));
	}
	while (i < addressBook->length)
	{
		if (strcmp(addressBook->personals[i].name, name) == 0)
		{
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}


/*
함수이름 : Correct
기    능 : 줄의 위치, 주소, 전화번호, 이메일주소를 입력받아 줄의 위치의 주소록을 수정한다.
입    력 : 줄의 위치, 주소, 전화번호, 이메일
출    력 : 줄의 위치
*/

Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);

	return index;
}


/*
함수이름 : Erase
기    능 : 줄의 위치를 입력받아 해당 줄의 정보를 지운다.
입    력 : 줄의 위치
출    력 : 줄의 위치
*/

Long Erase(AddressBook *addressBook, Long index)
{
	Long i = 0;
	Long j = 0;
	Personal(*temp);

	if (addressBook->capacity > 1)
	{
		temp = (Personal(*))calloc(addressBook->capacity -1, sizeof(Personal));
	}
	while (j > index)
	{
		temp[i] = addressBook->personals[j];
		i++;
		j++;
	}
	j++;
	while (j < addressBook->length)
	{
		temp[i] = addressBook->personals[j];
		i++;
		j++;
	}
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
	if (addressBook->capacity > 1)
	{
		addressBook->personals = temp;
	}
	(addressBook->length)--;
	(addressBook->capacity)--;
	index = -1;

	return index;
}

/*
함수이름 : Arrange
기    능 : 주소록의 개인들을 오름차순으로 정렬한다. 단 지워진 주소는 뒤에 배치한다.
입    력 : 없음
출    력 : 없음
*/

void Arrange(AddressBook *addressBook)
{
	Long i = 1;
	Long j;
	Personal temp;
	
	while (i < addressBook->length)
	{
		j = i - 1;
		temp = addressBook->personals[i];
		while (j >= 0 && strcmp(temp.name, addressBook->personals[j].name) < 0)
		{
			addressBook->personals[j + 1] = addressBook->personals[j];
			j--;
		}
		addressBook->personals[j + 1] = temp;
		i++;
	}
}

/*
함수이름 : Destroy
기    능 : 개인들을 할당해제한다.
입    력 : 없음
출    력 : 없음
*/

void Destroy(AddressBook *addressBook)
{
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
}

