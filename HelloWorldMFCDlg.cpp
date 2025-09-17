
// HelloWorldMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "HelloWorldMFC.h"
#include "HelloWorldMFCDlg.h"
#include "afxdialogex.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHelloWorldMFCDlg dialog



CHelloWorldMFCDlg::CHelloWorldMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HELLOWORLDMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHelloWorldMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_save, btn_save);
	DDX_Control(pDX, IDC_BUTTON_load, btn_load);
	DDX_Control(pDX, IDC_BUTTON_choose, btn_choose);
	DDX_Control(pDX, IDC_EDIT_path, edit_path);
	DDX_Control(pDX, IDC_EDIT_editbox, edit_box);
	DDX_Control(pDX, IDC_STATIC_url, static_url);
}

BEGIN_MESSAGE_MAP(CHelloWorldMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_save, &CHelloWorldMFCDlg::OnBnClickedButton_save)
	ON_BN_CLICKED(IDC_BUTTON_load, &CHelloWorldMFCDlg::OnBnClickedButton_load)
	ON_BN_CLICKED(IDC_BUTTON_choose, &CHelloWorldMFCDlg::OnBnClickedButton_choose)
	ON_EN_CHANGE(IDC_EDIT_editbox, &CHelloWorldMFCDlg::OnEnChangeEdit_editbox)
	ON_EN_CHANGE(IDC_EDIT_path, &CHelloWorldMFCDlg::OnEnChangeEdit_path)
END_MESSAGE_MAP()


// CHelloWorldMFCDlg message handlers

BOOL CHelloWorldMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHelloWorldMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHelloWorldMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHelloWorldMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHelloWorldMFCDlg::OnBnClickedButton_choose()
{
	// TODO: Add your control notification handler code here

	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	TCHAR szDisplayname[_MAX_PATH];
	szDisplayname[0] = '\0';
	bi.hwndOwner = m_hWnd;
	bi.pszDisplayName = szDisplayname;
	bi.lpszTitle = _T("Please select a folder to save the file:");

	LPITEMIDLIST pIdl = SHBrowseForFolder(&bi);
	if (pIdl != NULL)
	{
		TCHAR szPath[_MAX_PATH];
		szPath[0] = '\0';
		if (SHGetPathFromIDList(pIdl, szPath))
		{
			edit_path.SetWindowTextW(szPath);
		}
		LPMALLOC pMalloc = NULL;
		if (SUCCEEDED(SHGetMalloc(&pMalloc)))
		{
			pMalloc->Free(pIdl);
			pMalloc->Release();
		}
	}
}

void CHelloWorldMFCDlg::OnBnClickedButton_save()
{
	// TODO: Add your control notification handler code here
	TCHAR folderPath[_MAX_PATH];
	GetWindowText(HWND)


	
	CString editbox;
	edit_box.GetWindowTextW(editbox);
	if (path.IsEmpty()) {
		AfxMessageBox(_T("Please choose a path first!"));
		return;
	}  
	if (editbox.IsEmpty()) {
		AfxMessageBox(_T(" please text something"));
		return;
	}

	AfxMessageBox(_T("File saved successfully!"));

}
void CHelloWorldMFCDlg::OnBnClickedButton_load()
{
	// TODO: Add your control notification handler code here
	
}



void CHelloWorldMFCDlg::OnEnChangeEdit_editbox()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CHelloWorldMFCDlg::OnEnChangeEdit_path()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
