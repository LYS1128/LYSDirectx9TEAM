#include "stdafx.h"
#include "..\Public\Player.h"
#include "../Public/StatWindow.h"
#include "../Public/Monster.h"
#include "../Public/GameOver.h"
#include "../Public/Boss_Skill.h"
#include "../Public/BossHit_Effect.h"
#include "../Public/MultiCamera.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CPlayer::CPlayer(const CPlayer & rhs)
	: CGameObject(rhs)
{
}

HRESULT CPlayer::NativeConstruct_Prototype() {
	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CPlayer : NativeConstruct_Prototype");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayer::NativeConstruct(void* pArg) {
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CPlayer : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CPlayer : NativeConstruct");
		return E_FAIL;
	}
	

	m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(7.f, 10.f, 7.f));

	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_eBind = BIND_7;
	m_ePlayerState = U_STAND;
	m_eBasicState = STATE_U;

	m_tInfo.iMaxHp = 100;
	m_tInfo.iHp = m_tInfo.iMaxHp;

	m_tInfo.iMaxMp = 100;
	m_tInfo.iMp = m_tInfo.iMaxMp;

	m_tInfo.iAtt = 10;
	m_tInfo.iDef = 10;
	m_tInfo.iGold = 0;

	m_tInfo.iLevel = 1;
	m_tInfo.iExp = 0;
	m_tInfo.iMaxExp = 100;

	m_pTransformCom->Scaled(_float3(1.f, 1.3f,1.f));

	CShadow::SHADOW tShadow;

	m_mapCube = *(map<const _uint, _float4>*)pArg;
	tShadow.mapCube = m_mapCube;
	tShadow.pTargetTransform = m_pTransformCom;
	tShadow.pMyMonster = nullptr;

	if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Shadow", L"Prototype_GameObject_Shadow", &tShadow))) {
		MSG_BOX(L"Failed To CPlayer : NativeConstruct");
		return E_FAIL;
	}

	CText::FONT tFont;
	ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont.rc = RECT{ 782, 590, 1280,800 };
	lstrcpy(tFont.szText, L"0");
	tFont.tFontInfo.Height = 20;
	tFont.tFontInfo.Width = 15;
	tFont.eTextId = CText::TEXT_INVEN;
	tFont.vARGB = _float4(255, 255, 255, 255);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_InvenFont", L"Prototype_GameObject_Font", &tFont);

	CText::FONT tFont1;
	ZeroMemory(&tFont1.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont1.rc = RECT{ 834, 590, 1280,800 };
	lstrcpy(tFont1.szText, L"0");
	tFont1.tFontInfo.Height = 20;
	tFont1.tFontInfo.Width = 15;
	tFont1.eTextId = CText::TEXT_INVEN;
	tFont1.vARGB = _float4(255, 255, 255, 255);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_InvenFont", L"Prototype_GameObject_Font", &tFont1);

	CText::FONT tFont2;
	ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont2.rc = RECT{ 886, 590, 1280,800 };
	lstrcpy(tFont2.szText, L"0");
	tFont2.tFontInfo.Height = 20;
	tFont2.tFontInfo.Width = 15;
	tFont2.eTextId = CText::TEXT_INVEN;
	tFont2.vARGB = _float4(255, 255, 255, 255);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_InvenFont", L"Prototype_GameObject_Font", &tFont2);

	CText::FONT tFont3;
	ZeroMemory(&tFont3.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont3.rc = RECT{ 938, 590, 1280,800 };
	lstrcpy(tFont3.szText, L"0");
	tFont3.tFontInfo.Height = 20;
	tFont3.tFontInfo.Width = 15;
	tFont3.eTextId = CText::TEXT_INVEN;
	tFont3.vARGB = _float4(255, 255, 255, 255);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_InvenFont", L"Prototype_GameObject_Font", &tFont3);



	//HpMp가라로띄운곳

	CText::FONT tFont4;
	ZeroMemory(&tFont4.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont4.rc = RECT{ 640 - 40, 360 + 208, 1280,800 };
	lstrcpy(tFont4.szText, L"0");
	tFont4.tFontInfo.Height = 20;
	tFont4.tFontInfo.Width = 15;
	tFont4.eTextId = CText::TEXT_INVEN;
	tFont4.vARGB = _float4(255, 255, 255, 255);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_InvenFont", L"Prototype_GameObject_Font", &tFont4);

	CText::FONT tFont5;
	ZeroMemory(&tFont5.tFontInfo, sizeof(D3DXFONT_DESCW));
	tFont5.rc = RECT{650 ,360 + 208, 1280,800 };
	lstrcpy(tFont5.szText, L"0");
	tFont5.tFontInfo.Height = 20;
	tFont5.tFontInfo.Width = 15;
	tFont5.eTextId = CText::TEXT_INVEN;
	tFont5.vARGB = _float4(255, 255, 255, 255);
	m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_InvenFont", L"Prototype_GameObject_Font", &tFont5);

	return S_OK;
}

void CPlayer::Tick(_float fTimeDelta) {
	__super::Tick(fTimeDelta);
	Skill_Tick();

	_float4x4 worldmatrix = m_pTransformCom->Get_WorldMatrix();

	if (PLAYER_DEAD != m_eState) {
		Key_Input(fTimeDelta);

		Compute_ZDis(m_pTransformCom);

		Collision_Monster();
		Damaged_MonsterSkill();
	}
	else {
		m_eBind = BIND_1;
		Safe_Release(m_pTextureCom);
		m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureDie");
		Safe_AddRef(m_pTextureCom);
		return;
	}
	Diving();
	if (true == m_bDamaged) {
		++m_iDamagedTick;
		_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		_float3 vLook;
		switch (m_eBasicState) {
		case STATE_L: {
			vLook = _float3(-1.f, 0.f, 1.f);
			break;
		}
		case STATE_R: {
			vLook = _float3(1.f, 0.f, -1.f);
			break;
		}
		case STATE_U: {
			vLook = _float3(1.f, 0.f, 1.f);
			break;
		}
		case STATE_D: {
			vLook = _float3(-1.f, 0.f, -1.f);
			break;
		}
		case STATE_UL: {
			vLook = _float3(0.f, 0.f, 1.f);
			break;
		}
		case STATE_UR: {
			vLook = _float3(1.f, 0.f, 0.f);
			break;
		}
		case STATE_DL: {
			vLook = _float3(-1.f, 0.f, 0.f);
			break;
		}
		case STATE_DR: {
			vLook = _float3(0.f, 0.f, -1.f);
			break;
		}
		}
		D3DXVec3Normalize(&vLook, &vLook);
		vLook.y = -3.f;
		vPos -= vLook * m_pTransformCom->Get_TransDesc().fSpeedPerSec * 1.f * fTimeDelta;
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
		if (10 <= m_iDamagedTick) {
			m_iDamagedTick = 0;
			m_bDamaged = false;
		}
	}

	if (m_eState != STATE_SUPERARMOR && true == m_bSuper) {
		++m_iSuperTick;
		if (30 <= m_iSuperTick) {
			m_iSuperTick = 0;
			m_bSuper = false;
		}
	}
	
	++m_iMpUp;
	if (m_iMpUp >= 60 && m_tInfo.iMp < m_tInfo.iMaxMp)
	{
		m_iMpUp = 0;
		++m_tInfo.iMp;
	}
	auto iter = m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_InvenFont")->Get_List()->begin();

	CText* pText = (CText*)(*iter);
	_tchar sz[32] = L"";
	wsprintf(sz, L"%d", m_iHpPotion);
	pText->Set_Text(sz);

	++iter;

	CText* pText1 = (CText*)(*iter);
	_tchar sz1[32] = L"";
	wsprintf(sz1, L"%d", m_iMpPotion);
	pText1->Set_Text(sz1);

	++iter;

	CText* pText2 = (CText*)(*iter);
	_tchar sz2[32] = L"";
	wsprintf(sz2, L"%d", m_iSoul);
	pText2->Set_Text(sz2);

	++iter;

	CText*  pText3 = (CText*)(*iter);
	_tchar sz3[32] = L"";
	wsprintf(sz3, L"%d", m_iMeso);
	pText3->Set_Text(sz3);

	if ((_float)m_tInfo.iHp/(_float)m_tInfo.iMaxHp <= 0.2f && m_bHpLow == false)
	{
		m_bHpLow = true;
		m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_HpLow", L"Prototype_GameObject_HpLow");
	}

	//HpMp가라로띄운부부부부부부부부
	++iter;
	CText*  pText4 = (CText*)(*iter);
	_tchar sz4[32] = L"";
	wsprintf(sz4, L"%d", m_tInfo.iHp);
	pText4->Set_Text(sz4);
	++iter;
	CText*  pText5 = (CText*)(*iter);
	_tchar sz5[32] = L"";
	wsprintf(sz5, L"%d", m_tInfo.iMp);
	pText5->Set_Text(sz5);

	if (true == m_bAttack && 4 == m_iTick) {
		++m_iAttack;
		m_bMoving = true;
		if (4 == m_iAttack) {
			m_bAttack = false;
			m_bMoving = false;
			m_iAttack = 0;
		}
	}
}

void CPlayer::LateTick(_float fTimeDelta) {
	__super::LateTick(fTimeDelta);

	if (GetKeyState('N') & 0x8000) {
		m_tInfo.iExp += 10;
	}

	if (m_pGameInstance->Key_Down('K'))	{
		if (m_bStatWin == false) {
			if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_StatWindow", L"Prototype_GameObject_StatWindow_UI"))) {
				MSG_BOX(L"Failed To CPlayer : Late_Tick");
				return;
			}
			m_bStatWin = true;
		}
		else {
			CStatWindow* pStatWindow = (CStatWindow*)(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_StatWindow")->Get_List()->front());
			pStatWindow->Set_Dead();
			list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_FontS")->Get_List();
			for (auto iter : *pText)
			{
				if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_STAT)
					iter->Set_Dead();
			}
			m_bStatWin = false;
		}
	}

	if (m_tInfo.iExp >= m_tInfo.iMaxExp && m_tInfo.iLevel < 30)	{
		++m_tInfo.iLevel;
		Level_Up();
	}
	else if(m_tInfo.iLevel == 30) {
		m_tInfo.iExp = 0;
	}

	++m_iTick;

	if (m_iTick == 5) {
		++m_iSprite;
		m_iTick = 0;
	}

	if (m_bJumping == true) {
		_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		vPosition.y += (2.5f - (G * m_fJumpTime * 0.5f)) * 0.1f;
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);
		m_fJumpTime += 0.05f;
	}
	else {
		if (m_Grav != 2)
			Gravity(fTimeDelta);
	}
	Collision_Ground();

	if (m_pGameInstance->Key_Pressing(VK_CONTROL) && m_pGameInstance->Key_Down('1') && m_iHpPotion > 0)
	{
		m_iHpPotion -= 1;
		m_tInfo.iHp += 100;
		if (m_tInfo.iHp > m_tInfo.iMaxHp)
			m_tInfo.iHp = m_tInfo.iMaxHp;
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT);
		CSound_Manager::GetInstance()->PlaySound(L"Potion.wav", CSound_Manager::SYSTEM_EFFECT, VOLUME5);
	}
	if (m_pGameInstance->Key_Pressing(VK_CONTROL) && m_pGameInstance->Key_Down('2') && m_iMpPotion > 0)
	{
		m_iMpPotion -= 1;
		m_tInfo.iMp += 30;
		if (m_tInfo.iMp > m_tInfo.iMaxMp)
			m_tInfo.iMp = m_tInfo.iMaxMp;
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT);
		CSound_Manager::GetInstance()->PlaySound(L"Potion.wav", CSound_Manager::SYSTEM_EFFECT, VOLUME5);
	}

	if (0 >= m_tInfo.iHp && m_eState != PLAYER_DEAD) {
		Player_Dead();
		m_bDead = true;
	}
	
	m_pRendererCom->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CPlayer::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CPlayer : Render");
		return E_FAIL;
	}
	if (m_eBind == BIND_10)	{
		if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(m_iSprite % 10))) {
			MSG_BOX(L"Failed To CPlayer : Render");
			return E_FAIL;
		}
	}
	else if (m_eBind == BIND_7)	{
		if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(m_iSprite % 7))) {
			MSG_BOX(L"Failed To CPlayer : Render");
			return E_FAIL;
		}
	}
	else if (m_eBind == BIND_5) {
		if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(m_iSprite % 5))) {
			MSG_BOX(L"Failed To CPlayer : Render");
			return E_FAIL;
		}
	}
	else if (m_eBind == BIND_1) {
		if (FAILED(m_pTextureCom->Bind_OnGraphicDevice(0))) {
			MSG_BOX(L"Failed To CPlayer : Render");
			return E_FAIL;
		}
	}
	if (FAILED(m_pTransformCom->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CPlayer : Render");
		return E_FAIL;
	}
	m_pVIBufferCom->Render();
	return S_OK;
}

HRESULT CPlayer::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransformCom, &TransformDesc))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Renderer"), LEVEL_STATIC, TEXT("Prototype_Component_Renderer"), (CComponent**)&m_pRendererCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_VIBuffer"), LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"), (CComponent**)&m_pVIBufferCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_Collsion"), LEVEL_STATIC, TEXT("Prototype_Component_Collision"), (CComponent**)&m_pCollisionCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(SetUp_Standing_Texture())) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	Safe_Release(m_pTextureCom);
	if (FAILED(SetUp_Run_Texture())) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	Safe_Release(m_pTextureCom);
	if (FAILED(SetUp_Stab_Texture())) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	Safe_Release(m_pTextureCom);
	if (FAILED(SetUp_HorCut_Texture())) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	Safe_Release(m_pTextureCom);
	if (FAILED(SetUp_VerCut_Texture())) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(L"Com_TextureDie", LEVEL_STATIC, L"Prototype_Component_Texture_Dead", (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Components");
		return E_FAIL;
	}
	//Safe_Release(m_pTextureCom);
	return S_OK;
}

HRESULT CPlayer::SetUp_Standing_Texture() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandL"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandL"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandR"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandR"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}
	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandLD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandLD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandLU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandLU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandRD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandRD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStandRU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandRU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Standing_Texture");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayer::SetUp_Run_Texture() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureL"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunL"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureR"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunR"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureLD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunLD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureLU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunLU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureRD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunRD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureRU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunRU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Run_Texture");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayer::SetUp_Stab_Texture() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabL"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabL"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabR"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabR"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabLD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabLD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabLU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabLU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabRD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabRD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureStabRU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabRU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_Stab_Texture");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayer::SetUp_HorCut_Texture() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_U"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_U"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_D"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_D"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_L"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_L"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_R"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_R"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_LD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_LD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_LU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_LU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_RD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_RD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Horcut_RU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_RU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_HorCut_Texture");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CPlayer::SetUp_VerCut_Texture() {
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_U"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_U"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_D"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_D"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_L"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_L"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_R"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_R"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_LD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_LD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_LU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_LU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_RD"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_RD"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}

	Safe_Release(m_pTextureCom);
	if (FAILED(__super::SetUp_Components(TEXT("Com_Texture_Vercut_RU"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_RU"), (CComponent**)&m_pTextureCom))) {
		MSG_BOX(L"Failed To CPlayer : SetUp_VerCut_Texture");
		return E_FAIL;
	}
	return S_OK;
}

void CPlayer::Key_Input(_float fTimeDelta) {
	if (LEVEL_STAGESPECIAL != g_iLevel) {
		//점프
		if (m_pGameInstance->Key_Down(VK_SPACE) && m_bJumping == false) {
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"Jump.wav", CSound_Manager::EFFECT, VOLUME5);
			m_bJumping = true;
		}

#pragma region 찌르기
		if (!m_pGameInstance->Key_Pressing(VK_CONTROL))
		{
			if (m_iFreezeTick == m_iFreezeCool * 60 && m_pGameInstance->Key_Down('1')) {
				m_iFreezeTick = 0;
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT);
				CSound_Manager::GetInstance()->PlaySound(L"Attack2.wav", CSound_Manager::SYSTEM_EFFECT, VOLUME5);

				EFFECT EffectInfo;
				EffectInfo.eBasicState = m_eBasicState;
				EffectInfo.mapCube = m_mapCube;
				EffectInfo.pTargetTransform = m_pTransformCom;

				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", L"Prototype_GameObject_Freeze", &EffectInfo))) {
					MSG_BOX(L"Failed To CFreeze : NativeConstruct");
					return;
				}

				m_bAttack = true;
				m_bMoving = true;
				switch (m_eBasicState) {
				case STATE_U: {
					m_ePlayerState = U_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabU");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				case STATE_D: {
					m_ePlayerState = D_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabD");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				case STATE_L: {
					m_ePlayerState = L_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabL");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				case STATE_R: {
					m_ePlayerState = R_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabR");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				case STATE_UL: {
					m_ePlayerState = LU_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabLU");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				case STATE_UR: {
					m_ePlayerState = RU_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabRU");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				case STATE_DL: {
					m_ePlayerState = LD_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabLD");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				case STATE_DR: {
					m_ePlayerState = RD_STAB;
					m_eBind = BIND_5;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabRD");
					Safe_AddRef(m_pTextureCom);
					break;
				}
				}
			}
		}
#pragma endregion

#pragma region 종베기
		if (!m_pGameInstance->Key_Pressing(VK_CONTROL))
		{
			if (m_iSkillOpen & 64) {
				if (m_iCrayTick == m_iCrayCool * 60 && m_tInfo.iMp >= 10 && m_pGameInstance->Key_Down('2')) {
					m_tInfo.iMp -= 10;
					m_iCrayTick = 0;
					CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT);
					CSound_Manager::GetInstance()->PlaySound(L"Rock.wav", CSound_Manager::SYSTEM_EFFECT, VOLUME5);
					EFFECT EffectInfo;
					EffectInfo.eBasicState = m_eBasicState;
					EffectInfo.mapCube = m_mapCube;
					EffectInfo.pTargetTransform = m_pTransformCom;

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", L"Prototype_GameObject_VerCutEffect", &EffectInfo))) {
						MSG_BOX(L"Failed To CEffectCray : NativeConstruct");
						return;
					}

					m_bAttack = true;
					m_bMoving = true;
					switch (m_eBasicState) {
					case STATE_U: {
						m_ePlayerState = U_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_U");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					case STATE_D: {
						m_ePlayerState = D_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_D");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					case STATE_L: {
						m_ePlayerState = L_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_L");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					case STATE_R: {
						m_ePlayerState = R_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_R");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					case STATE_UL: {
						m_ePlayerState = LU_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_LU");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					case STATE_UR: {
						m_ePlayerState = RU_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_RU");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					case STATE_DL: {
						m_ePlayerState = LD_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_LD");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					case STATE_DR: {
						m_ePlayerState = RD_HORCUT;
						m_eBind = BIND_5;
						Safe_Release(m_pTextureCom);
						m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Horcut_RD");
						Safe_AddRef(m_pTextureCom);
						break;
					}
					}
				}
			}
		}

#pragma endregion

#pragma region 횡베기
		if (m_iSkillOpen & 32) {
			if (m_iIceTick == m_iIceCool * 60 && m_tInfo.iMp >= 30 && m_pGameInstance->Key_Down('3')) {

				list<TARGET> TargetList;
				_float3 vPosition = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
				list<CGameObject*>* pMonsterlist = nullptr;
				if (LEVEL_STAGEBOSS != g_iLevel) {
					pMonsterlist = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Monster");
				}
				else {
					pMonsterlist = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Boss");
				}
				if (nullptr != pMonsterlist) {
					for (int i = 0; i < pMonsterlist->size(); ++i) {
						CTransform* pMonsterTransform;
						if (LEVEL_STAGEBOSS != g_iLevel) {
							pMonsterTransform = (CTransform*)(m_pGameInstance->Get_Component(g_iLevel, L"Layer_Monster", L"Com_Transform", i));
						}
						else {
							pMonsterTransform = (CTransform*)(m_pGameInstance->Get_Component(g_iLevel, L"Layer_Boss", L"Com_Transform", i));
						}
						TARGET tTarget;
						tTarget.vPos = pMonsterTransform->Get_State(CTransform::STATE_POSITION);
						tTarget.fDis = sqrtf(pow(vPosition.x - tTarget.vPos.x, 2) + pow(vPosition.y - tTarget.vPos.y, 2) + pow(vPosition.z - tTarget.vPos.z, 2));
						TargetList.push_back(tTarget);
					}
					if (0 < TargetList.size()) {
						TargetList.sort([](TARGET p1, TARGET p2)->bool {
							return p1.fDis < p2.fDis; });

						if (5.f >= TargetList.front().fDis) {

							CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT);
							CSound_Manager::GetInstance()->PlaySound(L"Magic_Ice.wav", CSound_Manager::SYSTEM_EFFECT, VOLUME5);
							m_tInfo.iMp -= 30;

							m_iIceTick = 0;
							m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", L"Prototype_GameObject_Ice", &TargetList.front().vPos);

							m_bAttack = true;
							m_bMoving = true;
							switch (m_eBasicState) {
							case STATE_U: {
								m_ePlayerState = U_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Vercut_U");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							case STATE_D: {
								m_ePlayerState = D_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Vercut_D");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							case STATE_L: {
								m_ePlayerState = L_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Vercut_L");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							case STATE_R: {
								m_ePlayerState = R_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Vercut_R");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							case STATE_UL: {
								m_ePlayerState = LU_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Vercut_LU");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							case STATE_UR: {
								m_ePlayerState = RU_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Vercut_RU");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							case STATE_DL: {
								m_ePlayerState = LD_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStabLD");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							case STATE_DR: {
								m_ePlayerState = RD_VERCUT;
								m_eBind = BIND_5;
								Safe_Release(m_pTextureCom);
								m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Texture_Vercut_RD");
								Safe_AddRef(m_pTextureCom);
								break;
							}
							}
						}
						else {
							goto WARNING_MESSAGE;
						}
					}
					else {
						goto WARNING_MESSAGE;
					}
				}
				else {
				WARNING_MESSAGE:
					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 515, 500, 980, 700 };
					lstrcpy(tFont.szText, L"주변에 공격할 몬스터가 없습니다!");
					tFont.tFontInfo.Height = 25;
					tFont.tFontInfo.Width = 15;
					tFont.eTextId = CText::TEXT_WARNING;
					tFont.vARGB = _float4(255, 210, 80, 80);
					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Warning_Text", L"Prototype_GameObject_Font", &tFont);
				}
			}
		}
#pragma endregion

#pragma region 움직이기

		if (m_pGameInstance->Key_Pressing('W')) {
			if (m_pGameInstance->Key_Pressing('A')) {
				m_pTransformCom->Go_Straight(fTimeDelta / sqrtf(2));
				m_pTransformCom->Go_Left(fTimeDelta / sqrtf(2));
				if (false == m_bAttack) {
					m_ePlayerState = UL_RUN;
					m_eBasicState = STATE_UL;
					m_eBind = BIND_10;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureLU");
					Safe_AddRef(m_pTextureCom);
				}
			}
			else if (m_pGameInstance->Key_Pressing('D')) {
				m_pTransformCom->Go_Straight(fTimeDelta / sqrtf(2));
				m_pTransformCom->Go_Right(fTimeDelta / sqrtf(2));
				if (false == m_bAttack) {
					m_ePlayerState = UR_RUN;
					m_eBasicState = STATE_UR;
					m_eBind = BIND_10;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureRU");
					Safe_AddRef(m_pTextureCom);
				}
			}
			else {
				m_pTransformCom->Go_Straight(fTimeDelta);
				if (false == m_bAttack) {
					m_ePlayerState = U_RUN;
					m_eBasicState = STATE_U;
					m_eBind = BIND_10;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureU");
					Safe_AddRef(m_pTextureCom);
				}
			}
			m_bMoving = true;
			return;
		}
		if (m_pGameInstance->Key_Pressing('S')) {
			if (m_pGameInstance->Key_Pressing('A')) {
				m_pTransformCom->Go_BackWard(fTimeDelta / sqrtf(2));
				m_pTransformCom->Go_Left(fTimeDelta / sqrtf(2));
				if (false == m_bAttack) {
					m_ePlayerState = DL_RUN;
					m_eBasicState = STATE_DL;
					m_eBind = BIND_10;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureLD");
					Safe_AddRef(m_pTextureCom);
				}
			}
			else if (m_pGameInstance->Key_Pressing('D')) {
				m_pTransformCom->Go_BackWard(fTimeDelta / sqrtf(2));
				m_pTransformCom->Go_Right(fTimeDelta / sqrtf(2));
				if (false == m_bAttack) {
					m_ePlayerState = DR_RUN;
					m_eBasicState = STATE_DR;
					m_eBind = BIND_10;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureRD");
					Safe_AddRef(m_pTextureCom);
				}
			}
			else {
				m_pTransformCom->Go_BackWard(fTimeDelta);
				if (false == m_bAttack) {
					m_ePlayerState = D_RUN;
					m_eBasicState = STATE_D;
					m_eBind = BIND_10;
					Safe_Release(m_pTextureCom);
					m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureD");
					Safe_AddRef(m_pTextureCom);
				}
			}
			m_bMoving = true;
			return;
		}
		if (m_pGameInstance->Key_Pressing('A')) {
			m_pTransformCom->Go_Left(fTimeDelta);
			if (false == m_bAttack) {
				m_ePlayerState = L_RUN;
				m_eBasicState = STATE_L;
				m_eBind = BIND_10;
				Safe_Release(m_pTextureCom);
				m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureL");
				Safe_AddRef(m_pTextureCom);
			}
			m_bMoving = true;
			return;
		}
		if (m_pGameInstance->Key_Pressing('D')) {
			m_pTransformCom->Go_Right(fTimeDelta);
			if (false == m_bAttack) {
				m_ePlayerState = R_RUN;
				m_eBasicState = STATE_R;
				m_eBind = BIND_10;
				Safe_Release(m_pTextureCom);
				m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureR");
				Safe_AddRef(m_pTextureCom);
			}
			m_bMoving = true;
			return;
		}

#pragma endregion

#pragma region 마나쉴드
		if (m_iSkillOpen & 16) {
			if (m_iShieldTick == m_iShieldCool * 60 && m_tInfo.iMp >= 30 && m_pGameInstance->Key_Down('4')) {
				m_tInfo.iMp -= 30;
				m_iShieldTick = 0;
				m_eState = STATE_SUPERARMOR;
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT);
				CSound_Manager::GetInstance()->PlaySound(L"Shield.wav", CSound_Manager::SYSTEM_EFFECT, VOLUME5);
				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Shield", L"Prototype_GameObject_Shield", &m_eBasicState))) {
					MSG_BOX(L"Failed To CShield : NativeConstruct");
					return;
				}

			}
		}
#pragma endregion

#pragma region 지진

		if (m_iEarthquakeTick == m_iEarthquakeCool * 60 && m_tInfo.iMp >= 50 && m_pGameInstance->Key_Down('5')) {

			if (m_iSkillOpen & 8) {
				m_tInfo.iMp -= 50;
				m_iEarthquakeTick = 0;
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::SYSTEM_EFFECT);
				CSound_Manager::GetInstance()->PlaySound(L"Explosion1.wav", CSound_Manager::SYSTEM_EFFECT, VOLUME5);
				
				for (_uint i = 0; i < 50; ++i)
				{
					_float3 Pos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Hit_Effect", L"Prototype_GameObject_EQParticle", &Pos))) {
						MSG_BOX(L"Failed To CEarthQuake : NativeConstruct");
						return;
					}
				}

				EFFECT EffectInfo;
				EffectInfo.eBasicState = m_eBasicState;
				EffectInfo.mapCube = m_mapCube;
				EffectInfo.pTargetTransform = m_pTransformCom;
				if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Effect", L"Prototype_GameObject_EarthQuake", &EffectInfo))) {
					MSG_BOX(L"Failed To CEarthQuake : NativeConstruct");
					return;
				}
				
			}

		}

#pragma endregion

#pragma region 달빛
		if (m_iMoonLightTick == m_iMoonLightCool * 60 && m_tInfo.iMp >= 200 && m_pGameInstance->Key_Down('6')) {
			if (m_iSkillOpen & 4) {
				m_tInfo.iMp -= 200;
				m_iMoonLightTick = 0;
				m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Skill_UI", L"Prototype_GameObject_Ultimate_UI", this);
			}
		}


#pragma endregion

	}

#pragma region 1인칭 저격

	FPS();

#pragma endregion

	Standing();

	m_bMoving = false;

#pragma region 버그키

	if (m_pGameInstance->Key_Down('M')) {
		if (false == m_bSuper) {
			m_eState = STATE_SUPERARMOR;
			m_bSuper = true;
			return;
		}
		m_eState = STATE_ALIVE;
		m_bSuper = false;
	}
	if (m_pGameInstance->Key_Pressing('B')) {
		_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
		vPos.y += 1.f;
		m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
	}

#pragma endregion

}

void CPlayer::Standing() {
	if (false == m_bMoving && false == m_bAttack) {
		switch (m_eBasicState) {
		case STATE_U: {
			m_ePlayerState = U_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandU");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		case STATE_D: {
			m_ePlayerState = D_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandD");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		case STATE_L: {
			m_ePlayerState = L_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandL");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		case STATE_R: {
			m_ePlayerState = R_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandR");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		case STATE_UL: {
			m_ePlayerState = LU_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandLU");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		case STATE_UR: {
			m_ePlayerState = RU_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandRU");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		case STATE_DL: {
			m_ePlayerState = LD_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandLD");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		case STATE_DR: {
			m_ePlayerState = RD_STAND;
			m_eBind = BIND_7;
			Safe_Release(m_pTextureCom);
			m_pTextureCom = (CTexture*)m_pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_TextureStandRD");
			Safe_AddRef(m_pTextureCom);
			break;
		}
		}
	}
}

void CPlayer::Collision_Ground() {
	m_Grav = 0;
	_float3 NewPos = _float3(m_pTransformCom->Get_State(CTransform::STATE_POSITION).x, m_pTransformCom->Get_State(CTransform::STATE_POSITION).y - ((m_pTransformCom->Get_Scale().y) / 2) + 0.75f, m_pTransformCom->Get_State(CTransform::STATE_POSITION).z);

	_uint PlayerIndex = (_uint)(NewPos.x + 0.5) * 10000
		+ (_uint)(NewPos.y + 0.5) * 100
		+ (_uint)(NewPos.z + 0.5);
	if ((m_mapCube.find(PlayerIndex) != m_mapCube.end()))
	{
		m_pCollisionCom->My_Collision((*(m_mapCube.find(PlayerIndex))).second, m_pTransformCom);
		return;
	}

	_uint MapIndex[17]{
		PlayerIndex - 10000 + 1, PlayerIndex + 1, PlayerIndex + 10000 + 1,
		PlayerIndex - 10000 ,PlayerIndex + 10000,
		PlayerIndex - 10000 - 1, PlayerIndex - 1, PlayerIndex + 10000 - 1,

		PlayerIndex - 10000 - 100 + 1, PlayerIndex - 100 + 1, PlayerIndex + 10000 - 100 + 1,
		PlayerIndex - 10000 - 100, PlayerIndex - 100, PlayerIndex + 10000 - 100,
		PlayerIndex - 10000 - 100 - 1, PlayerIndex - 100 - 1, PlayerIndex + 10000 - 100 - 1,
	};

	for (_uint i = 0; i < 17; ++i) {
		if ((m_mapCube.find(MapIndex[i]) != m_mapCube.end())) {
			_uint Coll = m_pCollisionCom->After_Collision((*(m_mapCube.find(MapIndex[i]))).second, m_pTransformCom);
			if (Coll == 2)
				m_Grav = 2;

			if (Coll != 0) {
				//if (m_pCollisionCom->Collision_Cube((*(m_mapCube.find(MapIndex[i]))).second, m_pTransformCom, _float3(0.7f, 1.3f, 0.7f))) {
				m_bJumping = false;
				m_fJumpTime = 0.f;
				if (PLAYER_DEAD == m_eState && m_bDead == true) {
					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_GameOver", L"Prototype_GameObject_GameOver_UI" ,this);
					m_bDead = false;
				}
			}
		}
	}
}

void CPlayer::Gravity(_float fTimeDelta) {
	_float3 vGravity = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	vGravity.y -= G * fTimeDelta;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vGravity);
}

void CPlayer::Diving() {
	if (LEVEL_STAGESPECIAL != g_iLevel) {
		if (-10.f >= m_pTransformCom->Get_State(CTransform::STATE_POSITION).y) {
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(0.f, 10.f, 0.f));
			//m_tInfo.iHp = _uint(m_tInfo.iHp * 0.5f);
		}
	}
	else {
		if (-10.f >= m_pTransformCom->Get_State(CTransform::STATE_POSITION).y) {
			m_pTransformCom->Set_State(CTransform::STATE_POSITION, _float3(12.5f, 1.5f, 0.f));
		}
	}
}

void CPlayer::Level_Up() {
	m_tInfo.iMaxHp += (_uint)(m_tInfo.iMaxHp * 0.1f);
	m_tInfo.iHp = m_tInfo.iMaxHp;

	m_tInfo.iMaxMp += (_uint)(m_tInfo.iMaxMp * 0.1f);
	m_tInfo.iMp = m_tInfo.iMaxMp;

	m_tInfo.iAtt += 3;
	m_tInfo.iDef += 3;

	m_tInfo.iExp -= m_tInfo.iMaxExp;
	m_tInfo.iMaxExp += (_uint)(m_tInfo.iMaxExp * 0.1f);

	m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_LevelUp", L"Prototype_GameObject_LevelUp", m_pTransformCom);
}

void CPlayer::Collision_Monster() {
	list<CGameObject*>* MonsterList;
	if (g_iLevel != LEVEL_STAGEBOSS)
		MonsterList = (m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Monster"));
	else
		MonsterList = (m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Boss"));
	if (nullptr != MonsterList) {
		for (auto& iter : *MonsterList) {
			if (m_pCollisionCom->Collision_Sphere(m_pTransformCom, (CTransform*)(iter->Get_Component(L"Com_Transform"))) && false == m_bDamaged && false == m_bSuper) {
				m_bSuper = true;
				_int iDamage = ((CMonster*)(iter))->Get_Monster_Info().iAtt - m_tInfo.iDef;
				if (iDamage > 0)
				{
					m_bDamaged = true;
					m_tInfo.iHp -= iDamage;
					for(_uint i = 0; i < iDamage/3+1;++i)
						m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_Blood", m_pTransformCom->Get_State(CTransform::STATE_POSITION));
				}
				else
					iDamage = 0;
				Write_Damage(iDamage);
			}
		}
	}
}

void CPlayer::Damaged_MonsterSkill() {
	if (g_iLevel == LEVEL_STAGEBOSS &&m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss") != nullptr && m_pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() != 0)
	{
		list<CGameObject*>* BossSkillList = (m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_BossSkill"));
		if (nullptr != BossSkillList) {
			for (auto& iter : *BossSkillList) {
				if (m_pCollisionCom->Collision_Cylinder((CTransform*)(iter->Get_Component(L"Com_Transform")), m_pTransformCom) && false == m_bDamaged && false == m_bSuper) {								
					_uint iDamage = ((CBoss_Skill*)(iter))->Get_Damage() - m_tInfo.iDef;
					m_bSuper = true;
					if (iDamage > 0)
					{				
						m_bDamaged = true;
						m_tInfo.iHp -= iDamage;
						for (_uint i = 0; i < iDamage / 3 + 1; ++i)
							m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Hit_Effect", L"Prototype_GameObject_Blood", m_pTransformCom->Get_State(CTransform::STATE_POSITION));
					}
					else
						iDamage = 0;
					Write_Damage(iDamage);

					CBossHit_Effect::BOSSHIT tBossHit;
					tBossHit.eSkill = ((CBoss_Skill*)(iter))->Get_Skill_Boss();
					tBossHit.vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_PlayerHit", L"Prototype_GameObject_Boss_Claw_Effect", &tBossHit);
				}
			}
		}
	}
}

void CPlayer::Player_Dead() {
	m_eState = PLAYER_DEAD;
	_float3 vPos = m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	vPos.y += 10.f;
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPos);
}

void CPlayer::Skill_Tick() {
	if (m_iFreezeCool * 60 > m_iFreezeTick) {
		++m_iFreezeTick;
	}
	if (m_iCrayCool * 60 > m_iCrayTick) {
		++m_iCrayTick;
	}
	if (m_iIceCool * 60 > m_iIceTick) {
		++m_iIceTick;
	}
	if (m_iShieldCool * 60 > m_iShieldTick) {
		++m_iShieldTick;
	}
	if (m_iEarthquakeCool * 60 > m_iEarthquakeTick) {
		++m_iEarthquakeTick;
	}
	if (m_iMoonLightCool * 60 > m_iMoonLightTick) {
		++m_iMoonLightTick;
	}
}

void CPlayer::Write_Damage(_uint iDamage) {
	string szDamage = to_string(iDamage);

	CDamage::DAMAGE tDamage;
	ZeroMemory(&tDamage, sizeof(CDamage::DAMAGE));

	int iRandX = rand() % 4 - 2;
	int iRandY = rand() % 4 - 2;

	for (int i = 0; i < szDamage.size(); ++i) {
		tDamage.chDamageID = (_uint)szDamage[i];
		tDamage.fX = g_iWinCX * 0.5f + iRandX * 30.f + i * 30.f;
		tDamage.fY = g_iWinCY * 0.5f + iRandY * 45.f;
		tDamage.eDamageType = CDamage::DAMAGE_PLAYER;

		m_pGameInstance->Add_GameObjectToLayer(LEVEL_STATIC, L"Layer_Damage", L"Prototype_GameObject_Damage_UI", &tDamage);
	}
}

void CPlayer::Set_Revive() {
	m_tInfo.iHp = m_tInfo.iMaxHp;
	m_tInfo.iMp = m_tInfo.iMaxMp;
	m_tInfo.iExp = (_uint)(m_tInfo.iExp * 0.5f);
	m_bJumping = false;
	m_bAttack = false;
	m_bMoving = false;
	m_bDamaged = false;
	m_bDead = false;
	m_bStatWin = false;
	m_bSuper = false;
}

void CPlayer::Stop_Player()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 0.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	m_pTransformCom->Set_TransformState(TransformDesc);
}

void CPlayer::UnStop_Player()
{
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 5.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	m_pTransformCom->Set_TransformState(TransformDesc);
}

void CPlayer::FPS() {
	CMultiCamera* pCamera = (CMultiCamera*)(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front());
	Safe_AddRef(pCamera);

	if (nullptr == pCamera) {
		Safe_Release(pCamera);
		return;
	}

	if (3 == pCamera->Get_CameraMode()) {
		if (m_pGameInstance->Key_Down('Z')) {
			pCamera->Set_AbouluteFovy(D3DXToRadian(5.f));
		}
		else if (m_pGameInstance->Key_Down('X')) {
			pCamera->Set_AbouluteFovy(D3DXToRadian(45.f));
		}

		if (m_pGameInstance->Key_Down('C'))
		{
			CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
			CSound_Manager::GetInstance()->PlaySound(L"ReLoad.wav", CSound_Manager::EFFECT, VOLUME);

			m_iBullet = 20;
		}

		if (LEVEL_STAGESPECIAL == g_iLevel && m_pGameInstance->Key_Down(VK_LBUTTON)) {
			if (m_iBullet > 0) {
				m_iBullet -= 1;
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
				CSound_Manager::GetInstance()->PlaySound(L"gun8.wav", CSound_Manager::EFFECT, VOLUME);
				m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Bullet", L"Prototype_GameObject_Bullet");
			}
			else
			{
				CSound_Manager::GetInstance()->StopSound(CSound_Manager::EFFECT);
				CSound_Manager::GetInstance()->PlaySound(L"gun11.wav", CSound_Manager::EFFECT, VOLUME);
			}
		}
	}

	Safe_Release(pCamera);
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CPlayer* pInstance = new CPlayer(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype()))	{
		MSG_BOX(TEXT("Failed To CPlayer : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CPlayer::Clone(void* pArg) {
	CPlayer* pInstance = new CPlayer(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CPlayer : Clone"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer::Free() {
	__super::Free();
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pRendererCom);
	Safe_Release(m_pCollisionCom);
}