
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

//class CAboutDlg : public CDialogEx
//{
//public:
//	CAboutDlg();
//
//// Dialog Data
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_ABOUTBOX };
//#endif
//
//	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//
//// Implementation
//protected:
//	DECLARE_MESSAGE_MAP()
//};
//
//CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
//{
//}
//
//void CAboutDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialogEx::DoDataExchange(pDX);
//}
//
//BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//END_MESSAGE_MAP()


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
	DDX_Control(pDX, IDC_EDIT_editbox, edit_box);
	DDX_Control(pDX, IDC_TEXT_path, text_path);
}

BEGIN_MESSAGE_MAP(CHelloWorldMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_save, &CHelloWorldMFCDlg::OnBnClickedButton_save)
	ON_BN_CLICKED(IDC_BUTTON_load, &CHelloWorldMFCDlg::OnBnClickedButton_load)
	ON_BN_CLICKED(IDC_BUTTON_choose, &CHelloWorldMFCDlg::OnBnClickedButton_choose)
END_MESSAGE_MAP()

// CHelloWorldMFCDlg message handlers

BOOL CHelloWorldMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	//// IDM_ABOUTBOX must be in the system command range.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != nullptr)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//void CHelloWorldMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
//{
//	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
//	{
//		CAboutDlg dlgAbout;
//		dlgAbout.DoModal();
//	}
//	else
//	{
//		CDialogEx::OnSysCommand(nID, lParam);
//	}
//}
//
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
  //the minimized window.
HCURSOR CHelloWorldMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ---------------------------------- BUtton -----------------------------

void CHelloWorldMFCDlg::OnBnClickedButton_choose()
{
	// Khởi tạo bắt buộc
	BROWSEINFO bi;  // bi như là tên 1 hộp chứa thông tin hộp thoại chọn thư mục 
	ZeroMemory(&bi, sizeof(bi));   // Lệnh này để reset kiểu giải phóng nếu có dữ liệu cũ
	bi.hwndOwner = m_hWnd; // m_hWnd là cửa sổ chính của chương trình.
	LPITEMIDLIST pIdl = SHBrowseForFolder(&bi);   // SHBrowseForFolder là hàm mở hộp thoại chọn thư mục
	// pIdl gọi như là nơi ghi địa chỉ của thư mục đã chọn 
	if (pIdl != NULL)
	{
		wchar_t szPath[_MAX_PATH];
		szPath[0] = L'\0'; // Đặt ký tự đầu tiên = \0 nghĩa là xóa sạch nội dung cũ trước khi ghi cái khác vào 
		if (SHGetPathFromIDList(pIdl, szPath)) // SHGetPath... là lấy đường dẫn từ pIdl cho xuất vào szPath
		{
			text_path.SetWindowTextW(szPath); // Hiển thị trên text_box của UI
		}
	}
}

void CHelloWorldMFCDlg::OnBnClickedButton_save()
{
	// Khai báo kiểm tra các mục đã được chọn chưa 
	wchar_t folderPath[MAX_PATH];
	GetDlgItemText(IDC_TEXT_path, folderPath, MAX_PATH); // lấy đường dẫn thư mục vừa chọn bên trên gán vào folderPath

	if (wcslen(folderPath) == 0) // wcslen tính độ dài chuỗi wchar_t
	{
		MessageBox(L"Please choose a folder first", L" ⚠️ Warning!!!", MB_OK);
		return;
	}

	wchar_t content[4096];
	GetDlgItemText(IDC_EDIT_editbox, content, 4096); // lấy nội dung đã nhập trong edit box gán vào content 

	if (wcslen(content) == 0) // wcslen tính độ dài chuỗi wchar_t
	{
		MessageBox(L"Please text something", L" ⚠️ Warning!!!", MB_OK);
		return;
	}

	wchar_t szFile[MAX_PATH] = L""; // Tạo một mảng wchar_t để lưu tên file - mảng rỗng
	OPENFILENAME ofn;  // cấu trúc khởi tạo cấu hình save/open files 
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn); // khởi tạo kích thước là ofn để đọc đúng dữ liệu
	ofn.hwndOwner = m_hWnd; // set là hiển thị ở cửa sổ chính
	ofn.lpstrFile = szFile;  // hiển thị hộp thoại để tự đặt tên file lưu vào folder
	ofn.nMaxFile = MAX_PATH; // đặt kích thước cho tên file là tối đa để không bị vượt quá 
	ofn.lpstrInitialDir = folderPath;  // mở thư mục đã chọn 
	ofn.lpstrFilter = L"Text Documents\0*.txt\0All Files\0*.*\0"; // chỉ hiển thị txt hoặc all files
	ofn.nFilterIndex = 1;
	ofn.lpstrDefExt = L"txt";  // tự động thêm .txt cho file
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT; // OFN_OVERWRITEPROMPT là nếu file trùng tên, hỏi có muốn ghi đè không.

	if (GetSaveFileName(&ofn)) // bắt đầu hiển thị hộp thoại lưu file
	{
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, NULL, // tạo file gồm : đặt tên file; cho phép ghi write 
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		// create_always là luôn tạo file mới nếu có tên tồn tại thì ghi đè 
		if (hFile != INVALID_HANDLE_VALUE)  // kiểm tra xem đã thành công chưa 
		{
			DWORD dwWritten; // khai báo viết vào file
			WriteFile(hFile, content, (DWORD)(wcslen(content) * sizeof(wchar_t)), &dwWritten, NULL); // ghi vào file từ kích thước của content
			CloseHandle(hFile);
			MessageBox(L"Save file successfully!", L" ⚠️ Warning!!!", MB_OK);
		}
	}
}

void CHelloWorldMFCDlg::OnBnClickedButton_load()
{
	wchar_t folderPath[MAX_PATH];
	GetDlgItemText(IDC_TEXT_path, folderPath, MAX_PATH); // lấy đường dẫn 

	if (wcslen(folderPath) == 0) // wcslen là hàm tính độ dài chuỗi wchar_t
	{
		MessageBox(L"Please choose a folder first!", L" ⚠️ Warninggg !!!", MB_OK);
		return;
	}

	wchar_t szFile[MAX_PATH] = L""; // khởi tạo 1 mảng rỗng đọc tên file
	OPENFILENAME ofn; 
	ZeroMemory(&ofn, sizeof(ofn)); // giải phỏng toàn bộ nếu có dữ liệu cũ
	ofn.lStructSize = sizeof(ofn); // khởi tạo kích thước là ofn để đọc đúng dữ liệu
	ofn.hwndOwner = m_hWnd;// // set là hiển thị ở cửa sổ chính
	ofn.lpstrFile = szFile;  // hiển thị hộp thoại để tự đặt tên file lưu vào folder
	ofn.nMaxFile = MAX_PATH; // đặt kích thước cho tên file là tối đa để không bị vượt quá 
	ofn.lpstrInitialDir = folderPath;  // mở thư mục đã chọn 
	ofn.lpstrFilter = L"Text Documents\0*.txt\0All Files\0*.*\0"; // chỉ hiển thị txt hoặc all files
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // check xem file có tồn tại không 

	if (GetOpenFileName(&ofn))  // bắt đầu mở hộp thoại đã lưu file 
	{
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, //mở file vừa chọn để đọc 
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			DWORD dwRead; // khai báo biến dwRead  sẽ lưu số byte đọc được từ file 
			wchar_t detail[4096] = { 0 };// tạo mảng chứa nội dung file
			ReadFile(hFile, detail, sizeof(detail) - sizeof(wchar_t), &dwRead, NULL); // đọc dữ liệu từ file vào detail
			detail[dwRead / sizeof(wchar_t)] = L'\0'; // chuyển byte đã đọc thành kí tự 
			CloseHandle(hFile);

			SetDlgItemText(IDC_EDIT_editbox, detail); // hiển thị nội dung đã đọc vào edit box
			MessageBox(L"Load file successfully!", L" ⚠️ Warningg!!!", MB_OK);
		}
	}
}

void CHelloWorldMFCDlg::OnEnChangeEdit_editbox()
{
	 //TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
void CHelloWorldMFCDlg::OnEnChangeEdit_textpath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
// thu nha demo hihih 