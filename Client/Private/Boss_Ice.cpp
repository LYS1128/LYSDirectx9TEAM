#include "stdafx.h"
#include "..\Public\Boss_Ice.h"

CBoss_Ice::CBoss_Ice(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CMonster(pGraphic_Device)
{
}

CBoss_Ice::CBoss_Ice(const CBoss_Ice & rhs)
	: CMonster(rhs)
{
}

HRESULT CBoss_Ice::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CBoss_Ice : NativeConstruct_Prototype");
		return E_FAIL;
	}
	ZeroMemory(&m_tInfo, sizeof(INFO));

	m_tInfo.iMaxHp = 10;
	m_tInfo.iAtt = 110;
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_iDeadSprite = 0;

	m_vCollision = { 1.f, 1.f, 1.f };

	return S_OK;
}

HRESULT CBoss_Ice::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CBoss_Ice : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CBoss_Ice : NativeConstruct");
		return E_FAIL;
	}

	CTransform* PlayerTrans = (CTransform*)(m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform"));
	_float3 PlayerPos = PlayerTrans->Get_State(CTransform::STATE_POSITION);

	m_pTransform->Set_State(CTransform::STATE_POSITION, PlayerPos);
	m_fOriginPos = PlayerPos;

	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_pTransform->Set_State(CTransform::STATE_UP, _float3(0.f, 1.f, 0.f));

	m_pTransform->Scaled(_float3(1.01f, 1.51f, 1.01f));

	_float3 Pos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	for (_uint i = 0; i < 20; ++i)
	{
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_IceParticle", &Pos);
	}
	Pos += _float3(0.f, -0.3f, 0.f);
	for (_uint i = 0; i < 20; ++i)
	{
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_IceParticle", &Pos);

	}

	m_iSprite = 0;
	return S_OK;
}

void CBoss_Ice::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);

	CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());

	++m_iTick;
	if (m_iTick == 6)
	{
		pPlayer->Stop_Player();
		m_iTick = 0;
		++m_iSprite;		
	}
	
}

void CBoss_Ice::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);

	CPlayer* pPlayer = (CPlayer*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front());
	if (m_iSprite >= 14)
	{
		pPlayer->UnStop_Player();
		m_eState = STATE_DEAD;		
	}

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CBoss_Ice::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CBoss_Ice : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CBoss_Ice::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CBoss_Ice : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Boss_Ice"), LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Ice"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CBoss_Ice : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CBoss_Ice : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CBoss_Ice : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Collision", LEVEL_STATIC, L"Prototype_Component_Collision", (CComponent**)&m_pCollision))) {
		MSG_BOX(L"Failed To CBoss_Ice : SetUp_Components");
		return E_FAIL;
	}
	return S_OK;
}

CBoss_Ice* CBoss_Ice::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CBoss_Ice*	pInstance = new CBoss_Ice(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CBoss_Ice : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CBoss_Ice::Clone(void* pArg) {
	CBoss_Ice*	pInstance = new CBoss_Ice(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CBoss_Ice : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBoss_Ice::Free() {
	__super::Free();
}