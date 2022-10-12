#include "stdafx.h"
#include "..\Public\Boss_Phase2_LH.h"

CBoss_Phase2_LH::CBoss_Phase2_LH(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBoss_Phase2_LH::CBoss_Phase2_LH(const CBoss_Phase2_LH & rhs)
	:CMonster(rhs)
{
}

HRESULT CBoss_Phase2_LH::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Phase2_LH::NativeConstruct(void * pArg) {
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
	m_iDeadSprite = 0;
	//보스 정보 정하기
	m_tInfo.iAtt = 150;
	m_tInfo.iDef = 0;
	m_tInfo.iMaxHp = 3000; // 3000
	m_tInfo.iHp = m_tInfo.iMaxHp;

	//보스 위치 정하기
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(36.4f, 11.f, 19.2f));
	m_fOriginPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	//보스 크기 정하기
	m_pTransform->Scaled(_float3(3.51f, 4.01f, 3.51f));

	return S_OK;
}

void CBoss_Phase2_LH::Tick(_float fTimeDelta) {

	Diving();
	Skill_Tick();

	if (false == m_bDamage && false == m_bAttack) {
		Skill_Patern();
	}
}

void CBoss_Phase2_LH::LateTick(_float fTimeDelta) {
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

HRESULT CBoss_Phase2_LH::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Phase2_LH::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog_LH"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

void CBoss_Phase2_LH::Skill_Patern() {
	m_vTargetLook = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION) - m_pTransform->Get_State(CTransform::STATE_POSITION);
	m_vTargetLook.y = 0.f;
	m_fTargetDis = D3DXVec3Length(&m_vTargetLook);

	_uint m_iMySkill = dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Get_Skill();
	_uint m_iPreSkill = dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Get_PreSkill();


	if (18.f > m_fTargetDis && m_iMySkill == 1 && m_iMySkill != m_iPreSkill) {

		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 515, 100, 980, 700 };
		lstrcpy(tFont.szText, L"발록의 왼손이 일렉트릭 쇼크를 준비합니다!");
		tFont.tFontInfo.Height = 25;
		tFont.tFontInfo.Width = 15;
		tFont.eTextId = CText::TEXT_WARNING;
		tFont.vARGB = _float4(255, 0, 255, 0);
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Warning_Text", L"Prototype_GameObject_Font", &tFont);

		m_iElectricTick = 0;
		m_iSprite = 1;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_ELECTRIC;
		m_bAttack = true;

		dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Set_Skill(1);

	}
	if (18.f > m_fTargetDis && m_iMySkill == 3 && m_iMySkill != m_iPreSkill) {

		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 515, 100, 980, 700 };
		lstrcpy(tFont.szText, L"발록의 왼손이 퍼플 포그를 준비합니다!");
		tFont.tFontInfo.Height = 25;
		tFont.tFontInfo.Width = 15;
		tFont.eTextId = CText::TEXT_WARNING;
		tFont.vARGB = _float4(255, 0, 255, 0);
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Warning_Text", L"Prototype_GameObject_Font", &tFont);

		m_iPurplePogTick = 0;
		m_iSprite = 19;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_PURPLEPOG;
		m_bAttack = true;

		dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Set_Skill(3);
	}
}

void CBoss_Phase2_LH::Skill_Tick() {
	if (m_iElectricCool * 60 > m_iElectricTick) {
		++m_iElectricTick;
	}
	if (m_iPurplePogCool * 60 > m_iPurplePogTick) {
		++m_iPurplePogTick;
	}
}

void CBoss_Phase2_LH::Sprite_Frame() {
	++m_iTick;
	if (15 <= m_iTick) {
		m_iTick = 0;
		++m_iSprite;
		if (MONSTER_IDLE == m_eMState && 2 <= m_iSprite) {
			m_iSprite = 0;
		}
		else if (MONSTER_ATK == m_eMState) {
			if (ATTACK_ELECTRIC == m_eAttack && 14 == m_iSprite) {
				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_Electric_Shock")))
				{
					MSG_BOX(L"1");
					return;
				}
				m_bAttack = false;
				if (m_iSprite >= 19)
					m_iSprite = 0;
			}
			else if (ATTACK_PURPLEPOG == m_eAttack && 33 <= m_iSprite) {
				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_BossSkill", L"Prototype_GameObject_PurplePog")))
				{
					MSG_BOX(L"2");
					return;
				}
				m_bAttack = false;
				if (m_iSprite >= 41)
					m_iSprite = 0;
			}
			if (m_iSprite >= 42)
				m_iSprite = 0;
		}
		else if (MONSTER_HIT == m_eMState && 27 <= m_iSprite) {
			m_iSprite = 26;
			m_bAttack = false;
		}
		else if ( MONSTER_DEAD == m_eMState && 1 <= m_iSprite) {
			m_iSprite =	0;
			m_eState = STATE_DEAD;
		}
	}
}

void CBoss_Phase2_LH::Damaged() {
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

CBoss_Phase2_LH * CBoss_Phase2_LH::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBoss_Phase2_LH* pInstance = new CBoss_Phase2_LH(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBoss_Phase2_LH::Clone(void * pArg) {
	CBoss_Phase2_LH* pInstance = new CBoss_Phase2_LH(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss_Phase2_LH : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBoss_Phase2_LH::Free() {
	__super::Free();
}