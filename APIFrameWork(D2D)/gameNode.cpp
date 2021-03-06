#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init(void)
{
	_managerInit = false;
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(WINSIZEX_NUM, WINSIZEY_NUM)),
		&Rt);

	Rt->CreateCompatibleRenderTarget(D2D1::SizeF(WINSIZEX_NUM, WINSIZEY_NUM), D2D1::SizeU(WINSIZEX_NUM, WINSIZEY_NUM), &CRt);
	
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Magenta), &Brush);
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::WhiteSmoke, 0.5f), &WhiteSmokeBrush);
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 0.5f), &BlackBrush);
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &WhiteBrush);
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aqua), &AquablueBrush);
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &BlueBrush);
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 0.2f), &RedBrush);
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &SolidRedBrush);

	//조명초기화
	ID2D1GradientStopCollection *pGradientStops = NULL;
	static const D2D1_GRADIENT_STOP gradientStops[] = {
		{ 1.0f,  D2D1::ColorF(D2D1::ColorF::Black, 0.5f) },
		{ 0.5f,  D2D1::ColorF(D2D1::ColorF::Black, 0.1f) }
	};
	
	Rt->CreateGradientStopCollection(
		gradientStops,
		2,
		&pGradientStops);
	Rt->CreateRadialGradientBrush(
		D2D1::RadialGradientBrushProperties(
			D2D1::Point2F(WINSIZEX_NUM, WINSIZEY_NUM),
			D2D1::Point2F(0, 0),
			0,
			0),
		pGradientStops,
		&m_pRadialGradientBrush);
	pGradientStops->Release();
	setRadialGradientBrush(Rt, { WINSIZEX_NUM / 2 , WINSIZEY_NUM / 2 }, 1000, 1000, 1); //조명초기화

	Rt->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

	DWInit(L"나눔고딕", 12.0f, &WriteFactory, &TextFormat);

	_managerInit = managerInit;
	if (managerInit)
	{
		SOUNDMANAGER->init();
		KEYMANAGER->init();					//키매니져 셋팅
		IMAGEMANAGER->init();				//이미지매니져 셋팅
		TIMEMANAGER->init();
		SCENEMANAGER->init();				//씬매니져 셋팅
		CAMERAMANAGER->init();
		EFFECTMANAGER->init();
	}
	return S_OK;
}

void gameNode::release(void)
{
	if (_managerInit)
	{
		KEYMANAGER->releaseSingleton();
		//이미지매니져 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//타임매니져 해제, 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		//씬매니져 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//사운드 매니져 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//카메라 매니져 해제
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
		//이펙트 매니져 해제
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
	}
}

void gameNode::update(void)
{
}

void gameNode::render(void)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//PAINTSTRUCT ps;
	//HDC hdc;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//		case VK_ESCAPE:
	//			PostMessage(hWnd, WM_DESTROY, 0, 0);
	//		break;
	//	}
	//	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}