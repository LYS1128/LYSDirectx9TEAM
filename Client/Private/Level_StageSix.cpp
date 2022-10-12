#include "stdafx.h"
#include "..\Public\Level_StageSix.h"

CLevel_StageSix::CLevel_StageSix(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageSix::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSix : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageSix : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageSix : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_NPC(L"Layer_NPC"))) {
		MSG_BOX(L"Failed To CLevel_StageThree : NativeConstruct");
		return E_FAIL;
	}
	for (int i = 0; i <5; ++i)
	{
		if (FAILED(Ready_Layer_Monster(L"Layer_Monster"))) {
			MSG_BOX(L"Failed To CLevel_StageFive : NativeConstruct");
			return E_FAIL;
		}
	}
	g_iLevel = LEVEL_STAGESIX;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
	

	return S_OK;
}

void CLevel_StageSix::Tick(_float fTimeDelta) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CSound_Manager::GetInstance()->PlaySound(L"Stage_6.wav", CSound_Manager::BGM, VOLUME);

	if (pGameInstance->Find_Layer(LEVEL_STAGESIX, L"Layer_Monster")->Get_List()->size() < 16 && rand() % 180 == 0)
	{
		if (FAILED(Ready_Layer_Monster(L"Layer_Monster"))) {
			MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
			return;
		}
	}

	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGESEVEN)))) {
			return;
		}
	}
	Safe_Release(pGameInstance);

}

HRESULT CLevel_StageSix::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageSix : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("6스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageSix::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//list<CGameObject*>* p = (pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List());
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION,_float3(2.f,5.f,2.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSix::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(_float3(79.51f, 20.5f,58.51f)));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSix::Ready_Layer_NPC(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(3.5f, 2.5f, 3.5f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, pLayerTag, TEXT("Prototype_GameObject_Theif"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSix::Ready_Layer_Monster(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMonster::MONSTER tMonster;
	tMonster.mapCube = m_MapCube;
	tMonster.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tMonster.vPosition = _float3(rand() % 10 + 5.f, 10.f, rand() % 10 + 5.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, pLayerTag, TEXT("Prototype_GameObject_GhostStump"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(rand() % 10 + 20.f, 15.f, rand() % 10 + 15.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, pLayerTag, TEXT("Prototype_GameObject_FireBoar"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(rand() % 10 + 50.f, 25.f, rand() % 10 + 30.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, pLayerTag, TEXT("Prototype_GameObject_IronBoar"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
		return E_FAIL;
	}
	tMonster.vPosition = _float3(rand() % 10 + 70.f, 30.f, rand() % 10 + 47.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, pLayerTag, TEXT("Prototype_GameObject_CokeGolem"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSix::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageSixMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageSix : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_StageSix : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESIX, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageSix : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}


CLevel_StageSix* CLevel_StageSix::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageSix* pInstance = new CLevel_StageSix(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSix : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageSix::Free() {
	__super::Free();
}

HRESULT CLevel_StageSix::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageSix : Load_Map");
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