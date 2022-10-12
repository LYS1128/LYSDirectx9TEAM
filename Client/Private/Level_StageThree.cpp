#include "stdafx.h"
#include "..\Public\Level_StageThree.h"

CLevel_StageThree::CLevel_StageThree(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageThree::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageThree : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageThree : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageThree : NativeConstruct");
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
	if (FAILED(Ready_Layer_Monster(L"Layer_Monster"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	g_iLevel = LEVEL_STAGETHREE;

	if (FAILED(Ready_Layer_Camera(L"Layer_Camera"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);

	return S_OK;
}

void CLevel_StageThree::Tick(_float fTimeDelta) {

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CSound_Manager::GetInstance()->PlaySound(L"Stage_3.wav", CSound_Manager::BGM, VOLUME);

	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEFOUR)))) {
			return;
		}
	}

	if (rand() % 60 == 0) {
		for (int i = 0; i < 20; ++i) {
			if (FAILED(Ready_Layer_Sakura(L"Layer_Sakura"))) {
				MSG_BOX(L"Failed To CLevel_Tutorial : Tick");
				return;
			}
		}
	}


	Safe_Release(pGameInstance);
}

HRESULT CLevel_StageThree::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageThree : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("3스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageThree::Ready_Layer_Monster(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMonster::MONSTER tMonster;
	tMonster.mapCube = m_MapCube;
	tMonster.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tMonster.vPosition = _float3(21.51f, 30.f, 21.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(17.51f, 27.f,22.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(12.51f, 24.f, 22.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(21.51f, 19.f, 20.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(6.51f, 20.f,18.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(14.51f, 22.f, 15.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(20.51f, 20.f, 14.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(21.51f, 15.f, 3.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(18.51f, 15.f, 6.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}

	tMonster.vPosition = _float3(10.51f, 10.f, 6.51f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_CuteBear"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_CuteBear");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageThree::Ready_Layer_Sakura(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_Sakura")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Snow");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);	
	return S_OK;
}
HRESULT CLevel_StageThree::Ready_Layer_Camera(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMultiCamera* pCamera = (CMultiCamera*)(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front());
	Safe_AddRef(pCamera);
	if (nullptr == pCamera) {
		Safe_Release(pGameInstance);
		Safe_Release(pCamera);
		return E_FAIL;
	}
	if (g_iLevel == LEVEL_STAGETHREE)
	{
		pCamera->Set_ModeDefault();
	}

	Safe_Release(pCamera);
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLevel_StageThree::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(3.5f, 2.5f, 5.5f));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageThree::Ready_Layer_Player(const _tchar* pLayerTag) {
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

HRESULT CLevel_StageThree::Ready_Layer_NPC(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(4.5f, 2.5f, 4.5f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_Warrior"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageThree::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageThreeMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageThree : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_StageThree : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageThree : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}


CLevel_StageThree* CLevel_StageThree::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageThree* pInstance = new CLevel_StageThree(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageThree : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageThree::Free() {
	__super::Free();
}

HRESULT CLevel_StageThree::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageThree : Load_Map");
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