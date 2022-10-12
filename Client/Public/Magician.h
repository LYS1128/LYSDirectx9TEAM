#pragma once
#include "Client_Define.h"
#include "NPC.h"
#include "TextWindow.h"
#include "QuestWindow.h"
#include "Portal.h"

BEGIN(Client)


class CMagician final : public CNPC
{
private:
	explicit CMagician(LPDIRECT3DDEVICE9 pGraphic_Device);
	CMagician(const CMagician& rhs);
	virtual ~CMagician() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
public:
	HRESULT SetUp_Components();
	_uint m_iTick = 0, m_iSprite = 0;
	_uint m_iTextSprite = 0;
	_uint m_iTalkState = 0; //0���� �� �Ȱ� ���� 1�ѹ� �� �� ���� 2����Ʈ�� �Ϸ��� ����
public:
	static CMagician* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free();
};

END