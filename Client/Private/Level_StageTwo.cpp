#include "stdafx.h"
#include "..\Public\Level_StageTwo.h"

CLevel_StageTwo::CLevel_StageTwo(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageTwo::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageTwo : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_NPC(L"Layer_NPC"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	for (int i = 0; i < 5; ++i)
	{
		if (FAILED(Ready_Layer_Monster(L"Layer_Monster"))) {
			MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
			return E_FAIL;
		}
	}
	g_iLevel = LEVEL_STAGETWO;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
	

	return S_OK;
}

void CLevel_StageTwo::Tick(_float fTimeDelta) {

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CSound_Manager::GetInstance()->PlaySound(L"Stage_2.wav", CSound_Manager::BGM, VOLUME);

	if (pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Monster")->Get_List()->size() < 5 && rand() % 180 == 0)
	{
		if (FAILED(Ready_Layer_Monster(L"Layer_Monster"))) {
			MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
			return;
		}
	}

	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGETWO_1)))) {
			return;
		}
	}

	if (rand() % 60 == 0) {
		for (int i = 0; i < 20; ++i) {
			if (FAILED(Ready_Layer_Sakura(L"Layer_Ssakura"))) {
				MSG_BOX(L"Failed To CLevel_Tutorial : Tick");
				return;
			}
		}
	}
	Safe_Release(pGameInstance);

}

HRESULT CLevel_StageTwo::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageTwo : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("2스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageTwo::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//list<CGameObject*>* p = (pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List());
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION,_float3(3.f,5.f,3.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageTwo::Ready_Layer_Sakura(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, pLayerTag, TEXT("Prototype_GameObject_Sakura")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Snow");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageTwo::Ready_Layer_Monster(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

		CMonster::MONSTER tMonster;
		tMonster.mapCube = m_MapCube;
		tMonster.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
		tMonster.vPosition = _float3(rand() % 5 + 3.f, 10.f, rand() % 10 + 20.f);

		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, pLayerTag, TEXT("Prototype_GameObject_Slime"), &tMonster))) {
			MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
			return E_FAIL;
		}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageTwo::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageTwoMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageTwo : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_StageTwo : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageTwo : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageTwo::Ready_Layer_NPC(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(26.5f, 2.5f, 4.5f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, pLayerTag, TEXT("Prototype_GameObject_Magician"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageTwo::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(26.5f, 2.5f, 8.5f));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel_StageTwo* CLevel_StageTwo::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageTwo* pInstance = new CLevel_StageTwo(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageTwo : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageTwo::Free() {
	__super::Free();
}

HRESULT CLevel_StageTwo::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageTwo : Load_Map");
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