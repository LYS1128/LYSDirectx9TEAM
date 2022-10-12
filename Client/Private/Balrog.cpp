#include "stdafx.h"
#include "..\Public\Balrog.h"

CBalrog::CBalrog(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBalrog::CBalrog(const CBalrog & rhs)
	: CMonster(rhs)
{
}

HRESULT CBalrog::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBalrog : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	return S_OK;
}

HRESULT CBalrog::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBalrog : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBalrog : NativeConstruct");
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

	//보스 정보
	m_tInfo.iAtt = 200;
	m_tInfo.iDef = 0;
	m_iDeadSprite = 113;
	m_tInfo.iMaxHp = 6000; // 6000
	m_tInfo.iHp = m_tInfo.iMaxHp;

	m_tMonster.m_eKind = CMonster::MONSTER_NOONOO;


	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(37.f, 12.f, 22.f));
	m_fOriginPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	//_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	//D3DXVec3Normalize(&BuffLook, &BuffLook);
	//m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	//_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	//D3DXVec3Normalize(&BuffRight, &BuffRight);
	//m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_pTransform->Scaled(_float3(7.f, 7.f, 7.f));

	///* 수정할곳 */
	//m_iSprite = 0;
	return S_OK;
}

void CBalrog::Tick(_float fTimeDelta)
{
	Compute_ZDis(m_pTransform);




	if (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() != 1)
		m_tInfo.iHp = m_tInfo.iMaxHp;

	Diving();
	Collision_Ground();
	Skill_Tick();

	++m_iHandTick;

	if(m_iHandTick >= 420)
	{
		m_iNowSkill = m_iPreSkill + 1;
		if (m_iNowSkill == 5)
			m_iNowSkill = 1;
		m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossEffect", L"Prototype_GameObject_Circle", &m_iNowSkill);
		m_iHandTick = 0;

		///////나우스킬을가지고 자기뒤에후광바꾸는에디드오브젝트??그게여기들어가ㅂ면될듯?
		//에디드오브젝트레잉너
	}


	++m_iMyTick;
	if (m_iMyTick >= 90)
	{
		m_iMyTick = 0;
		m_vTargetLook = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION) - m_pTransform->Get_State(CTransform::STATE_POSITION);
		m_vTargetLook.y = 0.f;
		m_fTargetDis = D3DXVec3Length(&m_vTargetLook);

		if (18.f > m_fTargetDis && m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() == 1)
		{
			BOSSPATERN tBossPatern;
			tBossPatern.vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
			tBossPatern.vTargetLook = m_vTargetLook;
			m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossEffect", L"Prototype_GameObject_Boss_Blast", &tBossPatern);
		}
	}

	if (false == m_bDamage&&false== m_bAttack) {
		Skill_Patern();
	}


	
}

void CBalrog::LateTick(_float fTimeDelta)
{
	//__super::LateTick(fTimeDelta);
	//++m_iTick;
	//if (MONSTER_IDLE == m_eMState) {
	//	if (0 == m_iTick % 7) {
	//		++m_iSprite;
	//		if (1 <= m_iSprite) {
	//			m_iSprite = 0;
	//		}
	//		m_iTick = 0;
	//	}
	//}
	////왼손A
	//else if (m_eMState == MONSTER_ATK1) {
	//	if (0 == m_iTick % 20) {
	//		++m_iSprite;
	//		if (27 <= m_iSprite) {
	//			m_iSprite = 2;
	//		}
	//		m_iTick = 0;
	//	}
	//}
	////왼손B
	//else if (m_eMState == MONSTER_ATK2) {
	//	if (0 == m_iTick % 20) {
	//		++m_iSprite;
	//		if (47 <= m_iSprite) {
	//			m_iSprite = 28;
	//		}
	//	}
	//}
	////왼손C
	//else if (m_eMState == MONSTER_ATK3) {
	//	if (0 == m_iTick % 20) {
	//		++m_iSprite;
	//		if (71 <= m_iSprite) {
	//			m_iSprite = 48;
	//		}
	//	}
	//}
	////오른손A
	//else if (m_eMState == MONSTER_ATK4) {
	//	if (0 == m_iTick % 20) {
	//		++m_iSprite;
	//		if (94 <= m_iSprite) {
	//			m_iSprite = 72;
	//		}
	//	}
	//}
	////오른손B
	//else if (m_eMState == MONSTER_ATK5) {
	//	if (0 == m_iTick % 20) {
	//		++m_iSprite;
	//		if (112 <= m_iSprite) {
	//			m_iSprite = 95;
	//		}
	//	}
	//}
	//else if (m_eMState == MONSTER_DEAD) {
	//	if (0 == m_iTick % 1) {
	//		++m_iSprite;
	//		if (113 == m_iSprite) {
	//			m_iSprite = 113;
	//			m_eState = STATE_DEAD;

	//			CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());
	//			pPlayer->Exp_Plus(15);
	//		}
	//	}
	//}
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

HRESULT CBalrog::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBalrog : Render");
		return E_FAIL;
	}
	return S_OK;
}

void CBalrog::Skill_Patern()
{
	m_vTargetLook = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION) - m_pTransform->Get_State(CTransform::STATE_POSITION);
	m_vTargetLook.y = 0.f;
	m_fTargetDis = D3DXVec3Length(&m_vTargetLook);

	if (0.f <= m_fTargetDis && 6.f > m_fTargetDis && m_iMabubjinCool * 60 == m_iMabubjinTick) {
		m_iMabubjinTick = 0;
		m_iSprite = 28;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_MABUBJIN;
		m_bAttack = true;
	}
	else if (6.f <= m_fTargetDis && 9.f > m_fTargetDis && m_iFireBallCool * 60 == m_iFireBallTick) {
		m_iFireBallTick = 0;
		m_iSprite = 9;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_FIREBALL;
		m_bAttack = true;
	}
}

void CBalrog::Skill_Tick()
{
	if (m_iFireBallCool * 60 > m_iFireBallTick) {
		++m_iFireBallTick;
	}
	if (m_iMabubjinCool * 60 > m_iMabubjinTick) {
		++m_iMabubjinTick;
	}
}

void CBalrog::Sprite_Frame()
{
	++m_iTick;
	if (10 <= m_iTick) {
		m_iTick = 0;
		++m_iSprite;
		if (MONSTER_IDLE == m_eMState && 1 <= m_iSprite) {
			m_iSprite = 0;
		}
		else if (MONSTER_ATK == m_eMState) {
			if (ATTACK_FIREBALL == m_eAttack && 24 <= m_iSprite) {
				m_iSprite = 3;
				m_bAttack = false;

				BOSSPATERN tBossPatern;
				tBossPatern.vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
				tBossPatern.vTargetLook = m_vTargetLook;
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_Boss_FireBall_Attack", &tBossPatern);
			}
			else if (ATTACK_MABUBJIN == m_eAttack && 47 <= m_iSprite) {
				_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
				vPos.y -= m_pTransform->Get_Scale().y * 0.4f;
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkillCasting", L"Prototype_GameObject_Boss_Mabubjin", &vPos);
				m_iSprite = 25;
				m_bAttack = false;
			}
		}
		else if (MONSTER_HIT == m_eMState && 1 <= m_iSprite) {
			m_iSprite = 0;
			m_bAttack = false;
		}
		else if (MONSTER_DEAD == m_eMState && 121 <= m_iSprite) {
			m_iSprite = 113;
			m_eState = STATE_DEAD;
		}
	}
}

void CBalrog::Damaged()
{
	list<CGameObject*>* pSkillList = m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Effect");
	if (nullptr != pSkillList) {
		for (auto& iter : *pSkillList) {
			CTransform* pSkillTransform = (CTransform*)(iter->Get_Component(L"Com_Transform"));
			_float3 vSkillPosition = pSkillTransform->Get_State(CTransform::STATE_POSITION);
			_float3 vSkillScale = pSkillTransform->Get_Scale();

			_float3 vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
			_float3 vColScale = _float3(1.f, m_pTransform->Get_Scale().y, 1.f);

			_float fDis = sqrtf(pow(vSkillPosition.x - vPosition.x, 2) + pow(vSkillPosition.z - vPosition.z, 2));
			if (false == m_bDamage && fDis < 2.f && vSkillPosition.y < vPosition.y + vColScale.y * 0.5f && vSkillPosition.y > vPosition.y - vColScale.y) {
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

HRESULT CBalrog::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBalrog : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Balrog"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBalrog : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBalrog : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBalrog : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CBalrog : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CBalrog * CBalrog::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBalrog*	pInstance = new CBalrog(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBalrog : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBalrog::Clone(void * pArg)
{
	CBalrog*	pInstance = new CBalrog(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBalrog : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBalrog::Free()
{
	__super::Free();
}
