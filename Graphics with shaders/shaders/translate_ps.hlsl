
Texture2D texture0 : register(t0);
SamplerState Sampler0 : register(s0);

cbuffer TranslationBuffer
{
	float textureTranslation;
};


struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 main(InputType input) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float4 textureColour;
	
	input.tex.x += textureTranslation;

	return texture0.Sample(Sampler0, input.tex);
}