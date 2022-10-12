#pragma once

#include "Tool_Define.h"


// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTileList();

	BOOL OnInitDialog();

	CListBox m_ListBox;
	CStatic m_Picture;
	CStatic m_Picture2;
	int		m_iDrawID = 0;
	CButton m_Check;
	bool	m_Del;

	map<CString, CImage*>		m_PngImage;
	map<CString, CImage*>		m_FrontImage;
	afx_msg void OnSaveCube();
};
