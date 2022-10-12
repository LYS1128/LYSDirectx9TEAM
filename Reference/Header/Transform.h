#pragma once
#include "Component.h"
#include "Shader.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent{
public:
	enum STATE { STATE_RIGHT, STATE_UP, STATE_LOOK, STATE_POSITION, STATE_END };
public:
	typedef struct tagTransformDesc {
		_float fSpeedPerSec;
		_float fRotationPerSec;
		_float fScalePerSec;
	}TRANSFORMDESC;
private:
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;
public:
	virtual HRESULT NativeConstruct_Prototype();
	virtual HRESULT NativeConstruct(void* pArg);
public:
	_float3 Get_State(STATE eState);
	_float3 Get_Scale();
	_float4x4 Get_WorldMatrix();
	TRANSFORMDESC Get_TransDesc();
	void Set_State(STATE eState, const _float3& vState);
	void Set_WorldMatrix(_float4x4 WorldMatrix);
	void Set_TransformState(const TRANSFORMDESC& TransformDesc);
public:
	HRESULT Bind_OnGraphicDevice() const;
	HRESULT Bind_OnShader(class CShader* pShader, D3DXHANDLE hParameters);
public:
	HRESULT Go_Straight(_float fTimeDelta);
	HRESULT Go_BackWard(_float fTimeDelta);
	HRESULT Go_Right(_float fTimeDelta);
	HRESULT Go_Left(_float fTimeDelta);
	HRESULT Go_UpLeft(_float fTimeDelta);
	HRESULT Go_UpRight(_float fTimeDelta);
	HRESULT Go_DownLeft(_float fTimeDelta);
	HRESULT Go_DownRight(_float fTimeDelta);

	HRESULT Go_Up(_float fTimeDelta);

	HRESULT Go_Down(_float fTimeDelta);

	HRESULT Scaled(_float3 vScale);
	HRESULT Scaling(_float fTimeDelta);

	HRESULT TextureTurn();
	HRESULT Turn(const _float3& vAxis, _float fTimeDelta);
	HRESULT Chase(const _float3& vTargetPos, _float fTimeDelta, _float fLimitDistance = 1.f);
	HRESULT LookAt(const _float3& vTargetPos);

	HRESULT MoveOnTerrain(_float3* pVertex, _float fTimeDelta);
private:
	_float4x4 m_WorldMatrix;
	TRANSFORMDESC m_tTransformDesc;
public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END