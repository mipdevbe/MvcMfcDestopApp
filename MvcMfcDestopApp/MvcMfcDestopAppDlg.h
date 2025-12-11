
// MvcMfcDestopAppDlg.h : header file
//

#pragma once
#include <memory>
#include ".\View\IView.h"
#include ".\Model\IModel.h"


// CMvcMfcDestopAppDlg dialog
class CMvcMfcDestopAppDlg : public CDialogEx, public IView
{
	CListBox _lstCompanies;
	CListBox _lstEmployees;

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
	afx_msg void OnSelchangeLstCategories();
	DECLARE_MESSAGE_MAP()



	// IView interface
public:
	void CreateView() override; 
	void LoadView() override;
	void UpdateView(const std::vector<std::unique_ptr<IModel>>& data) override; // Pure virtual method
	void CloseView() override; // Pure virtual method


	afx_msg void OnBnClickedSearch();
	CEdit _searchCriteria;
	afx_msg void OnBnClickedDeleteEntry();
};
