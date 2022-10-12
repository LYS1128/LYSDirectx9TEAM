#include "stdafx.h"
#include "..\Public\UI.h"

CUI::CUI(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CUI::CUI(const CUI& rhs)
	:CGameObject(rhs)
{
	memcpy(&m_tUIInfo, &rhs.m_tUIInfo, sizeof(UIINFO));
}

HRESULT CUI::NativeConstruct_Prototype() {
	ZeroMemory(&m_tUIInfo, sizeof(UIINFO));
	return S_OK;
}

HRESULT CUI::NativeConstruct(void* pArg) {
	m_pGraphic_Device->GetViewport(&m_ViewPort);
	D3DXMatrixOrthoLH(&m_ProjMatrix, (_float)m_ViewPort.Width, (_float)m_ViewPort.Height, 0.f, 1.f);
	
	m_pPlayer = (CPlayer*)pArg;
	
	return S_OK;
}

void CUI::Tick(_float fTimeDelta) {
	m_pTransform->Scaled(_float3(m_tUIInfo.fCX, m_tUIInfo.fCY, 1.f));
	m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(m_tUIInfo.fX - m_ViewPort.Width * 0.5f, -m_tUIInfo.fY + m_ViewPort.Height * 0.5f, 0.0f));
}

void CUI::LateTick(_float fTimeDelta) {
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_UI, this);
}

HRESULT CUI::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CUI : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite))) {
		MSG_BOX(L"Failed To CUI : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CUI : Render");
		return E_FAIL;
	}
	_float4x4 ViewMatrix;
	D3DXMatrixIdentity(&ViewMatrix);

	_float4x4 OriginView;
	m_pGraphic_Device->GetTransform(D3DTS_VIEW, &OriginView);
	_float4x4 OriginProj;
	m_pGraphic_Device->GetTransform(D3DTS_PROJECTION, &OriginProj);

	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &ViewMatrix);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &m_ProjMatrix);

	m_pVIBuffer->Render();

	m_pGraphic_Device->SetTransform(D3DTS_VIEW, &OriginView);
	m_pGraphic_Device->SetTransform(D3DTS_PROJECTION, &OriginProj);

	return S_OK;
}

void CUI::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTexture);
	Safe_Release(m_pRenderer);
}