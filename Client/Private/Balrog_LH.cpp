#include "stdafx.h"
#include "..\Public\Balrog_LH.h"

CBalrog_LH::CBalrog_LH(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBalrog_LH::CBalrog_LH(const CBalrog_LH & rhs)
	: CMonster(rhs)
{
}

HRESULT CBalrog_LH::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBalrog_LH : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 100;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_tInfo.iAtt = 10;
	m_iDeadSprite = 0;

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CBalrog_LH::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBalrog_LH : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBalrog_LH : NativeConstruct");
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

	m_pTransform->Scaled(_float3(3.51f, 4.01f, 3.51f));

	m_iSprite = 0;
	return S_OK;
}

void CBalrog_LH::Tick(_float fTimeDelta) {

	__super::Tick(fTimeDelta);

	Diving();

	_float3 vTargetPos = m_tMonster.pTargetTransform->Get_State(CTransform::STATE_POSITION);
	_float3 vMyPos = m_pTransform->Get_State(CTransform::STATE_POSITION);
	_float3 Dir2 = vTargetPos - vMyPos;

	_float Dir = D3DXVec3Length(&Dir2);

	//Un_Gravity(fTimeDelta);

	CTransform* pPlayerTransform = (CTransform*)m_pGameInstance->Get_Component(LEVEL_STATIC, TEXT("Layer_Player"), TEXT("Com_Transform"), 0);
	Safe_AddRef(pPlayerTransform);
	_float3 fPlayerPos = pPlayerTransform->Get_State(CTransform::STATE_POSITION);

	CMonster::MONSTER tMonster;
	tMonster.mapCube = m_tMonster.mapCube;
	tMonster.pTargetTransform = m_tMonster.pTargetTransform;
	tMonster.vPosition = fPlayerPos;

	++m_tickCount;
	if (m_tickCount == 250)
	{
		m_tickCount = 0;
		m_iRand = rand() % 100 + 1;
		m_bCheck = true;
	}
	
	if (Dir <= 10.f)
	{
		if (m_iRand <= 30)
		{
			m_bCheck2 = true;
			if (m_bPreCheck2 != m_bCheck2)
			{
				m_bPreCheck2 = true;
				Safe_Release(m_pTexture);
				m_pTexture = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STAGEBOSS, L"Layer_Monster", L"Com_Texture_Balrog_LH", 3);
				Safe_AddRef(m_pTexture);
			}
			if (m_bCheck == true && m_iSprite >= 8)
			{
				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_Electric_Shock"), &tMonster))) {
					MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
					return;
				}
				m_bCheck = false;
			}
			++m_iTick;
			if (m_iTick == 8)
			{
				m_iTick = 0;
				++m_iSprite;

				if (m_iSprite >= 18)
					m_iSprite = 0;
			}
		}
		else if (m_iRand >= 70)
		{
			m_bCheck2 = false;
			if (m_bPreCheck2 != m_bCheck2)
			{
				m_bPreCheck2 = false;
				Safe_Release(m_pTexture);
				m_pTexture = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STAGEBOSS, L"Layer_Monster", L"Com_Texture_Balrog_LH2", 3);
				Safe_AddRef(m_pTexture);
			}
			if (m_bCheck == true && m_iSprite >= 11)
			{
				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, TEXT("Layer_Monster"), TEXT("Prototype_GameObject_PurplePog"), &tMonster))) {
					MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Monster");
					return;
				}
				m_bCheck = false;
			}
			++m_iTick;
			if (m_iTick == 8)
			{
				m_iTick = 0;
				++m_iSprite;

				if (m_iSprite >= 22)
					m_iSprite = 0;
			}
		}
		else
			m_iSprite = 0;
	}


	Safe_Release(pPlayerTransform);

}

void CBalrog_LH::LateTick(_float fTimeDelta) {

	__super::LateTick(fTimeDelta);
	if (m_tInfo.iHp <= 0)
		m_eState = STATE_DEAD;
	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);

}

HRESULT CBalrog_LH::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBalrog_LH : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBalrog_LH::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBalrog_LH : SetUp_Components");
		return E_FAIL;
	}

	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Balrog_LH2"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog_LH2"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBalrog_LH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBalrog_LH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBalrog_LH : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CBalrog_LH : SetUp_Components");
		return E_FAIL;
	}
	Safe_Release(m_pTexture);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Balrog_LH"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog_LH"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBalrog_LH : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CBalrog_LH* CBalrog_LH::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBalrog_LH*	pInstance = new CBalrog_LH(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBalrog_LH : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBalrog_LH::Clone(void* pArg) {
	CBalrog_LH*	pInstance = new CBalrog_LH(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBalrog_LH : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBalrog_LH::Free() {
	__super::Free();
}