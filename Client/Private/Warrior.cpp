#include "stdafx.h"
#include "..\Public\Warrior.h"

CWarrior::CWarrior(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CNPC(pGraphic_Device)
{
}

CWarrior::CWarrior(const CWarrior & rhs)
	: CNPC(rhs)
{
}

HRESULT CWarrior::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CWarrior : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CWarrior::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CWarrior : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CWarrior : NativeConstruct");
		return E_FAIL;
	}



	m_pTransform->Set_State(CTransform::STATE_POSITION, ((NPC*)pArg)->vPosition);

	_float3 BuffLook = _float3(1.f, 0.f, 1.f);
	D3DXVec3Normalize(&BuffLook, &BuffLook);
	m_pTransform->Set_State(CTransform::STATE_LOOK, BuffLook);

	_float3 BuffRight = _float3(1.f, 0.f, -1.f);
	D3DXVec3Normalize(&BuffRight, &BuffRight);
	m_pTransform->Set_State(CTransform::STATE_RIGHT, BuffRight);

	m_pTransform->Scaled(_float3(1.5f, 2.0f, 1.5f));

	return S_OK;
}

void CWarrior::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);
	if (m_pGameInstance->Key_Down('Z') && Check_Player_InArea())
	{
		if (g_iLevel == LEVEL_STAGETHREE)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�� ���? ��������?");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� ���? �������ִ� ����ֳİ��?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� ��ó�� �׷� ��� �� ��µ���? ��¥ ����̳׿�.");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S��������2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�װ� �𸣰ڰ� Ȥ�� �� �� �����ֽ� �� �־��?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� �̻��� ���������� �� ��ƾ� �ϴµ� ������� �ö󰡱Ⱑ �ʹ� �����Ƽ���;");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S��������2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"��� ���� ��� �ϳ� �˷��帱�Կ�. ��¥ �ϱ� ����ε� Ư���� �˷��帮�°ſ���.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���۹�: 3(IceUp)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(32);

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�� ������ �ҷ��ּ���. �� ���̽� ���ڶ� ���÷� ������.");

					++m_iTextSprite;
					break; }
				case 10: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"���� ���� �� ( %d");
					tQuest.tFont.tFontInfo.Width = 15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 10;
					tQuest.iOption = 0;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_iTextSprite = 0;
					m_iTalkState = 1;
					break;
				}
				}
			}
			else if (m_iTalkState == 1)
			{
				if (Complete_Quest() == true)
				{
					m_iTalkState = 2;
					return;
				}

				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�� ���? ���� �������� �� ���� �����̳׿�.");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
			else if (m_iTalkState == 2)
			{
				switch (m_iTextSprite)
				{
				case 0: {
					list<CGameObject*>* listQuest = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Quest");
					((CQuest*)(listQuest->front()))->Set_Dead();
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
					

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�� ���? �������� �� �����̳׿�! �����ؿ�.");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�׷��� �� �ҿ��� �� ������ ��� �ǰ���? ���� ����̳׿�.");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S��������2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�ƹ�ư �� ���Ͻ� �� ������ ���ݸ� �� ���� �����ֽðھ��?");
					++m_iTextSprite;
					break; }
				case 4: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�� ��Ź�� ����ֽø� ����ó�� ��Ż�� ����帱�Կ�.");
					++m_iTextSprite;

					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 6: {

					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���ƿ�! ���� ������������ ������.");
					++m_iTextSprite;

					break; }
				case 7: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					m_iTalkState = 3;
					break;
				}
				}
			}
			else if (m_iTalkState == 3)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"���ڶ� ���־��.");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETHREE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
		}
		else if (g_iLevel == LEVEL_STAGEFOUR)
		{

			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"���̱���!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"��� �� ���������� ������ ���̾��ٴ� �� �ƽó���?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���� �������?");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� ���� ��� ���� ���� ����� ���Ͱ� ��Ÿ�� ���ķ� ���ڱ� ���� ������ �����߾��.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�׷��� �� ���͸� ���� ��ƾ� �ϴµ���....");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���� ��⿣ �ʹ� �����Ƽ���;");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S��������2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�켱 �� �ֺ��� �ִ� ���͵��� 20���� ������ ����� �ֽðھ��?");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���� ���� ���� ��Ż�� �� �غ� �ϰ� �����Կ�.");

					++m_iTextSprite;
					break; }
				case 9: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"���� ���� �� ( %d");
					tQuest.tFont.tFontInfo.Width = 15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 20;
					tQuest.iOption = 0;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_pTransform->Set_State(CTransform::STATE_POSITION, _float3(28.51f, 9.5f, 32.51f));

					m_iTextSprite = 0;
					m_iTalkState = 1;
					break;
				}
				}
			}
			else if (m_iTalkState == 1)
			{
				if (Complete_Quest() == true)
				{
					m_iTalkState = 2;
					return;
				}

				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(���̽�Ƽ�� ���ô� ���̴�.)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
			else if (m_iTalkState == 2)
			{
				switch (m_iTextSprite)
				{
				case 0: {
					list<CGameObject*>* listQuest = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Quest");
					((CQuest*)(listQuest->front()))->Set_Dead();
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�� ���? ���� ���� ������ �� �����̳׿�.");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"��ħ ��Ż�� ��� �� ���̿���.");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S��������2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"������ �ǹ̷� ���͸� ���� �� ������ �� ���� ����� �˷��帱�Կ�.");
					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���۹�: 4(Shield)");

					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(16);

					++m_iTextSprite;

					break; }
				case 5: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���ƿ�! ���� ������������ ������.");
					++m_iTextSprite;

					break; }
				case 6: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					m_iTalkState = 3;
					break;
				}
				}
			}
			else if (m_iTalkState == 3)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(���̽�Ƽ�� �� �� �� ���ð� �ִ�.)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFOUR, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
		}
		else if (g_iLevel == LEVEL_STAGEFIVE)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�̰��� ��Ż�� ���� ���� �����ؿ�. ��Ż�� ��Ű�� �ִ� ȣ�� ���͸� ����ֽø�....");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� ���? �� �̷δ� ����? ��? ��¥ ���?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���� ���� �� �����ŵ��? ��¥ �̻��� ���̳׿�.");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"����.... �׷��� �ϴ� �� ����. ��·�� ȣ���� ����ּž� ��Ż�� �� �� �־��.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S��������2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"������ ���� �̷����� ���� �ʰڳ׿�....");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� ���! ���� ����� ���������!");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���� �� �� �����̼� �� �� �ִ� ����� �˷��帱�Կ�.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���۹�: (1��Ī ī�޶�), (3��Ī ī�޶�)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(3);

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� ����ϼ���~!");

					++m_iTextSprite;
					break; }
				case 10: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"���� ���� �� ( %d");
					tQuest.tFont.tFontInfo.Width = 15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 1;
					tQuest.iOption = 0;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_iTextSprite = 0;
					m_iTalkState = 1;
					break;
				}
				}
			}
			else if (m_iTalkState == 1)
			{
				if (Complete_Quest() == true)
				{
					m_iTalkState = 2;
					return;
				}

				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(�ް� �󶼿��� �ް��� ��� �Դ� ���̴�.)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
			else if (m_iTalkState == 2)
			{
				switch (m_iTextSprite)
				{
				case 0: {
					list<CGameObject*>* listQuest = m_pGameInstance->Find_Layer_List(g_iLevel, L"Layer_Quest");
					((CQuest*)(listQuest->front()))->Set_Dead();
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"��! ���� ���ƿ��̳׿�.");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�� ���! ���� ã���̴ٱ���? ����ؿ�!");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�׷��� ��Ż������.... ��� ����...?");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"... ... ... .");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�� ���ڱ� ���� ���� �;�������! �̸� �����Կ�!");
					++m_iTextSprite;

					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...???");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S��������2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� ���� ��ġ�󼭴� �ƴϰ��! �׷��� ��Ż�� ���� ���� �ſ���!");
					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�׷��� ���� ���� ������������ �� ������ ��� �Ϳ� ���� �˰� �ִ� ������� �ִ��.");
					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� ��Ż���ʹ� �� �п��� ������ ��û�غ�����!");
					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���̿�!");
					++m_iTextSprite;
					break; }
				case 10: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					m_iTalkState = 3;
					break;
				}
				}
			}
			else if (m_iTalkState == 3)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"���� ������ ��� ������....");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEFIVE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
		}
		else if (g_iLevel == LEVEL_STAGESEMIAFTER)
		{

			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�� ���! ���� ����� ���͸� �����̱���!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEMIAFTER, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"������. ���������� ����ó�� �����ϰ� ���ƿԾ��.");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEMIAFTER, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� ���� ���������� �������!");

					++m_iTextSprite;
					break; }
				case 3: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEMIAFTER, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESEMIAFTER, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					m_iTalkState = 1;
					break;
				}
				}
			}
			else if (m_iTalkState == 1)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"S��������2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(�� ���� �� �˾Ҵµ�.... ���~)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGESEMIAFTER, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEMIAFTER, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGESEMIAFTER, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}
					m_iTextSprite = 0;
					break;
				}
				}
			}
		}
	}
}


void CWarrior::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	++m_iTick;
	BillBoard(m_pTransform);

	if (m_iTick == 10) {
		++m_iSprite;
		m_iTick = 0;
	}

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CWarrior::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CWarrior : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite % 8))) {
		MSG_BOX(L"Failed To CWarrior : Render");
		return E_FAIL;
	}
	if (FAILED(m_pTransform->Bind_OnGraphicDevice())) {
		MSG_BOX(L"Failed To CWarrior : Render");
		return E_FAIL;
	}

	m_pVIBuffer->Render();
	return S_OK;
}

HRESULT CWarrior::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CWarrior : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureWarrior"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Warrior"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CWarrior : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CWarrior : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CWarrior : SetUp_Components");
		return E_FAIL;
	}

	return S_OK;
}

CWarrior * CWarrior::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CWarrior*	pInstance = new CWarrior(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CWarrior : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CWarrior::Clone(void * pArg)
{
	CWarrior*	pInstance = new CWarrior(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CWarrior : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWarrior::Free()
{
	__super::Free();
}
