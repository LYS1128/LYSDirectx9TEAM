#include "stdafx.h"
#include "..\Public\Typhon.h"

CTyphon::CTyphon(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CTyphon::CTyphon(const CTyphon & rhs)
	: CMonster(rhs)
{
}

HRESULT CTyphon::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CTyphon : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 550; /* 수정할곳 */
	m_tInfo.iAtt = 100;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_iDeadSprite = 16; /* 수정할곳 */

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CTyphon::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CTyphon : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CTyphon : NativeConstruct");
		return E_FAIL;
	}

	CShadow::SHADOW tShadow;
	tShadow.mapCube = m_tMonster.mapCube;
	tShadow.pTargetTransform = m_pTransform;
	tShadow.pMyMonster = this;
	m_tMonster.m_eKind = CMonster::MONSTER_CUTEBEAR;

														/* 수정할곳 */
	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Shadow", L"Prototype_GameObject_Shadow", &tShadow))) {
		MSG_BOX(L"Failed To CTyphon : NativeConstruct");
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
													/* 수정할곳 */
	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_MonsterHp", L"Prototype_GameObject_MonsterHpBar", &tMonsterInfo))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	CMonsterRealHp::MONSTERINFO tMonsterInfoReal;
	tMonsterInfoReal.pMonster = this;
	tMonsterInfoReal.vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

													/* 수정할곳 */
	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_MonsterHp", L"Prototype_GameObject_MonsterRealHp", &tMonsterInfoReal))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	/* 수정할곳 */
	m_iSprite = 0;
	return S_OK;
}

void CTyphon::Tick(_float fTimeDelta) {
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
		m_iSprite = 16;  /* 수정할곳 */
		if (65 <= m_iDamageTick) {
			m_bDamage = false;
			m_iDamageTick = 0;
		}
	}
}

void CTyphon::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	++m_iTick;
	if (MONSTER_WALK == m_eMState) {
		if (0 == m_iTick % 12) {		/* 수정할곳 */
			++m_iSprite;
			if (4 <= m_iSprite) {		/* 수정할곳 */
				m_iSprite = 0;			/* 수정할곳 */
			}
			m_iTick = 0;
		}
	}
	else if (MONSTER_IDLE == m_eMState) {
		if (0 == m_iTick % 12) {		/* 수정할곳 */
			++m_iSprite;
			if (4 <= m_iSprite) {		/* 수정할곳 */
				m_iSprite = 0;		
			}
			m_iTick = 0;
		}
	}
	else if (m_eMState == MONSTER_HIT) {
		if (0 == m_iTick % 10) {			/* 수정할곳 */
			++m_iSprite;
			if (16 <= m_iSprite) {		/* 수정할곳 */
				m_iSprite = 16;			/* 수정할곳 */
			}
		}
	}
	else if (m_eMState == MONSTER_DEAD) {
		if (0 == m_iTick % 10) {		/* 수정할곳 */
			++m_iSprite;
			if (29 <= m_iSprite) {		/* 수정할곳 */
				m_iSprite = 29;
				m_eState = STATE_DEAD;

				CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());
				pPlayer->Exp_Plus(200);	/* 수정할곳 */

				Quest();
			}
		}
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CTyphon::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CTyphon : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CTyphon::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CTyphon : SetUp_Components");
		return E_FAIL;
	}
												/* 수정할곳 */		/* 수정할곳 */								/* 수정할곳 */
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Typhon"), LEVEL_STAGEEIGHT, TEXT("Prototype_Component_Texture_Typhon"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CTyphon : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CTyphon : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CTyphon : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CTyphon : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CTyphon* CTyphon::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CTyphon*	pInstance = new CTyphon(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CTyphon : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CTyphon::Clone(void* pArg) {
	CTyphon*	pInstance = new CTyphon(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CTyphon : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTyphon::Free() {
	__super::Free();
}