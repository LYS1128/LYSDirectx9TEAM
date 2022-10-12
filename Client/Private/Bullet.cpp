#include "stdafx.h"
#include "..\Public\Bullet.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CBullet::CBullet(const CBullet & rhs)
	:CGameObject(rhs)
{
}

HRESULT CBullet::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBullet : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBullet::NativeConstruct(void * pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBullet : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBullet : NativeConstruct");
		return E_FAIL;
	}
	_float4x4 WorldMatrix;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &WorldMatrix);
	D3DXMatrixInverse(&WorldMatrix, nullptr, &WorldMatrix);

	_float3 vPos = *((_float3*)(&WorldMatrix.m[3][0]));
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);

	m_vLook = *((_float3*)(&WorldMatrix.m[2][0]));

	m_pTransform->Scaled(_float3(0.1f, 0.1f, 0.1f));

	return S_OK;
}

void CBullet::Tick(_float fTimeDelta) {
	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	vPos += m_vLook * m_pTransform->Get_TransDesc().fSpeedPerSec * fTimeDelta;
	m_pTransform->Set_State(CTransform::STATE_POSITION, vPos);
}

void CBullet::LateTick(_float fTimeDelta) {

	_float3 vPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	if (-1.f >= vPos.x || 26.f <= vPos.x || -1.f >= vPos.y || 5.f <= vPos.y || -1.f >= vPos.z || 26.f <= vPos.z) {
		m_eState = STATE_DEAD;
	}
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CBullet::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBullet : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(0))) {
		MSG_BOX(L"Failed To CBullet : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CBullet : Render");
		return E_FAIL;
	}

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	m_pVIBuffer->Render();

	m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

HRESULT CBullet::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bullet"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Cube", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CSnow : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CBullet* CBullet::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBullet*	pInstance = new CBullet(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBullet : CSnow"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBullet::Clone(void * pArg) {
	CBullet*	pInstance = new CBullet(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBullet : CSnow"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBullet::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pCollision);
}