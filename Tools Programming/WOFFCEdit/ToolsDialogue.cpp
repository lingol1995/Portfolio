#include "ToolsDialogue.h"
#include "stdafx.h"
#include <iostream>

//OWN CODE
// SelectDialogue dialog

IMPLEMENT_DYNAMIC(ToolsDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a method.
BEGIN_MESSAGE_MAP(ToolsDialogue, CDialogEx)
ON_COMMAND(IDOK, &ToolsDialogue::End)							//Cancel button
ON_BN_CLICKED(IDOK, &ToolsDialogue::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON1, &ToolsDialogue::OnBnClickedButton1)	//Set button
END_MESSAGE_MAP()

ToolsDialogue::ToolsDialogue()
{
	translateX = 0.0f;									//For moving selected object
	translateY = 0.0f;
	translateZ = 0.0f;

	rotateX = 0.0f;										//For rotating selecting object
	rotateY = 0.0f;
	rotateZ = 0.0f;

	scaleX = 1.0f;										//For scaling selected object
	scaleY = 1.0f;
	scaleZ = 1.0f;

	name = "Object";									//For setting name of object
	texture_name = "database/data/placeholder.dds";		//For setting texture of object
	mesh_name = "database/data/placeholder.cmo";		//For setting mesh of an object
}

ToolsDialogue::ToolsDialogue(CWnd* pParent) 
: CDialogEx(IDD_DIALOG2, pParent)
{

}

ToolsDialogue::~ToolsDialogue()
{

}

void ToolsDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BOOL ToolsDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void ToolsDialogue::End()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}


void ToolsDialogue::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

//SETTING THE POSITION, SCALE, ROTATION, NAME, TEXTURE FROM FIELDS
void ToolsDialogue::OnBnClickedButton1()
{
	update = true;

	CWnd* pWnd;
	
	CString edit_translateX, edit_translateY, edit_translateZ,
		edit_RotateX, edit_RotateY, edit_RotateZ,
		edit_ScaleX, edit_ScaleY, edit_ScaleZ,
		edit_texture, edit_mesh;


	pWnd = GetDlgItem(IDC_EDIT1);							//Get data from first edit control
	pWnd->GetWindowText(edit_translateX);					//Keep in Cstring
	swscanf_s(edit_translateX, L"%f", &translateX);			//Convert to proper string
	

	pWnd = GetDlgItem(IDC_EDIT2);							//Get Data from second edit control
	pWnd->GetWindowText(edit_translateY);
	swscanf_s(edit_translateY, L"%f", &translateY);			//Convert

	pWnd = GetDlgItem(IDC_EDIT3);						
	pWnd->GetWindowText(edit_translateZ);					//Data from third 
	swscanf_s(edit_translateZ, L"%f", &translateZ);			//Convert

	pWnd = GetDlgItem(IDC_EDIT5);			
	pWnd->GetWindowText(edit_RotateX);						//Get Data
	swscanf_s(edit_RotateX, L"%f", &rotateX);				//Convert

	pWnd = GetDlgItem(IDC_EDIT6);							//Get Data
	pWnd->GetWindowText(edit_RotateY);
	swscanf_s(edit_RotateY, L"%f", &rotateY);				//Convert

	pWnd = GetDlgItem(IDC_EDIT7);
	pWnd->GetWindowText(edit_RotateZ);
	swscanf_s(edit_RotateZ, L"%f", &rotateZ);

	pWnd = GetDlgItem(IDC_EDIT8);
	pWnd->GetWindowText(edit_ScaleX);
	swscanf_s(edit_ScaleX, L"%f", &scaleX);

	pWnd = GetDlgItem(IDC_EDIT9);
	pWnd->GetWindowText(edit_ScaleY);
	swscanf_s(edit_ScaleY, L"%f", &scaleY);

	pWnd = GetDlgItem(IDC_EDIT10);
	pWnd->GetWindowText(edit_ScaleZ);
	swscanf_s(edit_ScaleZ, L"%f", &scaleZ);

	std::string s;

	pWnd = GetDlgItem(IDC_EDIT4);				
	pWnd->GetWindowText(edit_name);						//Get name from field
	
	CT2CA pszConvertedAnsiString(edit_name);				//Convert to LPQSTR
	std::string strStd(pszConvertedAnsiString);				//Create string from this 
	name = strStd;											//Set name
		
	pWnd = GetDlgItem(IDC_EDIT11);							//Get Texture from field
	pWnd->GetWindowText(edit_texture);			
	CT2CA pszConvertedAnsiString1(edit_texture);			//Convert to LPQSTR
	std::string strStd1(pszConvertedAnsiString1);			//Create string
	texture_name = strStd1;									//Set Texture destination text

	if (texture_name == "")									//If there is nothing entered
	{
		texture_name = "database/data/placeholder.dds";		//Set to default text
	}

	pWnd = GetDlgItem(IDC_EDIT12);							//Get from field (mesh)
	pWnd->GetWindowText(edit_mesh);						
	CT2CA pszConvertedAnsiString3(edit_mesh);				//Convert to LPCSTR
	std::string strStd3(pszConvertedAnsiString3);			//Make string from this

	mesh_name = strStd3;									//Set this as mesh string
	if (mesh_name == "")									//If nothing is entered
	{
		mesh_name = "database/data/placeholder.cmo";		//Set default
	}
	
}

