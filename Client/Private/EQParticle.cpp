#include "stdafx.h"
#include "..\Public\EQParticle.h"



CEQParticle::CEQParticle(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CEQParticle::CEQParticle(const CEQParticle & rhs)
	:CGameObject(rhs)
{
}

HRESULT CEQParticle::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CRain : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CEQParticle::NativeConstruct(void * pArg)
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
	_uint Rand = rand();

	m_pTransform->Scaled(_float3(0.1f, 0.1f, 0.1f));
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(Pos.x+cos(Rand),Pos.y-0.3f,Pos.z+ sin(Rand)));

	m_fGO = _float3(cos(Rand), (rand() % 11) / 10.f, sin(Rand));
	D3DXVec3Normalize(&m_fGO, &m_fGO);

	return S_OK;
}

void CEQParticle::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	++m_TickCount;
	if (m_TickCount >= 50)
		m_eState = STATE_DEAD;

	m_pTransform->Scaling(-fTimeDelta/5);


	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vPos += m_fGO * m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta*((rand() % 11) / 10.f);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
}

void CEQParticle::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CEQParticle::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(rand()%3+6))) {
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

HRESULT CEQParticle::SetUp_Components()
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

CEQParticle * CEQParticle::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CEQParticle*	pInstance = new CEQParticle(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSlime : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CEQParticle::Clone(void * pArg)
{
	CEQParticle*	pInstance = new CEQParticle(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSlime : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEQParticle::Free()
{
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}