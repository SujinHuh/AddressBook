//UpdatingForm.h
/*
파일이름 : UpdatingForm.c
기    능 : 주소록 GUI 헤더파일
작 성 자 : 이병도
작성일자 : 2017년 6월 21일
*/
#ifndef _UPDATINGFORM_H
#define _UPDATINGFORM_H

#include<windows.h>

BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL UpdatingForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL UpdatingForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);

BOOL UpdatingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);


#endif // _UPDATINGFORM_H