#include "..\Public\Layer.h"

CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObject* pGameObject) {
	if (nullptr == pGameObject) {
		MSG_BOX(L"Failed To CLayer : Add_GameObject");
		return E_FAIL;
	}
	m_ObjectList.push_back(pGameObject);
	return S_OK;
}

void CLayer::Tick(_float fTimeDelta) {
	for (auto& pGameObject : m_ObjectList) {
		pGameObject->Tick(fTimeDelta);
	}
}

void CLayer::LateTick(_float fTimeDelta) {
	for (auto& iter = m_ObjectList.begin(); iter != m_ObjectList.end();) {
		(*iter)->LateTick(fTimeDelta);
		if (CGameObject::STATE_DEAD == (*iter)->Get_State()) {
			Safe_Release(*iter);
			iter = m_ObjectList.erase(iter);
		}
		else {
			++iter;
		}
	}
}

CComponent* CLayer::Get_Component(const _tchar* pComponentTag, _uint iIndex) {
	if (iIndex >= m_ObjectList.size()) {
		return nullptr;
	}
	auto iter = m_ObjectList.begin();

	for (_uint i = 0; i < iIndex; ++i) {
		++iter;
	}
	return (*iter)->Get_Component(pComponentTag);
}

list<class CGameObject*>* CLayer::Get_List()
{
	return &m_ObjectList;
}

CLayer* CLayer::Create() {
	return new CLayer();
}

void CLayer::Free() {
	for (auto& pGameObject : m_ObjectList) {
		Safe_Release(pGameObject);
	}
	m_ObjectList.clear();
}