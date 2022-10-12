#include "stdafx.h"
#include "..\Public\Level_Tutorial.h"

CLevel_Tutorial::CLevel_Tutorial(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{

}

HRESULT CLevel_Tutorial::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_NPC(L"Layer_NPC"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_UI(L"Layer_Hexagon_UI"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : NativeConstruct");
		return E_FAIL;
	}



	g_iLevel = LEVEL_TUTORIAL;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
	CSound_Manager::GetInstance()->PlaySound(L"Tutorial.wav", CSound_Manager::BGM, VOLUME);

	return S_OK;
}

void CLevel_Tutorial::Tick(_float fTimeDelta) {

	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGEONE)))) {
			return;
		}
	}
	
	Safe_Release(pGameInstance);

}

HRESULT CLevel_Tutorial::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("튜토리얼레벨입니다."));
	return S_OK;
}

HRESULT CLevel_Tutorial::Ready_Layer_Camera(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CCamera::CAMERADESC CameraDesc;
	ZeroMemory(&CameraDesc, sizeof(CCamera::CAMERADESC));

	CameraDesc.vEye = _float3(-7.f, 7.f, -7.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.vAxisY = _float3(0.f, 1.f, 0.f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 300.0f;
	CameraDesc.fFovy = D3DXToRadian(45.0f);
	CameraDesc.fAspect = (_float)g_iWinCX / g_iWinCY;

	CameraDesc.TransformDesc.fSpeedPerSec = 0.3f;
	CameraDesc.TransformDesc.fRotationPerSec = 10.f;
	CameraDesc.TransformDesc.fScalePerSec = 1.f;

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_MultiCamera"), &CameraDesc))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Camera");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tutorial::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Player"),&m_MapCube))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Player");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tutorial::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/TutorialMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, pLayerTag, L"Prototype_GameObject_Ground",&iter))) {
			MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tutorial::Ready_Layer_NPC(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(7.5f, 2.5f, 7.5f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, pLayerTag, TEXT("Prototype_GameObject_Magician"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tutorial::Ready_Layer_UI(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CPlayer* pPlayer = (CPlayer*)(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());


	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Hexagon_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Hexagon_UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_LSkillBox_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_LSkillBox_UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_RSkillBox_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_RSkillBox_UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_HP_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : HP_UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_MP_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : MP_UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_AlphaHP_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : AlphaHP_UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_AlphaMP_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : AlphaMP_UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_ExpBar_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : ExpBar_UI");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_ExpIng_UI")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : ExpIng_UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Exp_Invisible_UI"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : ExpIng_UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Exp_Text"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Exp_Text");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Exp_Text2"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Exp_Text2");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Exp_Text3")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Exp_Text3");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_PlayerName_UI"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : PlayerName_UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, TEXT("Layer_Mouse"), TEXT("Prototype_GameObject_Mouse_UI")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_UI");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_CoolDown"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : CoolDown");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_CoolDown3"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : CoolDown3");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_CoolDown4"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : CoolDown4");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_CoolDown5"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : CoolDown5");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_CoolDown6"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : CoolDown6");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_CoolDown7"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : CoolDown7");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_CoolDown8"), pPlayer))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : CoolDown8");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_Tutorial::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CNPC::NPC tNPC;
	tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
	tNPC.vPosition = _float3(17.f, 3.5f, 17.f);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, pLayerTag, TEXT("Prototype_GameObject_Portal"), &tNPC))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_NPC");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}



CLevel_Tutorial* CLevel_Tutorial::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_Tutorial* pInstance = new CLevel_Tutorial(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Tutorial::Free() {
	__super::Free();
}

HRESULT CLevel_Tutorial::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Load_Map");
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