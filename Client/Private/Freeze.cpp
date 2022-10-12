#include "stdafx.h"
#include "..\Public\Freeze.h"

CFreeze::CFreeze(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CFreeze::CFreeze(const CFreeze & rhs)
	: CEffect(rhs)
{
}

HRESULT CFreeze::NativeConstruct_Prototype()
{
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CFreeze : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_fDamagePercent = 1.0f;
	return S_OK;
}

HRESULT CFreeze::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CFreeze : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CFreeze : NativeConstruct");
		return E_FAIL;
	}
	m_tSkillFrame.fFrame = 0.f;
	m_tSkillFrame.iSpriteEnd = 7;
	m_eSkillID = SKILL_FREEZE;


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

	m_pTransform->Scaled(_float3(1.5f, 1.5f, 1.5f));

	_float3 vBuff;

	m_tEffect.eBasicState = ((CPlayer::EFFECT*)pArg)->eBasicState;
	m_tEffect.mapCube = ((CPlayer::EFFECT*)pArg)->mapCube;
	m_tEffect.pTargetTransform = ((CPlayer::EFFECT*)pArg)->pTargetTransform;

	switch (m_tEffect.eBasicState) {
	case CPlayer::STATE_L: {
		vBuff = _float3(-2.5f, 0.f, 1.f);
		break;
	}
	case CPlayer::STATE_R: {
		vBuff = _float3(1.f, 0.f, -2.5f);
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
	m_fGoGoGo = vBuff / 2;

	m_pTransform->Set_State(CTransform::STATE_POSITION, fPlayerPos + vBuff * 1.f);

	Safe_Release(pTargetTransform);

	return S_OK;
}

void CFreeze::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	/*_float3 fNextPos = m_pTransform->Get_State(CTransform::STATE_POSITION) + m_fGoGoGo * m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta;
	m_pTransform->Set_State(CTransform::STATE_POSITION, fNextPos);*/

	_uint EffectIndex = (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).x + 0.5) * 10000
		+ (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).y + 0.5) * 100
		+ (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).z + 0.5);

	for (_uint i = EffectIndex; (i - (_uint)(i / 10000) * 10000) / 100 != 0;) {
		if ((m_tEffect.mapCube.find(i - 100) != m_tEffect.mapCube.end())) {
			m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x,
				(*(m_tEffect.mapCube.find(i - 100))).second.y + 0.51f + 1.25f, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
			break;
		}
		i -= 100;
	}
	m_iDamage = _uint(((CPlayer*)m_pPlayer)->Get_Player_Info().iAtt * m_fDamagePercent);
}

void CFreeze::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);
	
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CFreeze::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CFreeze : Render");
		return E_FAIL;
	}
	return S_OK;
}


HRESULT CFreeze::SetUp_Components()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CFreeze : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Collision"), LEVEL_STATIC, TEXT("Prototype_Component_Collision"), (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CFreeze : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CFreeze : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CFreeze : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Freeze"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Stab_Effect"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CFreeze : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CFreeze * CFreeze::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CFreeze* pInstance = new CFreeze(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CFreeze : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CFreeze::Clone(void * pArg)
{
	CFreeze* pInstance = new CFreeze(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CFreeze : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CFreeze::Free()
{
	__super::Free();
	Safe_Release(m_pCollision);
}
