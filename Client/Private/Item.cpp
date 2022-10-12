#include "stdafx.h"
#include "..\Public\Item.h"


CItem::CItem(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CItem::CItem(const CItem& rhs)
	:CGameObject(rhs)
{
}

HRESULT CItem::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CItem : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CItem::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CItem : NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct");
		return E_FAIL;
	}

	m_pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front());
	m_tItem.iOption = ((ITEM*)pArg)->iOption;
	m_tItem.pTargetTransform = ((ITEM*)pArg)->pTargetTransform;
	m_tItem.mapCube = ((ITEM*)pArg)->mapCube;
	m_tItem.vPosition = ((ITEM*)pArg)->vPosition;
	m_pTransform->Set_State(CTransform::STATE_POSITION, (m_tItem.pTargetTransform)->Get_State(CTransform::STATE_POSITION)+ m_tItem.vPosition);

	_uint PlayerIndex = (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).x + 0.5) * 10000
		+ (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).y + 0.5) * 100
		+ (_uint)(m_pTransform->Get_State(CTransform::STATE_POSITION).z + 0.5);

	for (_uint i = PlayerIndex; (i - (_uint)(i / 10000) * 10000) / 100 != 0;) {
		if ((m_tItem.mapCube.find(i - 100) != m_tItem.mapCube.end())) {
			m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x,
				(*(m_tItem.mapCube.find(i - 100))).second.y + 1.f, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
			break;
		}
		i -= 100;
	}
	
	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_pTransform->Scaled(_float3(0.5f, 1.0f, 0.5f));

	return S_OK;
}

void CItem::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	if (Check_Player_InArea())
	{
		m_eState = STATE_DEAD;
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
		CSound_Manager::GetInstance()->PlaySound(L"Get_Item.wav", CSound_Manager::EFFECT, VOLUME5);
		if (m_tItem.iOption == 0)
		{
			m_pPlayer->PlusHpPo();
		}
		else if (m_tItem.iOption == 1)
		{
			m_pPlayer->PlusMpPo();
		}
		else if (m_tItem.iOption == 2)
		{
			m_pPlayer->PlusSoul();
		}
		else if (m_tItem.iOption == 3)
		{
			m_pPlayer->PlusMeso();
		}

	}
}

void CItem::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CItem::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CItem : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_tItem.iOption))) {
		MSG_BOX(L"Failed To CMagician : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CMagician : Render");
		return E_FAIL;
	}

	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CItem::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureItem"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CTheif : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

_bool CItem::Check_Player_InArea() {
	_float3 vTargetPosition = ((CTransform*)(m_pPlayer->Get_Component(L"Com_Transform")))->Get_State(CTransform::STATE_POSITION);
	CTransform* pTransPlayer = (CTransform*)(m_pPlayer->Get_Component(L"Com_Transform"));
	_float3 vPosition = m_pTransform->Get_State(CTransform::STATE_POSITION);
	_float3 vScale = m_pTransform->Get_Scale();

	/*if (vPosition.y - vScale.y <= vTargetPosition.y && vPosition.y + vScale.y >= vTargetPosition.y) {
		_float fDis = sqrtf(pow((vPosition.x - vTargetPosition.x), 2) + pow((vPosition.z - vTargetPosition.z), 2));
		if (vScale.x * 0.5f >= fDis) {
			return true;
		}
	}*/
	_float fXYDis = sqrtf(pow((vTargetPosition.x - vPosition.x), 2) + pow((vTargetPosition.z - vPosition.z), 2));
	_float fDis = sqrtf(pow(fXYDis, 2) + pow((vTargetPosition.y - vPosition.y), 2));

	if (m_pCollision->Collision_Cylinder(m_pTransform, pTransPlayer)) {
		return true;
	}
	else if (fDis < 1.f)
	{
		_float3 fGo = vTargetPosition - vPosition;
		D3DXVec3Normalize(&fGo, &fGo);
		m_pTransform->Set_State(CTransform::STATE_POSITION, vPosition + fGo*0.05);
		return false;
	}
	return false;
}


CItem* CItem::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CItem*	pInstance = new CItem(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CSlime : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CItem::Clone(void* pArg) {
	CItem*	pInstance = new CItem(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CSlime : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CItem::Free() {
	__super::Free();
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pCollision);
}