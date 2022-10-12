#include "stdafx.h"
#include "..\Public\Level_StageTwo_1.h"

CLevel_StageTwo_1::CLevel_StageTwo_1(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageTwo_1::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : NativeConstruct");
		return E_FAIL;
	}
	g_iLevel = LEVEL_STAGETWO_1;

	if (FAILED(Ready_Layer_Camera(L"Layer_Camera"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
	

	return S_OK;
}

void CLevel_StageTwo_1::Tick(_float fTimeDelta) {

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CSound_Manager::GetInstance()->PlaySound(L"Stage_2.wav", CSound_Manager::BGM, VOLUME);

	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGETHREE)))) {
			return;
		}
	}

	_float3 PlayerPos = dynamic_cast<CTransform*>(pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"))->Get_State(CTransform::STATE_POSITION);
	
	if (PlayerPos.x >= 10.f && PlayerPos.z >= 3.f && bCheck == false)
	{
		bCheck = true;
		CPlayer* pPlayer = (CPlayer*)(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());
		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO_1, L"Layer_UI", L"Prototype_GameObject_QuizUI", pPlayer);
	}
	if (bCheck == true)
	{
		if (pGameInstance->Find_Layer(LEVEL_STAGETWO_1, L"Layer_UI")->Get_List()->size() == 0)
		{
			if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGETHREE)))) {
				return;
			}
		}
	}
	
	Safe_Release(pGameInstance);
}

HRESULT CLevel_StageTwo_1::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("2스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageTwo_1::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//list<CGameObject*>* p = (pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List());
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_RIGHT, _float3(1.f, 0.f, 0.f));
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_UP, _float3(0.f, 1.f, 0.f));
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_LOOK, _float3(0.f, 0.f, 1.f));
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION,_float3(12.f,5.f,3.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLevel_StageTwo_1::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(26.5f, 200.5f, 8.5f));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLevel_StageTwo_1::Ready_Layer_Camera(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMultiCamera* pCamera = (CMultiCamera*)(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front());
	Safe_AddRef(pCamera);
	if (nullptr == pCamera) {
		Safe_Release(pGameInstance);
		Safe_Release(pCamera);
		return E_FAIL;
	}
	if (g_iLevel == LEVEL_STAGETWO_1)
	{
		pCamera->Set_ModeOX();
	}

	Safe_Release(pCamera);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageTwo_1::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/OXMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO_1, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_StageTwo_1 : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO_1, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel_StageTwo_1* CLevel_StageTwo_1::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageTwo_1* pInstance = new CLevel_StageTwo_1(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageTwo_1::Free() {
	__super::Free();
}

HRESULT CLevel_StageTwo_1::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageTwo_1 : Load_Map");
		return E_FAIL;
	}
	DWORD dwByte = 0;
	_float4* pInfo = nullptr;

	while (true) {
		pInfo = new _float4;

		ReadFile(hFile, pInfo, sizeof(_float4), &dwByte, nullptr);

		if (0 == dwByte) {
			Safe_Delete(pInfo);
			break;
		}
		_uint iCubeIndex = (_uint(pInfo->x + 0.5f) * 10000 + _uint(pInfo->y + 0.5f) * 100 + _uint(pInfo->z + 0.5f));
		m_MapCube.insert(map<_uint, _float4>::value_type(iCubeIndex, *pInfo));
		
		Safe_Delete(pInfo);
	}
	CloseHandle(hFile);
	return S_OK;
}