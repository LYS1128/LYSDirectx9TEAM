#include "stdafx.h"
#include "..\Public\Monster.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CMonster::CMonster(const CMonster & rhs)
	: CGameObject(rhs)
{
	memcpy(&m_tInfo, &rhs.m_tInfo, sizeof(INFO));
	m_iDeadSprite = rhs.m_iDeadSprite;
	m_vCollision = rhs.m_vCollision;
}

HRESULT CMonster::NativeConstruct_Prototype() {
	return S_OK;
}

HRESULT CMonster::NativeConstruct(void* pArg) {
	if (nullptr == pArg) {
		MSG_BOX(L"Failed To CMonster : NativeConstruct");
		return E_FAIL;
	}
	m_tMonster.mapCube = ((MONSTER*)pArg)->mapCube;
	m_tMonster.pTargetTransform = ((MONSTER*)pArg)->pTargetTransform;
	m_tMonster.m_eKind = ((MONSTER*)pArg)->m_eKind;
	return S_OK;
}

void CMonster::Tick(_float fTimeDelta) {

	if (m_Grav != 2)
		Gravity(fTimeDelta);
	
	Collision_Ground();
	Compute_ZDis(m_pTransform);

	if (false == m_bDamage && MONSTER_DEAD != m_eMState) {
		Damaged(m_tMonster.m_eKind);
	}

}

void CMonster::LateTick(_float fTimeDelta) {

	
	if (m_eMPreState != m_eMState) {
		m_eMPreState = m_eMState;
	}

}

HRESULT CMonster::Render() {

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite))) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CSlime : Render");
		return E_FAIL;
	}
	m_pVIBuffer->Render();

	return S_OK;
}

void CMonster::Collision_Ground() {
	m_Grav = 0;
	_float3 NewPos = _float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y - ((m_pTransform->Get_Scale().y) / 2) + 0.75f, m_pTransform->Get_State(CTransform::STATE_POSITION).z);

	_uint PlayerIndex = (_uint)(NewPos.x + 0.5) * 10000
		+ (_uint)(NewPos.y + 0.5) * 100
		+ (_uint)(NewPos.z + 0.5);

	if ((m_tMonster.mapCube.find(PlayerIndex) != m_tMonster.mapCube.end()))
	{
		m_pCollision->My_Collision((*(m_tMonster.mapCube.find(PlayerIndex))).second, m_pTransform);
		return;
	}

	_uint MapIndex[17]{
		PlayerIndex - 10000 + 1, PlayerIndex + 1, PlayerIndex + 10000 + 1,
		PlayerIndex - 10000 , PlayerIndex + 10000,
		PlayerIndex - 10000 - 1, PlayerIndex - 1, PlayerIndex + 10000 - 1,

		PlayerIndex - 10000 - 100 + 1, PlayerIndex - 100 + 1, PlayerIndex + 10000 - 100 + 1,
		PlayerIndex - 10000 - 100, PlayerIndex - 100, PlayerIndex + 10000 - 100,
		PlayerIndex - 10000 - 100 - 1, PlayerIndex - 100 - 1, PlayerIndex + 10000 - 100 - 1,
	};

	_float3 vCollsionPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	for (_uint i = 0; i < 17; ++i) {

		if ((m_tMonster.mapCube.find(MapIndex[i]) != m_tMonster.mapCube.end())) {
			_uint Coll = m_pCollision->After_Collision((*(m_tMonster.mapCube.find(MapIndex[i]))).second, m_pTransform);
			if (Coll == 2)
				m_Grav = 2;
		}
	}
}

void CMonster::Diving() {
	if (-10.f >= m_pTransform->Get_State(CTransform::STATE_POSITION).y) {
		m_pTransform->Set_State(CTransform::STATE_POSITION, m_fOriginPos);
	}
}

void CMonster::Gravity(_float fTimeDelta) {
	_float3 vGravity = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vGravity.y -= G * fTimeDelta;
	m_pTransform->Set_State(CTransform::STATE_POSITION, vGravity);

}

void CMonster::Look_Player(_float3 vTarget, _float* fDistance) {
	_float3 vMyLook = m_pTransform->Get_State(CTransform::STATE_LOOK);
	_float3 vMyPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	_float3 vDir = vTarget - vMyPos;
	*fDistance = D3DXVec3Length(&vDir);

	if ((vMyPos.x / vMyPos.z) < (vTarget.x / vTarget.z)) {
		m_bLook = true;
		if (m_bLook != m_bPreLook) {
			m_pTransform->TextureTurn();
			m_bPreLook = true;
		}
	}
	else {
		m_bLook = false;
		if (m_bLook != m_bPreLook) {
			m_pTransform->TextureTurn();
			m_bPreLook = false;
		}
	}
}

void CMonster::Random_Move(_float fTimeDelta) {
	++m_iMoveMove;
	if (m_iMoveMove >= 30)
	{
		m_iMoveMove = 0;
		_uint iRandom = (rand() % 100) + 1;
		if (5 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(1.f, 0.f, 0.f);
		}
		else if (10 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(-1.f, 0.f, 0.f);
		}
		else if (15 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(0.f, 0.f, 1.f);
		}
		else if (20 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(0.f, 0.f, -1.f);
		}
		else if (25 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(1.f, 0.f, 1.f);
			D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		}
		else if (30 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(-1.f, 0.f, 1.f);
			D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		}
		else if (35 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(1.f, 0.f, -1.f);
			D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		}
		else if (40 >= iRandom) {
			m_eMState = MONSTER_WALK;
			m_vDirection = _float3(-1.f, 0.f, -1.f);
			D3DXVec3Normalize(&m_vDirection, &m_vDirection);
		}
		else {
			m_eMState = MONSTER_IDLE;
			m_vDirection = _float3(0.f, 0.f, 0.f);
		}
	}
	_float3 vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vPosition += m_vDirection * m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta;
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPosition);
}

void CMonster::Damaged(MONSTERKIND m_eMonsterKind) {
	CLayer* pEffectLayer = m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Effect");
	if (pEffectLayer != nullptr)
	{
		list<class CGameObject*> listEffect = *(pEffectLayer)->Get_List();

		if (listEffect.size() != 0)
		{
			for (auto iter : listEffect)
			{
				CTransform* EffectPos = dynamic_cast<CTransform*>(iter->Get_Component(L"Com_Transform"));
				Safe_AddRef(EffectPos);
				if (m_pCollision->Collision_Cylinder(m_pTransform, EffectPos)) {
					_uint iDamage = ((CEffect*)iter)->Get_Damage() - m_tInfo.iDef;
					if (rand() % 10 == 0)
					{
						iDamage *= 2.f;
						dynamic_cast<CMultiCamera*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front())->Set_Critical(true);
					}
					m_tInfo.iHp -= iDamage;
					Write_Damage(iDamage);
					m_bDamage = true;
					m_eMState = MONSTER_HIT;

					_float3 Pos = m_pTransform->Get_State(CTransform::STATE_POSITION);

					if (((CEffect*)iter)->Get_SkillID() == SKILL_FREEZE)
					{
						for (_uint i = 0; i < 100; ++i)
							m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_Particle", &Pos);
					}
					else if (((CEffect*)iter)->Get_SkillID() == SKILL_ICE)
					{
						for (_uint i = 0; i < 20; ++i)
						{
							m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_IceParticle", &Pos);
						}
						Pos += _float3(0.f, -0.3f, 0.f);
						for (_uint i = 0; i < 20; ++i)
						{
							m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_IceParticle", &Pos);

						}
					}

					CHit_Effect::HIT tHit;
					tHit.vPoisition = m_pTransform->Get_State(CTransform::STATE_POSITION);
					tHit.eHitType = ((CEffect*)iter)->Get_SkillID();

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_Hit_Effect", &tHit);
					if (0 >= m_tInfo.iHp) {
						Dead_Sound(m_eMonsterKind);
						m_tInfo.iHp = 0;
						m_iSprite = m_iDeadSprite;
						m_eMState = MONSTER_DEAD;
					}
				}
				Safe_Release(EffectPos);
			}
		}
	}
}


void CMonster::Drop_Item() {
	_uint iDropItem = rand() % 100 + 1;
	if (iDropItem%2 == 0) {
		//메소
		CItem::ITEM tItem;
		tItem.mapCube = m_tMonster.mapCube;
		tItem.pTargetTransform = m_pTransform;
		tItem.iOption = 3;
		tItem.vPosition = _float3(0.2f, 0.f, 0.2f);

		if (FAILED(m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Item", L"Prototype_GameObject_Item", &tItem))) {
			MSG_BOX(L"Failed To CSlime : NativeConstruct");
			return;
		}
	}
	if (iDropItem % 3 == 0) {
		//Add_GameObjectToLayer (드랍 아이템 : 고유 아이템/기타)
		CItem::ITEM tItem;
		tItem.mapCube = m_tMonster.mapCube;
		tItem.pTargetTransform = m_pTransform;
		tItem.iOption = 2;
		tItem.vPosition = _float3(-0.2f, 0.f, 0.2f);

		if (FAILED(m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Item", L"Prototype_GameObject_Item", &tItem))) {
			MSG_BOX(L"Failed To CSlime : NativeConstruct");
			return;
		}
	}
	if (iDropItem % 4 == 0) {
		//Add_GameObjectToLayer (드랍 아이템 : 물약HP)
		CItem::ITEM tItem;
		tItem.mapCube = m_tMonster.mapCube;
		tItem.pTargetTransform = m_pTransform;
		tItem.iOption = 0;
		tItem.vPosition = _float3(-0.2f, 0.f, -0.2f);

		if (FAILED(m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Item", L"Prototype_GameObject_Item", &tItem))) {
			MSG_BOX(L"Failed To CSlime : NativeConstruct");
			return;
		}
	}
	if (iDropItem % 6 == 0) {
		//Add_GameObjectToLayer (드랍 아이템 : 물약MP)
		CItem::ITEM tItem;
		tItem.mapCube = m_tMonster.mapCube;
		tItem.pTargetTransform = m_pTransform;
		tItem.iOption = 1;
		tItem.vPosition = _float3(0.2f, 0.f, -0.2f);

		if (FAILED(m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Item", L"Prototype_GameObject_Item", &tItem))) {
			MSG_BOX(L"Failed To CSlime : NativeConstruct");
			return;
		}
	}
}

void CMonster::Write_Damage(_uint iDamage) {
	string szDamage = to_string(iDamage);

	CDamage::DAMAGE tDamage;
	ZeroMemory(&tDamage, sizeof(CDamage::DAMAGE));

	int iRandX = rand() % 4 - 2;
	int iRandY = rand() % 4 - 2;

	for (int i = 0; i < szDamage.size(); ++i) {
		tDamage.chDamageID = (_uint)szDamage[i];
		tDamage.fX = g_iWinCX * 0.5f + iRandX * 30.f + i * 30.f;
		tDamage.fY = g_iWinCY * 0.5f + iRandY * 45.f;
		tDamage.eDamageType = CDamage::DAMAGE_MONSTER;

		m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Damage", L"Prototype_GameObject_Damage_UI", &tDamage);
	}
}

void CMonster::Quest() {
	list<CGameObject*>* listQuest = (m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Quest"));
	if (nullptr != listQuest && listQuest->size() != 0) {
		((CQuest*)(listQuest->front()))->Set_MonsterCnt();
	}
}

void CMonster::Dead_Sound(MONSTERKIND m_eMonsterKind)
{
	if (0 >= m_tInfo.iHp)
	{
		switch (m_eMonsterKind)
		{
		case Client::CMonster::MONSTER_BOSS:
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"Ghost.wav", CSound_Manager::EFFECT, VOLUME);
			break;
		case Client::CMonster::MONSTER_GOLEM:
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"Golem.wav", CSound_Manager::EFFECT, VOLUME);
			break;
		case Client::CMonster::MONSTER_COKEMUSH:
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"Slime_Dead.wav", CSound_Manager::EFFECT, VOLUME);
			break;
		case Client::CMonster::MONSTER_CUTEBEAR:
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"Ghost.wav", CSound_Manager::EFFECT, VOLUME);
			break;
		case Client::CMonster::MONSTER_FIREBOAR:
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"Pig.wav", CSound_Manager::EFFECT, VOLUME);
			break;
		case Client::CMonster::MONSTER_NOONOO:
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"NooNoo_Dead.wav", CSound_Manager::EFFECT, VOLUME);
			break;
		case Client::CMonster::MONSTER_GOURD:
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"Explosion1.wav", CSound_Manager::EFFECT, VOLUME);
			break;
		default:
			break;
		}
	}
}


void CMonster::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pCollision);
}