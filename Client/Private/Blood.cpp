#include "stdafx.h"
#include "..\Public\Blood.h"

CBlood::CBlood(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CBlood::CBlood(const CBlood & rhs)
	:CGameObject(rhs)
{
}

HRESULT CBlood::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBlood : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBlood::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBlood : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBlood : NativeConstruct");
		return E_FAIL;
	}

	_float3 Pos = *((_float3*)pArg);
	m_fOriginPosY = Pos.y;

	m_pTransform->Set_State(CTransform::STATE_POSITION, Pos);
	m_pTransform->Scaled(_float3(0.15f + 0.05f*(m_iRand%2), 0.15f + 0.05f*(m_iRand % 2), 0.15f + 0.05f*(m_iRand % 2)));
	//m_pTransform->Scaled(_float3(1.f, 1.f, 1.f));
	m_fGO = _float3(cos(m_iRand), m_iRand % 3+1, sin(m_iRand));
	D3DXVec3Normalize(&m_fGO, &m_fGO);

	return S_OK;
}

void CBlood::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	m_fTickCount += 0.1f;
	if (m_fTickCount >= 3.f)
		m_eState = STATE_DEAD;

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	vPos += m_fGO*0.3;
	vPos.y -= ((1.f * pow(m_fTickCount, 2)) * 0.5f);

	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
	m_pTransform->Scaling(-fTimeDelta);
}

void CBlood::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CBlood::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBlood : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(17))) {
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

HRESULT CBlood::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

		TransformDesc.fSpeedPerSec = 1.f;

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

CBlood * CBlood::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBlood*	pInstance = new CBlood(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBlood : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBlood::Clone(void * pArg) {
	CBlood*	pInstance = new CBlood(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBlood : CRain"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBlood::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}