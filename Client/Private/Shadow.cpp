#include "stdafx.h"
#include "..\Public\Shadow.h"
#include "../Public/Monster.h"

CShadow::CShadow(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CShadow::CShadow(const CShadow & rhs)
	:CGameObject(rhs)
{
}

HRESULT CShadow::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CShadow : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CShadow::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CShadow : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CShadow : NativeConstruct");
		return E_FAIL;
	}

	m_pTransformCom->Scaled(_float3(0.7f, 0.7f, 0.7f));

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 5.f, 0.f));

	m_pTransformCom->Set_State(CTransform::STATE_LOOK, _float3(0.f, 1.f, 0.f));

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, BuffRight);

	_float3 BuffUp = _float3(-1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffUp, &BuffUp);
	m_pTransformCom->Set_State(CTransform::STATE_UP, BuffUp);

	m_tShadow.mapCube = ((SHADOW*)pArg)->mapCube;
	m_tShadow.pTargetTransform = ((SHADOW*)pArg)->pTargetTransform;
	m_tShadow.pMyMonster = ((SHADOW*)pArg)->pMyMonster;

	return S_OK;
}

void CShadow::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	_uint PlayerIndex = (_uint)(m_tShadow.pTargetTransform->Get_State(CTransform::STATE_POSITION).x + 0.5) * 10000
		+ (_uint)(m_tShadow.pTargetTransform->Get_State(CTransform::STATE_POSITION).y + 0.5) * 100
		+ (_uint)(m_tShadow.pTargetTransform->Get_State(CTransform::STATE_POSITION).z + 0.5);

	for (_uint i = PlayerIndex; (i - (_uint)(i / 10000) * 10000) / 100 != 0;) {
		if ((m_tShadow.mapCube.find(i - 100) != m_tShadow.mapCube.end())) {
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(m_pTransformCom->Get_State(CTransform::STATE_POSITION).x,
				(*(m_tShadow.mapCube.find(i - 100))).second.y + 0.51f, m_pTransformCom->Get_State(CTransform::STATE_POSITION).z));
			break;
		}
		i -= 100;
	}

	_float3 vTargetPos = m_tShadow.pTargetTransform->Get_State(CTransform::STATE_POSITION);
	_float3 vMyPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	_float vDir = vTargetPos.y - vMyPos.y;

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(vTargetPos.x + 0.15f,vMyPos.y,vTargetPos.z + 0.15f));
	if (vDir > 1) {
		m_pTransformCom->Scaled(_float3(0.7f / vDir, 0.7f / vDir, 0.7f / vDir));
	}
	else {
		m_pTransformCom->Scaled(_float3(0.7f, 0.7f, 0.7f));
	}
	Compute_ZDis(m_pTransformCom);
}

void CShadow::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_ALPHABLEND, this);
	if (m_tShadow.pMyMonster != nullptr && STATE_DEAD == m_tShadow.pMyMonster->Get_State()) {
		m_eState = STATE_DEAD;
	}
}

HRESULT CShadow::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CShadow : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(0))) {
		MSG_BOX(L"Failed To CShadow : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CShadow : Render");
		return E_FAIL;
	}
	m_pVIBufferCom->Render();
	return S_OK;
}

HRESULT CShadow::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 10.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc))) {
		MSG_BOX(L"Failed To CShadow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom))) {
		MSG_BOX(L"Failed To CShadow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom))) {
		MSG_BOX(L"Failed To CShadow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureShadow"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shadow"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CShadow : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CShadow* CShadow::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CShadow* pInstance = new CShadow(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))	{
		MSG_BOX(TEXT("Failed To CShadow : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CShadow::Clone(void* pArg) {
	CShadow* pInstance = new CShadow(*this);

	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CShadow : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CShadow::Free() {
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
}