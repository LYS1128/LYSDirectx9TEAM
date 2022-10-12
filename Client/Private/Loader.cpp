#include "stdafx.h"
#include "..\Public\Loader.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	:m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

CRITICAL_SECTION CLoader::Get_CriticalSection() {
	return m_CriticalSection;
}

LEVEL CLoader::Get_LevelIndex() {
	return m_eLevel;
}

_bool CLoader::Get_Finished() const {
	return m_bFinished;
}

unsigned int APIENTRY ThreadEntryFunc(void* pArg) {
	CLoader* pLoader = (CLoader*)pArg;
	EnterCriticalSection(&pLoader->Get_CriticalSection());

	switch (pLoader->Get_LevelIndex()) {
	case LEVEL_TUTORIAL: {
		pLoader->Loading_LevelTurotial();
		break;
	}
	case LEVEL_STAGEONE: {
		pLoader->Loading_LevelStageOne();
		break;
	}
	case LEVEL_STAGETWO: {
		pLoader->Loading_LevelStageTwo();
		break;
	}
	case LEVEL_STAGETWO_1: {
		pLoader->Loading_LevelStageTwo_1();
		break;
	}
	case LEVEL_STAGETHREE: {
		pLoader->Loading_LevelStageThree();
		break;
	}
	case LEVEL_STAGEFOUR: {
		pLoader->Loading_LevelStageFour();
		break;
	}
	case LEVEL_STAGESEMIBOSS: {
		pLoader->Loading_LevelStageSemiBoss();
		break;
	}
	case LEVEL_STAGESEMIAFTER: {
		pLoader->Loading_LevelStageSemiAfter();
		break;
	}
	case LEVEL_STAGEFIVE: {
		pLoader->Loading_LevelStageFive();
		break;
	}
	case LEVEL_STAGESIX: {
		pLoader->Loading_LevelStageSix();
		break;
	}
	case LEVEL_STAGESEVEN: {
		pLoader->Loading_LevelStageSeven();
		break;
	}
	case LEVEL_STAGEEIGHT: {
		pLoader->Loading_LevelStageEight();
		break;
	}
	case LEVEL_STAGEBOSS: {
		pLoader->Loading_LevelStageBoss();
		break;
	}
	case LEVEL_STAGESPECIAL: {
		pLoader->Loading_LevelStageSpecial();
		break;
	}
	}
	LeaveCriticalSection(&pLoader->Get_CriticalSection());
	return 0;
}

HRESULT CLoader::NativeConstruct(LEVEL eLevel) {
	m_eLevel = eLevel;
	InitializeCriticalSection(&m_CriticalSection);
	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntryFunc, this, 0, nullptr);
	if (0 == m_hThread) {
		MSG_BOX(L"Failed To CLoader : NativeConstruct");
		return E_FAIL;
	}
	return S_OK;
}

HRESULT CLoader::Loading_LevelTurotial() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV1"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_1/Loading_Stage2_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV1)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV1"), CLoading_Level1::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV1");
		return E_FAIL;
	}


#pragma region 텍스쳐 로딩

#pragma region 튜토리얼 오브젝트 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../../Resources/Tile/Tile%d.dds"), 341)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(타일)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shadow"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Shadow/Shadow.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(그림자)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Sky"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../Resource/Object/Sky/SkyBox%d.dds"), 14)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(하늘)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Magician"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/NPC/Magician/Npc_Magician%d.png"), 6)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(상현공주)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RedPortal"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Portal/RedGate%d.png"), 24)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(빨간포탈)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BluePortal"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Portal/WarpGate%d.png"), 24)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(파란포탈)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Dead"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Dead/Dead.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(묘비)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_GameOver"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/GameOver/GameOver.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(게임오버)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Particle"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../Resource/Object/Effect/Particle/Particle%d.dds"),24)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(파티클)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Blood"), CBlood::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(피...)");
		return E_FAIL;
	}
#pragma endregion

#pragma region UI로딩
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Hexagon_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_Health.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Hexagon_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LSkillBox_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_SkillBox_Left.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LSkillBox_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_RSkillBox_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_SkillBox_Right.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(RSkillBox_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_HP_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_HP.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(HP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MP_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_MP.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(MP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_AlphaHP_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_HP_Alpha1.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(AlphaHP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_AlphaMP_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_MP_Alpha1.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(AlphaMP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_TextWindow"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_NPCText.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(TextWindow)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_StatWindow"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Player_Stat.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(StatWindow)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ExpBar_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_ExpBar1.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(ExpBar_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_ExpIng_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_ExpBar_ing.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(ExpIng_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Invisible_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_ExpBar1.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(InvisibleBar_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Text"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Exp_Text_2_%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Exp_Text)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Text2"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Exp_Text_1_%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Exp_Text2)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Exp_Text3"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Exp_Text_2.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Exp_Text3)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_PlayerName_UI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Player_Name%d.png"), 30)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(PlayerName_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_CoolDown"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/SkillBlock%d.png"), 18)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_HpLow"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/HpLow.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(HpLow)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_LevelUp"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/LevelUp/LevelUp_%d.png"), 21)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(레벨업)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 달리기 텍스쳐

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_U/Run_U%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_D/Run_D%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunL"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_L/Run_L%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunR"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_R/Run_R%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunLD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_LD/Run_LD%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunLU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_LU/Run_LU%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunRD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_RD/Run_RD%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_RunRU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Run/Run_RU/Run_RU%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달리기)");
		return E_FAIL;
	}

#pragma endregion

#pragma region 스탠딩 텍스쳐

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_U/Stand_U%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_D/Stand_D%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandL"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_L/Stand_L%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandR"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_R/Stand_R%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandLD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_LD/Stand_LD%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandLU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_LU/Stand_LU%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandRD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_RD/Stand_RD%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StandRU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stand/Stand_RU/Stand_RU%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(스탠딩)");
		return E_FAIL;
	}

#pragma endregion

#pragma region 평타 텍스쳐

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_U/Stab_U%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_D/Stab_D%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabL"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_L/Stab_L%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabR"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_R/Stab_R%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabLD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_LD/Stab_LD%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabLU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_LU/Stab_LU%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabRD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_RD/Stab_RD%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_StabRU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Stab/Stab_RU/Stab_RU%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(평타)");
		return E_FAIL;
	}

#pragma endregion

#pragma region 아이스 텍스쳐

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_U"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_U/Horcut_U%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_D"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_D/Horcut_D%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_L"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_L/Horcut_L%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_R"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_R/Horcut_R%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_LD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_LD/Horcut_LD%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_LU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_LU/Horcut_LU%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_RD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_RD/Horcut_RD%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Horcut_RU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Horcut/Horcut_RU/Horcut_RU%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스)");
		return E_FAIL;
	}

#pragma endregion

#pragma region 크레이 텍스쳐

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_U"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_U/Vercut_U%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_D"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_D/Vercut_D%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_L"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_L/Vercut_L%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_R"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_R/Vercut_R%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_LD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_LD/Vercut_LD%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_LU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_LU/Vercut_LU%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_RD"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_RD/Vercut_RD%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_RU"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Player/Vercut/Vercut_RU/Vercut_RU%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(크레이)");
		return E_FAIL;
	}



#pragma endregion

#pragma region 평타 이펙트 텍스처
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Stab_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Effect/Freeze/Freeze%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(프리징이펙트)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 히트 이펙트 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Freeze_Hit"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Hit_Effect/Freeze/Freeze%d.png"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Freeze)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Cray_Hit"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Hit_Effect/Cray/pngwing%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Cray)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Ice_Hit"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Hit_Effect/Ice/Hit_Ice%d.png"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Freeze)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Earthquake_Hit"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Hit_Effect/Earthquake/pngegg%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Freeze)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MoonLight_Hit"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Hit_Effect/Moon/Moon%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Freeze)");
		return E_FAIL;
	}

#pragma endregion

#pragma endregion


#pragma region 게임오브젝트

#pragma region 튜토리얼 오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ground"), CGround::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(지형)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Shadow"), CShadow::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(그림자)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Player"), CPlayer::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(플레이어)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Magician"), CMagician::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(상현공주)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Portal"), CPortal::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(포탈)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sky"), CSky::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(하늘)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MultiCamera"), CMultiCamera::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(카메라)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_GameOver_UI"), CGameOver::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(게임오버)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Particle"), CParticle::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(파티클)");
		return E_FAIL;
	}

#pragma endregion

#pragma region UI 오브젝트

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Hexagon_UI"), CHexagon_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Hexagon_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LSkillBox_UI"), CLSkillBox::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CLSkillBox_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_RSkillBox_UI"), CRSkillBox::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CRSkillBox_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_HP_UI"), CHP_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(HP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MP_UI"), CMP_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(MP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_AlphaHP_UI"), CAlphaHP_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(AlphaHP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_AlphaMP_UI"), CAlphaMP_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(AlphaMP_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_TextWindow_UI"), CTextWindow::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(TextWindow_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_QuestWindow_UI"), CQuestWindow::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(TextWindow_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StatWindow_UI"), CStatWindow::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(StatWindow_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ExpBar_UI"), CExp_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(ExpBar_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ExpIng_UI"), CExpIng_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(ExpIng_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Exp_Invisible_UI"), CExp_Invisible_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Exp_Invisible_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Exp_Text"), CExp_Text::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Exp_Text)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Exp_Text2"), CExp_Text2::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Exp_Text2)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Exp_Text3"), CExp_Text3::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Exp_Text3)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PlayerName_UI"), CPlayerName_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(PlayerName_UI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CoolDown"), CCool_Down::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CoolDown3"), CCool_Down3::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown3)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CoolDown4"), CCool_Down4::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown4)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CoolDown5"), CCool_Down5::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown5)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CoolDown6"), CCool_Down6::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown6)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CoolDown7"), CCool_Down7::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown7)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CoolDown8"), CCool_Down8::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CoolDown8)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_HpLow"), CHpLow::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(HpLow)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LevelUp"), CLevelUp::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(레벨업)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 평타 이펙트 오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Freeze"), CFreeze::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(프리징이펙트)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 히트 이펙트 오브젝트

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Hit_Effect"), CHit_Effect::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(히트 이펙트)");
		return E_FAIL;
	}
#pragma endregion

#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLoader::Loading_LevelStageOne() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	
	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

	
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV2"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_2/Loading_Stage3_%d.png"), 13)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV2)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV2"), CLoading_Level2::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV2");
		return E_FAIL;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEONE, TEXT("Prototype_Component_Texture_Gourd"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Gourd/Gourd%d.png"), 9)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(박)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_종이접기"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Damage/종이접기/종이접기%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(종이접기 데미지)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_검은사슬"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Damage/검은사슬/검은사슬%d.png"), 10)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(검은사슬 데미지)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MonsterHpBar"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/MonsterHpBar.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(몬스터 체력바)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_MonsterRealHp"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/MonsterRealHp.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(몬스터 체력)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_UI_QuestWindow"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/UI_QuestText.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(QuestWindow)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Item"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Item/Item%d.png"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이템)");
		return E_FAIL;
	}

#pragma endregion

#pragma region 게임오브젝트
	if (FAILED(pGameInstance->Add_Prototype(L"Prototype_GameObject_MonsterHpBar", CMonsterHpBar::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(MonsterHpBar)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(L"Prototype_GameObject_MonsterRealHp", CMonsterRealHp::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(MonsterRealHp)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Gourd"), CGourd::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CGourd)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Damage_UI"), CDamage::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Damage)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(L"Prototype_Quest", CQuest::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Quest)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Item"), CItem::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Item)");
		return E_FAIL;
	}

#pragma endregion



	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageTwo() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Player_Vercut_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Effect/Cray/Cray%d.png"), 8)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(종베기이펙트)");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGETWO, TEXT("Prototype_Component_Texture_Slime"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Slime/Slime%d.png"), 18)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(슬라임)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGETWO, TEXT("Prototype_Component_Texture_Sakura"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../Resource/Object/Effect/Sakura/Sakura%d.dds"), 3)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(꽃잎)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Slime"), CSlime::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(슬라임)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_VerCutEffect"), CEffectCray::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(종베기이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Sakura"), CSakura::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(종베기이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CrayParticle"), CCray_ParticleEffect::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(종베기이펙트)");
		return E_FAIL;
	}


#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageTwo_1()
{
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV3"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_3/Loading_Stage_3_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV3)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV3"), CLoading_Level3::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV3");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGETWO_1, TEXT("Prototype_Component_Texture_QuizUI"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Quiz/Quiz%d.png"), 105)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(QuizUI)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_QuizUI"), CQuiz_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : QuizUI");
		return E_FAIL;
	}

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;

}
HRESULT CLoader::Loading_LevelStageThree() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}


	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV4"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_4/Loading_Stage_4_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV4)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV4"), CLoading_Level4::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV4");
		return E_FAIL;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Warrior"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/NPC/Warrior/Warrior%d.png"), 8)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(윤서꺼얌)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGETHREE, TEXT("Prototype_Component_Texture_CuteBear"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/CuteBear/CuteBear%d.png"), 27)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CuteBear)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_Ice"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Effect/IceUp/%d.png"), 20)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스이펙트)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Warrior"), CWarrior::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(윤서꺼얌)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CuteBear"), CCuteBear::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CuteBear)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ice"), CIce::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이스이펙트)");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_IceParticle"), CIcePart::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(파티클)");
		return E_FAIL;
	}
#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageFour() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV4_1"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_4-1/Loading_Stage4_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV4_1)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV4_1"), CLoading_Level4_1::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV4");
		return E_FAIL;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Snow"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../Resource/Object/Effect/Snow/RealSnow.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(눈)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEFOUR, TEXT("Prototype_Component_Texture_CokeMush"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/CokeMushroom/CokeMush%d.png"), 21)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CokeMush)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEFOUR, TEXT("Prototype_Component_Texture_IceGolem"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/IceGolem/IceGolem%d.png"), 23)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(IceGolem)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Shield"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Effect/Shield/Shield%d.png"), 6)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(쉴드이펙트)");
		return E_FAIL;
	}

#pragma endregion

#pragma region 게임오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Snow"), CSnow::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Snow)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CokeMush"), CCokeMushroom::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CokeMushroom)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_IceGolem"), CIceGolem::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(IceGolem)");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Shield"), CShield::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(쉴드이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_ShieldParticle"), CShieldParticle::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(쉴드파티클)");
		return E_FAIL;
	}
#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageSemiBoss() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_Semi0"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_SemiBoss/Loading_SemiNext13.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(로딩이미지)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Semi0"), CLoad_Semi0::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : semi0");
		return E_FAIL;
	}


	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_NooNoo"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/NooNoo/NooNoo%d.png"), 46)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(NooNoo)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_CloneNooNoo"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/NooNoo/NooNoo%d.png"), 46)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CloneNooNoo)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_MiniNooNoo"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/NooNoo/MiniNooNoo%d.png"), 8)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(MiniNooNoo)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEMIBOSS, TEXT("Prototype_Component_Texture_Semi1"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_SemiBoss/Loading_SemiNext%d.png"), 15)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(세미1)");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_BossHpBar"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/HpBoss.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(BossHpBar)");
		return E_FAIL;
	}

#pragma endregion

#pragma region 게임오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_NooNoo"), CNooNoo::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(NooNoo)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MiniNooNoo"), CMiniNooNoo::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(MiniNooNoo)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CloneNooNoo"), CCloneNooNoo::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(CloneNooNoo)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Semi1"), CSemi_1::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Semi1)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_BossHpBar"), CBossHpBar::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(보스 체력바)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_BossHpReal"), CBossRealHp::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(보스 체력)");
		return E_FAIL;
	}
#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageSemiAfter() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV5"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_5/Loading_Stage_5_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV4)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV5"), CLoading_Level5::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV4");
		return E_FAIL;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEMIAFTER, TEXT("Prototype_Component_Texture_Semi2"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_SemiBossNext/Loading_SemiBoss%d.png"), 15)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(세미2)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Semi2"), CSemi_2::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Semi2)");
		return E_FAIL;
	}

#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageFive() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV6"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_6/Loading_Stage_6_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV6)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV6"), CLoading_Level6::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV6");
		return E_FAIL;
	}




#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEFIVE, TEXT("Prototype_Component_Texture_Pumpkin"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Pumpkin/Pumpkin%d.png"), 24)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(펌킨)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Aim"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/FPS/Aim.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(에임)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Pumpkin"), CPumpkin::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(펌킨)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Aim_UI"), CFPS::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(에임)");
		return E_FAIL;
	}
#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageSix() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV7"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_7/Loading_Stage_7_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV7)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV7"), CLoading_Level7::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV7");
		return E_FAIL;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_EarthQuake"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Effect/EarthQuake/EarthQuake/EarthQuake%d.png"), 9)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(지진이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Theif"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/NPC/Theif/Thief%d.png"), 8)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(문어왕한승)");
		return E_FAIL;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESIX, TEXT("Prototype_Component_Texture_GhostStump"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/GhostStump/GhostStump%d.png"), 17)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(고스텀프)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESIX, TEXT("Prototype_Component_Texture_IronBoar"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/IronBoar/IronBoar%d.png"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이언보어)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESIX, TEXT("Prototype_Component_Texture_CokeGolem"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/CokeGolem/CokeGolem%d.png"), 22)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(코크골렘)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESIX, TEXT("Prototype_Component_Texture_FireBoar"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/FireBoar/FireBoar%d.png"),12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(코크골렘)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_EarthQuake"), CEarthQuake::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(지진이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_GhostStump"), CGhostStump::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(고스텀프)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_IronBoar"), CIronBoar::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(아이언보어)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_CokeGolem"), CCokeGolem::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(코크골렘)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_FireBoar"), CFireBoar::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(파이어보어)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Theif"), CTheif::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(문어왕한승)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_EQParticle"), CEQParticle::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(파티클)");
		return E_FAIL;
	}
#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageSeven() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLV8"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Stage_8/Loading_Stage_8_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLV8)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLV8"), CLoading_Level8::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLV8");
		return E_FAIL;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_MoonLight"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Effect/MoonLight/MoonLight%d.png"),30)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(달빛이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Effect_Dark"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Effect/Dark/Dark.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(어둠)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Wraith"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Wraith/Wraith%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageSeven(레이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_SangIn"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/NPC/SangIn/SangIn%d.png"), 6)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(송채바리)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Store"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Store.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(상점)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Red"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Item/Item0.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(빨간포션)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Blue"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Item/Item1.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(파란포션)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESEVEN, TEXT("Prototype_Component_Texture_Exit"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Exit.png"), 1)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(나가기)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ultimate_UI"), CUltimate_Skill::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(궁)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Dark_UI"), CDark_Effect::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(어둠)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_MoonLight"), CMoonLight_Effect::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(문라이트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Wraith"), CWraith::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageSeven(레이스)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_SangIn"), CSangIn::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(송채바리)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Store"), CStore::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(상점)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_StoreObject"), CStore_Potion::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(상점 재고)");
		return E_FAIL;
	}

#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}
HRESULT CLoader::Loading_LevelStageEight() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

	for (int i = 0; i < (int)LOADING; ++i)
	{
		int a = 10;
	}

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_LOADING, TEXT("Prototype_Component_Texture_LDLVBoss"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Level_Loading/Loading_Boss/Loading_Stage_Boss_%d.png"), 12)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(LDLVBoss)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_LDLVBoss"), CLoading_LevelBoss::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : LDLVBoss");
		return E_FAIL;
	}

#pragma region 텍스쳐
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Rain"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../Resource/Object/Effect/Rain/Rain.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(비)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEEIGHT, TEXT("Prototype_Component_Texture_Typhon"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Typhon/Typhon%d.png"), 30)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Typhon)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Rain"), CRain::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Rain)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Typhon"), CTyphon::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(Typhon)");
		return E_FAIL;
	}

#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLoader::Loading_LevelStageBoss() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region 텍스쳐

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Phase1"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/JrBalrog/JrBalrog%d.png"), 30)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(페이즈1 주니어발록)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Claw_Attack"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/Claw/Claw_Attack%d.png"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(클로어택)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Claw_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/Claw/Claw_Effect%d.png"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(클로이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_FireBall_Attack"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/FireBall/FireBall_Attack%d.png"), 3)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(파이어볼 어택)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_FireBall_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/FireBall/FireBall_Effect%d.png"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(파이어볼 이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Mabubjin"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/Mabubjin/Mabubjin_Attack.png"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(마법진)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Mabubjin_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/Mabubjin/Mabubjin_Effect%d.png"), 7)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(마법진 이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Meteor"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/Meteor/Meteor_Attack%d.png"), 8)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(메테오 어택)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Meteor_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase1/Meteor/Meteor_Effect%d.png"), 2)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(메테오 이펙트)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Body/Balrog%d.png"), 122)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(마왕발록)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Blast"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Blast/Blast%d.png"), 6)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(블래스터)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Wyvern"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Wyvern/Wyvern%d.png"), 18)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(와이번)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog_RH"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/RightHandA/RightHandA%d.png"), 57)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(발록오른손)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Ice"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Boss_Ice/Boss_Ice%d.png"), 15)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Boss_Ice)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Balrog_LH"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/LeftHandA/LeftHandA%d.png"), 43)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(발록왼손)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Electric_Shock"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Electric_Shock/Electric_Shock%d.png"), 9)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Electric_Shock)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Electric_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Electric_Shock/Lightning%d.png"), 3)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Electric_Shock)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_PurplePog"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/PurPlePog/PurPlePog%d.png"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(PurplePog)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_PurplePog_Effect"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/PurPlePog/PogHit%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(PurplePog)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Crash"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Crash/Crash%d.png"), 4)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(PurplePog)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Boss_Circle"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/Boss/Phase2/Circle/SkillCircle%d.png"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(PurplePog)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Ash"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../Resource/Object/Effect/Ash/Ash%d.dds"), 5)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(꽃잎)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGEBOSS, TEXT("Prototype_Component_Texture_Siren"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Siren/Siren%d.png"), 11)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(꽃잎)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 게임오브젝트

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss"), CBoss_Phase1::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(Boss)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Claw_Effect"), CBossHit_Effect::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(BossHit_Effect)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Claw_Attack"), CClaw_Attack::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(Claw_Attack)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_FireBall_Attack"), CFireBall_Attack::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(FireBall_Attack)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Mabubjin"), CMabubjin::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(Mabubjin)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Mabubjin_Attack"), CMabubjin_Attack::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(Mabubjin_Attack)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Meteor"), CMeteor::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelBoss(Meteor)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Balrog"), CBalrog::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(마왕발록)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Blast"), CBlast::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(블래스터)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Wyvern"), CWyvern::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(와이번)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Balrog_RH"), CBoss_Phase2_RH::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(발록오른손)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Boss_Ice"), CBoss_Ice::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Boss_Ice)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Balrog_LH"), CBoss_Phase2_LH::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(발록왼손)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Electric_Shock"), CElectric_Shock::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Electric_Shock)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_PurplePog"), CPurplePog::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(PurplePog)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Crash"), CCrash::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(PurplePog)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Circle"), CCircle::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Circle)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Ash"), CAsh::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Circle)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Siren"), CSiren::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(Circle)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BossMeteor"), CBossMeteor::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(운석파티클)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_FireParticle"), CFireParticle::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(운석파티클)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_BlastParticle"), CBlastParticle::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageBoss(운석파티클)");
		return E_FAIL;
	}
#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}

HRESULT CLoader::Loading_LevelStageSpecial() {
	m_bFinished = false;
	CGameInstance* pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(pGameInstance);

#pragma region 텍스쳐

	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESPECIAL, TEXT("Prototype_Component_Texture_Special"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/Monster/EmoSlime/EmoSlime%d.png"), 25)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageSpecial(몬스터)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Bullet"), CBullet::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : 불릿");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STAGESPECIAL, TEXT("Prototype_Component_Texture_UI_Bullet"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, TEXT("../Resource/Object/UI/Pistol_UI/Pistol_UI%d.png"), 21)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageSpecial(UI_Bullet)");
		return E_FAIL;
	}
#pragma endregion

#pragma region 오브젝트

	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_Special"), CSpecialMonster::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageSpecial(몬스터)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(LEVEL_STATIC, TEXT("Prototype_Component_Texture_Bullet"), CTexture::Create(m_pGraphic_Device, CTexture::TYPE_CUBE, TEXT("../../Resources/Tile/Bullet.dds"))))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelTurotial(불릿)");
		return E_FAIL;
	}
	if (FAILED(pGameInstance->Add_Prototype(TEXT("Prototype_GameObject_UI_Bullet"), CBullet_UI::Create(m_pGraphic_Device)))) {
		MSG_BOX(L"Failed To CLoader : Loading_LevelStageSpecial(UI_Bullet)");
		return E_FAIL;
	}
#pragma endregion

	m_bFinished = true;
	Safe_Release(pGameInstance);
	return S_OK;
}

CLoader* CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eLevel) {
	CLoader* pInstance = new CLoader(pGraphic_Device);
	if (FAILED(pInstance->NativeConstruct(eLevel))) {
		MSG_BOX(TEXT("Failed To CLoader : Create"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoader::Free() {
	WaitForSingleObject(m_hThread, INFINITE);
	DeleteCriticalSection(&m_CriticalSection);
	DeleteObject(m_hThread);
	CloseHandle(m_hThread);
	Safe_Release(m_pGraphic_Device);
}