#include "stdafx.h"
#include "..\Public\MiniNooNoo.h"

CMiniNooNoo::CMiniNooNoo(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CMiniNooNoo::CMiniNooNoo(const CMiniNooNoo & rhs)
	: CMonster(rhs)
{
}

HRESULT CMiniNooNoo::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMiniNooNoo : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 100000;
	m_tInfo.iAtt = 100;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_iDeadSprite = 3;

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CMiniNooNoo::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMiniNooNoo : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMiniNooNoo : NativeConstruct");
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

void CMiniNooNoo::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	Diving();
	m_pTransform->Go_Down(fTimeDelta);

	_float3 vTargetPos = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION);
	_float Dir = 0;

	Look_Player(vTargetPos, &Dir);

	if (true == m_bDamage && MONSTER_DEAD != m_eMState) {
		++m_iDamageTick;
		m_iSprite = 3;
		if (65 <= m_iDamageTick) {
			m_bDamage = false;
			m_iDamageTick = 0;
		}
	}
	_float3 f = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (-2.f >= f.y)
		m_eState = STATE_DEAD;
}

void CMiniNooNoo::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	++m_iTick;
	if (MONSTER_WALK == m_eMState) {
		if (0 == m_iTick % 7) {
			++m_iSprite;
			if (2 <= m_iSprite) {
				m_iSprite = 0;
			}
			m_iTick = 0;
		}
	}
	else if (m_eMState == MONSTER_DEAD) {
		if (0 == m_iTick % 7) {
			++m_iSprite;
			if (7 <= m_iSprite) {
				m_iSprite = 7;
				m_eState = STATE_DEAD;
			}
		}
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CMiniNooNoo::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMiniNooNoo : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CMiniNooNoo::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMiniNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_MiniNooNoo"), LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_MiniNooNoo"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMiniNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMiniNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMiniNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CMiniNooNoo : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CMiniNooNoo* CMiniNooNoo::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CMiniNooNoo*	pInstance = new CMiniNooNoo(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMiniNooNoo : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CMiniNooNoo::Clone(void* pArg) {
	CMiniNooNoo*	pInstance = new CMiniNooNoo(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMiniNooNoo : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMiniNooNoo::Free() {
	__super::Free();
}