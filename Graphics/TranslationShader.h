// texture shader.h
#ifndef _TRANSLATIONSHADER_H_
#define _TRANSLATIONSHADER_H_

#include "BaseShader.h"

using namespace std;
using namespace DirectX;


class TranslationShader : public BaseShader
{

public:
	struct TranslateBufferType
	{
		float translation;
		XMFLOAT3 padding;
	};

	TranslationShader(ID3D11Device* device, HWND hwnd);
	~TranslationShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, float add);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount, float add);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_translateBuffer;
};

#endif