//AddressBook.c
/*
�����̸� : AddressBook.c
��    �� : �̸�, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �����Ͽ� �ּҷ��� ����� ã��, ��ġ��, �����, �����ϱ��� ����� �����Ѵ�.
�� �� �� : �̺���
�ۼ����� : 2017�� 6�� 12��
*/

//��ũ�� ����
#include "AddressBook.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stdafx.h"
#pragma warning (disable : 4996)

//�Լ� ����
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
�Լ��̸� : Create
��    �� : �Ҵ緮�� �Է¹޾� �Ҵ緮��ŭ ������� �غ��Ѵ�.
��    �� : �Ҵ緮
��    �� : ����
*/

void Create(AddressBook *addressBook, Long capacity)
{
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}


/*
�Լ��̸� : Record
��    �� : �ּҷϿ� ������ �����Ѵ�.
��    �� : �̸�, �ּ�, ��ȭ��ȣ, �̸����ּ�
��    �� : ÷��
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
�Լ��̸� : Find
��    �� : �Է¹��� �̸��� ���� �̸��� ã�� ã�� ���� ��ġ��� ã�� ���� ������ ã�´�.
��    �� : �̸�
��    �� : ���� ��ġ��, ���� ����
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
�Լ��̸� : Correct
��    �� : ���� ��ġ, �ּ�, ��ȭ��ȣ, �̸����ּҸ� �Է¹޾� ���� ��ġ�� �ּҷ��� �����Ѵ�.
��    �� : ���� ��ġ, �ּ�, ��ȭ��ȣ, �̸���
��    �� : ���� ��ġ
*/

Long Correct(AddressBook *addressBook, Long index, char(*address), char(*telephoneNumber), char(*emailAddress))
{
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].telephoneNumber, telephoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);

	return index;
}


/*
�Լ��̸� : Erase
��    �� : ���� ��ġ�� �Է¹޾� �ش� ���� ������ �����.
��    �� : ���� ��ġ
��    �� : ���� ��ġ
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
�Լ��̸� : Arrange
��    �� : �ּҷ��� ���ε��� ������������ �����Ѵ�. �� ������ �ּҴ� �ڿ� ��ġ�Ѵ�.
��    �� : ����
��    �� : ����
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
�Լ��̸� : Destroy
��    �� : ���ε��� �Ҵ������Ѵ�.
��    �� : ����
��    �� : ����
*/

void Destroy(AddressBook *addressBook)
{
	if (addressBook->personals != NULL)
	{
		free(addressBook->personals);
	}
}

