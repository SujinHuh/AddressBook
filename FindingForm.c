//FindingForm.c
/*
파일이름 : FindingForm.c
기    능 : GUI 주소록 FindingForm c파일
작 성 자 : 이병도
작성일자 : 2017년 6월 22일
*/
#include "stdafx.h"
#include "UpdatingForm.h"
#include "FindingForm.h"
#include "resource.h"
#include "AddressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <Commctrl.h>
#include <Windows.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG:
		ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND:
		ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY:
		ret = FindingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE:
		ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	LVCOLUMN column = { 0, };

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


BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND:
		ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}


BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	AddressBook *addressBook;
	Long index=0;
	TCHAR name[NAME];
	Long(*indexes);
	Long count;
	TCHAR number[64];
	HWND hUpdatingForm;
	LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED)
	{
		//2.1 성명을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)NAME, (LPARAM)name);

		//2.2 주소록 윈도우를 찾는다.
		hUpdatingForm=FindWindow("#32770", "주소록");

		//2.3 주소록 윈도우에서 주소록을 찾는다.
		addressBook = (AddressBook(*))GetWindowLong(hUpdatingForm, GWL_USERDATA);

		//2.4 주소록에서 개인을 찾는다.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL)
		{
			free(indexes);
			indexes = NULL;
		}
		Find(addressBook, name, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (Long)indexes);

		//2.5 리스트 뷰의 모든 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//2.6 리스트에서 찾은 개인들을 추가한다.
		item.mask = LVIF_TEXT;
		while (index < count)
		{
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



BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;
	switch (wParam) {
	case IDC_LIST_PERSONALS:
		ret = FindingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default:ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long index;
	TCHAR name[NAME];
	TCHAR address[ADDRESS];
	TCHAR telephoneNumber[TELEPHONENUMBER];
	TCHAR emailAddress[EMAILADDRESS];
	Long(*indexes);
	HWND hUpdatingForm;

	LVITEM item = { 0, };
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		//.1 리스트뷰에서 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//.2 리스트뷰에서 해당 항목을 읽는다.
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
		
		//.3 주소록 윈도우를 찾는다.
		hUpdatingForm = FindWindow("#32770", "주소록");


		//.4 주소록 윈도우의 개인에 해당 항목을 적는다.
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)emailAddress);

		//.5 주소록 윈도우의 리스트뷰에 해당 위치를 마크한다.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(hUpdatingForm, IDC_LIST_PERSONALS), LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM)indexes[index]);
		if (indexes != NULL)
		{
			free(indexes);
			indexes = NULL;
		}

		//.6 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}
	return FALSE;
}

BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	Long(*indexes);

	//8.1 윈도우를 닫는다.
	indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL)
	{
		free(indexes);
	}
	EndDialog(hWnd, 0);

	return FALSE;
}