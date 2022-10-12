#include "stdafx.h"
#include "..\Public\Level_Loading.h"

CLevel_Loading::CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_Loading::NativeConstruct(LEVEL eNextLevel) {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Fialed To CLevel_Loading : NativeConstruct");
		return E_FAIL;
	}

	m_eNextLevel = eNextLevel;

	if (FAILED(Ready_Loading())) {
		MSG_BOX(L"Failed To CLevel_Logo : NativeConstruct");
		return E_FAIL;
	}

	

	m_pLoader = CLoader::Create(m_pGraphic_Device, eNextLevel);
	if (nullptr == m_pLoader) {
		MSG_BOX(L"Fialed To CLevel_Loading : NativeConstruct");
		return E_FAIL;
	}
	return S_OK;
}

void CLevel_Loading::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	if (true == m_pLoader->Get_Finished()) {

		CLevel* pLevel = nullptr;
		switch (m_eNextLevel) {
		case LEVEL_TUTORIAL:
			pLevel = CLevel_Tutorial::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGEONE:
			pLevel = CLevel_StageOne::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGETWO:
			pLevel = CLevel_StageTwo::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGETWO_1:
			pLevel = CLevel_StageTwo_1::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGETHREE:
			pLevel = CLevel_StageThree::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGEFOUR:
			pLevel = CLevel_StageFour::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGESEMIBOSS:
			pLevel = CLevel_StageSemiBoss::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGESEMIAFTER:
			pLevel = CLevel_StageSemiAfter::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGEFIVE:
			pLevel = CLevel_StageFive::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGESIX:
			pLevel = CLevel_StageSix::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGESEVEN:
			pLevel = CLevel_StageSeven::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGEEIGHT:
			pLevel = CLevel_StageEight::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGEBOSS:
			pLevel = CLevel_StageBoss::Create(m_pGraphic_Device);
			break;
		case LEVEL_STAGESPECIAL:
			pLevel = CLevel_StageSpecial::Create(m_pGraphic_Device);
			break;
		}
		if (FAILED(pGameInstance->OpenLevel(m_eNextLevel, pLevel))) {
			Safe_Release(pGameInstance);
			return;
	}

	}

	Safe_Release(pGameInstance);
}

HRESULT CLevel_Loading::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Fialed To CLevel_Loading : Render");
		return E_FAIL;
	}
	_tchar szText[MAX_PATH] = TEXT("");
	lstrcpy(szText, TEXT("로딩 레벨입니다"));
	SetWindowText(g_hWnd, szText);
	return S_OK;
}

HRESULT CLevel_Loading::Ready_Loading()
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_LDSPR0"), TEXT("Prototype_GameObject_LDSPR0")))) {
		MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDSPR0");
		return E_FAIL;
	}

	switch (m_eNextLevel)
	{
	case LEVEL_STAGEONE:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level1"), TEXT("Prototype_GameObject_LDLV1")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV1");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGETWO:
	case LEVEL_STAGETWO_1:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level2"), TEXT("Prototype_GameObject_LDLV2")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV2");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGETHREE:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level3"), TEXT("Prototype_GameObject_LDLV3")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV3");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGEFOUR:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level4"), TEXT("Prototype_GameObject_LDLV4")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV4");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGESEMIBOSS:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level4_1"), TEXT("Prototype_GameObject_LDLV4_1")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV4_1");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGESEMIAFTER:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Semi0"), TEXT("Prototype_GameObject_Semi0")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_Semi0");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGEFIVE:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level5"), TEXT("Prototype_GameObject_LDLV5")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV5");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGESIX:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level6"), TEXT("Prototype_GameObject_LDLV6")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV6");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGESEVEN:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level7"), TEXT("Prototype_GameObject_LDLV7")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV7");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGEEIGHT:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_Level8"), TEXT("Prototype_GameObject_LDLV8")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLV8");
			return E_FAIL;
		}
		break;
	case LEVEL_STAGEBOSS:
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_LOADING, TEXT("Layer_LevelBoss"), TEXT("Prototype_GameObject_LDLVBoss")))) {
			MSG_BOX(L"Failed To CLevel_Logo : Ready_Layer_LDLVBoss");
			return E_FAIL;
		}
		break;

	}

	Safe_Release(pGameInstance);
	return S_OK;
}

CLevel_Loading* CLevel_Loading::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel) {
	CLevel_Loading*	pInstance = new CLevel_Loading(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct(eNextLevel))) {
		MSG_BOX(L"Fialed To CLevel_Loading : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_Loading::Free() {
	__super::Free();
	Safe_Release(m_pLoader);
}