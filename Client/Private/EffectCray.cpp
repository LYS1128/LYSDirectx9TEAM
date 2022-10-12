#include "stdafx.h"
#include "..\Public\EffectCray.h"

CEffectCray::CEffectCray(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CEffectCray::CEffectCray(const CEffectCray& rhs)
	:CEffect(rhs)
{
}

HRESULT CEffectCray::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CEffectCray : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_fDamagePercent = 3.0f;
	return S_OK;
}

HRESULT CEffectCray::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CEffectCray : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CEffectCray : NativeConstruct");
		return E_FAIL;
	}
	m_tSkillFrame.fFrame = 0.f;
	m_tSkillFrame.iSpriteEnd = 8;

	CTransform* pTargetTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	Safe_AddRef(pTargetTransform);

	_float3 fPlayerPos = pTargetTransform->Get_State(CTransform::STATE_POSITION);
	CPlayer::BASICSTATE ePlayerState = *(CPlayer::BASICSTATE*)pArg;

	_float3 vBuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&vBuffLook, &vBuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, vBuffLook);

	_float3 vBuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&vBuffRight, &vBuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, vBuffRight);

	m_pTransform->Scaled(_float3(2.5f, 2.5f, 2.5f));

	_float3 vBuff;

	m_tEffect.eBasicState = ((CPlayer::EFFECT*)pArg)->eBasicState;
	m_tEffect.mapCube = ((CPlayer::EFFECT*)pArg)->mapCube;
	m_tEffect.pTargetTransform = ((CPlayer::EFFECT*)pArg)->pTargetTransform;

	m_eSkillID = SKILL_CRAY;

	switch (m_tEffect.eBasicState) {
	case CPlayer::STATE_L: {
		vBuff = _float3(-1.f, 0.f, 1.f);
		break;
	}
	case CPlayer::STATE_R: {
		vBuff = _float3(1.f, 0.f, -1.f);
		break;
	}
	case CPlayer::STATE_U: {
		vBuff = _float3(1.f, 0.f, 1.f);
		break;
	}
	case CPlayer::STATE_D: {
		vBuff = _float3(-1.f, 0.f, -1.f);
		break;
	}
	case CPlayer::STATE_UL: {
		vBuff = _float3(0.f, 0.f, 1.f);
		break;
	}
	case CPlayer::STATE_UR: {
		vBuff = _float3(1.f, 0.f, 0.f);
		break;
	}
	case CPlayer::STATE_DL: {
		vBuff = _float3(-1.f, 0.f, 0.f);
		break;
	}
	case CPlayer::STATE_DR: {
		vBuff = _float3(0.f, 0.f, -1.f);
		break;
	}
	}
	D3DXVec3Normalize(&vBuff, &vBuff);
	m_fGoGoGo = vBuff/3;

	m_pTransform->Set_State(CTransform::STATE_POSITION, fPlayerPos + vBuff + _float3(0.f, 1.f,0.f));

	Safe_Release(pTargetTransform);
	
	return S_OK;
}

void CEffectCray::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	_float3 fNextPos = m_pTransform->Get_State(CTransform::STATE_POSITION) + m_fGoGoGo * m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta;
	m_pTransform->Set_State(CTransform::STATE_POSITION, fNextPos);

	_uint EffectIndex = (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).x + 0.5) * 10000
		+ (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).y + 0.5) * 100
		+ (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).z + 0.5);

	for (_uint i = EffectIndex; (i - (_uint)(i / 10000) * 10000) / 100 != 0;) {
		if ((m_tEffect.mapCube.find(i - 100) != m_tEffect.mapCube.end())) {
			m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x,
				(*(m_tEffect.mapCube.find(i - 100))).second.y + 0.51f + 1.25f , m_pTransform->Get_State(CTransform::STATE_POSITION).z));
			break;
		}
		i -= 100;
	}
	m_iDamage = _uint(((CPlayer*)m_pPlayer)->Get_Player_Info().iAtt * m_fDamagePercent);


}

void CEffectCray::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	Collision_Ground();
	if ((_uint)m_tSkillFrame.fFrame ==2 || (_uint)m_tSkillFrame.fFrame == 1)
	{
		ParticleEnd = true;
		for (int i = 0; i < rand() % 100; ++i) {
			m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_CrayParticle", m_pTransform->Get_State(CTransform::STATE_POSITION));
		}
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CEffectCray::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CEffectCray : Render");
		return E_FAIL;
	}
	return S_OK;
}

void CEffectCray::Collision_Ground() {
	_float3 NewPos = _float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y - ((m_pTransform->Get_Scale().y) / 2) + 0.75f, m_pTransform->Get_State(CTransform::STATE_POSITION).z);

	_uint PlayerIndex = (_uint)(NewPos.x + 0.5) * 10000
		+ (_uint)(NewPos.y + 0.5) * 100
		+ (_uint)(NewPos.z + 0.5);

	_uint MapIndex[17]{

		PlayerIndex - 10000 + 1, PlayerIndex + 1, PlayerIndex + 10000 + 1,
		PlayerIndex - 10000 , PlayerIndex + 10000,
		PlayerIndex - 10000 - 1, PlayerIndex - 1, PlayerIndex + 10000 - 1,

		PlayerIndex - 10000 - 100 + 1, PlayerIndex - 100 + 1, PlayerIndex + 10000 - 100 + 1,
		PlayerIndex - 10000 - 100, PlayerIndex - 100, PlayerIndex + 10000 - 100,
		PlayerIndex - 10000 - 100 - 1, PlayerIndex - 100 - 1, PlayerIndex + 10000 - 100 - 1,
	};

	for (_uint i = 0; i < 26; ++i) {
		if ((m_tEffect.mapCube.find(MapIndex[i]) != m_tEffect.mapCube.end())) {
			if ((m_pCollision->After_Collision((*(m_tEffect.mapCube.find(MapIndex[i]))).second, m_pTransform))) {
				m_eState = STATE_DEAD;
			}
				
			
		}
	}
}

void CEffectCray::Gravity(_float fTimeDelta) {
	_float3 vGravity = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vGravity.y -= G * fTimeDelta;
	m_pTransform->Set_State(CTransform::STATE_POSITION, vGravity);
}

HRESULT CEffectCray::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CEffectCray : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Collision"), LEVEL_STATIC, TEXT("Prototype_Component_Collision"), (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CEffectCray : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CEffectCray : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CEffectCray : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureShadow"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_Effect"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CEffectCray : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CEffectCray* CEffectCray::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CEffectCray* pInstance = new CEffectCray(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CEffectCray : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CEffectCray::Clone(void* pArg) {
	CEffectCray* pInstance = new CEffectCray(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CEffectCray : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEffectCray::Free() {
	__super::Free();
	Safe_Release(m_pCollision);
}