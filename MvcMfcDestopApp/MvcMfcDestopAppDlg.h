
// MvcMfcDestopAppDlg.h : header file
//

#pragma once
#include <memory>
#include ".\View\IView.h"

// CMvcMfcDestopAppDlg dialog
class CMvcMfcDestopAppDlg : public CDialogEx, public IView
{
// Construction
public:
	CMvcMfcDestopAppDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MVCMFCDESTOPAPP_DIALOG };
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


	// IView interface
public:
	void CreateView(); // Pure virtual method
	void LoadView(); // Pure virtual method
	void UpdateView(); // Pure virtual method
	void CloseView(); // Pure virtual method
};
