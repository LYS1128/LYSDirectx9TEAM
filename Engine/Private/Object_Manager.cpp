#include "..\Public\Object_Manager.h"

IMPLEMENT_SINGLETON(CObject_Manager)

CObject_Manager::CObject_Manager()
{
}

HRESULT CObject_Manager::Reserve_Manager(_uint iNumLevels) {
	if (0 != m_iNumLevels) {
		MSG_BOX(L"Failed To CObject_Manager : Reserve_Manager");
		return E_FAIL;
	}
	m_pLayers = new LAYERS[iNumLevels];
	m_iNumLevels = iNumLevels;
	return S_OK;
}

HRESULT CObject_Manager::Add_Prototype(const _tchar* pPrototypeTag, CGameObject* pPrototype) {
	if (nullptr == pPrototype || nullptr != Find_Prototype(pPrototypeTag)) {
		MSG_BOX(L"Failed To CObject_Manager : Add_Prototype");
		return E_FAIL;
	}
	m_Prototypes.insert(PROTOTYPES::value_type(pPrototypeTag, pPrototype));	
	return S_OK;
}

HRESULT CObject_Manager::Add_GameObjectToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg) {
	CGameObject* pPrototype = Find_Prototype(pPrototypeTag);
	if (nullptr == pPrototype) {
		MSG_BOX(L"Failed To CObject_Manager : Add_GameObjectToLayer1");
		return E_FAIL;
	}
	CGameObject* pGameObject = pPrototype->Clone(pArg);
	if (nullptr == pGameObject) {
		MSG_BOX(L"Failed To CObject_Manager : Add_GameObjectToLayer2");
		return E_FAIL;
	}
	CLayer*	pLayer = Find_Layer(iLevelIndex, pLayerTag);

	if (nullptr == pLayer) {
		pLayer = CLayer::Create();
		if (nullptr == pLayer) {
			MSG_BOX(L"Failed To CObject_Manager : Add_GameObjectToLayer3");
			return E_FAIL;
		}
		if (FAILED(pLayer->Add_GameObject(pGameObject))) {
			MSG_BOX(L"Failed To CObject_Manager : Add_GameObjectToLayer4");
			return E_FAIL;
		}
		m_pLayers[iLevelIndex].insert(LAYERS::value_type(pLayerTag, pLayer));
	}
	else {
		pLayer->Add_GameObject(pGameObject);
	}
	return S_OK;
}

void CObject_Manager::Tick(_float fTimeDelta) {
	for (_uint i = 0; i < m_iNumLevels; ++i) {
		for (auto& Pair : m_pLayers[i]) {
			Pair.second->Tick(fTimeDelta);
		}
	}
}

void CObject_Manager::LateTick(_float fTimeDelta) {
	for (_uint i = 0; i < m_iNumLevels; ++i) {
		for (auto& Pair : m_pLayers[i]) {
			Pair.second->LateTick(fTimeDelta);
		}
	}
}

HRESULT CObject_Manager::Clear(_uint iLevelIndex) {
	if (iLevelIndex >= m_iNumLevels) {
		MSG_BOX(L"Failed To CObject_Manager : Clear");
		return E_FAIL;
	}
	for (auto& Pair : m_pLayers[iLevelIndex]) {
		Safe_Release(Pair.second);
	}
	m_pLayers[iLevelIndex].clear();
	return S_OK;
}

CComponent* CObject_Manager::Get_Component(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex) {
	if (iLevelIndex >= m_iNumLevels) {
		return nullptr;
	}
	CLayer* pLayer = Find_Layer(iLevelIndex, pLayerTag);
	if (nullptr == pLayer) {
		return nullptr;
	}
	return pLayer->Get_Component(pComponentTag, iIndex);
}

CComponent * CObject_Manager::Find_Component(const _tchar * pComponentTag)
{
	return nullptr;
}

CGameObject* CObject_Manager::Find_Prototype(const _tchar* pPrototypeTag) {
	auto Pair = find_if(m_Prototypes.begin(), m_Prototypes.end(), CTagFinder(pPrototypeTag));
	if (Pair == m_Prototypes.end()) {
		return nullptr;
	}
	return Pair->second;
}

CLayer* CObject_Manager::Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag) {
	if (iLevelIndex >= m_iNumLevels) {
		return nullptr;
	}
	auto Pair = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTagFinder(pLayerTag));
	if (Pair == m_pLayers[iLevelIndex].end()) {
		return nullptr;
	}
	return Pair->second;
}

list<CGameObject*>* CObject_Manager::Find_Layer_List(_uint iLevelIndex, const _tchar * pLayerTag)
{
	if (iLevelIndex >= m_iNumLevels) {
		return nullptr;
	}
	auto Pair = find_if(m_pLayers[iLevelIndex].begin(), m_pLayers[iLevelIndex].end(), CTagFinder(pLayerTag));
	if (Pair == m_pLayers[iLevelIndex].end()) {
		return nullptr;
	}
	return Pair->second->Get_List();
}

void CObject_Manager::Free() {
	for (_uint i = 0; i < m_iNumLevels; ++i) {
		for (auto& Pair : m_pLayers[i]) {
			Safe_Release(Pair.second);
		}
		m_pLayers[i].clear();
	}
	Safe_Delete_Array(m_pLayers);

	for (auto& Pair : m_Prototypes) {
		Safe_Release(Pair.second);
	}
	m_Prototypes.clear();
}