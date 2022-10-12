#include "stdafx.h"
#include "..\Public\Level_StageSemiAfter.h"

CLevel_StageSemiAfter::CLevel_StageSemiAfter(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageSemiAfter::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_NPC(L"Layer_NPC"))) {
		MSG_BOX(L"Failed To CLevel_StageThree : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_White(L"Layer_White2"))) {
		MSG_BOX(L"Failed To CLevel_StageSemiBoss : NativeConstruct");
		return E_FAIL;
	}

	g_iLevel = LEVEL_STAGESEMIAFTER;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
	

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	dynamic_cast<CSemi_2*>(pGameInstance->Find_Layer_List(LEVEL_STAGESEMIAFTER, L"Layer_White2")->front())->Set_Check();
	Safe_Release(pGameInstance);
	return S_OK;
}

void CLevel_StageSemiAfter::Tick(_float fTimeDelta) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);


	CSound_Manager::GetInstance()->PlaySound(L"Stage_4_2.wav", CSound_Manager::BGM, VOLUME);


	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEFIVE)))) {
			return;
		}
	}
	Safe_Release(pGameInstance);

}

HRESULT CLevel_StageSemiAfter::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("5스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageSemiAfter::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//list<CGameObject*>* p = (pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List());
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
//	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION,_float3(0.f,10.f,0.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSemiAfter::Ready_Layer_White(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, pLayerTag, TEXT("Prototype_GameObject_Semi2")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Semi2");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSemiAfter::Ready_Layer_NPC(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(14.51f, 1.5f, 10.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, L"Layer_White", TEXT("Prototype_GameObject_Warrior"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSemiAfter::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(_float3(12.51f, 1.5f, 12.51f)));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSemiAfter::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageSemiAfter.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_StageSemiAfter : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}


CLevel_StageSemiAfter* CLevel_StageSemiAfter::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageSemiAfter* pInstance = new CLevel_StageSemiAfter(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageSemiAfter::Free() {
	__super::Free();
}

HRESULT CLevel_StageSemiAfter::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageSemiAfter : Load_Map");
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