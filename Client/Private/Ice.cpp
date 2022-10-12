#include "stdafx.h"
#include "..\Public\Ice.h"

CIce::CIce(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CIce::CIce(const CIce& rhs)
	:CEffect(rhs)
{
	m_tSkillFrame.fFrame = rhs.m_tSkillFrame.fFrame;
	m_tSkillFrame.iSpriteEnd = rhs.m_tSkillFrame.iSpriteEnd;
	m_fDamagePercent = rhs.m_fDamagePercent;
}

HRESULT CIce::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed Tp CIce : NativeConstruct_Prototype");
		return E_FAIL;
	}
	
	m_tSkillFrame.fFrame = 0.f;
	m_tSkillFrame.iSpriteEnd = 20;

	m_fDamagePercent = 3.f;

	return S_OK;
}

HRESULT CIce::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed Tp CIce : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed Tp CIce : NativeConstruct");
		return E_FAIL;
	}
	
	_float3 vPosition = *((_float3*)pArg);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPosition);

	m_eSkillID = SKILL_ICE;

	m_iDamage = _uint(m_pPlayer->Get_Player_Info().iAtt * m_fDamagePercent);

	m_pTransform->Scaled(_float3(2.5f, 2.5f, 2.5f));
	return S_OK;
}

void CIce::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
}

void CIce::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	BillBoard(m_pTransform);

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CIce::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed Tp CIce : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CIce::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(0.f);
	TransformDesc.fScalePerSec = 0.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CIce : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CIce : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CIce : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_Ice"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CIce : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CIce* CIce::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CIce* pInstance = new CIce(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CIce : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CIce::Clone(void* pArg) {
	CIce* pInstance = new CIce(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CIce : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CIce::Free() {
	__super::Free();
}