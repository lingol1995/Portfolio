
// Light vertex shader
// Standard issue vertex shader, apply matrices, pass info to pixel shader

cbuffer MatrixBuffer : register(cb0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightPosBuffer : register(cb1)
{
	float4 lightPosition1;
	float4 lightPosition2;
};

struct OutputType
{
	float4 position : POSITION;
	float3 position3D : POSITION3D;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;

	float3 lightPosition1: TEXCOORD1;
	float3 lightPosition2: TEXCOORD2;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 position3D : TEXCOORD2;
};


OutputType main(InputType input)
{
	OutputType output;
	float4 worldPosition;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection  	matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// world position of vertex
	output.position3D = mul(input.position, worldMatrix);
	
	worldPosition.xyz = output.position3D;
	//worldPosition.w = 1.f;

	output.lightPosition1.xyz = lightPosition1.xyz - worldPosition.xyz;
	output.lightPosition2.xyz = lightPosition2.xyz - worldPosition.xyz;

	output.lightPosition1 = normalize(output.lightPosition1);
	output.lightPosition2 = normalize(output.lightPosition2);

	return output;
}
