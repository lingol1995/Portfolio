#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "InputCommands.h"
#include "Inspector.h"
#include "ToolMain.h"
#include <iostream>

class ToolsDialogue :
	public CDialogEx
{
	DECLARE_DYNAMIC(ToolsDialogue);
public:
	ToolsDialogue();
	ToolsDialogue(CWnd* pParent);   // modal // takes in out scenegraph in the constructor
	
	virtual ~ToolsDialogue();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void WireframeMode();
	afx_msg void End();		//kill the dialogue

	InputCommands m_input;
	virtual BOOL OnInitDialog() override;

	int number;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	
	float translateX, translateY, translateZ, rotateX, rotateY, rotateZ,
		scaleX, scaleY, scaleZ;
	ToolMain tool_main;
	int sumand1;
	bool update;
	std::string name, texture_name, mesh_name;
	Inspector inspectorObject;
	//afx_msg void OnEnChangeEdit4();

	CString edit_name;
};

INT_PTR CALLBACK ToolProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);

