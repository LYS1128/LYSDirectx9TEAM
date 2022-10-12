#include "stdafx.h"
#include "../Public/Level_Loading.h"
#include "..\Public\NooNoo.h"

CNooNoo::CNooNoo(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CNooNoo::CNooNoo(const CNooNoo & rhs)
	: CMonster(rhs)
{
}

HRESULT CNooNoo::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CNooNoo : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 2000;
	m_tInfo.iAtt = 80;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_iDeadSprite = 32;

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CNooNoo::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CNooNoo : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CNooNoo : NativeConstruct");
		return E_FAIL;
	}

	CShadow::SHADOW tShadow;
	tShadow.mapCube = m_tMonster.mapCube;
	tShadow.pTargetTransform = m_pTransform;
	tShadow.pMyMonster = this;

	m_tMonster.m_eKind = CMonster::MONSTER_NOONOO;


	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, L"Layer_Shadow", L"Prototype_GameObject_Shadow", &tShadow))) {
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

	m_pTransform->Set_State(CTransform::STATE_UP, _float3(0.f,1.f,0.f));

	m_pTransform->Scaled(_float3(3.51f,6.51f, 3.51f));


	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, L"Layer_BossHp", L"Prototype_GameObject_UI_BossHpBar", this))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, L"Layer_MonsterHp", L"Prototype_GameObject_UI_BossHpReal", this))) {
		MSG_BOX(L"Failed To CGourd : NativeConstruct");
		return E_FAIL;
	}

	m_iSprite = 0;
	return S_OK;
}

void CNooNoo::Tick(_float fTimeDelta) {
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

	if (m_tickCount == 300)
	{
		m_tickCount = 0;
		m_iRand = rand() % 100 + 1;
	}

	CMonster::MONSTER tMonster;
	tMonster.mapCube = m_tMonster.mapCube;
	tMonster.pTargetTransform = m_tMonster.pTargetTransform;

	

	if (fHpPercent <= 0.3f && m_bLowHp == false)
	{
		m_bLowHp = true;

		if (m_bLowHp == true)
		{
			
			_float3 fDot1 = _float3(fPlayerPos.x - 3.f, m_tMonster.vPosition.y, fPlayerPos.z);
			_float3 fDot2 = _float3(fPlayerPos.x + 3.f, m_tMonster.vPosition.y, fPlayerPos.z);
			_float3 fDot3 = _float3(fPlayerPos.x, m_tMonster.vPosition.y, fPlayerPos.z - 3.f);
			_float3 fDot4 = _float3(fPlayerPos.x, m_tMonster.vPosition.y, fPlayerPos.z + 3.f);

			tMonster.vPosition = fDot2;
			if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_CloneNooNoo"),&tMonster))) {
				MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
				return;
			}
			tMonster.vPosition = fDot3;
			if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_CloneNooNoo"), &tMonster))) {
				MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
				return;
			}
			tMonster.vPosition = fDot4;
			if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_CloneNooNoo"), &tMonster))) {
				MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
				return;
			}

			m_pTransform->Set_State(CTransform::STATE_POSITION, fDot1);
		}

	}
	else
	{
		if (false == m_bDamage && m_bAtk == false) {
			if (Dir >= 3.2f) {
				m_eMState = MONSTER_WALK;
				m_bTargeting = true;
				m_pTransform->Chase(vTargetPos, fTimeDelta*3, 1.f);
			}
			else {
				if (m_iRand <= 70)
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
			if (65<= m_iDamageTick) {
				m_bDamage = false;
				m_iDamageTick = 0;

				if (m_bAtk == true)
					m_iSprite = m_iPresprite;

			}

			
		}
	}
	Safe_Release(pPlayerTransform);
}

void CNooNoo::LateTick(_float fTimeDelta) {
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

				CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());
				pPlayer->Exp_Plus(500);

			}
		}
	}
	if (m_bAtk == true) {
		if (0 == m_iTick % 14) {
			m_iPresprite = m_iSprite;
			++m_iSprite;
			if (m_iSprite == 26)
			{
				CMonster::MONSTER tMonster;
				tMonster.mapCube;
				tMonster.pTargetTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
				tMonster.vPosition =m_pTransform->Get_State(CTransform::STATE_POSITION);

				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIBOSS, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_NNA"), &tMonster))) {
					MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
					return;
				}
			}
			if (m_iSprite == 29)
			{
				for (_uint i = 0; i < 12; ++i)
				{
					CTransform* pPlayerTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
					Safe_AddRef(pPlayerTransform);
					_float3 fPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);
					fPlayerPos.x += rand() % 5 - 3 + (rand()%10)*0.1f;
					fPlayerPos.z += rand() % 5 - 3 + (rand() % 10)*0.1f;
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

HRESULT CNooNoo::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CNooNoo : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CNooNoo::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.5f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_NooNoo"), LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_NooNoo"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CNooNoo : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CNooNoo : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CNooNoo* CNooNoo::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CNooNoo*	pInstance = new CNooNoo(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CNooNoo : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CNooNoo::Clone(void* pArg) {
	CNooNoo*	pInstance = new CNooNoo(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CNooNoo : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CNooNoo::Free() {
	__super::Free();
}