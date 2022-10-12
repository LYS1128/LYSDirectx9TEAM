#include "stdafx.h"
#include "..\Public\ShieldParticle.h"

CShieldParticle::CShieldParticle(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CShieldParticle::CShieldParticle(const CShieldParticle & rhs)
	: CGameObject(rhs)
{
}

HRESULT CShieldParticle::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CShieldParticle : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CShieldParticle::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CShieldParticle : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CShieldParticle : NativeConstruct");
		return E_FAIL;
	}

	_float3 Pos = *((_float3*)pArg);
	m_iRand = rand();

	m_pTransform->Scaled(_float3(0.001f+0.0005*(m_iRand%2), 0.001f+ 0.0005*(m_iRand % 2), 0.001f +0.0005*(m_iRand % 2)));
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(Pos.x-0.5f, Pos.y, Pos.z-0.5f));

	//m_fGO = _float3(0.3f, 0.3f, 0.3f);
	m_fGO = _float3((rand() % 11 -5) / 10.f, (rand() % 11 - 5) / 10.f, (rand() % 11 - 5) / 10.f);
	D3DXVec3Normalize(&m_fGO, &m_fGO);
	
	return S_OK;
}

void CShieldParticle::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	++m_TickCount;
	if (m_TickCount >= 20)
		m_eState = STATE_DEAD;

	m_pTransform->Turn(m_fGO, fTimeDelta);
	m_pTransform->Scaling(-fTimeDelta/10);

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	//vPos += m_fGO*m_pTransform->Get_TransDesc().fSpeedPerSec*fTimeDelta/ 5.f;
	vPos += m_fGO*m_pTransform->Get_TransDesc().fRotationPerSec* fTimeDelta*((m_iRand % 100) / 10.f);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
}

void CShieldParticle::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CShieldParticle::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CShieldParticle : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iRand%2+15))) {
		MSG_BOX(L"Failed To CShieldParticle : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CShieldParticle : Render");
		return E_FAIL;
	}


	m_pVIBuffer->Render();


	return S_OK;
}

HRESULT CShieldParticle::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 10.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 30.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CShieldParticle : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Particle"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Particle"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CShieldParticle : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Cube", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CShieldParticle : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CShieldParticle : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CShieldParticle * CShieldParticle::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CShieldParticle*	pInstance = new CShieldParticle(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CShieldParticle : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CShieldParticle::Clone(void * pArg)
{
	CShieldParticle*	pInstance = new CShieldParticle(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CShieldParticle : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShieldParticle::Free()
{
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}
