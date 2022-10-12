#include "stdafx.h"
#include "..\Public\Level_StageBoss.h"

CLevel_StageBoss::CLevel_StageBoss(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CLevel(pGraphic_Device)
{
}

HRESULT CLevel_StageBoss::NativeConstruct() {
	if (FAILED(__super::NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageBoss : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_BackGround(L"Layer_Ground"))) {
		MSG_BOX(L"Failed To CLevel_StageBoss : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(Ready_Layer_Player(L"Layer_Player"))) {
		MSG_BOX(L"Failed To CLevel_StageBoss : NativeConstruct");
		return E_FAIL;
	}

	if (FAILED(Ready_Layer_Portal(L"Layer_Portal"))) {
		MSG_BOX(L"Failed To CLevel_StageBoss : NativeConstruct");
		return E_FAIL;
	}
	g_iLevel = LEVEL_STAGEBOSS;

	CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);


	return S_OK;
}

void CLevel_StageBoss::Tick(_float fTimeDelta) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CSound_Manager::GetInstance()->PlaySound(L"Boss2.wav", CSound_Manager::BGM, VOLUME);

	if (pGameInstance->Key_Down('0')) {
		if (FAILED(pGameInstance->OpenLevel(LEVEL_LOADING, CLevel_Loading::Create(m_pGraphic_Device, LEVEL_STAGESPECIAL)))) {
			return;
		}
	}

	if (rand() % 12 == 0) {
		for (int i = 0; i < 20; ++i) {
			if (FAILED(Ready_Layer_Ash(L"Layer_Ash"))) {
				MSG_BOX(L"Failed To CLevel_Tutorial : Tick");
				return;
			}
		}
	}

	if (m_iPhase == 3)
	{
		dynamic_cast<CMultiCamera*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front())->BossPhase1();
	}
	if (m_iPhase == 7)
	{
		dynamic_cast<CMultiCamera*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front())->BossPhase2();
	}
	if (m_iPhase == 8)
	{
		dynamic_cast<CMultiCamera*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Camera")->front())->BossPhase3();
	}


	if (m_iPhase == 0)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
		{
			MSG_BOX(L"Failed To CMagician : Tick");
			return;
		}


		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 150, 440, 1280,520 };
		lstrcpy(tFont.szText, L"세젤귀상현공주");
		tFont.tFontInfo.Height = 40;
		tFont.tFontInfo.Width = 30;
		tFont.eTextId = CText::TEXT_NPC;
		tFont.vARGB = _float4(255, 255, 255, 255);

		CText::FONT tFont2;
		ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont2.rc = RECT{ 300, 500, 1280, 550 };
		lstrcpy(tFont2.szText, L"헤에? 역시 그 때 느껴졌던 힘은 진짜였어! 너 진짜 맛있겠다~!");
		tFont2.tFontInfo.Height = 30;
		tFont2.tFontInfo.Width = 20;
		tFont2.eTextId = CText::TEXT_NPC;
		tFont2.vARGB = _float4(255, 255, 255, 255);

		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

		m_iPhase = 1;
	}
	else if (m_iPhase == 1 && pGameInstance->Key_Down('X'))
	{
		CText* pText = (CText*)(pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
		pText->Set_Text(L"조금만 더 놀아주도록 할까? 꺄하하하하~");
		m_iPhase = 2;
	}
	else if (m_iPhase == 2 && pGameInstance->Key_Down('X'))
	{
		CTextWindow* pTextWindow = (CTextWindow*)(pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_TextWindow")->Get_List()->front());
		pTextWindow->Set_Dead();

		list<CGameObject*>* pText = pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List();
		for (auto iter : *pText)
		{
			if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
				iter->Set_Dead();
		}

		if (FAILED(Ready_Layer_Boss(L"Layer_Boss"))) {
			MSG_BOX(L"Failed To CLevel_StageBoss : NativeConstruct");
			return;
		}

		m_iPhase = 3;
	}
	if (m_iPhase == 3 && pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() == 0)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
		{
			MSG_BOX(L"Failed To CMagician : Tick");
			return;
		}

		CText::FONT tFont;
		ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont.rc = RECT{ 150, 440, 1280,520 };
		lstrcpy(tFont.szText, L"세젤귀상현공주");
		tFont.tFontInfo.Height = 40;
		tFont.tFontInfo.Width = 30;
		tFont.eTextId = CText::TEXT_NPC;
		tFont.vARGB = _float4(255, 255, 255, 255);

		CText::FONT tFont2;
		ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont2.rc = RECT{ 300, 500, 1280, 550 };
		lstrcpy(tFont2.szText, L"하.... 너 정말 재미있네? 이것만큼은 안 꺼내려고 했는데....");
		tFont2.tFontInfo.Height = 30;
		tFont2.tFontInfo.Width = 20;
		tFont2.eTextId = CText::TEXT_NPC;


		tFont2.vARGB = _float4(255, 255, 255, 255);

		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

		m_iPhase = 4;
	}
	else if (m_iPhase == 4 && pGameInstance->Key_Down('X'))
	{
		CText* pText = (CText*)(pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
		pText->Set_Text(L"마왕발록! 본때를 보여줘!!!");
		m_iPhase = 5;
	}
	else if (m_iPhase == 5 && pGameInstance->Key_Down('X'))
	{
		CText* pText = (CText*)(pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->back());
		pText->Set_Text(L"마왕 발록");
		CText* pText2 = (CText*)(pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List()->front());
		pText2->Set_Text(L"너가 그렇게 싸움을 잘해??? 옥상으로 따라와..");
		m_iPhase = 6;
	}
	else if (m_iPhase == 6 && pGameInstance->Key_Down('X'))
	{
		CTextWindow* pTextWindow = (CTextWindow*)(pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_TextWindow")->Get_List()->front());
		pTextWindow->Set_Dead();

		list<CGameObject*>* pText = pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List();
		for (auto iter : *pText)
		{
			if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
				iter->Set_Dead();
		}
		m_iPhase = 7;

		if (FAILED(Ready_Layer_Boss2(L"Layer_Boss"))) {
			MSG_BOX(L"Failed To CLevel_StageBoss : Tick");
			return;
		}

	}

	if (m_iPhase == 7 && pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() == 1 && m_bCheck == false) {
		m_bCheck = true;
		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Effect_Warning", L"Prototype_GameObject_Siren");
	}
	if (m_iPhase == 7 && pGameInstance->Find_Layer_List(LEVEL_STAGEBOSS, L"Layer_Boss")->size() == 0)
	{
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
		{
			MSG_BOX(L"Failed To CMagician : Tick");
			return;
		}
		CSound_Manager::GetInstance()->StopSound(CSound_Manager::BGM);
		CSound_Manager::GetInstance()->PlaySound(L"Ending.wav", CSound_Manager::BGM, VOLUME);

		CText::FONT tFont3;
		ZeroMemory(&tFont3.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont3.rc = RECT{ 150, 440, 1280,520 };
		lstrcpy(tFont3.szText, L"세젤귀상현공주");
		tFont3.tFontInfo.Height = 40;
		tFont3.tFontInfo.Width = 30;
		tFont3.eTextId = CText::TEXT_NPC;
		tFont3.vARGB = _float4(255, 255, 255, 255);

		CText::FONT tFont4;
		ZeroMemory(&tFont4.tFontInfo, sizeof(D3DXFONT_DESCW));
		tFont4.rc = RECT{ 300, 500, 1280, 550 };
		lstrcpy(tFont4.szText, L"아라라...? 음... 어쩔수없닷.... 도망쳐~~");
		tFont4.tFontInfo.Height = 30;
		tFont4.tFontInfo.Width = 20;
		tFont4.eTextId = CText::TEXT_NPC;
		tFont4.vARGB = _float4(255, 255, 255, 255);

		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont4);
		pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_Font", L"Prototype_GameObject_Font", &tFont3);

		m_iPhase = 8;
	}
	else if (m_iPhase == 8 && pGameInstance->Key_Down('X'))
	{
		CTextWindow* pTextWindow = (CTextWindow*)(pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_TextWindow")->Get_List()->front());
		pTextWindow->Set_Dead();

		list<CGameObject*>* pText = pGameInstance->Find_Layer(LEVEL_STAGEBOSS, L"Layer_Font")->Get_List();
		for (auto iter : *pText)
		{
			if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
				iter->Set_Dead();
		}

		CNPC::NPC tNPC;
		tNPC.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");
		tNPC.vPosition = _float3(32.f, 9.5f, 17.f);
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, L"Layer_NPC", TEXT("Prototype_GameObject_Theif"), &tNPC))) {
			MSG_BOX(L"Failed To CLevel_StageBoss : Ready_Layer_NPC");
			return;
		}

		dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(_float3(30.f, 9.5f, 19.f)));
		dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);

		m_iPhase = 9;
	}
	Safe_Release(pGameInstance);
}

HRESULT CLevel_StageBoss::Render() {
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CLevel_StageBoss : Render");
		return E_FAIL;
	}
	//SetWindowText(g_hWnd, TEXT("보스스테이지입니다."));
	return S_OK;
}

HRESULT CLevel_StageBoss::Ready_Layer_Player(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	//list<CGameObject*>* p = (pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List());
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CShadow*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Shadow")->Get_List()->front())->Set_Map(m_MapCube);
	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Player")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(1.f,5.f, 1.f));
	dynamic_cast<CPlayer*>(pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_HpLow(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageBoss::Ready_Layer_Portal(const _tchar* pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	dynamic_cast<CTransform*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_Component(L"Com_Transform"))->Set_State(CTransform::STATE_POSITION, _float3(_float3(8.5f, 55.5f, 36.5f)));
	dynamic_cast<CPortal*>(pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(false);
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageBoss::Ready_Layer_BackGround(const _tchar* pLayerTag) {
	if (FAILED(Load_Map(L"../../Data/StageBossMap.dat"))) {
		MSG_BOX(L"Failed To CLevel_StageBoss : Ready_Layer_BackGround");
		return E_FAIL;
	}
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (auto iter : m_MapCube) {
		if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, pLayerTag, L"Prototype_GameObject_Ground", &iter))) {
			MSG_BOX(L"Failed To CLevel_StageBoss : Ready_Layer_BackGround");
			return E_FAIL;
		}
	}
	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, pLayerTag, TEXT("Prototype_GameObject_Sky")))) {
		MSG_BOX(L"Failed To CLevel_StageBoss : Ready_Layer_BackGround");
		return E_FAIL;
	}
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageBoss::Ready_Layer_Ash(const _tchar * pLayerTag)
{
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, pLayerTag, TEXT("Prototype_GameObject_Ash")))) {
		MSG_BOX(L"Failed To CLevel_Tutorial : Ready_Layer_Snow");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageBoss::Ready_Layer_Boss(const _tchar * pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMonster::MONSTER tMonster;
	tMonster.mapCube = m_MapCube;
	tMonster.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, pLayerTag, L"Prototype_GameObject_Boss", &tMonster))) {
		MSG_BOX(L"Failed To CLevel_StageBoss : Ready_Layer_Boss");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLevel_StageBoss::Ready_Layer_Boss2(const _tchar * pLayerTag) {
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	CMonster::MONSTER tMonster;
	tMonster.mapCube = m_MapCube;
	tMonster.pTargetTransform = (CTransform*)pGameInstance->Get_Component(LEVEL_STATIC, L"Layer_Player", L"Com_Transform");

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, pLayerTag, L"Prototype_GameObject_Balrog", &tMonster))) {
		MSG_BOX(L"Failed To CLevel_StageBoss : Ready_Layer_Boss2");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, pLayerTag, TEXT("Prototype_GameObject_Balrog_RH"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Ready_Layer_Boss2");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEBOSS, pLayerTag, TEXT("Prototype_GameObject_Balrog_LH"), &tMonster))) {
		MSG_BOX(L"Failed To CLevel_StageSeven : Ready_Layer_Boss2");
		return E_FAIL;
	}

	Safe_Release(pGameInstance);
	return S_OK;
}


CLevel_StageBoss* CLevel_StageBoss::Create(LPDIRECT3DDEVICE9 pGraphic_Device) {
	CLevel_StageBoss* pInstance = new CLevel_StageBoss(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct())) {
		MSG_BOX(L"Failed To CLevel_StageBoss : Create");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLevel_StageBoss::Free() {
	__super::Free();
}

HRESULT CLevel_StageBoss::Load_Map(const TCHAR* pPath) {
	HANDLE hFile = CreateFile(pPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) {
		MSG_BOX(L"Failed To CLevel_StageBoss : Load_Map");
		return E_FAIL;
	}
	DWORD dwByte = 0;
	_float4* pInfo = nullptr;

	while (true) {
		pInfo = new _float4;

		ReadFile(hFile, pInfo, sizeof(_float4), &dwByte, nullptr);

		if (0 == dwByte) {
			Safe_Delete(pInfo);
			break;
		}
		_uint iCubeIndex = (_uint(pInfo->x + 0.5f) * 10000 + _uint(pInfo->y + 0.5f) * 100 + _uint(pInfo->z + 0.5f));
		m_MapCube.insert(map<_uint, _float4>::value_type(iCubeIndex, *pInfo));

		Safe_Delete(pInfo);
	}
	CloseHandle(hFile);
	return S_OK;
}