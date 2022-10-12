#pragma once
#include "Base.h"
#include "GameObject.h"
#include "Layer.h"

BEGIN(Engine)

class CObject_Manager final : public CBase {
	DECLARE_SINGLETON(CObject_Manager)
private:
	CObject_Manager();
	virtual ~CObject_Manager() = default;
public:
	HRESULT Reserve_Manager(_uint iNumLevels);
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObjectToLayer(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pPrototypeTag, void* pArg);
	void Tick(_float fTimeDelta);
	void LateTick(_float fTimeDelta);
	HRESULT Clear(_uint iLevelIndex);
public:
	CComponent* Get_Component(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iIndex = 0);
public:
	CComponent* Find_Component(const _tchar* pComponentTag); 
	CGameObject* Find_Prototype(const _tchar* pPrototypeTag);
	CLayer* Find_Layer(_uint iLevelIndex, const _tchar* pLayerTag);
	list<CGameObject*>* Find_Layer_List(_uint iLevelIndex, const _tchar* pLayerTag);
private:
	map<const _tchar*, class CGameObject*> m_Prototypes;
	typedef map<const _tchar*, class CGameObject*> PROTOTYPES;
private:
	map<const _tchar*, class CLayer*>* m_pLayers = nullptr;
	typedef map<const _tchar*, class CLayer*> LAYERS;
private:
	_uint m_iNumLevels = 0;
public:
	virtual void Free() override;
};

END