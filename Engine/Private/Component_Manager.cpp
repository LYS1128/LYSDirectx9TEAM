#include "..\Public\Component_Manager.h"

IMPLEMENT_SINGLETON(CComponent_Manager)

CComponent_Manager::CComponent_Manager()
{
}

HRESULT CComponent_Manager::Reserve_Manager(_uint iNumLevels) {
	if (0 != m_iNumLevels) {
		MSG_BOX(L"Failed To CComponent_Manager : Reserve_Manager");
		return E_FAIL;
	}
	m_pPrototypes = new PROTOTYPES[iNumLevels];
	m_iNumLevels = iNumLevels;
	return S_OK;
}

HRESULT CComponent_Manager::Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype) {
	if (nullptr == m_pPrototypes || nullptr != Find_Prototype(iLevelIndex, pPrototypeTag)) {
		MSG_BOX(L"Failed To CComponent_Manager : Add_Prototype");
		return E_FAIL;
	}
	m_pPrototypes[iLevelIndex].insert(PROTOTYPES::value_type(pPrototypeTag, pPrototype));	
	return S_OK;
}

CComponent* CComponent_Manager::Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg) {
	if (nullptr == m_pPrototypes) {
		return nullptr;
	}

	CComponent* pPrototype = Find_Prototype(iLevelIndex, pPrototypeTag);
	if (nullptr == pPrototype) {
		return nullptr;
	}
	return pPrototype->Clone(pArg);	
}

CComponent* CComponent_Manager::Find_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag) {
	auto Pair = find_if(m_pPrototypes[iLevelIndex].begin(), m_pPrototypes[iLevelIndex].end(), CTagFinder(pPrototypeTag));
	if (Pair == m_pPrototypes[iLevelIndex].end()) {
		return nullptr;
	}
	return Pair->second;
}

void CComponent_Manager::Free() {
	for (_uint i = 0; i < m_iNumLevels; ++i) {
		for (auto& Pair : m_pPrototypes[i]) {
			Safe_Release(Pair.second);
		}
		m_pPrototypes[i].clear();
	}
	Safe_Delete_Array(m_pPrototypes);
}