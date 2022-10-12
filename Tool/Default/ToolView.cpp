
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}
void CToolView::OnInitialUpdate() {

	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : 현재 윈도우 창의 렉트 정보를 얻어오는 함수
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : 지정한 인자값으로 rect정보를 세팅하는 함수
	// 현재 0,0기준으로 창의 렉트를 조정하고 있는 상황
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};
	//GetClientRect : 현재 view 창의 rect 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	// 프레임과 view창의 가로, 세로 갭을 구한다.
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

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	pGameInstance->Tick_Engine(0.1f);

	pGameInstance->Render_Begin();
	m_pRenderer->Render_GameObjects();
	pGameInstance->Render_End();

	Safe_Release(pGameInstance);
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	pGameInstance->Tick_Engine(0.01f);

	pGameInstance->Render_Begin();
	m_pRenderer->Render_GameObjects();
	pGameInstance->Render_End();
	Safe_Release(pGameInstance);
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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


		//삭제하는곳
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
