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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"헐 띠용? 누구세용?");
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
					pText->Set_Text(L"엥 띠용? 상현공주는 어디있냐고용?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"이 근처에 그런 사람 안 사는데용? 진짜 띠용이네용.");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S윤서꺼얌2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"그건 모르겠고 혹시 저 좀 도와주실 수 있어용?");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"저 이상한 곰인형들을 다 잡아야 하는데 저기까지 올라가기가 너무 귀찮아서용;");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S윤서꺼얌2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"대신 좋은 기술 하나 알려드릴게용. 진짜 일급 비밀인데 특별히 알려드리는거에용.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"조작법: 3(IceUp)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(32);

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"다 잡으면 불러주세용. 전 아이스 초코라떼 마시러 갈래용.");

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
					lstrcpy(tQuest.tFont.szText, L"잡은 몬스터 수 ( %d");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"어 띠용? 아직 곰인형을 다 잡지 않으셨네용.");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"오 띠용? 곰인형을 다 잡으셨네용! 감사해용.");
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
					pText2->Set_Text(L"그런데 그 소울은 왜 모으고 계신 건가용? 정말 띠용이네용.");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S윤서꺼얌2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"아무튼 꽤 강하신 것 같은데 조금만 더 저를 도와주시겠어용?");
					++m_iTextSprite;
					break; }
				case 4: {
					dynamic_cast<CPortal*>(m_pGameInstance->Find_Layer(LEVEL_STATIC, L"Layer_Portal")->Get_List()->front())->Set_Open(true);
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"제 부탁을 들어주시면 지금처럼 포탈을 열어드릴게용.");
					++m_iTextSprite;

					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 6: {

					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGETHREE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"좋아용! 다음 스테이지에서 만나용.");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"초코라떼 맛있어용.");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"오셨군용!");
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
					pText->Set_Text(L"사실 이 스테이지는 따뜻한 곳이었다는 거 아시나용?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"정말 띠용이죠?");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"얼마 전에 언덕 위의 성에 눈사람 몬스터가 나타난 이후로 갑자기 눈이 내리기 시작했어용.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"그래서 그 몬스터를 제가 잡아야 하는데용....");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"제가 잡기엔 너무 귀찮아서용;");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S윤서꺼얌2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"우선 성 주변에 있는 몬스터들을 20마리 정도만 사냥해 주시겠어용?");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"저는 먼저 가서 포탈을 열 준비를 하고 있을게용.");

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
					lstrcpy(tQuest.tFont.szText, L"잡은 몬스터 수 ( %d");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(아이스티를 마시는 중이다.)");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"오 띠용? 벌써 스무 마리를 다 잡으셨네용.");
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
					pText2->Set_Text(L"마침 포탈을 방금 연 참이에용.");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S윤서꺼얌2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"감사의 의미로 몬스터를 잡을 때 도움이 될 만한 기술을 알려드릴게용.");
					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"조작법: 4(Shield)");

					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(16);

					++m_iTextSprite;

					break; }
				case 5: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFOUR, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"좋아용! 다음 스테이지에서 만나용.");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(아이스티를 한 잔 더 마시고 있다.)");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"이곳의 포탈을 여는 법은 간단해용. 포탈을 지키고 있는 호박 몬스터만 잡아주시면....");
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
					pText->Set_Text(L"헐 띠용? 저 미로는 뭐죵? 엥? 진짜 띠용?");

					++m_iTextSprite;

					break; }
				case 2: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"원래 저런 거 없었거든용? 진짜 이상한 일이네용.");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"어휴.... 그래도 하는 수 없죵. 어쨌든 호박을 잡아주셔야 포탈을 열 수 있어용.");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...;");

					++m_iTextSprite;
					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S윤서꺼얌2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"하지만 길이 이래서야 쉽지 않겠네용....");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"아 띠용! 좋은 방법이 생각났어용!");

					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"길을 좀 더 가까이서 볼 수 있는 방법을 알려드릴게용.");

					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText->Set_Text(L"조작법: (1인칭 카메라), (3인칭 카메라)");
					dynamic_cast<CPlayer*> (m_pGameInstance->Find_Layer_List(LEVEL_STATIC, L"Layer_Player")->front())->Set_SkillOpen(3);

					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"이제 출발하세용~!");

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
					lstrcpy(tQuest.tFont.szText, L"잡은 몬스터 수 ( %d");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(달고나 라떼에서 달고나만 골라 먹는 중이다.)");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"오! 빨리 돌아오셨네용.");
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
					pText2->Set_Text(L"헐 띠용! 길을 찾으셨다구용? 대단해용!");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"그런데 포탈까지는.... 어떻게 가죵...?");

					++m_iTextSprite;
					break; }
				case 3: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"... ... ... .");

					++m_iTextSprite;
					break; }
				case 4: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"저 갑자기 집에 가고 싶어져서용! 이만 가볼게용!");
					++m_iTextSprite;

					break; }
				case 5: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"zi존전ㅅr영웅");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"...???");

					++m_iTextSprite;
					break; }
				case 6: {
					CText* pText = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->back());
					pText->Set_Text(L"S윤서꺼얌2");
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"절대 제가 길치라서는 아니고용! 그래도 포탈은 열려 있을 거에용!");
					++m_iTextSprite;
					break; }
				case 7: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"그러고 보니 다음 스테이지에는 이 세상의 모든 것에 대해 알고 있는 문어왕이 있대용.");
					++m_iTextSprite;
					break; }
				case 8: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"다음 포탈부터는 그 분에게 도움을 요청해보세용!");
					++m_iTextSprite;
					break; }
				case 9: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGEFIVE, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"빠이용!");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"이제 집에는 어떻게 가지용....");
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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"와 띠용! 정말 눈사람 몬스터를 잡으셨군용!");
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
					pText2->Set_Text(L"보세용. 스테이지가 예전처럼 따뜻하게 돌아왔어용.");
					++m_iTextSprite;
					break; }
				case 2: {
					CText* pText2 = (CText*)(m_pGameInstance->Find_Layer(LEVEL_STAGESEMIAFTER, L"Layer_Font")->Get_List()->front());
					pText2->Set_Text(L"이제 다음 스테이지로 가볼까용!");

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
					lstrcpy(tFont.szText, L"S윤서꺼얌2");
					tFont.tFontInfo.Height = 40;
					tFont.tFontInfo.Width = 30;
					tFont.eTextId = CText::TEXT_NPC;
					tFont.vARGB = _float4(255, 255, 255, 255);

					CText::FONT tFont2;
					ZeroMemory(&tFont2.tFontInfo, sizeof(D3DXFONT_DESCW));
					tFont2.rc = RECT{ 300, 500, 1280, 550 };
					lstrcpy(tFont2.szText, L"(못 잡을 줄 알았는데.... 띠용~)");
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
