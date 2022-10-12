#include "..\Public\Level_Manager.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CLevel_Manager)

CLevel_Manager::CLevel_Manager()
	:m_pObject_Manager(CObject_Manager::GetInstance())
{
	Safe_AddRef(m_pObject_Manager);
}

HRESULT CLevel_Manager::OpenLevel(_uint iLevelIndex, CLevel* pLevel) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if(nullptr != m_pCurrentLevel) {
		if (FAILED(Clear_LevelResource(m_iLevelIndex))) {
			MSG_BOX(L"Failed To CLevel_Manager : OpenLevel");
			return E_FAIL;
		}
	}

	Safe_Release(m_pCurrentLevel);
	
	m_pCurrentLevel = pLevel;

	m_iLevelIndex = iLevelIndex;

	Safe_Release(pGameInstance);

	return S_OK;
}

void CLevel_Manager::Tick(_float fTimeDelta) {
	if (nullptr == m_pCurrentLevel) {
		return;
	}
	m_pCurrentLevel->Tick(fTimeDelta);
}

HRESULT CLevel_Manager::Render() {
	if (nullptr == m_pCurrentLevel) {
		MSG_BOX(L"Failed To CLevel_Manager : Render");
		return E_FAIL;
	}
	return m_pCurrentLevel->Render();
}

HRESULT CLevel_Manager::Clear_LevelResource(_uint iLevelIndex) {
	if (nullptr == m_pObject_Manager) {
		MSG_BOX(L"Failed To CLevel_Manager : Clear_LevelResource");
		return E_FAIL;
	}
	if (FAILED(m_pObject_Manager->Clear(iLevelIndex))) {
		MSG_BOX(L"Failed To CLevel_Manager : Clear_LevelResource");
		return E_FAIL;
	}
	return S_OK;
}

void CLevel_Manager::Free() {
	Safe_Release(m_pObject_Manager);
	Safe_Release(m_pCurrentLevel);
}
