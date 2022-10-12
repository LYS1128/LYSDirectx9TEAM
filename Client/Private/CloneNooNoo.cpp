#include "stdafx.h"
#include "..\Public\CloneNooNoo.h"

CCloneNooNoo::CCloneNooNoo(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CCloneNooNoo::CCloneNooNoo(const CCloneNooNoo & rhs)
	: CMonster(rhs)
{
}

HRESULT CCloneNooNoo::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CCloneNooNoo : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 200;
	m_tInfo.iAtt = 80;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_iDeadSprite = 32;

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CCloneNooNoo::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CCloneNooNoo : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CCloneNooNoo : NativeConstruct");
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

	m_pTransform->Scaled(_float3(3.51f,6.51f, 3.51f));

	CMonsterHpBar::MONSTERINFO tMonsterInfo;
	tMonsterInfo.pMonster = this;
	tMonsterInfo.vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, L"Layer_MonsterHp", L"Prototype_GameObject_MonsterHpBar", &tMonsterInfo))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	CMonsterRealHp::MONSTERINFO tMonsterInfoReal;
	tMonsterInfoReal.pMonster = this;
	tMonsterInfoReal.vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, L"Layer_MonsterHp", L"Prototype_GameObject_MonsterRealHp", &tMonsterInfoReal))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	m_iSprite = 0;
	return S_OK;
}

void CCloneNooNoo::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	Diving();

	_float3 vTargetPos = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION);
	_float Dir = 0;

	Look_Player(vTargetPos, &Dir);

	m_tMonster.vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);

	CTransform* pPlayerTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	Safe_AddRef(pPlayerTransform);
	_float3 fPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	++m_tickCount;

	_float fHpPercent = (_float)m_tInfo.iHp / m_tInfo.iMaxHp;

	if (m_tickCount == 300 && m_bAtk == false)
	{
		m_tickCount = 0;
		m_iRand = rand() % 100 + 1;
	}

	if (false == m_bDamage) {
		if (Dir >= 3.2f) {
			m_eMState = MONSTER_WALK;
			m_bTargeting = true;
			m_pTransform->Chase(vTargetPos, fTimeDelta, 1.f);
		}
		else {
			if (m_iRand <= 50)
			{
				m_bAtk = true;
				m_eMState = MONSTER_ATK;
				m_bTargeting = true;	
			}
			else
			{
				m_eMState = MONSTER_IDLE;
				m_bTargeting = false;
			}
		}
	}
	else if (true == m_bDamage && MONSTER_DEAD != m_eMState) {
		++m_iDamageTick;
		m_iSprite = 32;
		if (65 <= m_iDamageTick) {
			m_bDamage = false;
			m_iDamageTick = 0;
		}
	}
	Safe_Release(pPlayerTransform);
}

void CCloneNooNoo::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	++m_iTick;
	if (MONSTER_WALK == m_eMState) {
		if (0 == m_iTick % 15) {
			++m_iSprite;
			if (16 <= m_iSprite) {
				m_iSprite = 5;
			}
			m_iTick = 0;
		}
	}
	else if (MONSTER_IDLE == m_eMState) {
		if (0 == m_iTick % 20) {
			++m_iSprite;
			if (4 <= m_iSprite) {
				m_iSprite = 0;
			}
			m_iTick = 0;
		}
	}
	else if (m_eMState == MONSTER_HIT) {
		if (0 == m_iTick % 20) {
			++m_iSprite;
			if (32 <= m_iSprite) {
				m_iSprite = 32;
			}
		}
	}
	else if (m_eMState == MONSTER_DEAD) {
		if (0 == m_iTick % 20) {
			++m_iSprite;
			if (45 <= m_iSprite) {
				m_iSprite = 45;
				m_eState = STATE_DEAD;
			}
		}
	}
	else if (m_eMState == MONSTER_ATK) {
		if (0 == m_iTick % 14) {
			++m_iSprite;
			if (m_iSprite == 29)
			{
				for (_uint i = 0; i < 8; ++i)
				{
					CTransform* pPlayerTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
					Safe_AddRef(pPlayerTransform);
					_float3 fPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);
					fPlayerPos.x += rand() % 6 - 3;
					fPlayerPos.z += rand() % 6 - 3;
					CMonster::MONSTER tMonster;
					tMonster.mapCube;
					tMonster.pTargetTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
					tMonster.vPosition = _float3(fPlayerPos.x, 10.f, fPlayerPos.z);

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_MiniNooNoo"), &tMonster))) {
						MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
						return;
					}

					Safe_Release(pPlayerTransform);
				}
				m_bAtk = false;
			}
			if (31 <= m_iSprite) {
				m_iSprite = 19;
			}
		}
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CCloneNooNoo::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CCloneNooNoo : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CCloneNooNoo::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CCloneNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_NooNoo"), LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_NooNoo"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CCloneNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CCloneNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CCloneNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CCloneNooNoo : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CCloneNooNoo* CCloneNooNoo::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CCloneNooNoo*	pInstance = new CCloneNooNoo(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CCloneNooNoo : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CCloneNooNoo::Clone(void* pArg) {
	CCloneNooNoo*	pInstance = new CCloneNooNoo(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CCloneNooNoo : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCloneNooNoo::Free() {
	__super::Free();
}