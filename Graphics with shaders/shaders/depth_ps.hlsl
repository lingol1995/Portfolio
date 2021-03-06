struct InputType
{
    float4 position : SV_POSITION;
    float4 depthPosition : TEXCOORD0;
};

float4 main(InputType input) : SV_TARGET
{
	float depthValue;
	float4 color;

	// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
	depthValue = input.depthPosition.z / input.depthPosition.w;
	if (depthValue < 0.9f)
	{
		color = float4(1.0, 0.0f, 0.0f, 1.0f);
	}

	// The next 0.025% portion of the depth buffer color green.
	if (depthValue > 0.9f)
	{
		color = float4(0.0, 1.0f, 0.0f, 1.0f);
	}

	// The remainder of the depth buffer color blue.
	if (depthValue > 0.925f)
	{
		color = float4(0.0, 0.0f, 1.0f, 1.0f);
	}

	color = float4(depthValue, depthValue, depthValue, 1.f);

	return color;
}