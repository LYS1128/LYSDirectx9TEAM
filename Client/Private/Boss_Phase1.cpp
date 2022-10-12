#include "stdafx.h"
#include "..\Public\Boss_Phase1.h"

CBoss_Phase1::CBoss_Phase1(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBoss_Phase1::CBoss_Phase1(const CBoss_Phase1 & rhs)
	:CMonster(rhs)
{
}

HRESULT CBoss_Phase1::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Phase1 : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Phase1::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBoss : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossHp", L"Prototype_GameObject_UI_BossHpBar", this))) {
		MSG_BOX(L"Failed To CBoss : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossHp", L"Prototype_GameObject_UI_BossHpReal", this))) {
		MSG_BOX(L"Failed To CBoss : NativeConstruct");
		return E_FAIL;
	}
	m_iDeadSprite = 27;
	//보스 정보 정하기
	m_tInfo.iAtt = 150;
	m_tInfo.iDef = 0;
	m_tInfo.iMaxHp = 5000;
	m_tInfo.iHp = m_tInfo.iMaxHp;

	m_tMonster.m_eKind = CMonster::MONSTER_NOONOO;


	//보스 위치 정하기
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(8.f, 10.f, 8.f));
	m_fOriginPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	//보스 크기 정하기
	m_pTransform->Scaled(_float3(5.f, 5.f, 5.f));

	return S_OK;
}

void CBoss_Phase1::Tick(_float fTimeDelta) {
	if (m_Grav != 2) {
		Gravity(fTimeDelta);
	}
	Diving();
	Collision_Ground();
	Skill_Tick();

	if (false == m_bDamage && false == m_bAttack) {
		Skill_Patern();
	}
	if (m_iMeteorCool * 60 == m_iMeteorTick) {
		m_iMeteorTick = 0;
		for (int i = 0; i < rand() % 5 + 1; ++i) {
			m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_Boss_Meteor");
		}
	}
}

void CBoss_Phase1::LateTick(_float fTimeDelta) {
	Sprite_Frame();

	if (true == m_bDamage && MONSTER_DEAD != m_eMState && MONSTER_ATK != m_eMState) {
		++m_iDamageTick;
		if (60 <= m_iDamageTick) {
			m_iDamageTick = 0;
			m_bDamage = false;
		}
	}
	else if (true == m_bDamage && MONSTER_DEAD != m_eMState) {
		++m_iDamageTick;
		m_eMState = MONSTER_HIT;
		if (60 <= m_iDamageTick) {
			m_iDamageTick = 0;
			m_bDamage = false;
		}
	}
	else if (false == m_bDamage && false == m_bAttack) {
		m_eMState = MONSTER_IDLE;
	}
	Damaged();
	BillBoard(m_pTransform);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CBoss_Phase1::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBoss_Phase1 : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Phase1::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Phase1"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

void CBoss_Phase1::Skill_Patern() {
	m_vTargetLook = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION) - m_pTransform->Get_State(CTransform::STATE_POSITION);
	m_vTargetLook.y = 0.f;
	m_fTargetDis = D3DXVec3Length(&m_vTargetLook);

	if (3.f <= m_fTargetDis && 5.f > m_fTargetDis && m_iMabubjinCool * 60 == m_iMabubjinTick) {
		m_iMabubjinTick = 0;
		m_iSprite = 7;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_MABUBJIN;
		m_bAttack = true;
	}
	else if (5.f <= m_fTargetDis && 7.f > m_fTargetDis && m_iFireBallCool * 60 == m_iFireBallTick) {
		m_iFireBallTick = 0;
		m_iSprite = 15;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_FIREBALL;
		m_bAttack = true;
	}
	else if(0.f <= m_fTargetDis && 3.f > m_fTargetDis && m_iClawCool * 60 == m_iClawTick) {
		m_iClawTick = 0;
		m_iSprite = 22;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_CLAW;
		m_bAttack = true;
	}
}

void CBoss_Phase1::Skill_Tick() {
	if (m_iClawCool * 60 > m_iClawTick) {
		++m_iClawTick;
	}
	if (m_iFireBallCool * 60 > m_iFireBallTick) {
		++m_iFireBallTick;
	}
	if (m_iMabubjinCool * 60 > m_iMabubjinTick) {
		++m_iMabubjinTick;
	}
	if (m_iMeteorCool * 60 > m_iMeteorTick) {
		++m_iMeteorTick;
	}
}

void CBoss_Phase1::Sprite_Frame() {
	++m_iTick;
	if (15 <= m_iTick) {
		m_iTick = 0;
		++m_iSprite;
		if (MONSTER_IDLE == m_eMState && 2 <= m_iSprite) {
			m_iSprite = 0;
		}
		else if (MONSTER_ATK == m_eMState) {
			if (ATTACK_CLAW == m_eAttack && 25 == m_iSprite) {
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_Boss_Claw_Attack", &(m_pTransform->Get_State(CTransform::STATE_POSITION)));
			}
			else if (ATTACK_CLAW == m_eAttack && 26 <= m_iSprite) {
				m_iSprite = 22;
				m_bAttack = false;
			}
			else if (ATTACK_FIREBALL == m_eAttack && 21 <= m_iSprite) {
				m_iSprite = 15;
				m_bAttack = false;

				BOSSPATERN tBossPatern;
				tBossPatern.vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
				tBossPatern.vTargetLook = m_vTargetLook;
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_Boss_FireBall_Attack", &tBossPatern);
			}
			else if (ATTACK_MABUBJIN == m_eAttack && 15 <= m_iSprite) {
				_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
				vPos.y -= m_pTransform->Get_Scale().y * 0.4f;
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkillCasting", L"Prototype_GameObject_Boss_Mabubjin", &vPos);
				m_iSprite = 7;
				m_bAttack = false;
			}
		}
		else if (MONSTER_HIT == m_eMState && 27 <= m_iSprite) {
			m_iSprite = 26;
			m_bAttack = false;
		}
		else if (MONSTER_DEAD == m_eMState && 30 <= m_iSprite) {
			m_iSprite = 26;
			m_eState = STATE_DEAD;
		}
	}
}

void CBoss_Phase1::Damaged() {
	list<CGameObject*>* pSkillList = m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Effect");
	if (nullptr != pSkillList) {
		for (auto& iter : *pSkillList) {
			CTransform* pSkillTransform = (CTransform*)(iter->Get_Component(L"Com_Transform"));
			_float3 vSkillPosition = pSkillTransform->Get_State(CTransform::STATE_POSITION);
			_float3 vSkillScale = pSkillTransform->Get_Scale();

			_float3 vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
			_float3 vColScale = _float3(1.f, m_pTransform->Get_Scale().y, 1.f);

			_float fDis = sqrtf(pow(vSkillPosition.x - vPosition.x, 2) + pow(vSkillPosition.z - vPosition.z, 2));
			if (false == m_bDamage && fDis < 2.f && vSkillPosition.y < vPosition.y + vColScale.y * 0.5f && vSkillPosition.y > vPosition.y - vColScale.y ) {
				_uint iDamage = ((CEffect*)iter)->Get_Damage() - m_tInfo.iDef;
				m_tInfo.iHp -= iDamage;
				Write_Damage(iDamage);
				m_bDamage = true;

				CHit_Effect::HIT tHit;
				tHit.vPoisition = m_pTransform->Get_State(CTransform::STATE_POSITION);
				tHit.eHitType = ((CEffect*)iter)->Get_SkillID();

				m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_Hit_Effect", &tHit);

				if (0 >= m_tInfo.iHp) {
					m_tInfo.iHp = 0;
					m_iSprite = m_iDeadSprite;
					m_eMState = MONSTER_DEAD;
				}
			}
		}
	}
}

CBoss_Phase1 * CBoss_Phase1::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBoss_Phase1* pInstance = new CBoss_Phase1(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Phase1 : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBoss_Phase1::Clone(void * pArg) {
	CBoss_Phase1* pInstance = new CBoss_Phase1(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss_Phase1 : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBoss_Phase1::Free() {
	__super::Free();
}