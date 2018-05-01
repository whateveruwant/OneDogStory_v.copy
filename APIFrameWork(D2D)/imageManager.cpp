#include "stdafx.h"
#include "imageManager.h"

imageManager::imageManager() {}
imageManager::~imageManager() {}

//�̹����Ŵ��� �ʱ�ȭ
HRESULT imageManager::init(void)
{
	return S_OK;
}

//�̹����Ŵ��� ����
void imageManager::release(void)
{
	deleteAll();
}

//Ű������ �̹��� ���Ϸ� �ʱ�ȭ
image * imageManager::addImage(ID2D1RenderTarget * RenderTarget, tstring strKey, const TCHAR * fileName, float x, float y, int width, int height, bool isCenter)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ���Ͻ�Ų��
	if (img) return img;

	// �̹��� ���� ����
	img = new image;
	// �̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(RenderTarget, fileName, x, y, width, height, isCenter))) {
		SAFE_DELETE(img);
		return NULL;
	}

	// ������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	m_imageList.insert(make_pair(strKey, img));

	return img;
}

//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
image * imageManager::addFrameImage(ID2D1RenderTarget * RenderTarget, tstring strKey, const TCHAR * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isCenter)
{
	//�߰� �Ϸ��� Ű ������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰� �Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ���Ͻ�Ų��
	if (img) return img;

	// �̹��� ���� ����
	img = new image;
	// �̹����� ����� �ʱ�ȭ�� ���� �ʾҴٸ� NULL ����
	if (FAILED(img->init(RenderTarget, fileName, x, y, width, height, frameX, frameY, isCenter))) {
		SAFE_DELETE(img);
		return NULL;
	}

	// ������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	m_imageList.insert(make_pair(strKey, img));

	return img;
}

//�̹��� Ű������ ã��
image * imageManager::findImage(tstring strKey)
{
	// �ش�Ű �˻�
	mapImageIter key = m_imageList.find(strKey);

	// �˻��� Ű�� ã�Ҵٸ�
	if (key != m_imageList.end()) {
		return key->second;
	}
	// �˻��� Ű�� �̹����� �� ã�Ҵٸ�
	return NULL;
}

bool imageManager::searchImage(tstring strKey)
{
	// �ش�Ű �˻�
	mapImageIter key = m_imageList.find(strKey);

	// �˻��� Ű�� ã�Ҵٸ�
	if (key != m_imageList.end()) {
		return true;
	}
	// �˻��� Ű�� �̹����� �� ã�Ҵٸ�
	return false;
}

//�̹��� Ű������ ����
bool imageManager::deleteImage(tstring strKey)
{
	// �ش�Ű �˻�
	mapImageIter key = m_imageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != m_imageList.end()) {
		// �̹��� ����
		SAFE_RELEASE(key->second);
		// �޸� ����
		SAFE_DELETE(key->second);
		// �ʿ��� �ݺ��� ����
		m_imageList.erase(key);

		return true;
	}

	return false;
}

bool imageManager::deleteAll(void)
{
	// �� ��ü�� ���鼭 �����
	mapImageIter iter = m_imageList.begin();
	for (; iter != m_imageList.end();) {
		if (iter->second != NULL) {
			SAFE_RELEASE(iter->second);
			SAFE_DELETE(iter->second);
			iter = m_imageList.erase(iter);
		}
		else {
			++iter;
		}
	}

	// �� ��ü ����
	m_imageList.clear();

	return true;
}

void imageManager::render(tstring strKey, ID2D1RenderTarget * RenderTarget)
{
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget);
}

void imageManager::render(tstring strKey, ID2D1RenderTarget * RenderTarget, float x, float y)
{
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget, x, y);
}

void imageManager::render(tstring strKey, ID2D1RenderTarget * RenderTarget, float x, float y, float sourceWidth, float sourceHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget, x, y, sourceWidth, sourceHeight);
}

void imageManager::render(tstring strKey, ID2D1RenderTarget * RenderTarget, float x, float y, float sourceX, float sourceY, float sourceWidth, float sourceHeight)
{
	image* img = findImage(strKey);
	if (img) img->render(RenderTarget, x, y, sourceX, sourceY, sourceWidth, sourceHeight);
}

void imageManager::bottomFillOpacityRender(tstring strKey, ID2D1RenderTarget * RenderTarget, float x, float y, ID2D1Brush * Brush)
{
	image* img = findImage(strKey);
	if (img) img->bottomFillOpacityRender(RenderTarget, x, y, Brush);
}

void imageManager::alphaRender(tstring strKey, ID2D1RenderTarget * RenderTarget, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(RenderTarget, alpha);
}

void imageManager::alphaRender(tstring strKey, ID2D1RenderTarget * RenderTarget, float x, float y, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->alphaRender(RenderTarget, x, y, alpha);
}

void imageManager::frameRender(tstring strKey, ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(RenderTarget, currentFrameX, currentFrameY);
}

void imageManager::frameRender(tstring strKey, ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float x, float y)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(RenderTarget, currentFrameX, currentFrameY, x, y);
}

void imageManager::frameAlphaRender(tstring strKey, ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(RenderTarget, currentFrameX, currentFrameY, alpha);
}

void imageManager::bottomRender(tstring strKey, ID2D1RenderTarget * RenderTarget)
{
	image* img = findImage(strKey);
	if (img) img->bottomRender(RenderTarget);
}

void imageManager::bottomRender(tstring strKey, ID2D1RenderTarget * RenderTarget, float x, float y)
{
	image* img = findImage(strKey);
	if (img) img->bottomRender(RenderTarget, x, y);
}

void imageManager::bottomAlphaRender(tstring strKey, ID2D1RenderTarget * RenderTarget, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->bottomAlphaRender(RenderTarget, alpha);
}

void imageManager::bottomFrameRender(tstring strKey, ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY)
{
	image* img = findImage(strKey);
	if (img) img->bottomFrameRender(RenderTarget, currentFrameX, currentFrameY);
}

void imageManager::bottomFrameRender(tstring strKey, ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float x, float y)
{
	image* img = findImage(strKey);
	if (img) img->bottomFrameRender(RenderTarget, currentFrameX, currentFrameY, x, y);
}

void imageManager::bottomFrameFillOpacityRender(tstring strKey, ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float x, float y, ID2D1Brush * Brush)
{
	image* img = findImage(strKey);
	if (img) img->bottomFrameFillOpacityRender(RenderTarget, currentFrameX, currentFrameY, x, y, Brush);
}

void imageManager::bottomFrameAlphaRender(tstring strKey, ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float alpha)
{
	image* img = findImage(strKey);
	if (img) img->bottomFrameAlphaRender(RenderTarget, currentFrameX, currentFrameY, alpha);
}