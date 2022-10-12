#pragma once
#include "Base.h"
#include "Level.h"
#include "Object_Manager.h"

BEGIN(Engine)

class CLevel_Manager final : public CBase {
	DECLARE_SINGLETON(CLevel_Manager)
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;
public:
	HRESULT OpenLevel(_uint iLevelIndex, CLevel* pLevel);
	void Tick(_float fTimeDelta);
	HRESULT Render();
public:
	HRESULT Clear_LevelResource(_uint iLevelIndex);
private:
	_uint m_iLevelIndex = 0;
	CLevel* m_pCurrentLevel = nullptr;
	CObject_Manager* m_pObject_Manager = nullptr;
public:
	virtual void Free() override;
};

END