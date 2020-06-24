// Light pixel shader
// Calculate ambient and diffuse lighting for a single light (also texturing)
//
Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer LightBuffer : register(cb0)
{
	//float4 ambientColour;
	float4 diffuseColour1;
	float4 diffuseColour2;
	float3 position1;
	float3 position2;
	float padding;
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 position3D : TEXCOORD2;
	
	float3 lightPosition1: TEXCOORD1;
	float3 lightPosition2: TEXCOORD2;
	

};


float4 main(InputType input) : SV_TARGET
{
	float4 ambientColour;
	float4 textureColour;
	float3 lightDir;
	float4 colour = float4(0.0f, 0.0f, 1.0f, 1.0f);
		float lightIntensity1, lightIntensity2;
	float4 colour1, colour2;

	lightIntensity1 = saturate(dot(input.normal, input.lightPosition1));
	lightIntensity2 = saturate(dot(input.normal, input.lightPosition2));

		// Determine the diffuse color amount of each of the four lights.
	colour1 = diffuseColour1 * lightIntensity1;
	colour2 = diffuseColour2 * lightIntensity2;

	// Sample the texture pixel at this location.
	textureColour = shaderTexture.Sample(SampleType, input.tex);

	// Multiply the texture pixel by the combination of all four light colors to get the final result.
	colour = colour * textureColour;



	/*ambientColour = (0.0f, 0.0f, 0.0f, 0.0f);
textureColour = (0.0f, 0.0f, 0.0f, 0.0f);
colour = (0.0f, 0.0f, 0.0f, 0.0f);

	// Sample the pixel color from the texture using the sampler at this texture 	coordinate location.
	textureColour = shaderTexture.Sample(SampleType, input.tex);

	// Set the default output color to the ambient light value for all pixels.
	colour = ambientColour;

	// Invert the light direction for calculations.
	lightDir = normalize(input.position3D - position);

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, -lightDir));

	
	// Sample the pixel colour from the texture.
	
	if (lightIntensity > 0.0f)
	{
		// Determine the final diffuse color based on the diffuse color and the amount 	of light intensity.
		colour += (diffuseColour * lightIntensity);

		// Saturate the ambient and diffuse color.
		colour = saturate(colour);
	}

	// Multiply the texture pixel and the final diffuse colour
	colour = colour * textureColour;

	*/
	return colour;

}


