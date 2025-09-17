
// HelloWorldMFCDlg.h : header file
//

#pragma once


// CHelloWorldMFCDlg dialog
class CHelloWorldMFCDlg : public CDialogEx
{
// Construction
public:
	CHelloWorldMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HELLOWORLDMFC_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton_load();
	afx_msg void OnBnClickedButton_save();
	afx_msg void OnBnClickedButton_choose();
	afx_msg void OnEnChangeEdit_editbox();
	afx_msg void OnEnChangeEdit_path();
protected:
	CButton btn_save;
	CButton btn_load;
	CButton btn_choose;
	CEdit edit_path;
	CEdit edit_box;
	CStatic static_url;
};
