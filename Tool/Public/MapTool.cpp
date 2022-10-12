// ../Private/MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "../Default/stdafx.h"
#include "../Default/Tool.h"
#include "../Public/MapTool.h"
#include "afxdialogex.h"

#include "../Default/MainFrm.h"
#include "MyForm.h"
#include "../Default/ToolView.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{

}

CMapTool::~CMapTool()
{
	for_each(m_PngImage.begin(), m_PngImage.end(),
		[](auto& Pair) {
		Pair.second->Destroy();
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	});
	m_PngImage.clear();

	for_each(m_FrontImage.begin(), m_FrontImage.end(),
		[](auto& Pair) {
		Pair.second->Destroy();
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	});
	m_FrontImage.clear();
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_PICTURE2, m_Picture2);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_CHECK1, m_Check);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnTileList)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnSaveCube)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::OnTileList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);


	CString		strFindName = L"";

	int	iSelect = m_ListBox.GetCurSel();

	// 찾지 못하면 LB_ERR(-1)반환
	if (LB_ERR == iSelect)
		return;

	m_ListBox.GetText(iSelect, strFindName);

	auto	iter = m_PngImage.find(strFindName);

	if (iter == m_PngImage.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	auto	iter2 = m_FrontImage.find(strFindName);

	if (iter2 == m_FrontImage.end())
		return;

	m_Picture2.SetBitmap(*(iter2->second));

	int i = 0;

	for (; i < strFindName.GetLength(); ++i)
	{
		// isdigit : 매개 변수로 받는 문자열이 단일 문자인지 숫자인지 구별해주는 함수
		//			 숫자라고 판단될 경우 0이 아닌 값을 반환

		if (0 != isdigit(strFindName[i]))
			break;
	}
	// 인덱스 위치로부터 카운트한 숫자만큼 문자를 삭제하는 함수
	strFindName.Delete(0, i);
	m_iDrawID = _tstoi(strFindName);

	if (m_Check.GetCheck())
		m_Del = true;
	else
		m_Del = false;

	UpdateData(FALSE);
}

BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_Check.SetCheck(FALSE);

	TCHAR	szFileName[256] = L"";
	CString	 strRelativePath = L"";

	for (int i = 0; i < 334; ++i)
	{
		strRelativePath.Format(L"../../Resources/TileImage/Tile%d.png", i);
		CString	 strFileName = PathFindFileName(strRelativePath);

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_PngImage.find(strFileName);

		if (iter == m_PngImage.end())
		{
			CImage*		pPngImage = new CImage;
			pPngImage->Load(strRelativePath);

			m_PngImage.emplace(strFileName, pPngImage);
			m_ListBox.AddString(strFileName);
		}
	}


	for (int i = 0; i < 334; ++i)
	{
		strRelativePath.Format(L"../../Resources/FrontImage/Tile%d.png", i);
		CString	 strFileName = PathFindFileName(strRelativePath);

		lstrcpy(szFileName, strFileName.GetString());
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_FrontImage.find(strFileName);

		if (iter == m_FrontImage.end())
		{
			CImage*		pFrontImage = new CImage;
			pFrontImage->Load(strRelativePath);

			m_FrontImage.emplace(strFileName, pFrontImage);
		}
	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapTool::OnSaveCube()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog	Dlg(FALSE,	// true인 경우 열기 모드, false 인 경우 다른 이름으로 저장 모드
		L"dat", // default 파일 확장명, 저장 시 확장자명을 명시해주지 않으면 현재 기입한 확장자명을 사용하게 설정됨
		L"*.dat", // 대화상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복 파일 저장 시 경고메시지 띄우기 옵션)
		L"Data File(*.dat)|*.dat||",	// 대화 상자에 표시될 파일 형식, 콤보박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||
		this); // 부모 윈도우 주소

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트가 있는 디렉토리 경로를 얻어오는 함수
	GetCurrentDirectory(MAX_PATH, szPath);

	// 전체 경로에서 맨 마지막 경로를 잘라내는 함수
	// 경로 상에 맨 마지막 경로가 파일명이면 그 파일명을 제외한 경로만 남고, 만약 파일명이 없으면 마지막 폴더명을 잘라낸다.
	PathRemoveFileSpec(szPath);
	PathRemoveFileSpec(szPath);

	// data폴더 경로를 이어붙임
	lstrcat(szPath, L"\\Data");

	// 대화상자를 열었을 때 보이는 기본 경로 설정, 절대 경로인 상황
	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : 대화 상자를 실행, IDOK 실행 성공
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName 선택된 경로를 반환
		CString	strFind = Dlg.GetPathName();
		const TCHAR*	pGetPath = strFind.GetString();

		HANDLE		hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (INVALID_HANDLE_VALUE == hFile)
			return;


		CMainFrame*		pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*		pToolView = dynamic_cast<CToolView*>(pMain->m_MainSplitter.GetPane(0, 1));

		CGameInstance* pGameInstance = CGameInstance::GetInstance();
		Safe_AddRef(pGameInstance);



		list<CGameObject*> CubeList = *(pGameInstance->Find_Layer_List(0, L"Layer_Cube"));
		list<_float4> InfoList;
		for (auto iter : CubeList)
		{
			CTransform* CubeTrans = (CTransform*)iter->Get_Component(L"Com_Transform");
			InfoList.push_back(_float4(CubeTrans->Get_State(CTransform::STATE_POSITION).x, CubeTrans->Get_State(CTransform::STATE_POSITION).y, CubeTrans->Get_State(CTransform::STATE_POSITION).z, dynamic_cast<CCube*>(iter)->GetDraw()));
		}
		Safe_Release(pGameInstance);

		DWORD		dwByte = 0;

		for (auto& iter : InfoList)
			WriteFile(hFile, iter, sizeof(_float4), &dwByte, NULL);

		CloseHandle(hFile);
	}
}
