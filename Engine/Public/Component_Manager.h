#pragma once
#include "Base.h"
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Renderer.h"
#include "VIBuffer.h"
#include "VIBuffer_Rect.h"
#include "VIBuffer_Cube.h"
#include "Collision.h"

BEGIN(Engine)

class CComponent_Manager final : public CBase {
	DECLARE_SINGLETON(CComponent_Manager)
private:
	CComponent_Manager();
	virtual ~CComponent_Manager() = default;
public:
	HRESULT Reserve_Manager(_uint iNumLevels);
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, CComponent* pPrototype);
	CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg);
private:
	CComponent* Find_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag);
private:
	_uint m_iNumLevels = 0;
	map<const _tchar*, CComponent*>* m_pPrototypes = nullptr;
	typedef map<const _tchar*, CComponent*> PROTOTYPES;
public:
	virtual void Free() override;
};

END