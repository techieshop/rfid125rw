// IDReaderAPITestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IDReaderAPITest.h"
#include "IDReaderAPITestDlg.h"

#include "gReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL g_connect = FALSE;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDReaderAPITestDlg dialog

CIDReaderAPITestDlg::CIDReaderAPITestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIDReaderAPITestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIDReaderAPITestDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIDReaderAPITestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIDReaderAPITestDlg)
	DDX_Control(pDX, IDC_EDIT_8H10D, m_edit_8h10d);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_static_tips);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIDReaderAPITestDlg, CDialog)
	//{{AFX_MSG_MAP(CIDReaderAPITestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_READ, OnBTNRead)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDReaderAPITestDlg message handlers

BOOL CIDReaderAPITestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    //=============== Init COM port ==================
    CString str;
	CComboBox *pPortCBB = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
	for(int i=0 ; i<16; i++)
    {		
		str.Format(_T("%d"), i+1);
		pPortCBB->AddString( str);		
		pPortCBB->SetItemData(i, i+1);		
	} 
	pPortCBB->SetCurSel(0);

    //
    m_edit_8h10d.SetLimitText(10);

    //
    CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_T5577);
    pButton->SetCheck(TRUE);

    //================== Load DLL ====================
    TCHAR szBuf[MAX_PATH];	
    GetModuleFileName(NULL, (LPTSTR)szBuf, MAX_PATH);
    *strrchr( szBuf, '\\' ) = 0;    
   // strcat(szBuf, _T("\\RFID_LF_DLL.dll"));
    strcat(szBuf, _T("\\IDReaderAPI.dll"));

    m_hInstMaster = LoadLibrary(szBuf);	 
    
    if(m_hInstMaster)
    {
        (FARPROC&)gConnReader           = GetProcAddress(m_hInstMaster,_T("gConnReader"));
        (FARPROC&)gDiscReader           = GetProcAddress(m_hInstMaster,_T("gDiscReader"));
        (FARPROC&)gSetBaud              = GetProcAddress(m_hInstMaster,_T("gSetBaud"));
        (FARPROC&)gSetTimeOut           = GetProcAddress(m_hInstMaster,_T("gSetTimeOut"));
        (FARPROC&)gGetModel             = GetProcAddress(m_hInstMaster,_T("gGetModel"));
        (FARPROC&)gSetBeep              = GetProcAddress(m_hInstMaster,_T("gSetBeep"));
        (FARPROC&)gSetLED               = GetProcAddress(m_hInstMaster,_T("gSetLED"));
        (FARPROC&)gReadEM4100           = GetProcAddress(m_hInstMaster,_T("gReadEM4100"));
        (FARPROC&)gDirecteAccess        = GetProcAddress(m_hInstMaster,_T("gDirecteAccess"));
        (FARPROC&)ATA_WriteEM4100       = GetProcAddress(m_hInstMaster,_T("ATA_WriteEM4100"));
        (FARPROC&)EM_WriteEM4100        = GetProcAddress(m_hInstMaster,_T("EM_WriteEM4100"));

        if(
            NULL == gConnReader       ||
            NULL == gDiscReader       ||
            NULL == gSetBaud          ||
            NULL == gSetTimeOut       ||
            NULL == gGetModel         ||
            NULL == gSetBeep          ||
            NULL == gSetLED           ||
            NULL == gReadEM4100       ||
            NULL == gDirecteAccess    ||
            NULL == ATA_WriteEM4100   ||
            NULL == EM_WriteEM4100
            )
        {			
            AfxMessageBox(_T("Load IDReaderAPI.dll failed !"));      
        }
    }
    else
    {
        AfxMessageBox(_T("Load IDReaderAPI.dll failed !"));       
    }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIDReaderAPITestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIDReaderAPITestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

HCURSOR CIDReaderAPITestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIDReaderAPITestDlg::OnBtnConnect() 
{
	// TODO: Add your control notification handler code here
	BOOL status;
    CString str;

    //Get port string
    CComboBox *pPortCBB = (CComboBox*)GetDlgItem(IDC_COMBO_PORT);
    int nPort = pPortCBB->GetItemData(pPortCBB->GetCurSel());
    str.Format("com%d", nPort);

    //Disconnect reader
    gDiscReader(0);
    
    //Connect reader
    status = gConnReader(str.GetBuffer(str.GetLength()), 0);
    if(status != TRUE)
    {
        MessageBox("gConnReader failed !", "Error", MB_OK|MB_ICONERROR);
        return;
    }
    g_connect = TRUE;

    //Set beep
    gSetBeep(40, 0);
}

void CIDReaderAPITestDlg::OnBTNRead() 
{
	// TODO: Add your control notification handler code here
    int status;
    CString str;
    DWORD dwID;
    BYTE arrID[5];

    if(g_connect != TRUE)
    {
        m_static_tips.SetWindowText("Reader is not attached !");
        return;
    }

	status = gReadEM4100(arrID, 0);
    if(status != 1)
    {
        m_static_tips.SetWindowText("Read card faild !");
        return;
    }

    dwID = (arrID[1]<<24) + (arrID[2]<<16) + (arrID[3]<<8) + arrID[4];
    str.Format("%010d",dwID);
    m_edit_8h10d.SetWindowText(str);

    m_static_tips.SetWindowText("Read card success !");
    gSetBeep(20, 0);
}

void CIDReaderAPITestDlg::OnBtnWrite() 
{
	// TODO: Add your control notification handler code here
    int status;
    CString str;
    __int64 dwID;
    BYTE arrID[5];
    BYTE arrID2[5];

    if(g_connect != TRUE)
    {
        m_static_tips.SetWindowText("Reader is not attached !");
            return;
    }

    m_edit_8h10d.GetWindowText(str);
    dwID = _atoi64(str);
    if(dwID>0xFFFFFFFF)
    {
        m_static_tips.SetWindowText("Data out of range !");
        return;
    }
    arrID[0] = 0; //Version or Customer ID
    arrID[1] = (BYTE)((dwID>>24)&0xFF);
    arrID[2] = (BYTE)((dwID>>16)&0xFF);
    arrID[3] = (BYTE)((dwID>>8)&0xFF);
    arrID[4] = (BYTE)(dwID&0xFF);

    CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_T5577);
    if((pButton->GetCheck())) //T5577
    {
        status = ATA_WriteEM4100(arrID, 0, 0);
        if(status != TRUE)
        {
            m_static_tips.SetWindowText("Write card faild !");
            return;
        }

        status = gReadEM4100(arrID2, 0);
        if(status != TRUE)
        {
            m_static_tips.SetWindowText("Write card faild !");
            return;
        }

        for(int i=0; i<5; i++)
        {
            if(arrID[i] != arrID2[i])
            {
                break;
            }
        }
        if(i != 5)
        {
            m_static_tips.SetWindowText("Write card faild !");
            return;
        }
    }
    else //EM4305
    {
        status = EM_WriteEM4100(arrID, 0, 0);    
        if(status != 0)
        {
            m_static_tips.SetWindowText("Write card faild !");
            return;
        }
	}

    m_static_tips.SetWindowText("Write card success !");
    gSetBeep(20, 0);
    
}

void CIDReaderAPITestDlg::OnDestroy() 
{
    CDialog::OnDestroy();
    
    // TODO: Add your message handler code here
    if(m_hInstMaster) FreeLibrary(m_hInstMaster);
}
