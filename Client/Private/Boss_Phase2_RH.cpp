#include "stdafx.h"
#include "..\Public\Boss_Phase2_RH.h"

CBoss_Phase2_RH::CBoss_Phase2_RH(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBoss_Phase2_RH::CBoss_Phase2_RH(const CBoss_Phase2_RH & rhs)
	:CMonster(rhs)
{
}

HRESULT CBoss_Phase2_RH::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Phase2_RH : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Phase2_RH::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBoss : NativeConstruct");
		return E_FAIL;
	}
	
	m_tInfo.iMaxHp = 3500; // 3500
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_tInfo.iAtt = 150;
	m_tInfo.iDef = 0;
	m_iDeadSprite = 0;

	m_tMonster.mapCube = ((MONSTER*)pArg)->mapCube;
	m_tMonster.pTargetTransform = ((MONSTER*)pArg)->pTargetTransform;

	//보스 위치 정하기
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(34.3f, 11.7f, 22.3f));
	m_fOriginPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	//보스 크기 정하기
	m_pTransform->Scaled(_float3(3.51f, 4.01f, 3.51f));

	return S_OK;
}

void CBoss_Phase2_RH::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	Diving();
	Skill_Tick();

	if (false == m_bDamage && false == m_bAttack) {
		Skill_Patern();
	}

	++m_tickCount;
	if (m_tickCount == 250)
	{
		m_tickCount = 0;
		m_iRand = rand() % 100 + 1;
	}
}

void CBoss_Phase2_RH::LateTick(_float fTimeDelta) {
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

HRESULT CBoss_Phase2_RH::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBoss_Phase2_RH : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Phase2_RH::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBalrog_RH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBalrog_RH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBalrog_RH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CBalrog_RH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Balrog_RH"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog_RH"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBalrog_RH : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

void CBoss_Phase2_RH::Skill_Patern() {
	m_vTargetLook = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION) - m_pTransform->Get_State(CTransform::STATE_POSITION);
	m_vTargetLook.y = 0.f;
	m_fTargetDis = D3DXVec3Length(&m_vTargetLook);

	_uint m_iMySkill = dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Get_Skill();
	_uint m_iPreSkill = dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Get_PreSkill();

	if (18.f > m_fTargetDis && m_iMySkill == 2 && m_iMySkill != m_iPreSkill) {

		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 515, 130, 980, 700 };
		lstrcpy(tFont.szText, L"발록의 오른손이 아이스 바인드를 준비합니다!");
		tFont.tFontInfo.Height = 25;
		tFont.tFontInfo.Width = 15;
		tFont.eTextId = CText::TEXT_WARNING;
		tFont.vARGB = _float4(255, 0, 255, 0);
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Warning_Text", L"Prototype_GameObject_Font", &tFont);

		m_iIceTick = 0;
		m_iSprite = 0;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_ICE;
		m_bAttack = true;

		dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Set_Skill(2);
	}
	if (18.f > m_fTargetDis && m_iMySkill == 4 && m_iMySkill != m_iPreSkill) {

		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 515, 130, 980, 700 };
		lstrcpy(tFont.szText, L"발록의 오른손이 와이번 소환을 준비합니다!");
		tFont.tFontInfo.Height = 25;
		tFont.tFontInfo.Width = 15;
		tFont.eTextId = CText::TEXT_WARNING;
		tFont.vARGB = _float4(255, 0, 255, 0);
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Warning_Text", L"Prototype_GameObject_Font", &tFont);

		m_iWyTick = 0;
		m_iSprite = 29;
		m_eMState = MONSTER_ATK;
		m_eAttack = ATTACK_WYVERN;
		m_bAttack = true;

		dynamic_cast<CBalrog*> (m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->front())->Set_Skill(4);
	}
}

void CBoss_Phase2_RH::Skill_Tick() {
	if (m_iIceCool * 60 > m_iIceTick) {
		++m_iIceTick;
	}
	if (m_iWyCool * 60 > m_iWyTick) {
		++m_iWyTick;
	}
}

void CBoss_Phase2_RH::Sprite_Frame() {
	++m_iTick;
	if (15 <= m_iTick) {
		m_iTick = 0;
		++m_iSprite;
		if (MONSTER_IDLE == m_eMState && 2 <= m_iSprite) {
			m_iSprite = 0;
		}
		else if (MONSTER_ATK == m_eMState) {
			if (ATTACK_ICE == m_eAttack && 21 == m_iSprite) {
				MONSTER tMonster;
				tMonster.mapCube = m_tMonster.mapCube;
				tMonster.pTargetTransform = m_tMonster.pTargetTransform;
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Boss", L"Prototype_GameObject_Boss_Ice", &tMonster);
			}
			else if (ATTACK_ICE == m_eAttack && 29 <= m_iSprite) {
				m_iSprite = 0;
				m_bAttack = false;
			}
			else if (ATTACK_WYVERN == m_eAttack && 56 <= m_iSprite) {
				m_iSprite = 29;
				m_bAttack = false;

				MONSTER tMonster;
				tMonster.mapCube = m_tMonster.mapCube;
				tMonster.pTargetTransform = m_tMonster.pTargetTransform;
				tMonster.vPosition = _float3(rand() % 5 + 32.f, 15.f, rand() % 5 + 17.f);
				m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Boss", L"Prototype_GameObject_Wyvern", &tMonster);
			}
		}
		else if (MONSTER_HIT == m_eMState && 1 <= m_iSprite) {
			m_iSprite = 0;
			m_bAttack = false;
		}
		else if (MONSTER_DEAD == m_eMState && 1 <= m_iSprite) {
			m_iSprite = 0;
			m_eState = STATE_DEAD;
		}
	}
}

void CBoss_Phase2_RH::Damaged() {
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

CBoss_Phase2_RH * CBoss_Phase2_RH::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBoss_Phase2_RH* pInstance = new CBoss_Phase2_RH(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Phase2_RH : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBoss_Phase2_RH::Clone(void * pArg) {
	CBoss_Phase2_RH* pInstance = new CBoss_Phase2_RH(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss_Phase2_RH : Clone");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBoss_Phase2_RH::Free() {
	__super::Free();
}