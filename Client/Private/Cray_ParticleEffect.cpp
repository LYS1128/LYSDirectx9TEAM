#include "stdafx.h"
#include "..\Public\Cray_ParticleEffect.h"

CCray_ParticleEffect::CCray_ParticleEffect(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CCray_ParticleEffect::CCray_ParticleEffect(const CCray_ParticleEffect & rhs)
	:CGameObject(rhs)
{
}

HRESULT CCray_ParticleEffect::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBlood : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCray_ParticleEffect::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBlood : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBlood : NativeConstruct");
		return E_FAIL;
	}

	_float3 Pos = *((_float3*)pArg);
	m_fOriginPosY = Pos.y -0.5f;

	Rand = rand();

	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(Pos.x + 1.5f*((Rand%21)/20.f)*cos(Rand), Pos.y - 0.5f, Pos.z + 1.5f*((Rand %21) / 20.f)*sin(Rand)));
	m_pTransform->Scaled(_float3(0.05f-Rand%3*0.01f, 0.05f - Rand % 3 * 0.01f, 0.05f - Rand % 3 * 0.01f));
	
	return S_OK;
}

void CCray_ParticleEffect::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	m_fTickCount += 0.1f;
	if (m_fTickCount >=4.5f)
		m_eState = STATE_DEAD;

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (m_fTickCount < 2.5f)
		vPos.y += 0.05f*(2.5f-m_fTickCount);
	else if (m_fTickCount >= 2.5f)
	{
		if (m_pTransform->Get_State(CTransform::STATE_POSITION).y < m_fOriginPosY)
			m_tColl = true;
		if(m_tColl)
			vPos.y += 0.1f*(m_fTickCount - 2.5f);
		else
			vPos.y -= 0.08f*(m_fTickCount - 2.5f);
	}

	_float3 fGO = _float3(Rand % 5, Rand % 5, Rand % 5);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransform->Turn(fGO, fTimeDelta);
	//m_pTransform->Scaling(-fTimeDelta / 3);
}

void CCray_ParticleEffect::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CCray_ParticleEffect::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBlood : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(Rand %4+9))) {
		MSG_BOX(L"Failed To CBlood : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CBlood : Render");
		return E_FAIL;
	}

	m_pVIBuffer->Render();

	return S_OK;
}

HRESULT CCray_ParticleEffect::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 2.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CRain : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Particle"), (CComponent**)&m_pTexture))) {
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

CCray_ParticleEffect * CCray_ParticleEffect::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CCray_ParticleEffect*	pInstance = new CCray_ParticleEffect(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBlood : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCray_ParticleEffect::Clone(void * pArg) {
	CCray_ParticleEffect*	pInstance = new CCray_ParticleEffect(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBlood : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCray_ParticleEffect::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}