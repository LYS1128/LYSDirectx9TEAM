#include "..\Public\Button_Base.h"

CButton_Base::CButton_Base(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CButton_Base::CButton_Base(const CButton_Base& rhs)
	:CGameObject(rhs)
{
}

HRESULT CButton_Base::NativeConstruct_Prototype() {
	return S_OK;
}

HRESULT CButton_Base::NativeConstruct(void* pArg) {
	if (nullptr == pArg) {
		MSG_BOX(L"Failed To CButton_Base : NativeConstruct");
		return E_FAIL;
	}
	memcpy(&m_tButtonDesc, &pArg, sizeof(BUTTONDESC));

	m_pTransform = CTransform::Create(m_pGraphic_Device);
	if (nullptr == m_pGraphic_Device) {
		MSG_BOX(L"Failed To CButton_Base : NativeConstruct");
		return E_FAIL;
	}
	m_pTransform->Set_State(CTransform::STATE_POSITION, m_tButtonDesc.vPos);
	return S_OK;
}

void CButton_Base::Tick(_float fTimeDelta) {
}

void CButton_Base::LateTick(_float fTimeDelta) {
}

HRESULT CButton_Base::Render() {
	return S_OK;
}

void CButton_Base::Free() {
}