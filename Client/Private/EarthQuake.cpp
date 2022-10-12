#include "stdafx.h"
#include "..\Public\EarthQuake.h"

CEarthQuake::CEarthQuake(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CEffect(pGraphic_Device)
{
}

CEarthQuake::CEarthQuake(const CEarthQuake & rhs)
	: CEffect(rhs)
{
}

HRESULT CEarthQuake::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CEarthQuake : NativeConstruct_Prototype");
		return E_FAIL;
	}
	m_fDamagePercent = 4.0f;
	return S_OK;
}

HRESULT CEarthQuake::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CEarthQuake : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CEarthQuake : NativeConstruct");
		return E_FAIL;
	}

	m_tSkillFrame.fFrame = 0.f;
	m_tSkillFrame.iSpriteEnd = 9;

	m_eSkillID = SKILL_EARTHQUAKE;

	m_pTransform->Set_State(CTransform::STATE_LOOK, _float3(0.f, 1.f, 0.f));

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	_float3 BuffUp = _float3(-1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffUp, &BuffUp);
	m_pTransform->Set_State(CTransform::STATE_UP, BuffUp);

	m_tEffect.mapCube = ((CPlayer::EFFECT*)pArg)->mapCube;
	m_tEffect.pTargetTransform = ((CPlayer::EFFECT*)pArg)->pTargetTransform;

	_float3 vTargetPos = m_tEffect.pTargetTransform->Get_State(CTransform::STATE_POSITION);
	m_pTransform->Set_State(CTransform::STATE_POSITION, vTargetPos);
	m_pTransform->Scaled(_float3(5.0f, 5.0f, 5.0f));

	return S_OK;
}

void CEarthQuake::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	_uint PlayerIndex = (_uint)(m_tEffect.pTargetTransform->Get_State(CTransform::STATE_POSITION).x + 0.5) * 10000
		+ (_uint)(m_tEffect.pTargetTransform->Get_State(CTransform::STATE_POSITION).y + 0.5) * 100
		+ (_uint)(m_tEffect.pTargetTransform->Get_State(CTransform::STATE_POSITION).z + 0.5);

	for (_uint i = PlayerIndex; (i - (_uint)(i / 10000) * 10000) / 100 != 0;) {
		if ((m_tEffect.mapCube.find(i - 100) != m_tEffect.mapCube.end())) {
			m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x,
				(*(m_tEffect.mapCube.find(i - 100))).second.y + 0.51f, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
			break;
		}
		i -= 100;
	}

	_float3 vMyPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(vMyPos.x, vMyPos.y, vMyPos.z));
	
	Compute_ZDis(m_pTransform);
}

void CEarthQuake::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CEarthQuake::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CEarthQuake : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice((_uint)m_fFrame))) {
		MSG_BOX(L"Failed To CEarthQuake : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CEarthQuake : Render");
		return E_FAIL;
	}
	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CEarthQuake::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 10.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CEarthQuake : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CEarthQuake : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CEarthQuake : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_EarthQuake"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_EarthQuake"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CEarthQuake : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CEarthQuake* CEarthQuake::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CEarthQuake* pInstance = new CEarthQuake(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))	{
		MSG_BOX(TEXT("Failed To CEarthQuake : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CEarthQuake::Clone(void* pArg) {
	CEarthQuake* pInstance = new CEarthQuake(*this);

	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CEarthQuake : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CEarthQuake::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
}