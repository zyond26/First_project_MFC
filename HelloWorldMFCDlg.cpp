// HelloWorldMFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "HelloWorldMFC.h"
#include "HelloWorldMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

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

// ------------------ BUTTON: CHỌN THƯ MỤC ------------------

void CHelloWorldMFCDlg::OnBnClickedButton_choose()
{
    BROWSEINFO bi;
    ZeroMemory(&bi, sizeof(bi));
    bi.hwndOwner = m_hWnd;

    LPITEMIDLIST pIdl = SHBrowseForFolder(&bi);
    if (pIdl != NULL)
    {
        wchar_t szPath[_MAX_PATH] = L"";
        if (SHGetPathFromIDList(pIdl, szPath))
        {
            // Kiểm tra đường dẫn có tồn tại và là thư mục không
            DWORD dwAttrib = GetFileAttributes(szPath);
            if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
                MessageBox(L"The selected path is not a valid folder!", L"❌ Error", MB_OK | MB_ICONERROR);
                CoTaskMemFree(pIdl); // Giải phóng bộ nhớ
                return;
            }

            text_path.SetWindowTextW(szPath);
        }

        CoTaskMemFree(pIdl); // Giải phóng bộ nhớ cấp phát bởi SHBrowseForFolder
    }
}

// ------------------ BUTTON: LƯU FILE ------------------

void CHelloWorldMFCDlg::OnBnClickedButton_save()
{
    wchar_t folderPath[MAX_PATH] = L"";
    GetDlgItemText(IDC_TEXT_path, folderPath, MAX_PATH);

    if (wcslen(folderPath) == 0) {
        MessageBox(L"Please choose a folder first!", L"⚠️ Warning", MB_OK | MB_ICONWARNING);
        return;
    }

    DWORD dwAttrib = GetFileAttributes(folderPath);
    if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        MessageBox(L"The selected folder does not exist!", L"❌ Error", MB_OK | MB_ICONERROR);
        return;
    }

    wchar_t content[4096] = L"";
    GetDlgItemText(IDC_EDIT_editbox, content, 4096);

    if (wcslen(content) == 0) {
        MessageBox(L"Please enter some text before saving.", L"⚠️ Warning", MB_OK | MB_ICONWARNING);
        return;
    }

    wchar_t szFile[MAX_PATH] = L"";
    OPENFILENAME ofn = { sizeof(ofn) };// khởi tạo struct và gán kích thước 
    ofn.lStructSize = sizeof(ofn); // gán kích thước của struct OPENFILENAME cho windows biết
    ofn.hwndOwner = m_hWnd; // gán của sổ chính cho hộp thoại ;m_hWnd được quy định là main của MFC app rồi
    ofn.lpstrFile = szFile; // chỉ định nơi lưu tên file 
    ofn.nMaxFile = MAX_PATH; // đặt số ký tự tối đã cho tên file để tránh lỗi tràn bộ nhớ 
    ofn.lpstrInitialDir = folderPath; // đặt thư mục đã chọn để mở hộp thoại
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files\0*.*\0"; // bộ lọc các kiểu file 
    ofn.lpstrDefExt = L"txt"; // tự động là file text document kiểu tự động thêm đuôi nếu mình quên
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT; // gán cờ cảnh báo thư mục phải tồn tại và cho ghi đè 

    if (!GetSaveFileName(&ofn)) return;

    wchar_t fileName[MAX_PATH];
    wcscpy_s(fileName, ofn.lpstrFile);
    //wcscpy_s() là hàm sao chép chuỗi Unicode an toàn.
    //    ofn.lpstrFile là con trỏ tạm → copy sang fileName - biến cố định để dùng tiếp cho chắc chắn.

    // Kiểm tra quyền ghi (read-only)
    DWORD attr = GetFileAttributes(fileName);
    if (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_READONLY)) {
        MessageBox(L"The file is read-only.", L"❌ Error", MB_OK | MB_ICONERROR);
        return;
    }

    HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(L"Unable to create file.", L"❌ Error", MB_OK | MB_ICONERROR);
        return;
    }

    DWORD dwWritten = 0;
    if (!WriteFile(hFile, content, (DWORD)(wcslen(content) * sizeof(wchar_t)), &dwWritten, NULL)) {
        MessageBox(L"Error writing to file.", L"❌ Error", MB_OK | MB_ICONERROR);
        CloseHandle(hFile);
        return;
    }

    CloseHandle(hFile);
    MessageBox(L"File saved successfully!", L"✅ Done", MB_OK | MB_ICONINFORMATION);
}

// ------------------ BUTTON: load file ------------------

void CHelloWorldMFCDlg::OnBnClickedButton_load()
{
    wchar_t folderPath[MAX_PATH] = L"";
    GetDlgItemText(IDC_TEXT_path, folderPath, MAX_PATH);

    if (wcslen(folderPath) == 0) {
        MessageBox(L"Please choose a folder first!", L"⚠️ Warning", MB_OK | MB_ICONWARNING);
        return;
    }

    // Kiểm tra thư mục còn tồn tại không
    DWORD dwAttrib = GetFileAttributes(folderPath);
    if (dwAttrib == INVALID_FILE_ATTRIBUTES || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        MessageBox(L"The selected folder does not exist!", L"❌ Error", MB_OK | MB_ICONERROR);
        return;
    }

    wchar_t szFile[MAX_PATH] = L"";
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hWnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrInitialDir = folderPath;
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files\0*.*\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (!GetOpenFileName(&ofn)) {
        MessageBox(L"User cancelled or error in open file dialog", L"ℹ️ Info", MB_OK);
        return;
    }

    HANDLE hFile = CreateFile(
        ofn.lpstrFile,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) {
        MessageBox(L"Failed to open file.", L"❌ Error", MB_OK | MB_ICONERROR);
        return;
    }

    wchar_t buffer[4096] = { 0 };
    DWORD dwRead = 0;
    if (!ReadFile(hFile, buffer, sizeof(buffer) - sizeof(wchar_t), &dwRead, NULL)) {
        MessageBox(L"Error reading file.", L"❌ Error", MB_OK | MB_ICONERROR);
        CloseHandle(hFile);
        return;
    }

    if (dwRead == 0) {
        MessageBox(L"File is empty or could not be read.", L"⚠️ Warning", MB_OK | MB_ICONWARNING);
        CloseHandle(hFile);
        return;
    }

    buffer[dwRead / sizeof(wchar_t)] = L'\0'; // Đảm bảo kết thúc chuỗi
    CloseHandle(hFile);
    SetDlgItemText(IDC_EDIT_editbox, buffer);
    MessageBox(L"File loaded successfully!", L"✅ Done", MB_OK | MB_ICONINFORMATION);
}


void CHelloWorldMFCDlg::OnEnChangeEdit_editbox()
{
}
void CHelloWorldMFCDlg::OnEnChangeEdit_textpath()
{
}