#pragma once
#include "Client_Define.h"
#include "GameObject.h"
#include "GameInstance.h"


BEGIN(Client)
class CMonster;

class CShadow final : public CGameObject {
public:
	typedef struct tagShadow {
		map<const _uint, _float4> mapCube;
		CTransform* pTargetTransform;
		CMonster* pMyMonster;
	}SHADOW;
private:
	explicit CShadow(LPDIRECT3DDEVICE9 pGraphic_Device);
	CShadow(const CShadow& rhs);
	virtual ~CShadow() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render();
private:
	HRESULT SetUp_Components();
private:
	CTransform* m_pTransformCom = nullptr;
	CVIBuffer_Rect* m_pVIBufferCom = nullptr;
	CTexture* m_pTextureCom = nullptr;
	CRenderer* m_pRendererCom = nullptr;
private:
	SHADOW m_tShadow;
public:
	static CShadow* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg) override;
	virtual void Free() override;

public:
	void Set_Map(map<const _uint, _float4> Map) { m_tShadow.mapCube = Map; }
};

END