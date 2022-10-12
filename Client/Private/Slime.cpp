#include "stdafx.h"
#include "..\Public\Slime.h"

CSlime::CSlime(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CSlime::CSlime(const CSlime & rhs)
	: CMonster(rhs)
{
}

HRESULT CSlime::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CSlime : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 50;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_tInfo.iAtt = 18;
	m_iDeadSprite = 9;

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CSlime::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CSlime : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CSlime : NativeConstruct");
		return E_FAIL;
	}

	CShadow::SHADOW tShadow;
	tShadow.mapCube = m_tMonster.mapCube;
	tShadow.pTargetTransform = m_pTransform;
	tShadow.pMyMonster = this;

	m_tMonster.m_eKind = CMonster::MONSTER_COKEMUSH;


	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Shadow", L"Prototype_GameObject_Shadow", &tShadow))) {
		MSG_BOX(L"Failed To CSlime : NativeConstruct");
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

	m_pTransform->Scaled(_float3(1.51f,2.51f, 1.51f));

	CMonsterHpBar::MONSTERINFO tMonsterInfo;
	tMonsterInfo.pMonster = this;
	tMonsterInfo.vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_MonsterHp", L"Prototype_GameObject_MonsterHpBar", &tMonsterInfo))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	CMonsterRealHp::MONSTERINFO tMonsterInfoReal;
	tMonsterInfoReal.pMonster = this;
	tMonsterInfoReal.vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_MonsterHp", L"Prototype_GameObject_MonsterRealHp", &tMonsterInfoReal))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	m_iSprite = 2;
	return S_OK;
}

void CSlime::Tick(_float fTimeDelta) {

	__super::Tick(fTimeDelta);

	Diving();

	_float3 vTargetPos = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION);
	_float Dir = 0;

	Look_Player(vTargetPos, &Dir);

	if (false == m_bDamage) {
		if (Dir <= 3.f) {
			m_eMState = MONSTER_WALK;
			m_bTargeting = true;
			m_pTransform->Chase(vTargetPos, fTimeDelta, 1.f);
		}
		else {
			m_bTargeting = false;
		}

		if (false == m_bTargeting) {
			Random_Move(fTimeDelta);
		}
	}
	else if (true == m_bDamage && MONSTER_DEAD != m_eMState) {
		++m_iDamageTick;
		m_iSprite = 9;
		if (65 <= m_iDamageTick) {
			m_bDamage = false;
			m_iDamageTick = 0;
		}
	}

}

void CSlime::LateTick(_float fTimeDelta) {

	__super::LateTick(fTimeDelta);
	++m_iTick;
	if (MONSTER_WALK == m_eMState) {
		if (0 == m_iTick % 7) {
			++m_iSprite;
			if (8 <= m_iSprite) {
				m_iSprite = 2;
			}
			m_iTick = 0;
		}
	}
	else if (MONSTER_IDLE == m_eMState) {
		if (0 == m_iTick % 20) {
			++m_iSprite;
			if (2 <= m_iSprite) {
				m_iSprite = 0;
			}
			m_iTick = 0;
		}
	}
	else if (m_eMState == MONSTER_HIT) {
		if (0 == m_iTick % 10) {
			++m_iSprite;
			if (10 <= m_iSprite) {
				m_iSprite = 9;
			}
		}
	}
	else if (m_eMState == MONSTER_DEAD) {
		if (0 == m_iTick % 10) {
			++m_iSprite;
			if (18 <= m_iSprite) {
				m_iSprite = 17;
				Drop_Item();
				m_eState = STATE_DEAD;

				CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());
				pPlayer->Exp_Plus(30);

				Quest();
			}
		}
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

}

HRESULT CSlime::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CSlime::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureSlime"), LEVEL_STAGETWO, TEXT("Prototype_Component_Texture_Slime"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CSlime : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CSlime* CSlime::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CSlime*	pInstance = new CSlime(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSlime : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CSlime::Clone(void* pArg) {
	CSlime*	pInstance = new CSlime(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSlime : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CSlime::Free() {
	__super::Free();
}