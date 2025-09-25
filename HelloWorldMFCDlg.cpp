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
	wchar_t folderPath[MAX_PATH] = L"";
	GetDlgItemText(IDC_TEXT_path, folderPath, MAX_PATH);

	if (wcslen(folderPath) == 0) {
		MessageBox(L"Please choose a folder first!", L"⚠️ Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	wchar_t content[4096] = L"";
	GetDlgItemText(IDC_EDIT_editbox, content, 4096);

	if (wcslen(content) == 0) {
		MessageBox(L"Please enter some text before saving.", L"⚠️ Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	wchar_t szFile[MAX_PATH] = L""; // khởi tạo mảng rỗng để đọc tên file 
	OPENFILENAME ofn = { sizeof(ofn) }; // Khởi tạo biến ofn – struct chứa cấu hình cho hộp thoại "Save As".
	//	Cú pháp{ sizeof(ofn) } giúp gán trước kích thước của struct (thay vì dùng ZeroMemory).
	ofn.lStructSize = sizeof(ofn); // kích thước của struct đúng 
	ofn.hwndOwner = m_hWnd; //gán cửa sổ chính làm cửa sổ cha
	ofn.lpstrFile = szFile; // cho biết địa chỉ bộ nhớ - nơi sẽ lưu đường dẫn file 
	ofn.nMaxFile = MAX_PATH; // đặt kích thước tối đa là 260 kí tụ 
	ofn.lpstrInitialDir = folderPath; // gán thư mục mở đầu là thư mục đã chọn
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files\0*.*\0"; // bộ lọc hiển thị các kiểu file
	ofn.lpstrDefExt = L"txt"; // tự động set file là đuôi .txt lưu text document
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT; // kiểm tra thư mục có thật chưa và ghi đè file nếu đã có

	if (!GetSaveFileName(&ofn)) return; // bấm save nếu bấm cancel hoặc lỗi sẽ tắt hộp thoại 

	wchar_t fileName[MAX_PATH];
	wcscpy_s(fileName, ofn.lpstrFile);// copy tên file đã chọn
	//- ofn.lpstrFile là chuỗi con trỏ (`wchar_t*`) tạm thời
	// copy nó vào `fileName` là biến ổn định đã đặt, dùng tiếp được nhiều lần

	// Kiểm tra quyền ghi - readonly
	DWORD attr = GetFileAttributes(fileName);
	if (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_READONLY)) {
		/*	INVALID_FILE_ATTRIBUTES → File không tồn tại, trả về `0xFFFFFFFF`
			(attr & FILE_ATTRIBUTE_READONLY) → Kiểm tra xem file có cờ "chỉ đọc" hay không*/
		MessageBox(L"The file is read-only.", L"❌ Error", MB_OK | MB_ICONERROR);
		return;
	}

	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// mở hoặc tạo file với tên filename để cho hàm writefile 
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(L"Unable to create file.", L"❌ Error", MB_OK | MB_ICONERROR);
		return;
	}

	DWORD dwWritten = 0; // khai báo dữ liệu để ghi 
	DWORD dwToWrite = (DWORD)(wcslen(content) * sizeof(wchar_t)); // số byte cần ghi 
	// Phải nhân với sizeof(wchar_t) vì WriteFile ghi theo byte, không phải theo ký tự ; wchar_t = 2 byte
	//wcslen(content) : độ dài ký tự ( không tính '\0' )
	if (!WriteFile(hFile, content, dwToWrite, &dwWritten, NULL)) {
		MessageBox(L"Error writing to file.", L"❌ Error", MB_OK | MB_ICONERROR);
		CloseHandle(hFile);
		return;
	}
	CloseHandle(hFile);
	MessageBox(L"File saved successfully!", L"✅ Done", MB_OK | MB_ICONINFORMATION);
}

void CHelloWorldMFCDlg::OnBnClickedButton_load()
{
	wchar_t folderPath[MAX_PATH] = L"";
	GetDlgItemText(IDC_TEXT_path, folderPath, MAX_PATH);

	if (wcslen(folderPath) == 0) {
		MessageBox(L"Please choose a folder first!", L"⚠️ Warning", MB_OK | MB_ICONWARNING);
		return;
	}

	wchar_t szFile[MAX_PATH] = L""; // khởi tạo mảng rỗng chuỗi unicode để đọc tên file - Max_Path là 260 kí tự
	OPENFILENAME ofn;// OPENFILENAME là struct chưa cấu hình cho hộp thoại mở file
	ZeroMemory(&ofn, sizeof(ofn)); // giải phóng toàn bộ nếu có dữ liệu cũ
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd; // đặt là hiển thị ở cửa sổ chính
	ofn.lpstrFile = szFile; // gán con trỏ đến mảng szfile - nơi sẽ lưu đường dẫn file đã chọn( tên file)
	ofn.nMaxFile = MAX_PATH;// đặt độ dài tối da cho tên file là 260 kí tự
	ofn.lpstrInitialDir = folderPath; // đặt thư mục mặc mở ra là folder đã chọn
	ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files\0*.*\0"; // bộ lọc hiển thị các kiểu file sẽ lưu
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	// Các tùy chọn hộp thoại : 
	// OFN_PATHMUSTEXIST: thư mục chọn phải tồn tại
	//OFN_FILEMUSTEXIST: chỉ chọn được file có thật(không nhập linh tinh)

	if (!GetOpenFileName(&ofn)) {
		MessageBox(L"User cancelled or error in open file dialog", L"Info", MB_OK);
		return;
	}
	HANDLE hFile = CreateFile(
		ofn.lpstrFile,           // Tên file vừa chọn
		GENERIC_READ,            // Mở để đọc
		0,                       // Không chia sẻ file
		NULL,                    // Không bảo mật đặc biệt
		OPEN_EXISTING,           // File phải tồn tại sẵn
		FILE_ATTRIBUTE_NORMAL,   // File thường
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) { // nếu mở file lỗi thì có thông báo lỗi
		MessageBox(L"Failed to open file.", L"❌ Error", MB_OK | MB_ICONERROR);
		return;
	}

	wchar_t buffer[4096] = { 0 };
	DWORD dwRead = 0;
	if (!ReadFile(hFile, buffer, sizeof(buffer) - sizeof(wchar_t), &dwRead, NULL)) {
		//sizeof(buffer) - sizeof(wchar_t) ?
		//	buffer là mảng wchar_t, kích thước mỗi phần tử là 2 byte(trên Windows).
		//	sizeof(buffer) = 4096 bytes tổng bộ nhớ.
		//	Nhưng ta trừ đi 1 wchar(2 byte) để chừa chỗ thêm ký tự kết thúc chuỗi L'\0' sau khi đọc xong.
		MessageBox(L"Error reading file.", L"❌ Error", MB_OK | MB_ICONERROR);
		CloseHandle(hFile);
		return;
	}

	buffer[dwRead / sizeof(wchar_t)] = L'\0';  // chuyển byte đã đọc thành kí tự 

	CloseHandle(hFile);
	SetDlgItemText(IDC_EDIT_editbox, buffer); // hiển thị nội dung đã đọc vào edit box
	MessageBox(L"File loaded successfully!", L"✅ Done", MB_OK | MB_ICONINFORMATION);
}

void CHelloWorldMFCDlg::OnEnChangeEdit_editbox()
{
}
void CHelloWorldMFCDlg::OnEnChangeEdit_textpath()
{
}