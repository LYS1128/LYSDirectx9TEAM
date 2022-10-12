#include "stdafx.h"
#include "..\Public\Boss_JJol.h"

CBoss_JJol::CBoss_JJol(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBoss_JJol::CBoss_JJol(const CBoss_JJol & rhs)
	: CMonster(rhs)
{
}

HRESULT CBoss_JJol::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_JJol : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 1000;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_iDeadSprite = 0;

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CBoss_JJol::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss_JJol : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBoss_JJol : NativeConstruct");
		return E_FAIL;
	}

	

	m_pTransform->Set_State(CTransform::STATE_POSITION, ((MONSTER*)pArg)->vPosition);
	m_fOriginPos = ((MONSTER*)pArg)->vPosition;

	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_pTransform->Set_State(CTransform::STATE_UP, _float3(0.f, 1.f, 0.f));

	m_pTransform->Scaled(_float3(1.01f, 1.51f, 1.01f));


	m_iSprite = 0;
	return S_OK;
}

void CBoss_JJol::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	_float3 vTargetPos = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION);
	_float Dir = 0;

	++m_iTick;
	if (m_iTick == 6)
	{
		m_iTick = 0;
		++m_iSprite;		
	}
}

void CBoss_JJol::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);

	if (m_iSprite >= 8)
		m_eState = STATE_DEAD;

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CBoss_JJol::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBoss_JJol : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_JJol::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_JJol : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Electric_Shock"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Electric_Shock"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBoss_JJol : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBoss_JJol : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBoss_JJol : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CBoss_JJol : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CBoss_JJol* CBoss_JJol::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBoss_JJol*	pInstance = new CBoss_JJol(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBoss_JJol : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBoss_JJol::Clone(void* pArg) {
	CBoss_JJol*	pInstance = new CBoss_JJol(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBoss_JJol : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBoss_JJol::Free() {
	__super::Free();
}