#pragma once
#include "Base.h"
#include "Tool_Define.h"

BEGIN(Tool)

class CDevice : public CBase
{
	DECLARE_SINGLETON(CDevice)

private:
	CDevice();
	virtual ~CDevice() = default;

public:
	LPDIRECT3DDEVICE9		Get_Device() { return m_pDevice; }

public:
	HRESULT		InitDevice();

	void		Render_Begin();
	void		Render_End(HWND hWnd = nullptr);

private:
	void		SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	LPDIRECT3D9				m_p3D;			// com ��ü : �� �༮�� ��ġ�� sdk ������ �˻��ϰ� �� ���� �ȿ� �ִ� ��ü ������ ����ϴ� ��ü�� �ش�
	LPDIRECT3DDEVICE9		m_pDevice;		// �׸���� ���õ� ���� ����� ž���� ��ü

public:
	virtual void Free();
};

END