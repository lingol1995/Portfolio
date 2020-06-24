// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "lab1.h"

Lab1::Lab1(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in) : BaseApplication(hinstance, hwnd, screenWidth, screenHeight, in)
{
	m_Input = in;
	
	///////////////////////////////////////////////////////////////SCENE OBJECTS//////////////////////////////////////////////////////////
	m_Plane = new PlaneMesh(m_Direct3D->GetDevice(), L"../res/wood.jpg");		//plane
	m_Teapot = new Model(m_Direct3D->GetDevice(), L"../res/metal.jpg", L"../res/teapot.obj", XMFLOAT3(10, 1.6, -20), XMFLOAT3(0.20, 0.20, 0.20));	//teapot model
	m_Book = new Model(m_Direct3D->GetDevice(), L"../res/book.jpg", L"../res/book.obj", XMFLOAT3(20, 0.0, -30), XMFLOAT3(0.025, 0.025, 0.025));	//book model
	m_Cup = new Model(m_Direct3D->GetDevice(), L"../res/red.jpg", L"../res/mug.obj", XMFLOAT3(30, 1.6, -20), XMFLOAT3(0.025, 0.025, 0.025));	//book model
	m_Moon = new SphereMesh(m_Direct3D->GetDevice(), L"../res/moon.jpg", XMFLOAT3(50, 10.0, 70), XMFLOAT3(3.0, 3.0,3.0));					//moon
	m_Spillage = new SphereMesh(m_Direct3D->GetDevice(), L"../res/jelly.jpg", XMFLOAT3(29.7, 0.3, 15.2), XMFLOAT3(1.7, 0.7,4.8));																//cube (textures translate)
	m_LavaLamp = new SphereMesh(m_Direct3D->GetDevice(), L"../res/jelly.jpg", XMFLOAT3(5, 2, 5), XMFLOAT3(0.7, 0.7, 0.7));					//lavalamp (vertex manipulation)
	m_Lava = new SphereMesh(m_Direct3D->GetDevice(), L"../res/jelly.jpg", XMFLOAT3(5, 4, 5), XMFLOAT3(1.0, 1.0, 1.0));
	m_Sweet = new SphereMesh(m_Direct3D->GetDevice(), L"../res/red.jpg", XMFLOAT3(10, 0.3, 15.0), XMFLOAT3(0.4, 0.4, 0.4));				//sweets
	m_Sweet2 = new SphereMesh(m_Direct3D->GetDevice(), L"../res/Blue.jpg", XMFLOAT3(18, 0.3, 25.0), XMFLOAT3(0.4, 0.4, 0.4));
	m_Sweet3 = new SphereMesh(m_Direct3D->GetDevice(), L"../res/red.jpg", XMFLOAT3(20, 0.3, 15.0), XMFLOAT3(0.4, 0.4, 0.4));
	m_backWall = new PointMesh(m_Direct3D->GetDevice(),L"../res/metal.jpg");			//started off as triangles, changed to quads and edited in geometry shader
	m_Wall = new Walls(m_Direct3D->GetDevice(), L"../res/bunny.png");			//left and right wall
	m_TessMesh = new TessellationMesh(m_Direct3D->GetDevice(), L"../res/metal.jpg");	//Tesselation Mesh (triangle)
	
	///////////////////////////////////////////////////////LIGHTS///////////////////////////////////////////////////////
	m_Light = new Light;
	m_Light->SetDiffuseColour(1.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetAmbientColour(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light->SetLookAt(5.0f, 0.0f, 0.0f);
	m_Light->SetPosition(1.0f, 5.0f, -5.0f);
	
	m_Light2 = new Light;
	m_Light2->SetDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light2->SetAmbientColour(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light2->SetLookAt(5.0f, 0.0f, 0.0f);
	m_Light2->SetPosition(0.0f, 4.2, -4.0f);
	
	m_Light3 = new Light;
	m_Light3->SetDiffuseColour(0.6f, 0.6f, 0.0f, 1.0f);
	m_Light3->SetAmbientColour(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light3->SetLookAt(5.0f, 0.0f, 0.0f);
	m_Light3->SetPosition(1.0f, 5.0, -5.0f);

	m_Light4 = new Light;			//Specular light
	m_Light4->SetDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light4->SetAmbientColour(0.2f, 0.2f, 0.2f, 1.0f);
	m_Light4->SetLookAt(5.0f, 0.0f, 0.0f);
	m_Light4->SetPosition(50.0f, 10.0, 50.0f);
	m_Light4->SetDirection(0.0f, -1.0f, 0.0f);
	m_Light4->SetSpecularColour(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light4->SetSpecularPower(0.3f);

	/////////////////////////////////////////////////////RENDERTEXTURE////////////////////////////////////////////////////////////////////////

	m_RenderTexture = new RenderTexture(m_Direct3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);		//Render to Texture shader (depth used)
	m_blurWhole = new RenderTexture(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);
	m_DownSample = new RenderTexture(m_Direct3D->GetDevice(), screenWidth / 2, screenHeight / 2, SCREEN_NEAR, SCREEN_DEPTH);
	m_horBlur = new RenderTexture(m_Direct3D->GetDevice(), screenWidth/2, screenHeight/2, SCREEN_NEAR, SCREEN_DEPTH);
	m_verBlur = new RenderTexture(m_Direct3D->GetDevice(), screenWidth/2, screenHeight/2, SCREEN_NEAR, SCREEN_DEPTH);
	m_UpSample = new RenderTexture(m_Direct3D->GetDevice(), screenWidth/2, screenHeight/2, SCREEN_NEAR, SCREEN_DEPTH);
	m_screen = new RenderTexture(m_Direct3D->GetDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);				//Small screen in top corner (RenderTexture shader)
	m_final = new RenderTexture(m_Direct3D->GetDevice(), screenWidth, screenHeight , SCREEN_NEAR, SCREEN_DEPTH);

	screenW = screenWidth/2;
	screenH = screenHeight / 2;

	///////////////////////////////////////////////////////////SHADERS////////////////////////////////////////////////////////////////////////////////
	
	m_Depth = new DepthShader(m_Direct3D->GetDevice(), hwnd);					//Depth Shader
	m_TextureShader = new TextureShader(m_Direct3D->GetDevice(), hwnd);			//Texture Shader
	m_specShader = new SpecularShader(m_Direct3D->GetDevice(), hwnd);			//Specular Shader
	m_Shadow = new ShadowShader(m_Direct3D->GetDevice(), hwnd);					//Shadow Shader
	m_Manipulation = new ManipulationShader(m_Direct3D->GetDevice(), hwnd);		//Manipulation shader
	m_geometry = new GeometryShader(m_Direct3D->GetDevice(), hwnd);				//Geometry Shader
	m_translation = new TranslationShader(m_Direct3D->GetDevice(), hwnd);		//Texture Translation shader
	m_TessShader = new TessellationShader(m_Direct3D->GetDevice(), hwnd);		//Tesselation Shader
	m_Horizontal = new HorizontalBlurShader(m_Direct3D->GetDevice(), hwnd);			//Horizontal Blur Shader
	m_Vertical = new VerticalBlurShader(m_Direct3D->GetDevice(), hwnd);				//Vertical Blur Shader
	m_geometry = new GeometryShader(m_Direct3D->GetDevice(), hwnd);			//wall (Geometry Shader)
	m_wallShader = new WallGeometryShader(m_Direct3D->GetDevice(), hwnd);			//wall (Geometry Shader - new geometry shader named wall)

	/////////////////////////////////////////////////////////////ORTHO MESHES////////////////////////////////////////////////////////////////
	m_OrthoMesh = new OrthoMesh(m_Direct3D->GetDevice(), 200, 150, -700, 225);		//Orthomesh (small screen etc)
	m_fullOrtho = new OrthoMesh(m_Direct3D->GetDevice(), screenWidth*3, screenHeight*3);		//used in blurring
	m_smallOrtho = new OrthoMesh(m_Direct3D->GetDevice(), screenWidth/2, screenHeight/2);		//small screen used in blurring 
	m_finalOrtho = new OrthoMesh(m_Direct3D->GetDevice(), 300, 200, 230, 200);		//Orthomesh (small screen etc)

	///////////////////////////////////////////////////////////////VARIABLES/////////////////////////////////////////////////////

	m_Time = new Timer();						//Timer
	time = 0;									//Time initialised 
	height = 2.0f;								//height of vertex manipulation initialised 
	tess = 1;									//Tesselation Amount
	textureTranslation = 0.0f;					//Translation initialised
}


Lab1::~Lab1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D objects.
	if (m_Moon)
	{
		delete m_Moon;
		m_Moon = 0;
	}

	if (m_Plane)
	{
		delete m_Plane;
		m_Plane = 0;
	}

	if (m_Cup)
	{
		delete m_Cup;
		m_Cup = 0;
	}

	if (m_Spillage)
	{
		delete m_Spillage;
		m_Spillage = 0;
	}

	if (m_Sweet)
	{
		delete m_Sweet;
		m_Sweet = 0;
	}

	if (m_OrthoMesh)
	{
		delete m_OrthoMesh;
		m_OrthoMesh = 0;
	}

	if (m_ColourShader)
	{
		delete m_ColourShader;
		m_ColourShader = 0;
	}

	if (m_RenderTexture)
	{
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	if (m_TextureShader)
	{
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	if (m_Light4)
	{
		delete m_Light4;
		m_Light4 = 0;
	}

	if (m_Shadow)
	{
		delete m_Shadow;
		m_Shadow = 0;
	}

	if (m_Depth)
	{
		delete m_Depth;
		m_Depth = 0;
	}

	if (m_geometry)
	{
		delete m_geometry;
		m_geometry = 0;
	}

	if (m_translation)
	{
		delete m_translation;
		m_translation = 0;
	}

	if (m_TessMesh)
	{
		delete m_TessMesh;
		m_TessMesh = 0;
	}

	if (m_TessShader)
	{
		delete m_TessShader;
		m_TessShader = 0;
	}

	if (m_final)
	{
		delete m_final;
		m_final = 0;
	}

	if (m_horBlur)
	{
		delete m_horBlur;
		m_horBlur = 0;
	}

	if (m_verBlur)
	{
		delete m_verBlur;
		m_verBlur = 0;
	}

	if (m_blurWhole)
	{
		delete m_blurWhole;
		m_blurWhole = 0;
	}



}

void Lab1::RenderToTexture()		//Depth
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, lightViewMatrix2, lightProjectionMatrix2, lightViewMatrix3, lightProjectionMatrix3;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.6f, 0.6f, 0.4f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	/////////////////////////////////////////////LIGHT MATRICES///////////////////////////////////////////////////////////////////
	m_Light->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH);		//projection matrix for first light
	m_Light->GenerateViewMatrix();										
	lightViewMatrix = m_Light->GetViewMatrix();							//Get light's view
	lightProjectionMatrix = m_Light->GetProjectionMatrix();
	
	m_Light2->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH);		//projection for second light
	m_Light2->GenerateViewMatrix();
	lightViewMatrix2 = m_Light2->GetViewMatrix();
	lightProjectionMatrix2 = m_Light2->GetProjectionMatrix();

	m_Light3->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH);		//projection matrix for third light
	m_Light3->GenerateViewMatrix();
	lightViewMatrix3 = m_Light3->GetViewMatrix();
	lightProjectionMatrix3 = m_Light3->GetProjectionMatrix();

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_Direct3D->GetWorldMatrix(worldMatrix);

	m_Moon->SendData(m_Direct3D->GetDeviceContext());		//Render moon in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix2, lightProjectionMatrix2);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Moon->GetIndexCount());

	m_Sweet->SendData(m_Direct3D->GetDeviceContext());		//Render sweet in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix3, lightProjectionMatrix3);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Sweet->GetIndexCount());
	
	m_Sweet2->SendData(m_Direct3D->GetDeviceContext());		//Render sweet in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix3, lightProjectionMatrix3);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Sweet2->GetIndexCount());

	m_Sweet3->SendData(m_Direct3D->GetDeviceContext());		//Render sweet in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix3, lightProjectionMatrix3);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Sweet3->GetIndexCount());

	m_Plane->SendData(m_Direct3D->GetDeviceContext());		//Render Plane in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix3, lightProjectionMatrix3);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Plane->GetIndexCount());


	m_Teapot->SendData(m_Direct3D->GetDeviceContext());		//Render Teapot in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Teapot->GetIndexCount());

	m_Book->SendData(m_Direct3D->GetDeviceContext());		//Render book in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix3, lightProjectionMatrix3);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Book->GetIndexCount());

	m_Cup->SendData(m_Direct3D->GetDeviceContext());		//Render cup in depth shader
	m_Depth->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	m_Depth->Render(m_Direct3D->GetDeviceContext(), m_Book->GetIndexCount());

	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();

}

//////////////////////////////////Small Screen//////////////////
bool Lab1::RenderScene()				//Normal textured objects on small screen
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Set the render target to be the render to texture.
	m_screen->SetRenderTarget(m_Direct3D->GetDeviceContext());			//small screen in corner

	// Clear the render to texture.
	m_screen->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//All shown on small screen (m_screen)
	m_Moon->SendData(m_Direct3D->GetDeviceContext());			
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Moon->GetTexture());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Moon->GetIndexCount());					//Render textured moon

	m_Plane->SendData(m_Direct3D->GetDeviceContext());
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Plane->GetTexture());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Plane->GetIndexCount());					//Render textured plane

	m_Teapot->SendData(m_Direct3D->GetDeviceContext());
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Teapot->GetTexture());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Teapot->GetIndexCount());					//Render textured teapot

	m_Cup->SendData(m_Direct3D->GetDeviceContext());									//specular lit mug
	m_specShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Cup->GetTexture(),m_Light4);
	m_specShader->Render(m_Direct3D->GetDeviceContext(), m_Cup->GetIndexCount());

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();


	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

/////////////////////////////////BLURRING FUNCTIONS////////////////////////////////////////////////////////////
void Lab1::BlurWholeScene()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Set the render target to be the render to texture.
	m_blurWhole->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_blurWhole->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 1.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	m_Direct3D->TurnZBufferOff();

	m_Moon->SendData(m_Direct3D->GetDeviceContext());		//Render moon in texture shader
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Moon->GetTexture());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Moon->GetIndexCount());

	m_Plane->SendData(m_Direct3D->GetDeviceContext());		//Render Plane in texture shader
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Plane->GetTexture());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Plane->GetIndexCount());

	m_LavaLamp->SendData(m_Direct3D->GetDeviceContext());	//Render lava lamp orbs in manipulation shader
	m_Manipulation->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_LavaLamp->GetTexture(), m_Light2, time, height);
	m_Manipulation->Render(m_Direct3D->GetDeviceContext(), m_LavaLamp->GetIndexCount());

	m_Lava->SendData(m_Direct3D->GetDeviceContext());
	m_Manipulation->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Lava->GetTexture(), m_Light2, time, height);
	m_Manipulation->Render(m_Direct3D->GetDeviceContext(), m_Lava->GetIndexCount());

	m_Teapot->SendData(m_Direct3D->GetDeviceContext());		//render teapot in texture shader
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Teapot->GetTexture());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Teapot->GetIndexCount());

	m_Direct3D->TurnZBufferOn();
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();

}

void Lab1::DownSample()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

	// Set the render target to be the render to texture (Down Sample).
	m_DownSample->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_DownSample->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);
	
	orthoMatrix = m_DownSample->GetOrthoMatrix();
	m_Direct3D->TurnZBufferOff();

	m_smallOrtho->SendData(m_Direct3D->GetDeviceContext());
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix,  m_blurWhole->GetShaderResourceView());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_smallOrtho->GetIndexCount());

	m_Direct3D->TurnZBufferOn();
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();
}

void Lab1::Horizontal()		//HORIZONTAL BLUR
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

	// Set the render target to be the render to texture (horizontal blur).
	m_horBlur->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_horBlur->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.6f, 0.6f, 0.4f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	orthoMatrix = m_horBlur->GetOrthoMatrix();
	m_Direct3D->TurnZBufferOff();

	m_smallOrtho->SendData(m_Direct3D->GetDeviceContext());
	m_Horizontal->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, m_DownSample->GetShaderResourceView(), screenW);
	m_Horizontal->Render(m_Direct3D->GetDeviceContext(), m_smallOrtho->GetIndexCount());

	m_Direct3D->TurnZBufferOn();
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();
}

void Lab1::Vertical() //VERTICAL BLUR
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

	// Set the render target to be the render to texture (vertical blur).
	m_verBlur->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_verBlur->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	orthoMatrix = m_verBlur->GetOrthoMatrix();
	m_Direct3D->TurnZBufferOff();

	m_smallOrtho->SendData(m_Direct3D->GetDeviceContext());
	m_Vertical->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, m_horBlur->GetShaderResourceView(), screenH);		//get horizontal resource view
	m_Vertical->Render(m_Direct3D->GetDeviceContext(), m_smallOrtho->GetIndexCount());

	m_Direct3D->TurnZBufferOn();
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();

}

void Lab1::UpSample()	//UP SAMPLE
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

	// Set the render target to be the render to texture.
	m_UpSample->SetRenderTarget(m_Direct3D->GetDeviceContext());
	
	// Clear the render to texture.
	m_UpSample->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	orthoMatrix = m_UpSample->GetOrthoMatrix();		//Get up sample matrix
	m_Direct3D->TurnZBufferOff();

	m_fullOrtho->SendData(m_Direct3D->GetDeviceContext());
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, m_verBlur->GetShaderResourceView());		//get vertical blur resource view
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_fullOrtho->GetIndexCount());

	m_Direct3D->TurnZBufferOn();
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();
}

void Lab1::FinalBlur()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;

	// Set the render target to be the render to texture.
	m_final->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_final->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 1.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	orthoMatrix = m_final->GetOrthoMatrix();
	m_Direct3D->TurnZBufferOff();

	m_fullOrtho->SendData(m_Direct3D->GetDeviceContext());
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, m_UpSample->GetShaderResourceView());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_fullOrtho->GetIndexCount());

	m_Direct3D->TurnZBufferOn();
	m_Direct3D->SetBackBufferRenderTarget();
	m_Direct3D->ResetViewport();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Lab1::Frame()
{
	bool result;

	result = BaseApplication::Frame();
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	
	RenderToTexture();			//Depth etc.
	BlurWholeScene();			//Blurring functions
	DownSample();				//^^
	Horizontal();				//^^
	Vertical();					//^^
	UpSample();					//^^
	FinalBlur();				//^^
	RenderScene();				//Small screen rendering 

	result = Render();			//Scene
	
	if (m_Input->isKeyDown('G'))		//if G is pressed
	{
		m_Direct3D->TurnOnWireframe();		//Turn wireframe on
	}

	if (m_Input->isKeyDown('F'))		//if F is pressed
	{
		m_Direct3D->TurnOffWireframe();		//Turn off Wireframe
	}

	if (!result)
	{
		return false;
	}

	return true;
}

bool Lab1::Render()	//MAIN SCENE
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	
	textureTranslation -= 0.05f;		//translate texture by 0.05
	if (textureTranslation < 0.0f)		//if translation is less than 0 
	{
		textureTranslation += 1.0f;		//start again
	}

	// Clear the scene. (default blue colour)
	m_Direct3D->BeginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();
	
	m_Time->Frame();
	time += m_Time->GetTime();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	
	m_backWall->SendData(m_Direct3D->GetDeviceContext());		//Render back wall and front wall in geometry shader
	m_geometry->SetShaderParameters(m_Direct3D->GetDeviceContext(),worldMatrix, viewMatrix, projectionMatrix, m_backWall->GetTexture());
	m_geometry->Render(m_Direct3D->GetDeviceContext(), m_backWall->GetIndexCount());

	m_Wall->SendData(m_Direct3D->GetDeviceContext());			//Render right and left walls in geometry shader
	m_wallShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Wall->GetTexture());
	m_wallShader->Render(m_Direct3D->GetDeviceContext(), m_Wall->GetIndexCount());
	
	m_Moon->SendData(m_Direct3D->GetDeviceContext());			//Render moon with shadow shader
	m_Shadow->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Moon->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light2);
	m_Shadow->Render(m_Direct3D->GetDeviceContext(), m_Moon->GetIndexCount());
	
	m_Spillage->SendData(m_Direct3D->GetDeviceContext());		//Render spillage with translation shader
	m_translation->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Spillage->GetTexture(), textureTranslation);
	m_translation->Render(m_Direct3D->GetDeviceContext(), m_Spillage->GetIndexCount(),textureTranslation);
	
	m_LavaLamp->SendData(m_Direct3D->GetDeviceContext());		//Render lava lamp orbs with manipulation shader
	m_Manipulation->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_LavaLamp->GetTexture(), m_Light2, time, height);
	m_Manipulation->Render(m_Direct3D->GetDeviceContext(), m_LavaLamp->GetIndexCount());
	
	m_Lava->SendData(m_Direct3D->GetDeviceContext());	
	m_Manipulation->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Lava->GetTexture(), m_Light2, time, height);
	m_Manipulation->Render(m_Direct3D->GetDeviceContext(), m_Lava->GetIndexCount());

	m_Teapot->SendData(m_Direct3D->GetDeviceContext());			//Render teapot with shadow shader
	m_Shadow->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Teapot->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light);
	m_Shadow->Render(m_Direct3D->GetDeviceContext(), m_Teapot->GetIndexCount());

	m_Book->SendData(m_Direct3D->GetDeviceContext());			//Render book with shadow shader
	m_Shadow->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Book->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light3);
	m_Shadow->Render(m_Direct3D->GetDeviceContext(), m_Book->GetIndexCount());

	m_Plane->SendData(m_Direct3D->GetDeviceContext());			//Render plane with shadow shader
	m_Shadow->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Plane->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light3);
	m_Shadow->Render(m_Direct3D->GetDeviceContext(), m_Plane->GetIndexCount());

	m_Cup->SendData(m_Direct3D->GetDeviceContext());			//Render cup with shadow shader
	m_Shadow->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Cup->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light);
	m_Shadow->Render(m_Direct3D->GetDeviceContext(), m_Cup->GetIndexCount());

	m_Sweet->SendData(m_Direct3D->GetDeviceContext());			//Render sweets with specular shader
	m_specShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Sweet->GetTexture(), m_Light4);
	m_specShader->Render(m_Direct3D->GetDeviceContext(), m_Sweet->GetIndexCount());

	m_Sweet2->SendData(m_Direct3D->GetDeviceContext());			
	m_specShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Sweet2->GetTexture(), m_Light4);
	m_specShader->Render(m_Direct3D->GetDeviceContext(), m_Sweet2->GetIndexCount());

	m_Sweet3->SendData(m_Direct3D->GetDeviceContext());			//Render sweets with specular shader
	m_specShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Sweet3->GetTexture(), m_Light4);
	m_specShader->Render(m_Direct3D->GetDeviceContext(), m_Sweet3->GetIndexCount());

	m_TessMesh->SendData(m_Direct3D->GetDeviceContext());		//Render triangle with tessellation shader
	if (m_Input->isKeyDown('L'))
	{
		tess++;							//Increase tessellation when pressing 'L' key
		
	}

	else if (m_Input->isKeyDown('K'))
	{
		tess--;							//Decrease tessellation when pressing 'K' key

	}
	m_TessShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_TessMesh->GetTexture(), tess, tess/2);
	m_TessShader->Render(m_Direct3D->GetDeviceContext(), m_TessMesh->GetIndexCount());

	m_Direct3D->TurnZBufferOff();

	m_Direct3D->GetOrthoMatrix(orthoMatrix);		// ortho matrix for 2D rendering
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	m_OrthoMesh->SendData(m_Direct3D->GetDeviceContext());		//screen in top left corner (textured objects)
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, m_screen->GetShaderResourceView());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_OrthoMesh->GetIndexCount());
	
	m_finalOrtho->SendData(m_Direct3D->GetDeviceContext());		//screen in top right corner (blurred objects);
	m_TextureShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, m_final->GetShaderResourceView());
	m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_finalOrtho->GetIndexCount());

	m_Direct3D->TurnZBufferOn();

	m_Direct3D->EndScene();

	return true;
}


