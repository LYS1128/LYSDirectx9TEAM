
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "MyForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView
HWND g_hWnd;

IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}
void CToolView::OnInitialUpdate() {

	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : ���� ������ â�� ��Ʈ ������ ������ �Լ�
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : ������ ���ڰ����� rect������ �����ϴ� �Լ�
	// ���� 0,0�������� â�� ��Ʈ�� �����ϰ� �ִ� ��Ȳ
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};
	//GetClientRect : ���� view â�� rect ������ ������ �Լ�
	GetClientRect(&rcMainView);

	// �����Ӱ� viewâ�� ����, ���� ���� ���Ѵ�.
	float	fRowFrm = float(rcWnd.right - rcMainView.right);
	float	fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	pMainFrm->SetWindowPos(nullptr, 300, 100, int(g_iWinCX + fRowFrm), int(g_iWinCY + fColFrm), SWP_NOZORDER);


	CView::OnInitialUpdate();
	g_hWnd = m_hWnd;


	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CGraphic_Device::INITENGINE InitDevice;
	ZeroMemory(&InitDevice, sizeof(CGraphic_Device::INITENGINE));

	InitDevice.hWnd = g_hWnd;
	InitDevice.iWinCX = g_iWinCX;
	InitDevice.iWinCY = g_iWinCY;

	pGameInstance->Initialize_Engine_Tool(1, InitDevice, &m_pGraphic_Device);

	pGameInstance->Add_Prototype(0, TEXT("Prototype_Component_Renderer"), m_pRenderer = CRenderer::Create(m_pGraphic_Device));

	Safe_AddRef(m_pRenderer);

	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	pGameInstance->Add_Prototype(0, TEXT("Prototype_Component_Transform"), CTransform::Create(m_pGraphic_Device));
	pGameInstance->Add_Prototype(0, L"Prototype_Component_VIBuffer_Cube", CVIBuffer_Cube::Create(m_pGraphic_Device));
	pGameInstance->Add_Prototype(L"Prototype_Object_Cube", CCube::Create(m_pGraphic_Device));
	pGameInstance->Add_Prototype(0, TEXT("Prototype_Component_Texture_Default"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../../Resources/Tile/Tile%d.dds"), 334));
	pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Camera_Default"), CCamera_Default::Create(m_pGraphic_Device));


	HANDLE hFile = CreateFile(L"../../Data/StageBossMap.dat", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwByte = 0;

	_float4* pInfo = nullptr;

	while (true) {
		pInfo = new _float4;

		ReadFile(hFile, pInfo, sizeof(_float4), &dwByte, nullptr);

		if (0 == dwByte) {
			Safe_Delete(pInfo);
			break;
		}

		pGameInstance->Add_GameObjectToLayer(0, L"Layer_Cube", TEXT("Prototype_Object_Cube"), pInfo);

		Safe_Delete(pInfo);
	}
	//CloseHandle(hFile);


	//for (_uint i = 0; i < 25; ++i)
	//{
	//	for (_uint j = 0; j < 25; ++j)
	//	{
	//		Info = _float4((_float)i, 0.f, (_float)j, 27.f);
	//		pGameInstance->Add_GameObjectToLayer(0, L"Layer_Cube", TEXT("Prototype_Object_Cube"), &Info);
	//	}
	//}


	CCamera::CAMERADESC			CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

	CameraDesc.vEye = _float3(10.f, 10.f, 10.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 100.0f;
	CameraDesc.fFovy = D3DXToRadian(60.0f);
	CameraDesc.fAspect = (_float)g_iWinCX / g_iWinCY;

	CameraDesc.TransformDesc.fSpeedPerSec = 10.f;
	CameraDesc.TransformDesc.fRotationPerSec = 10.f;
	CameraDesc.TransformDesc.fScalePerSec = 1.f;


	pGameInstance->Add_GameObjectToLayer(0, L"Layer_Cameara", TEXT("Prototype_GameObject_Camera_Default"), &CameraDesc);

	Safe_Release(pGameInstance);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	pGameInstance->Tick_Engine(0.1f);

	pGameInstance->Render_Begin();
	m_pRenderer->Render_GameObjects();
	pGameInstance->Render_End();

	Safe_Release(pGameInstance);
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	pGameInstance->Tick_Engine(0.01f);

	pGameInstance->Render_Begin();
	m_pRenderer->Render_GameObjects();
	pGameInstance->Render_End();
	Safe_Release(pGameInstance);
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonDown(nFlags, point);

	CMainFrame*		pMain = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CMyForm*		pMyForm = dynamic_cast<CMyForm*>(pMain->m_MainSplitter.GetPane(0,0));
	CMapTool*		pMapTool = &(pMyForm->m_MapTool);

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	pGameInstance->Set_Graphic_Device(m_pGraphic_Device);
	Safe_AddRef(pGameInstance);

	CMouse::RAY Ray = pGameInstance->Make_Ray(g_hWnd, g_iWinCX, g_iWinCY);
	
	CMouse::PICK* tPick;
	vector<CMouse::PICK> vecPick;
	list<CGameObject*> CubeList = *(pGameInstance->Find_Layer_List(0, L"Layer_Cube"));
	_float4x4 WorldMatrix;

	for (int i = 0; i < CubeList.size(); ++i) {
		CTransform* pTransform = (CTransform*)(pGameInstance->Get_Component(0, L"Layer_Cube", L"Com_Transform", i));
		Safe_AddRef(pTransform);

		WorldMatrix = pTransform->Get_WorldMatrix();

		CVIBuffer_Cube* pVIBuffer = (CVIBuffer_Cube*)(pGameInstance->Get_Component(0, L"Layer_Cube", L"Com_VIBuffer", i));
		Safe_AddRef(pVIBuffer);
		VTXCUBETEX* pVertices = pVIBuffer->Get_Vertices();

		tPick = pGameInstance->Picking_Cube(pVertices, WorldMatrix);
		if (nullptr != tPick) {
			CMouse::PICK Buff = *tPick;
			vecPick.push_back(Buff);
		}
		Safe_Release(pTransform);
		Safe_Release(pVIBuffer);
	}
	if (0 != vecPick.size()) {
		sort(vecPick.begin(), vecPick.end(), [](CMouse::PICK first, CMouse::PICK second) -> bool
		{
			return first.fDis < second.fDis;
		});

		_float3 vRes = Ray.vRayPos + vecPick.front().fDis * Ray.vRay;

		_float3 Pos1 = vecPick.front().vPos1;
		_float3 Pos2 = vecPick.front().vPos2;
		_float3 Pos3 = vecPick.front().vPos3;

		_float Dist1 = sqrtf((Pos1.x - Pos2.x)*(Pos1.x - Pos2.x) + (Pos1.y - Pos2.y)*(Pos1.y - Pos2.y) + (Pos1.z - Pos2.z)*(Pos1.z - Pos2.z));
		_float Dist2 = sqrtf((Pos1.x - Pos3.x)*(Pos1.x - Pos3.x) + (Pos1.y - Pos3.y)*(Pos1.y - Pos3.y) + (Pos1.z - Pos3.z)*(Pos1.z - Pos3.z));
		_float Dist3 = sqrtf((Pos3.x - Pos2.x)*(Pos3.x - Pos2.x) + (Pos3.y - Pos2.y)*(Pos3.y - Pos2.y) + (Pos3.z - Pos2.z)*(Pos3.z - Pos2.z));
		
		_float3 NewPos;
		_float4 NewInfo;


		//�����ϴ°�
		bool Check = *(&pMapTool->m_Del);
		if (Check)
		{
			list<CGameObject*>* CubeList = pGameInstance->Find_Layer_List(0,L"Layer_Cube");
			for (auto iter = (*CubeList).begin();iter != (*CubeList).end();)
			{
				CTransform* CubeTrans = (CTransform*)(*iter)->Get_Component(L"Com_Transform");
				Safe_AddRef(CubeTrans);
				if (vecPick.front().vCenter == CubeTrans->Get_State(CTransform::STATE_POSITION))
				{
					Safe_Release(*iter);
					iter = CubeList->erase(iter);
				}
				else
					++iter;
				Safe_Release(CubeTrans);
			}
		}
		else
		{
			if (Dist1 == Dist2)
			{
				_float3 Center = _float3((Pos3.x + Pos2.x) / 2, (Pos3.y + Pos2.y) / 2, (Pos3.z + Pos2.z) / 2);
				NewPos = vecPick.front().vCenter + (Center - vecPick.front().vCenter) * 2;
				NewInfo = _float4(NewPos.x, NewPos.y, NewPos.z, (_float)(*(&pMapTool->m_iDrawID)));
				pGameInstance->Add_GameObjectToLayer(0, L"Layer_Cube", TEXT("Prototype_Object_Cube"), &NewInfo);
			}
			else if (Dist1 == Dist3)
			{
				_float3 Center = _float3((Pos3.x + Pos1.x) / 2, (Pos3.y + Pos1.y) / 2, (Pos3.z + Pos1.z) / 2);
				NewPos = vecPick.front().vCenter + (Center - vecPick.front().vCenter) * 2;
				NewInfo = _float4(NewPos.x, NewPos.y, NewPos.z, (_float)(*(&pMapTool->m_iDrawID)));
				pGameInstance->Add_GameObjectToLayer(0, L"Layer_Cube", TEXT("Prototype_Object_Cube"), &NewInfo);
			}
			else
			{
				_float3 Center = _float3((Pos2.x + Pos1.x) / 2, (Pos2.y + Pos1.y) / 2, (Pos2.z + Pos1.z) / 2);
				NewPos = vecPick.front().vCenter + (Center - vecPick.front().vCenter) * 2;
				NewInfo = _float4(NewPos.x, NewPos.y, NewPos.z, (_float)(*(&pMapTool->m_iDrawID)));
				pGameInstance->Add_GameObjectToLayer(0, L"Layer_Cube", TEXT("Prototype_Object_Cube"), &NewInfo);
			}
		}
	}
	Safe_Release(pGameInstance);
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMouseMove(nFlags, point);

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	pGameInstance->Tick_Engine(0.01f);

	pGameInstance->Render_Begin();
	m_pRenderer->Render_GameObjects();
	pGameInstance->Render_End();
	Safe_Release(pGameInstance);
}


void CToolView::OnDestroy()
{
	CView::OnDestroy();

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	pGameInstance->Release_Engine();
	pGameInstance->Free();
	Safe_Release(m_pRenderer);
	Safe_Release(m_pVIBuffer);
	Safe_Release(pGameInstance);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
