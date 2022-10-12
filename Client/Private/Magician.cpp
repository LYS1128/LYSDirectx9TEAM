#include "stdafx.h"
#include "..\Public\Magician.h"

CMagician::CMagician(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CNPC(pGraphic_Device)
{
}

CMagician::CMagician(const CMagician & rhs)
	: CNPC(rhs)
{
}

HRESULT CMagician::NativeConstruct_Prototype()
{

	if (FAILED(__super::NativeConstruct_Prototype())) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct_Prototype");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CMagician::NativeConstruct(void * pArg)
{
	if (FAILED(__super::NativeConstruct(pArg))) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct");
		return E_FAIL;
	}
	if (FAILED(SetUp_Components())) {
		MSG_BOX(L"Failed To CMagician : NativeConstruct");
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

void CMagician::Tick(_float fTimeDelta)
{
	__super::Tick(fTimeDelta);

	if (m_pGameInstance->Key_Down('Z') && Check_Player_InArea())
	{
		if (g_iLevel == LEVEL_TUTORIAL)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"ġ��� ���̺�~");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"ġ��� ���̺�~!");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� �� ���� ��~!");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"...��? ����, �̷� ���� �̹�����?");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"����������?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"��.... �׷� ����.... ���;;");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�׷��ٸ� �������� ���� �Ұ��ϰڽ��ϴ���.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�ȳ��ϼ�����! ���� ���������Դϴ���.");

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"��� ������ ���� �ຸ�Ƿ�����?");

					++m_iTextSprite;
					break; }
				case 10: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 11: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"��... �̰� ����ü?!");

					++m_iTextSprite;
					break; }
				case 12: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...��� Ȥ�� �Ѱ��ϴٸ� �� ������ ������ �Ǿ���� �ʰھ����?");

					++m_iTextSprite;
					break; }
				case 13: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���۹�: WSAD(�����¿�) SPACE(����) ENTER(��Ż)");

					++m_iTextSprite;
					break; }
				case 14: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L";;;");

					++m_iTextSprite;
					break; }
				case 15: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� �ִ� ��Ż�� Ÿ�� ���� ���������� ��������! ��ٸ��� �����Կ���!");

					++m_iTextSprite;
					break; }
				case 16: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"? ���� ��������.");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_TUTORIAL, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_TUTORIAL, L"Layer_Font")->Get_List();
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
		else if (g_iLevel == LEVEL_STAGEONE)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"������ ���̳׿���. (�ð踦 ����....)");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"...�������ϴ���. ���� ó������ �ٵ� �׷����󱸿���.");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...?");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"����� �������! �츮 ���迡�� ��Ƴ��� �� �ִ� ����� �˷��帱�Կ���.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"Ȥ�� �����ϴ� ����� �˰� ����������?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"������.... ���� �˷��帱�Կ���. ");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���۹�: 1(Freezing)");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� �� �񷯺�������.");

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 10: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���ƿ���. �غ� �� �� �� ���׿���.");

					++m_iTextSprite;
					break; }
				case 11: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� �� ��Ż�� �������ΰ� ���̼�����? ���� ������ ���� ��Ż�� �̿��Ͻ� �� �������.");


					++m_iTextSprite;
					break; }
				case 12: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� �� ���ʿ� �ִ� �� ���͸� ������ ��Ż�� ���� �͸� ���ƿ���.");

					++m_iTextSprite;
					break; }
				case 13: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"��.... �׷��� ���� �� ���� ó�����ش�?");

					++m_iTextSprite;
					break; }
				case 14: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 15: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�� �ٳ��������.");

					++m_iTextSprite;
					break; }
				case 16: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"����!");
					++m_iTextSprite;
					break; }
				case 17: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���۹� - K(����â����)");
					++m_iTextSprite;
					break; }
				case 18: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�׷� ���� ��������. (1��... 2��... 3��..........)");
					++m_iTextSprite;
					break; }
				case 19: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L";;;;;;");

					++m_iTextSprite;

					break; 
				}
				case 20: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"���� ���� �� ( %d");
					tQuest.tFont.tFontInfo.Width =15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 1;
					tQuest.iOption = 0;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"34��... 35��... 36��...");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
					

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�ƶ��... ���� ���� �μ��̴� ���̿�����...? �����ΰɿ���....");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1:{
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"(���� �̷��� ����...? �� �༮ ���⺸��... �Ǿб�?)");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 3: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���ƿ���! ���� ��Ż�� ������ �Ķ������� �������ſ�����!");
					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"� ���� ���������� �̵��ؿ���! ��������!");
					++m_iTextSprite;
					
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...?");

					++m_iTextSprite;
					break; }
				case 6: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"������~ ������~");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEONE, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEONE, L"Layer_Font")->Get_List();
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
		else if (g_iLevel == LEVEL_STAGETWO)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"������! ���������!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"Ȥ�� �������� ����ϴ� ����� �Ƽ�����?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�� ������ ���͵�� �¼��� ���ؼ� ������ �ʼ�������! �ʼ�~!");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"HP�� ���ڶ�� �Ķ�����, MP�� ���ڶ�� ���������� �Ծ������!");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"��.... �ݴ��ΰ�...? �ƹ�ư! ���� �����̿�����!");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���۹�: Ctrl+1(��������). Ctrl+2(�Ķ�����)");
					dynamic_cast<CPlayer*>((m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front()))->PlusHpPo();
					dynamic_cast<CPlayer*>((m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front()))->PlusMpPo();

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�׸���, �����Կ��� ������ �ʿ��� ��ų�� �ϳ� �˷��帱�Կ���!");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�켱 �Ź��̶� �縻�� ���� �ż��� �ǽ��� �غ��ϼ�����!");

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...?");

					++m_iTextSprite;
					break; }
				case 10: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"����̿�����! ���� �ຸ�Ƿ�����?");

					++m_iTextSprite;
					break; }
				case 11: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���۹�: 2(Cray)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(64);

					++m_iTextSprite;
					break; }
				case 12: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�����? �� ���� ������ ���� �� ����������?");

					++m_iTextSprite;
					break; }
				case 13: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�׷� �������� ��� �� ���ŷ� ������ �ҿ��� �ټ� �� ������������!");

					++m_iTextSprite;
					break; }
				case 14: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���Ͱ� ����Ʈ�� ������ ��ó�� �ٰ����� ���� �� �־����.");

					++m_iTextSprite;
					break; }
				case 15: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"��������! �䰪�Ϸ� ��������!");

					++m_iTextSprite;
					break; }
				case 16: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 17: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_QuestWindow", L"Prototype_GameObject_QuestWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CQuest::QUEST tQuest;
					tQuest.tFont.eTextId = CText::TEXT_QUEST;
					tQuest.tFont.rc = { 1060, 325, g_iWinCX, 400 };
					lstrcpy(tQuest.tFont.szText, L"���� �ҿ��� �� ( %d");
					tQuest.tFont.tFontInfo.Width = 15;
					tQuest.tFont.tFontInfo.Height = 10;
					tQuest.tFont.vARGB = _float4(255, 0, 0, 0);
					tQuest.iRequireMonsterCnt = 5;
					tQuest.iOption = 1;

					m_pGameInstance->Add_GameObjectToLayer(g_iLevel, L"Layer_Quest", L"Prototype_Quest", &tQuest);

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"��.... �ҿ��� ��� �ִ°�����? ȥ������!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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
					CQuestWindow* pQuestWindow = (CQuestWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_QuestWindow")->Get_List()->front());
					pQuestWindow->Set_Dead();
				

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"�ϳ�... ��... �ټ�!");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���߾����! ��Ż�� ������ �Ķ������� ���߾����!");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"���� ������������ ����� �Ƿ��� ���� ���ھ����!");
					++m_iTextSprite;
					break; }
				case 3: {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"������~ ������~");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGETWO, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {

					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGETWO, L"Layer_Font")->Get_List();
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
		else if (g_iLevel == LEVEL_STAGEEIGHT)
		{
			if (m_iTalkState == 0)
			{
				switch (m_iTextSprite)
				{
				case 0: {

					if (FAILED(m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_TextWindow", L"Prototype_GameObject_TextWindow_UI")))
					{
						MSG_BOX(L"Failed To CMagician : Tick");
						return;
					}

					CText::FONT tFont;
					ZeroMemory(&tFont.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont.rc = RECT{ 150, 440, 1280,520 };
					lstrcpy(tFont.szText, L"�����ͻ�������");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"��ӳ�~ �̰� ������? �츮 ������ �ƴϾ�?");
					tFont2.tFontInfo.Height = 30;
					tFont2.tFontInfo.Width = 20;
					tFont2.eTextId = CText::TEXT_NPC;
					tFont2.vARGB = _float4(255, 255, 255, 255);

					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Font", L"Prototype_GameObject_Font", &tFont2);
					m_pGameInstance->Add_GameObjectToLayer(LEVEL_STAGEEIGHT, L"Layer_Font", L"Prototype_GameObject_Font", &tFont);

					++m_iTextSprite;

					break; }
				case 1: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�����ϴ�~ ���� ������ �� ����?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...!");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�����̳�? �¾�~ ���� ���� �ٸ糽 ���̾�.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"��� ������ ���忡 ���� ���谡�� �� ���´ٴ� �ҹ� �����?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"���� �� ��ƸԾ��������~");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi������r����");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...!!!");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"�����ͻ�������");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"�� �� �ʿ� ����~ �ʵ� �� �� �ϳ��� ���̴ϱ�.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�װ� ������ ���� �ҿ��� ���� ��������~ �ʴ� ���⼭ �׵��� ��.");
					dynamic_cast<CPlayer*>(m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Lost_Soul();

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"�׷�, �ȳ�?");

					++m_iTextSprite;
					break; }
				case 10 : {
					CTextWindow* pTextWindow = (CTextWindow*)(m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_TextWindow")->Get_List()->front());
					pTextWindow->Set_Dead();

					list<CGameObject*>* pText = m_pGameInstance->Find_Layer(LEVEL_STAGEEIGHT, L"Layer_Font")->Get_List();
					for (auto iter : *pText)
					{
						if (dynamic_cast<CText*>(iter)->Get_TextID() == CText::TEXT_NPC)
							iter->Set_Dead();
					}

					m_eState = STATE_DEAD;
					m_iTextSprite = 0;
					m_iTalkState = 1;
					break;
				}
				}
			}
		}
	}
}

void CMagician::LateTick(_float fTimeDelta)
{
	__super::LateTick(fTimeDelta);

	++m_iTick;

	if (m_iTick == 10) {
		++m_iSprite;
		m_iTick = 0;
	}

	m_pRenderer->Add_RenderGroup(CRenderer::GROUP_NONBLEND, this);
}

HRESULT CMagician::Render()
{
	if (FAILED(__super::Render())) {
		MSG_BOX(L"Failed To CMagician : Render");
		return E_FAIL;
	}

	if (FAILED(m_pTexture->Bind_OnGraphicDevice(m_iSprite%6))) {
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

HRESULT CMagician::SetUp_Components() {
	CTransform::TRANSFORMDESC TransformDesc;
	ZeroMemory(&TransformDesc, sizeof(CTransform::TRANSFORMDESC));

	TransformDesc.fSpeedPerSec = 1.f;
	TransformDesc.fRotationPerSec = D3DXToRadian(90.0f);
	TransformDesc.fScalePerSec = 1.f;

	if (FAILED(__super::SetUp_Components(TEXT("Com_Transform"), LEVEL_STATIC, TEXT("Prototype_Component_Transform"), (CComponent**)&m_pTransform, &TransformDesc))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(TEXT("Com_TextureMagician"), LEVEL_STATIC, TEXT("Prototype_Component_Texture_Magician"), (CComponent**)&m_pTexture))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_VIBuffer", LEVEL_STATIC, L"Prototype_Component_VIBuffer_Rect", (CComponent**)&m_pVIBuffer))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
	}
	if (FAILED(__super::SetUp_Components(L"Com_Renderer", LEVEL_STATIC, L"Prototype_Component_Renderer", (CComponent**)&m_pRenderer))) {
		MSG_BOX(L"Failed To CMagician : SetUp_Components");
		return E_FAIL;
 	}

	return S_OK;
}

CMagician * CMagician::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CMagician*	pInstance = new CMagician(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct_Prototype())) {
		MSG_BOX(TEXT("Failed To CMagician : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CMagician::Clone(void * pArg)
{
	CMagician*	pInstance = new CMagician(*this);
	if (FAILED(pInstance->NativeConstruct(pArg))) {
		MSG_BOX(TEXT("Failed To CMagician : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMagician::Free()
{
	__super::Free();
}
