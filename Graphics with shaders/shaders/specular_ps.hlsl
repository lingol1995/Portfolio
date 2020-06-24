Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer LightBuffer : register(cb0)
{
	float4 ambientColour;
	float4 diffuseColour;
	float3 direction;
	float specularPower;
	float4 specularColour;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};


float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float3 lightDir;
	float lightIntensity;
	float4 colour;
	float3 reflection;
	float4 specular;
	float4 finalSpec;

	// Sample the pixel colour from the texture.
	textureColour = shaderTexture.Sample(SampleType, input.tex);
	colour = float4(0.0f, 0.0f, 0.0f, 1.0f);
	// Set the default output colour to the ambient light value for all pixels.
	colour = ambientColour;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, -direction));

	if (lightIntensity > 0.0f)
	{
		colour += (diffuseColour * lightIntensity);
		colour = saturate(colour);

		// Calculate reflection vector based on the light intensity, normal vector and light direction
		reflection = reflect(direction, input.normal);

		// Determine the amount of specular light based on the reflection vector, viewing direction, and   
		specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);

		//sum up specular light
		finalSpec = specularColour * specular;
	}

	colour = colour * textureColour;

	// Add the specular component last to the output colour.
	colour = saturate(colour + finalSpec);

	return colour;


}
