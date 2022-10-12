#pragma once
#include "Client_Define.h"
#include "GameInstance.h"
#include "Level.h"
#include "Loader.h"
//·¹º§
#include "Level_Tutorial.h"
#include "Level_StageOne.h"
#include "Level_StageTwo.h"
#include "Level_StageTwo_1.h"
#include "Level_StageThree.h"
#include "Level_StageFour.h"
#include "Level_StageSemiBoss.h"
#include "Level_StageSemiAfter.h"
#include "Level_StageFive.h"
#include "Level_StageSix.h"
#include "Level_StageSeven.h"
#include "Level_StageEight.h"
#include "Level_StageBoss.h"
#include "Level_StageSpecial.h"


BEGIN(Client)

class CLevel_Loading final : public CLevel {
private:
	explicit CLevel_Loading(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CLevel_Loading() = default;
public:
	virtual HRESULT NativeConstruct(LEVEL eNextLevel);
	virtual void Tick(_float fTimeDelta) override;
	virtual HRESULT Render() override;
public:
	HRESULT Ready_Loading();
private:
	LEVEL m_eNextLevel = LEVEL_END;
	CLoader* m_pLoader = nullptr;
public:
	static CLevel_Loading* Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel);
	virtual void Free() override;
};

END