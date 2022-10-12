#include "stdafx.h"
#include "..\Public\FireParticle.h"



CFireParticle::CFireParticle(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CFireParticle::CFireParticle(const CFireParticle & rhs)
	:CGameObject(rhs)
{
}

HRESULT CFireParticle::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CRain : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CFireParticle::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CRain : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CRain : NativeConstruct");
		return E_FAIL;
	}

	_float3 Pos = *((_float3*)pArg);
	m_pTransform->Scaled(_float3(0.1f, 0.1f, 0.1f));

	_float3 PosVec = _float3(rand()%10-5.f,rand()%10-5.f,rand()%10-5.f);
	D3DXVec3Normalize(&PosVec,&PosVec);
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(Pos.x+PosVec.x,Pos.y + PosVec.y,Pos.z + PosVec.z));

	return S_OK;
}

void CFireParticle::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	++m_TickCount;
	if (m_TickCount >= 30)
		m_eState = STATE_DEAD;

	m_pTransform->Scaling(-fTimeDelta/5);
	_float3 fGO = _float3(Rand % 5, Rand % 5, Rand % 5);
	m_pTransform->Turn(fGO, fTimeDelta);
}

void CFireParticle::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CFireParticle::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(rand()%3+21))) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}


	m_pVIBuffer->Render();


	return S_OK;
}

HRESULT CFireParticle::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 7.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Particle"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Particle"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Cube", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CFireParticle * CFireParticle::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CFireParticle*	pInstance = new CFireParticle(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSlime : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFireParticle::Clone(void * pArg)
{
	CFireParticle*	pInstance = new CFireParticle(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSlime : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFireParticle::Free()
{
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}
