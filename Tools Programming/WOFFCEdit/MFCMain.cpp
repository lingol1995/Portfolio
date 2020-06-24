#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT, &MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_WINDOWS_TOOLS, &MFCMain::MenuWindowsTools)
	ON_COMMAND(ID_BUTTON40001, &MFCMain::SavingButton)					//Saving button
	ON_COMMAND(ID_BUTTON40007, &MFCMain::WireframeButton)				//Wireframe button
	ON_COMMAND(ID_BUTTON40008, &MFCMain::CameraDragButton)				//Camera dragging button
	ON_COMMAND(ID_BUTTON40009, &MFCMain::CreateObjectButton)			//Creating object button
	ON_COMMAND(ID_BUTTON40010, &MFCMain::TransformToolButton)			//Transform object button
	ON_COMMAND(ID_BUTTON40011, &MFCMain::WireframeOffButton)			//Transform object button
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//get the rect from the MFC window so we can get its dimensions
//	m_toolHandle = Frame->GetSafeHwnd();							//handle of main window
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetWindowRect(&WindowRECT);
	m_width = WindowRECT.Width();
	m_height = WindowRECT.Height();

	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();
	
	m_ToolSystem.onActionInitialise(m_toolHandle, 800, 600);
	
	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			int ID = m_ToolSystem.getCurrentSelectionID();
			std::wstring statusString = L"Selected Object: " + std::to_wstring(ID);
			m_ToolSystem.Tick(&msg);

			//send current object ID to status bar in The main frame
			m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);	
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::MenuWindowsTools()
{
	m_ToolsDialogue.Create(IDD_DIALOG2);	//Start up modeless - Inspector dialog
	m_ToolsDialogue.ShowWindow(SW_SHOW);	//show modeless

}

void MFCMain::SavingButton()
{
	m_ToolSystem.onActionSave();			//Saving Scene
}

void MFCMain::WireframeButton()
{
	m_ToolSystem.wire = true;				//Set it to true on button press
	
}

void MFCMain::WireframeOffButton()
{
	m_ToolSystem.wire = false;			//Set it to false on button press
}

void MFCMain::CameraDragButton()
{
	if (m_ToolSystem.cameraMove == false)	//If camera moving button hasn't been pressed before
		m_ToolSystem.cameraMove = true;		//Enable mouse drag camera
}

void MFCMain::CreateObjectButton()
{
	m_ToolSystem.onActionCreate();			//Create Object on button press
}

void MFCMain::TransformToolButton()
{
	//Set and Update the selected object's position, rotation, scale, texture, name and mesh on press of button
	update = true;							
	m_ToolSystem.moveSelected(m_ToolsDialogue.translateX, m_ToolsDialogue.translateY, m_ToolsDialogue.translateZ,	//Translating
		m_ToolsDialogue.rotateX, m_ToolsDialogue.rotateY, m_ToolsDialogue.rotateZ);

	m_ToolSystem.scaleSelected(m_ToolsDialogue.scaleX, m_ToolsDialogue.scaleY, m_ToolsDialogue.scaleZ);				//Scaling
	
	m_ToolSystem.changeTexture(m_ToolsDialogue.name, m_ToolsDialogue.texture_name, m_ToolsDialogue.mesh_name);		//Attribute editing
}

MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
