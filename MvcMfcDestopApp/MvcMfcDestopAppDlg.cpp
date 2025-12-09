// MvcMfcDestopAppDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MvcMfcDestopApp.h"
#include "MvcMfcDestopAppDlg.h"
#include "./View/EmployeeView.h"
#include "afxdialogex.h"

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


// CMvcMfcDestopAppDlg dialog



CMvcMfcDestopAppDlg::CMvcMfcDestopAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MVCMFCDESTOPAPP_DIALOG, pParent), IView()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMvcMfcDestopAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_CATEGORIES, _lstCompanies);
	DDX_Control(pDX, IDC_LST_ITEMS, _lstEmployees);
}

BEGIN_MESSAGE_MAP(CMvcMfcDestopAppDlg, CDialogEx)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LST_CATEGORIES, &CMvcMfcDestopAppDlg::OnSelchangeLstCategories)
	ON_MESSAGE(WM_EMPLOYEES_LOADED,&CMvcMfcDestopAppDlg::OnEmployeesLoaded)
	ON_LBN_SELCHANGE(IDC_LST_CATEGORIES, &CMvcMfcDestopAppDlg::OnSelchangeLstCategories)
	ON_COMMAND(IDR_REFRESH_ITEM, &CMvcMfcDestopAppDlg::OnBnClickedRefresh)
END_MESSAGE_MAP()


// CMvcMfcDestopAppDlg message handlers

BOOL CMvcMfcDestopAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//-------------------------------- ----------------
	// Initialize Controllers
	//-------------------------------- ----------------

	static_cast<CMvcMfcDestopAppApp*>(AfxGetApp())->_controllers.Companies().Load();

	//-------------------------------- ----------------


	//-------------------------------- ----------------
	// Initialize Views
	//-------------------------------- ----------------
	auto iview = static_cast<CMvcMfcDestopAppApp*>(AfxGetApp())->_controllers.Employees().View<EmployeeView>();
	auto employeeView = std::static_pointer_cast<EmployeeView>(iview);
	employeeView->setUpdateCallback([this](const std::vector<std::shared_ptr<IModel>>& data)
		{
			// Update Employees List Box
			_lstEmployees.ResetContent();
			for (const auto& item : data) {
				auto employee = std::dynamic_pointer_cast<EmployeeModel>(item);
				if (!employee) continue;
				CString name(employee->getName().c_str());
				_lstEmployees.AddString(name);
			}
		});

	// 
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

void CMvcMfcDestopAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMvcMfcDestopAppDlg::OnPaint()
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
HCURSOR CMvcMfcDestopAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMvcMfcDestopAppDlg::CreateView()
{
}

void CMvcMfcDestopAppDlg::LoadView()
{
}

void CMvcMfcDestopAppDlg::UpdateView(const std::vector<std::shared_ptr<IModel>>& data)
{
	// Populate company list
	_lstCompanies.ResetContent();
	for (const auto& item : data) {
		auto company = std::dynamic_pointer_cast<CompanyModel>(item);
		if (!company) continue;
		CString name(company->getName().c_str());
		_lstCompanies.AddString(name);
	}
}

void CMvcMfcDestopAppDlg::CloseView()
{

}

void CMvcMfcDestopAppDlg::OnSelchangeLstCategories()
{
	int currentSelection = _lstCompanies.GetCurSel()+ 1;
	static_cast<CMvcMfcDestopAppApp*>(AfxGetApp())->_controllers.Employees().LoadAsync(currentSelection,this->m_hWnd);
}

LRESULT CMvcMfcDestopAppDlg::OnEmployeesLoaded(WPARAM, LPARAM) {
	static_cast<CMvcMfcDestopAppApp*>(AfxGetApp())->_controllers.Employees().PublishLatest();
	return 0;
}
void CMvcMfcDestopAppDlg::OnBnClickedRefresh()
{
	auto& app = *static_cast<CMvcMfcDestopAppApp*>(AfxGetApp());
	app._controllers.Companies().Load();
	app._controllers.Employees().LoadAsync(-1,m_hWnd);

}