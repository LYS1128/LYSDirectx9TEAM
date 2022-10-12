#include "..\public\Timer_Manager.h"

IMPLEMENT_SINGLETON(CTimer_Manager)

CTimer_Manager::CTimer_Manager()
{
}

HRESULT CTimer_Manager::Add_Timers(const _tchar* pTimerTag) {
	if (nullptr != Find_Timers(pTimerTag)) {
		return E_FAIL;
	}
	CTimer* pTimer = CTimer::Create();
	if (nullptr == pTimer) {
		return E_FAIL;
	}
	m_Timers.insert(TIMERS::value_type(pTimerTag, pTimer));

	return S_OK;
}

_double CTimer_Manager::Compute_TimeDelta(const _tchar* pTimerTag) {
	CTimer*	pTimer = Find_Timers(pTimerTag);	
	if (nullptr == pTimer) {
		return E_FAIL;
	}
	return pTimer->Compute_TimeDelta();	
}

CTimer* CTimer_Manager::Find_Timers(const _tchar* pTimerTag) {
	auto Pair = find_if(m_Timers.begin(), m_Timers.end(), CTagFinder(pTimerTag));

	if (Pair == m_Timers.end()) {
		return nullptr;
	}
	return Pair->second;
}

void CTimer_Manager::Free() {
	for (auto& Pair : m_Timers) {
		Safe_Release(Pair.second);
	}
	m_Timers.clear();
}