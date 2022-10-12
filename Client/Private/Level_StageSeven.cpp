#include "stdafx.h"
#include "..\Public\Level_StageSeven.h"

CLevel_StageSeven::CLevel_StageSeven(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageSeven::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSeven : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageSeven : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageSeven : NativeConstruct");
		return E_FAIL;
	}
	for (_uint i = 0; i < 10; ++i)
	{
		if (FAILED(Ready_Layer_Monster(L"Layer_Monster"))) {
			MSG_BOX(L"Failed To CLevel_StageSeven : NativeConstruct");
			return E_FAIL;
		}
	}
	if (FAILED(Ready_Layer_NPC(L"Layer_NPC"))) {
		MSG_BOX(L"Failed To CLevel_StageThree : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	g_iLevel = LEVEL_STAGESEVEN;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);


	return S_OK;
}

void CLevel_StageSeven::Tick(_float fTimeDelta) {

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CSound_Manager::GetInstance()->PlaySound(L"Stage_7.wav", CSound_Manager::BGM, VOLUME);

	if (pGameInstance->Find_Layer(LEVEL_STAGESEVEN, L"Layer_Monster")->Get_List()->size() < 9 && rand() % 180 == 0)
	{
		if (FAILED(Ready_Layer_Monster(L"Layer_Monster"))) {
			MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
			return;
		}
	}


	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEEIGHT)))) {
			return;
		}
	}
	Safe_Release(pGameInstance);
}

HRESULT CLevel_StageSeven::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("7스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageSeven::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//list<CGameObject*>* p = (pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List());
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION,_float3(1.f,5.f,1.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageSeven::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(_float3(14.51f, 10.5f, 7.51f)));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLevel_StageSeven::Ready_Layer_NPC(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(3.5f, 1.5f, 3.5f);
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, pLayerTag, TEXT("Prototype_GameObject_Theif"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	tNPC.vPosition = _float3(14.5f, 10.5f, 10.5f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, pLayerTag, TEXT("Prototype_GameObject_SangIn"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLevel_StageSeven::Ready_Layer_Monster(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMonster::MONSTER tMonster;
	tMonster.mapCube = m_MapCube;
	tMonster.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tMonster.vPosition = _float3(rand()%13+7.f, 5.f, rand()%8+7.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, pLayerTag, TEXT("Prototype_GameObject_Wraith"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Ready_Layer_Monster");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}


HRESULT CLevel_StageSeven::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageSevenMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_StageSeven : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEVEN, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}


CLevel_StageSeven* CLevel_StageSeven::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageSeven* pInstance = new CLevel_StageSeven(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageSeven::Free() {
	__super::Free();
}

HRESULT CLevel_StageSeven::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Load_Map");
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