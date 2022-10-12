#include "..\Public\Graphic_Device.h"

IMPLEMENT_SINGLETON(CGraphic_Device)

CGraphic_Device::CGraphic_Device()
	:m_p3D(nullptr), m_pDevice(nullptr)
{
}

HRESULT CGraphic_Device::InitDevice(HWND hWnd, unsigned int iWinCX, unsigned int iWinCY, LPDIRECT3DDEVICE9* ppGraphic_Device) {
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps))) {
		MSG_BOX(L"GetDeviceCaps Failed");
		return E_FAIL;
	}

	DWORD vp = 0;

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	}
	else {
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(hWnd, iWinCX, iWinCY, d3dpp);

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &m_pDevice))) {
		MSG_BOX(L"CreateDevice Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MSG_BOX(L"m_pSprite Failed");
		return E_FAIL;
	}

	*ppGraphic_Device = m_pDevice;

	Safe_AddRef(m_pDevice);
	return S_OK;
}

void CGraphic_Device::SetParameters(HWND hWnd, unsigned int iWinCX, unsigned int iWinCY, D3DPRESENT_PARAMETERS& d3dpp) {
	d3dpp.BackBufferWidth = iWinCX;
	d3dpp.BackBufferHeight = iWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void CGraphic_Device::Render_Begin() {
	m_pDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 124, 124, 124), 1.f, 0);
	m_pDevice->BeginScene();
}

void CGraphic_Device::Render_End() {
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, 0, nullptr);
}

void CGraphic_Device::Free() {
	Safe_Release(m_pDevice);
	Safe_Release(m_p3D);
}