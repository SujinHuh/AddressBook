//FindingForm.h
/*
파일이름 : FindingForm.c
기    능 : GUI 주소록 FindingForm 헤더파일
작 성 자 : 이병도
작성일자 : 2017년 6월 22일
*/
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H

#include <windows.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);


#endif // _FINDINGFORM_H