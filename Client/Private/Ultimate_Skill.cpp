#include "stdafx.h"
#include "..\Public\Ultimate_Skill.h"

CUltimate_Skill::CUltimate_Skill(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CUI(pGraphic_Device)
{
}

CUltimate_Skill::CUltimate_Skill(const CUltimate_Skill & rhs)
	:CUI(rhs)
{
}

HRESULT CUltimate_Skill::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CUltimate_Skill : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUltimate_Skill::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CUltimate_Skill : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CUltimate_Skill : NativeConstruct");
		return E_FAIL;
	}
	m_tUIInfo.fCX = 1280.f;
	m_tUIInfo.fCY = 720.f;
	m_tUIInfo.fX = 640.f;
	m_tUIInfo.fY = 360.f;

	m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Skill_UI", L"Prototype_GameObject_Dark_UI", this);

	return S_OK;
}

void CUltimate_Skill::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	++m_iTickCount;
	if (5 <= m_iTickCount) {
		++m_iSprite;
		m_iTickCount = 0;
		if (30 <= m_iSprite) {
			m_iSprite = 0;
			m_eState = STATE_DEAD;

			list<CGameObject*>* pMonsterList = nullptr;
			if (LEVEL_STAGEBOSS != g_iLevel) {
				pMonsterList = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Monster");
			}
			else {
				pMonsterList = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Boss");
			}
			if (nullptr != pMonsterList) {
				if (0 != pMonsterList->size()) {
					for (auto& iter = pMonsterList->begin(); iter != pMonsterList->end(); ++iter) {
						CTransform* pTargetTransform = (CTransform*)((*iter)->Get_Component(L"Com_Transform"));
						_float3 fTargetPos = pTargetTransform->Get_State(CTransform::STATE_POSITION);
						m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", L"Prototype_GameObject_MoonLight", &fTargetPos);
					}
				}
			}
		}
	}
}

void CUltimate_Skill::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);
}

HRESULT CUltimate_Skill::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CUltimate_Skill : Render");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CUltimate_Skill::SetUp_Components() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform))) {
		MSG_BOX(L"Failed To CUltimate_Skill : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_MoonLight"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CUltimate_Skill : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CUltimate_Skill : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CUltimate_Skill : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CUltimate_Skill * CUltimate_Skill::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CUltimate_Skill* pInstance = new CUltimate_Skill(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CUltimate_Skill : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CUltimate_Skill::Clone(void * pArg) {
	CUltimate_Skill* pInstance = new CUltimate_Skill(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CUltimate_Skill : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CUltimate_Skill::Free() {
	__super::Free();
}