//UpdatingForm.c
/* 
파일이름 : UpdatingForm.c
기    능 : 주소록 GUI
작 성 자 : 이병도
작성일자 : 2017년 6월 21일
*/
#include"stdafx.h"
#include "UpdatingForm.h"
#include "FindingForm.h"
#include "resource.h"
#include "AddressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <Commctrl.h>
#pragma warning(disable : 4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_UPDATINGFORM), NULL, UpdatingFormProc);
	return response;
}

BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG:
		ret = UpdatingForm_OnInitDialog(hWnd, wParam, lParam);break;
	case WM_COMMAND:
		ret = UpdatingForm_OnCommand(hWnd, wParam, lParam);break;
	case WM_NOTIFY:
		ret = UpdatingForm_OnNotify(hWnd, wParam, lParam);break;
	case WM_CLOSE:
		ret = UpdatingForm_OnClose(hWnd, wParam, lParam);break;
	default:ret = FALSE; break;
	}
	return ret;
}

BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook *addressBook;
	LVCOLUMN column = { 0, };
	//1.1 주소록을 준비한다
	addressBook = (AddressBook(*))malloc(sizeof(AddressBook));
	Create(addressBook, 60000);
	SetWindowLong(hWnd, GWL_USERDATA, (Long)addressBook);
	//1.2 리스트뷰의 헤더를 만든다.
	//wParam = (WPARAM)(int) icol;
	//lParam = (LPARAM)(const LV_COLUMN FAR*) pcol;
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 40;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column); 
	column.cx = 70;
	column.pszText = "성명";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 200;
	column.pszText = "주소";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 200;
	column.pszText = "전화번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "이메일";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	return FALSE;
}


BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam)) {
	    case IDC_BUTTON_RECORD:
		    ret = UpdatingForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	    case IDC_BUTTON_FIND:
		    ret = UpdatingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
		case IDC_BUTTON_CORRECT:
		    ret = UpdatingForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
		case IDC_BUTTON_ERASE:
		    ret = UpdatingForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
		case IDC_BUTTON_ARRANGE:
			ret = UpdatingForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}


BOOL UpdatingForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook *addressBook;
	Long index;
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONENUMBER];
	TCHAR emailAddress[EMAILADDRESS];
	TCHAR number[64];
    LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 개인을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)ADDRESS, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)TELEPHONENUMBER, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)EMAILADDRESS, (LPARAM)emailAddress);

		//2.2 주소록에 개인을 적는다.
		addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(addressBook, name, address, telephoneNumber, emailAddress);

		//2.3 리스트뷰에 항목을 추가한다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		sprintf(number, "%d", index + 1);
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
		item.iSubItem = 1;
		item.pszText = addressBook->personals[index].name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return FALSE;
}


BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), hWnd, FindingFormProc);
	}
	return FALSE;
}


BOOL UpdatingForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook *addressBook;
	Long index;
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONENUMBER];
	TCHAR emailAddress[EMAILADDRESS];
    LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED)
	{
		//4.1 개인을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)ADDRESS, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)TELEPHONENUMBER, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)EMAILADDRESS, (LPARAM)emailAddress);

		//4.2 리스트뷰에서 선택된 항목의 위치를 읽는다.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//4.3 주소록에서 해당 개인을 고친다
		addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(addressBook, index, address, telephoneNumber, emailAddress);

		//4.4 리스트뷰에 해당 항목을 수정한다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return FALSE;
}


BOOL UpdatingForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook *addressBook;
	Long index;
	Long i;
	TCHAR number[64];
	LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED)
	{
		//5.1 리스트뷰에서 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//5.2 주소록에서 해당 개인을 지운다.
		addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = Erase(addressBook, index);

		//5.3 리스트뷰에서 해당 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);

		//5.4 리스트뷰에서 해당 항목 이후의 번호를 수정한다.
		item.mask = LVIF_TEXT;
		i = index;
		while (i < addressBook->length)
		{
			sprintf(number, "%d", i + 1);
			item.iItem = i;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			i++;
		}
	}
	return  FALSE;
}


BOOL UpdatingForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook *addressBook;
	Long index=0;
	TCHAR number[64];
    LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED)
	{
		//6.1 주소록을 정리한다.
		addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(addressBook);

		//6.2 리스트뷰의 모든 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//6.3 리스트뷰에 주소록을 추가한다.
		item.mask = LVIF_TEXT;
		while (index < addressBook->length) {
			item.iItem = index;
			item.iSubItem = 0;
			sprintf(number, "%d", index + 1);
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);
			item.iSubItem = 1;
			item.pszText = addressBook->personals[index].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 2;
			item.pszText = addressBook->personals[index].address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 3;
			item.pszText = addressBook->personals[index].telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			item.iSubItem = 4;
			item.pszText = addressBook->personals[index].emailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			index++;
		}
	}
	return FALSE;
}

BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam) {
	case IDC_LIST_PERSONALS:
		ret = UpdatingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}

BOOL UpdatingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long index;
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONENUMBER];
	TCHAR emailAddress[EMAILADDRESS];

	LVITEM item = { 0, };
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//7.1 리스트뷰에서 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//7.2 리스트뷰에서 해당 항목을 읽는다.
		item.mask = LVIF_TEXT;
		item.iSubItem = 1;
		item.cchTextMax = NAME;
		item.pszText = name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 2;
		item.cchTextMax = ADDRESS;
		item.pszText = address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 3;
		item.cchTextMax = TELEPHONENUMBER;
		item.pszText = telephoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		item.iSubItem = 4;
		item.cchTextMax = EMAILADDRESS;
		item.pszText = emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//7.3 읽은 항목을 개인에 적는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)emailAddress);
	}
	return FALSE;
}

BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook *addressBook;

	//8.1 주소록을 지운다.
	addressBook = (AddressBook(*))GetWindowLong(hWnd, GWL_USERDATA);
	if(addressBook != NULL) {
		Destroy(addressBook);
		free(addressBook);
	}

	//8.2 윈도우를 닫는다.
	EndDialog(hWnd, 0);

	return FALSE;
}
