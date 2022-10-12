#pragma once
#include "Client_Define.h"
#include "GameInstance.h"
#include "Player.h"
#include "Text.h"

BEGIN(Client)

class CQuest final : public CText {
public:
	typedef struct tagQuest {
		FONT tFont;
		_uint iRequireMonsterCnt;
		_uint iOption;
	}QUEST;
protected:
	explicit CQuest(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CQuest(const CQuest& rhs);
	virtual ~CQuest() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	void Set_MonsterCnt();
	_uint Get_MonsterCnt() { return m_iMonsterCnt; }
	_bool Get_Complete() { return m_bComplete; }
private:
	QUEST m_tQuest;
	_tchar m_szQuest[256] = L"";
	_uint m_iMonsterCnt = 0;
	_bool m_bComplete = false;
public:
	static CQuest* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;
};

END