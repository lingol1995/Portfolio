// Light shader.h
// Basic single light shader setup
#ifndef _SpecularShader_H_
#define _SpecularShader_H_

#include "BaseShader.h"
#include "light.h"

using namespace std;
using namespace DirectX;


class SpecularShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT3 direction;
		XMFLOAT4 specular;
		float specPower;

		//float padding;
	};

public:

	SpecularShader(ID3D11Device* device, HWND hwnd);
	~SpecularShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, Light* light);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightBuffer;
};

#endif