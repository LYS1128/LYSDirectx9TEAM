#pragma once
#include "Client_Define.h"
#include "UI.h"
#include "Sound_Manager.h"

BEGIN(Client)

class CQuiz_UI final : public CUI
{
public:
	explicit CQuiz_UI(LPDIRECT3DDEVICE9 pGrpahic_Device);
	CQuiz_UI(const CQuiz_UI& rhs);
	virtual ~CQuiz_UI() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	_uint m_iQuizCount = 0;
	_bool m_bCheck = false;

public:
	static CQuiz_UI* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

};

END