// ../Private/MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "../Default/stdafx.h"
#include "../Default/Tool.h"
#include "../Public/MapTool.h"
#include "afxdialogex.h"

#include "../Default/MainFrm.h"
#include "MyForm.h"
#include "../Default/ToolView.h"


// CMapTool ��ȭ �����Դϴ�.

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


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::OnTileList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);


	CString		strFindName = L"";

	int	iSelect = m_ListBox.GetCurSel();

	// ã�� ���ϸ� LB_ERR(-1)��ȯ
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
		// isdigit : �Ű� ������ �޴� ���ڿ��� ���� �������� �������� �������ִ� �Լ�
		//			 ���ڶ�� �Ǵܵ� ��� 0�� �ƴ� ���� ��ȯ

		if (0 != isdigit(strFindName[i]))
			break;
	}
	// �ε��� ��ġ�κ��� ī��Ʈ�� ���ڸ�ŭ ���ڸ� �����ϴ� �Լ�
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMapTool::OnSaveCube()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog	Dlg(FALSE,	// true�� ��� ���� ���, false �� ��� �ٸ� �̸����� ���� ���
		L"dat", // default ���� Ȯ���, ���� �� Ȯ���ڸ��� ��������� ������ ���� ������ Ȯ���ڸ��� ����ϰ� ������
		L"*.dat", // ��ȭ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ� ���� ���� �� ���޽��� ���� �ɼ�)
		L"Data File(*.dat)|*.dat||",	// ��ȭ ���ڿ� ǥ�õ� ���� ����, �޺��ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	// ���� ������Ʈ�� �ִ� ���丮 ��θ� ������ �Լ�
	GetCurrentDirectory(MAX_PATH, szPath);

	// ��ü ��ο��� �� ������ ��θ� �߶󳻴� �Լ�
	// ��� �� �� ������ ��ΰ� ���ϸ��̸� �� ���ϸ��� ������ ��θ� ����, ���� ���ϸ��� ������ ������ �������� �߶󳽴�.
	PathRemoveFileSpec(szPath);
	PathRemoveFileSpec(szPath);

	// data���� ��θ� �̾����
	lstrcat(szPath, L"\\Data");

	// ��ȭ���ڸ� ������ �� ���̴� �⺻ ��� ����, ���� ����� ��Ȳ
	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : ��ȭ ���ڸ� ����, IDOK ���� ����
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName ���õ� ��θ� ��ȯ
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
