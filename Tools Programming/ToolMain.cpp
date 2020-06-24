#include "ToolMain.h"
#include "resource.h"
#include <vector>
#include <sstream>

//ToolMain Class - own code
ToolMain::ToolMain()
{
	m_currentChunk = 0;							//default value
	m_selectedObject = 1;						//initial selection ID
	m_sceneGraph.clear();						//clear the vector for the scenegraph
	m_databaseConnection = NULL;

	//zero input commands
	m_toolInputCommands.forward		= false;	//For moving camera forward
	m_toolInputCommands.back		= false;	//For moving camera back
	m_toolInputCommands.left		= false;	//For moving camera left
	m_toolInputCommands.right		= false;	//For moving camera right

	m_toolInputCommands.leftclicked = false;	//For left clicking
	m_toolInputCommands.movingLeft = false;		//For moving left
	m_toolInputCommands.movingRight = false;	//For moving right
	m_toolInputCommands.movingUp = false;		//For moving up
	m_toolInputCommands.movingDown = false;		//For moving down

	m_toolInputCommands.movingForward = false;	//For moving forward
	m_toolInputCommands.movingBack = false;		//For moving back

	m_toolInputCommands.dragging = false;		//For dragging mouse
	m_toolInputCommands.mouseWheel = false;		//For moving mouse wheel

	m_toolInputCommands.newMouseX = 0;			//For detecting mouse clicks
	m_toolInputCommands.newMouseY = 0;			

	m_toolInputCommands.oldMouseX = 0;
	m_toolInputCommands.oldMouseY = 0;

	m_toolInputCommands.oldMouseZ = 0;
	m_toolInputCommands.newMouseZ = 0;
}


ToolMain::~ToolMain()
{
	sqlite3_close(m_databaseConnection);		//Close the database connection
}


int ToolMain::getCurrentSelectionID()
{
	return m_selectedObject;					//For selection
}

void ToolMain::onActionInitialise(HWND handle, int width, int height)
{
	//window size, handle etc for directX
	m_width		= width;
	m_height	= height;
	m_d3dRenderer.GetDefaultSize(m_width, m_height);
	m_d3dRenderer.Initialize(handle, m_width, m_height);

	//database connection establish
	int rc;
	rc = sqlite3_open("database/test.db", &m_databaseConnection);

	if (rc) 
	{
		TRACE("Can't open database");
		//if the database cant open. Perhaps a more catastrophic error would be better here
	}
	else 
	{
		TRACE("Opened database successfully");
	}

	onActionLoad();
}


void ToolMain::onActionLoad()
{
	//load current chunk and objects into lists
	if (!m_sceneGraph.empty())		//is the vector empty
	{
		m_sceneGraph.clear();		//if not, empty it
	}

	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query
	sqlite3_stmt *pResultsChunk;

	//OBJECTS IN THE WORLD
	//prepare SQL Text
	sqlCommand = "SELECT * from Objects";				//sql command which will return all records from the objects table.
	//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0 );
	
	//loop for each row in results until there are no more rows.  ie for every row in the results. We create an object
	while (sqlite3_step(pResults) == SQLITE_ROW)
	{	
		SceneObject newSceneObject;
		newSceneObject.ID = sqlite3_column_int(pResults, 0);
		newSceneObject.chunk_ID = sqlite3_column_int(pResults, 1);
		newSceneObject.model_path		= reinterpret_cast<const char*>(sqlite3_column_text(pResults, 2));
		newSceneObject.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 3));
		newSceneObject.posX = sqlite3_column_double(pResults, 4);
		newSceneObject.posY = sqlite3_column_double(pResults, 5);
		newSceneObject.posZ = sqlite3_column_double(pResults, 6);
		newSceneObject.rotX = sqlite3_column_double(pResults, 7);
		newSceneObject.rotY = sqlite3_column_double(pResults, 8);
		newSceneObject.rotZ = sqlite3_column_double(pResults, 9);
		newSceneObject.scaX = sqlite3_column_double(pResults, 10);
		newSceneObject.scaY = sqlite3_column_double(pResults, 11);
		newSceneObject.scaZ = sqlite3_column_double(pResults, 12);
		newSceneObject.render = sqlite3_column_int(pResults, 13);
		newSceneObject.collision = sqlite3_column_int(pResults, 14);
		newSceneObject.collision_mesh = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 15));
		newSceneObject.collectable = sqlite3_column_int(pResults, 16);
		newSceneObject.destructable = sqlite3_column_int(pResults, 17);
		newSceneObject.health_amount = sqlite3_column_int(pResults, 18);
		newSceneObject.editor_render = sqlite3_column_int(pResults, 19);
		newSceneObject.editor_texture_vis = sqlite3_column_int(pResults, 20);
		newSceneObject.editor_normals_vis = sqlite3_column_int(pResults, 21);
		newSceneObject.editor_collision_vis = sqlite3_column_int(pResults, 22);
		newSceneObject.editor_pivot_vis = sqlite3_column_int(pResults, 23);
		newSceneObject.pivotX = sqlite3_column_double(pResults, 24);
		newSceneObject.pivotY = sqlite3_column_double(pResults, 25);
		newSceneObject.pivotZ = sqlite3_column_double(pResults, 26);
		newSceneObject.snapToGround = sqlite3_column_int(pResults, 27);
		newSceneObject.AINode = sqlite3_column_int(pResults, 28);
		newSceneObject.audio_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 29));
		newSceneObject.volume = sqlite3_column_double(pResults, 30);
		newSceneObject.pitch = sqlite3_column_double(pResults, 31);
		newSceneObject.pan = sqlite3_column_int(pResults, 32);
		newSceneObject.one_shot = sqlite3_column_int(pResults, 33);
		newSceneObject.play_on_init = sqlite3_column_int(pResults, 34);
		newSceneObject.play_in_editor = sqlite3_column_int(pResults, 35);
		newSceneObject.min_dist = sqlite3_column_double(pResults, 36);
		newSceneObject.max_dist = sqlite3_column_double(pResults, 37);
		newSceneObject.camera = sqlite3_column_int(pResults, 38);
		newSceneObject.path_node = sqlite3_column_int(pResults, 39);
		newSceneObject.path_node_start = sqlite3_column_int(pResults, 40);
		newSceneObject.path_node_end = sqlite3_column_int(pResults, 41);
		newSceneObject.parent_id = sqlite3_column_int(pResults, 42);
		newSceneObject.editor_wireframe = sqlite3_column_int(pResults, 43);
		newSceneObject.name = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 44));
		
		//send completed object to scenegraph
		m_sceneGraph.push_back(newSceneObject);
	}

	//THE WORLD CHUNK
	//prepare SQL Text
	sqlCommand = "SELECT * from Chunks";				//sql command which will return all records from  chunks table. There is only one tho.
														//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResultsChunk, 0);

	sqlite3_step(pResultsChunk);
	m_chunk.ID = sqlite3_column_int(pResultsChunk, 0);
	m_chunk.name = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 1));
	m_chunk.chunk_x_size_metres = sqlite3_column_int(pResultsChunk, 2);
	m_chunk.chunk_y_size_metres = sqlite3_column_int(pResultsChunk, 3);
	m_chunk.chunk_base_resolution = sqlite3_column_int(pResultsChunk, 4);
	m_chunk.heightmap_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 5));
	m_chunk.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 6));
	m_chunk.tex_splat_alpha_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 7));
	m_chunk.tex_splat_1_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 8));
	m_chunk.tex_splat_2_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 9));
	m_chunk.tex_splat_3_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 10));
	m_chunk.tex_splat_4_path = reinterpret_cast<const char*>(sqlite3_column_text(pResultsChunk, 11));
	m_chunk.render_wireframe = sqlite3_column_int(pResultsChunk, 12);
	m_chunk.render_normals = sqlite3_column_int(pResultsChunk, 13);
	m_chunk.tex_diffuse_tiling = sqlite3_column_int(pResultsChunk, 14);
	m_chunk.tex_splat_1_tiling = sqlite3_column_int(pResultsChunk, 15);
	m_chunk.tex_splat_2_tiling = sqlite3_column_int(pResultsChunk, 16);
	m_chunk.tex_splat_3_tiling = sqlite3_column_int(pResultsChunk, 17);
	m_chunk.tex_splat_4_tiling = sqlite3_column_int(pResultsChunk, 18);

	//Process REsults into renderable
	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);
	//build the renderable chunk 
	m_d3dRenderer.BuildDisplayChunk(&m_chunk);

}

void ToolMain::UpdateSceneGraph()
{
	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query
	sqlite3_stmt *pResultsChunk;
														
	sqlCommand = "SELECT * from Objects WHERE   ID = (SELECT MAX(ID) from Objects);";		//Select the last entry from database
	//Send Command and fill result object
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0);			//Fill result object with last entry
	while (sqlite3_step(pResults) == SQLITE_ROW)											//Last entry's row
	{	
		SceneObject newSceneObject;															//Create Object from database entries
		newSceneObject.ID = sqlite3_column_int(pResults, 0);
		newSceneObject.chunk_ID = sqlite3_column_int(pResults, 1);
		newSceneObject.model_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 2));
		newSceneObject.tex_diffuse_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 3));
		newSceneObject.posX = sqlite3_column_double(pResults, 4);
		newSceneObject.posY = sqlite3_column_double(pResults, 5);
		newSceneObject.posZ = sqlite3_column_double(pResults, 6);
		newSceneObject.rotX = sqlite3_column_double(pResults, 7);
		newSceneObject.rotY = sqlite3_column_double(pResults, 8);
		newSceneObject.rotZ = sqlite3_column_double(pResults, 9);
		newSceneObject.scaX = sqlite3_column_double(pResults, 10);
		newSceneObject.scaY = sqlite3_column_double(pResults, 11);
		newSceneObject.scaZ = sqlite3_column_double(pResults, 12);
		newSceneObject.render = sqlite3_column_int(pResults, 13);
		newSceneObject.collision = sqlite3_column_int(pResults, 14);
		newSceneObject.collision_mesh = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 15));
		newSceneObject.collectable = sqlite3_column_int(pResults, 16);
		newSceneObject.destructable = sqlite3_column_int(pResults, 17);
		newSceneObject.health_amount = sqlite3_column_int(pResults, 18);
		newSceneObject.editor_render = sqlite3_column_int(pResults, 19);
		newSceneObject.editor_texture_vis = sqlite3_column_int(pResults, 20);
		newSceneObject.editor_normals_vis = sqlite3_column_int(pResults, 21);
		newSceneObject.editor_collision_vis = sqlite3_column_int(pResults, 22);
		newSceneObject.editor_pivot_vis = sqlite3_column_int(pResults, 23);
		newSceneObject.pivotX = sqlite3_column_double(pResults, 24);
		newSceneObject.pivotY = sqlite3_column_double(pResults, 25);
		newSceneObject.pivotZ = sqlite3_column_double(pResults, 26);
		newSceneObject.snapToGround = sqlite3_column_int(pResults, 27);
		newSceneObject.AINode = sqlite3_column_int(pResults, 28);
		newSceneObject.audio_path = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 29));
		newSceneObject.volume = sqlite3_column_double(pResults, 30);
		newSceneObject.pitch = sqlite3_column_double(pResults, 31);
		newSceneObject.pan = sqlite3_column_int(pResults, 32);
		newSceneObject.one_shot = sqlite3_column_int(pResults, 33);
		newSceneObject.play_on_init = sqlite3_column_int(pResults, 34);
		newSceneObject.play_in_editor = sqlite3_column_int(pResults, 35);
		newSceneObject.min_dist = sqlite3_column_double(pResults, 36);
		newSceneObject.max_dist = sqlite3_column_double(pResults, 37);
		newSceneObject.camera = sqlite3_column_int(pResults, 38);
		newSceneObject.path_node = sqlite3_column_int(pResults, 39);
		newSceneObject.path_node_start = sqlite3_column_int(pResults, 40);
		newSceneObject.path_node_end = sqlite3_column_int(pResults, 41);
		newSceneObject.parent_id = sqlite3_column_int(pResults, 42);
		newSceneObject.editor_wireframe = sqlite3_column_int(pResults, 43);
		newSceneObject.name = reinterpret_cast<const char*>(sqlite3_column_text(pResults, 44));

		//send completed object to scenegraph
		m_sceneGraph.push_back(newSceneObject);
	}
	//Process REsults into renderable
	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);
}

void ToolMain::moveSelected(float X, float Y, float Z, float rotX, float rotY, float rotZ)
{
	m_sceneGraph.at(m_selectedObject - 1).posX = X;			//Translate object in scene graph	
	m_sceneGraph.at(m_selectedObject - 1).posY = Y;
	m_sceneGraph.at(m_selectedObject - 1).posZ = Z;
	m_sceneGraph.at(m_selectedObject - 1).rotX = rotX;		//Rotate object
	m_sceneGraph.at(m_selectedObject - 1).rotY = rotY;
	m_sceneGraph.at(m_selectedObject - 1).rotZ = rotZ;

	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);			//Update display list
}

void ToolMain::scaleSelected(float X, float Y, float Z)
{
	m_sceneGraph.at(m_selectedObject - 1).scaX = X;			//Rotate object in scene graph
	m_sceneGraph.at(m_selectedObject - 1).scaY = Y;
	m_sceneGraph.at(m_selectedObject - 1).scaZ = Z;

	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);			//Update display list
}

void ToolMain::changeTexture(std::string name, std::string texture, std::string mesh)
{
	m_sceneGraph.at(m_selectedObject - 1).name = name;					//For changing name of object in scene graph
	m_sceneGraph.at(m_selectedObject - 1).tex_diffuse_path = texture;	//For changing name of texture destination 
	m_sceneGraph.at(m_selectedObject - 1).model_path = mesh;			//For changing name of mesh destination

	m_d3dRenderer.BuildDisplayList(&m_sceneGraph);						//Update display list
}

void ToolMain::onActionCreate()							//Add a new object to the database
{
	int rc;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query

	int numObjects = m_sceneGraph.size();				//Loop thru the scene graph.

		std::stringstream command3;
		command3 << "INSERT INTO Objects "				//"Insert" command into database to add entry
			<< "VALUES(" << numObjects+1 << ","			//Count number of objects +1 since there is one more added
			<<	0							<< ","
			<< "'database/data/placeholder.cmo'" << ","	//Mesh destination
			<< "'database/data/placeholder.dds'" << ","	//Texture destination
			<< numObjects + 1 << ","					//X Position (different to others)
			<< 1 << ","									//Same Y Position
			<< numObjects+1 << ","						//Z position (different to others)
			<< 0 << ","									//Rotation
			<< 0 << ","
			<< 0 << ","
			<< 1 << ","									//Scaling
			<< 1 << ","
			<< 1 << ","
			<< 0 << ","									//Rendering							
			<< 0 << ","									//Collision
			<< "'" <<  "'" << ","						//Collision mesh
			<< 0 << ","									//Collectable
			<< 0 << ","									//Destructable
			<< 0 << ","									//Health
			<< 1 << ","									//Editor render
			<< 1 << ","									//Editor texture
			<< 0 << ","									//Editor Normals
			<< 0 << ","									//Editor Collision
			<< 0 << ","									//Editor Pivot
			<< 0 << ","									//Pivots
			<< 0 << ","
			<< 0 << ","
			<< 0 << ","									//Snap to Ground
			<< 0 << ","									//AI Node
			<< "'"  << "'" << ","						//Audio Path
			<< 0 << ","									//Volume
			<< 0 << ","									//Pitch
			<< 0 << ","									//Pan
			<< 0 << ","									//One shot
			<< 0 << ","									//Play on init
			<< 0 << ","									//Play on edit
			<< 0 << ","									//Min distance
			<< 0 << ","									//Max Distance
			<< 0 << ","									//Camera
			<< 0 << ","									//Path Node
			<< 0 << ","									//Starting path node
			<< 0 << ","									//Ending Path Node
			<< 0 << ","									//Parent ID
			<< 0 << ","									//Editor Wireframe
			<< "'Name '"								//Name
			<< ")";

		std::string sqlCommand3 = command3.str();		//Get the command
		rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand3.c_str(), -1, &pResults, 0);		//Prepare database with new data
		sqlite3_step(pResults);
		
		UpdateSceneGraph();									//Create the object, add to scene graph and update display list
		
											//MessageBox(NULL, L"Objects Saved", L"Notification", MB_OK);
}

void ToolMain::onActionSave()
{
	//SQL
	int rc;
	char *sqlCommand;
	char *ErrMSG = 0;
	sqlite3_stmt *pResults;								//results of the query
	
	//OBJECTS IN THE WORLD Delete them all
	//prepare SQL Text
	sqlCommand = "DELETE FROM Objects";	 //will delete the whole object table.   Slightly risky but hey.
	rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand, -1, &pResults, 0);
	sqlite3_step(pResults);

	//Populate with our new objects
	std::wstring sqlCommand2;
	int numObjects = m_sceneGraph.size();	//Loop thru the scengraph.

	for (int i = 0; i < numObjects; i++)
	{
		std::stringstream command;
		command << "INSERT INTO Objects " 
			<<"VALUES(" << m_sceneGraph.at(i).ID << ","
			<< m_sceneGraph.at(i).chunk_ID  << ","
			<< "'" << m_sceneGraph.at(i).model_path <<"'" << ","
			<< "'" << m_sceneGraph.at(i).tex_diffuse_path << "'" << ","
			<< m_sceneGraph.at(i).posX << ","
			<< m_sceneGraph.at(i).posY << ","
			<< m_sceneGraph.at(i).posZ << ","
			<< m_sceneGraph.at(i).rotX << ","
			<< m_sceneGraph.at(i).rotY << ","
			<< m_sceneGraph.at(i).rotZ << ","
			<< m_sceneGraph.at(i).scaX << ","
			<< m_sceneGraph.at(i).scaY << ","
			<< m_sceneGraph.at(i).scaZ << ","
			<< m_sceneGraph.at(i).render << ","
			<< m_sceneGraph.at(i).collision << ","
			<< "'" << m_sceneGraph.at(i).collision_mesh << "'" << ","
			<< m_sceneGraph.at(i).collectable << ","
			<< m_sceneGraph.at(i).destructable << ","
			<< m_sceneGraph.at(i).health_amount << ","
			<< m_sceneGraph.at(i).editor_render << ","
			<< m_sceneGraph.at(i).editor_texture_vis << ","
			<< m_sceneGraph.at(i).editor_normals_vis << ","
			<< m_sceneGraph.at(i).editor_collision_vis << ","
			<< m_sceneGraph.at(i).editor_pivot_vis << ","
			<< m_sceneGraph.at(i).pivotX << ","
			<< m_sceneGraph.at(i).pivotY << ","
			<< m_sceneGraph.at(i).pivotZ << ","
			<< m_sceneGraph.at(i).snapToGround << ","
			<< m_sceneGraph.at(i).AINode << ","
			<< "'" << m_sceneGraph.at(i).audio_path << "'" << ","
			<< m_sceneGraph.at(i).volume << ","
			<< m_sceneGraph.at(i).pitch << ","
			<< m_sceneGraph.at(i).pan << ","
			<< m_sceneGraph.at(i).one_shot << ","
			<< m_sceneGraph.at(i).play_on_init << ","
			<< m_sceneGraph.at(i).play_in_editor << ","
			<< m_sceneGraph.at(i).min_dist << ","
			<< m_sceneGraph.at(i).max_dist << ","
			<< m_sceneGraph.at(i).camera << ","
			<< m_sceneGraph.at(i).path_node << ","
			<< m_sceneGraph.at(i).path_node_start << ","
			<< m_sceneGraph.at(i).path_node_end << ","
			<< m_sceneGraph.at(i).parent_id << ","
			<< m_sceneGraph.at(i).editor_wireframe << ","
			<< "'" << m_sceneGraph.at(i).name << "'"
			<< ")";
		std::string sqlCommand2 = command.str();
		rc = sqlite3_prepare_v2(m_databaseConnection, sqlCommand2.c_str(), -1, &pResults, 0);
		sqlite3_step(pResults);	
	}
	MessageBox(NULL, L"Objects Saved", L"Notification", MB_OK);
}

void ToolMain::onActionSaveTerrain()
{
	m_d3dRenderer.SaveDisplayChunk(&m_chunk);
}

void ToolMain::Tick(MSG *msg)
{
	//do we have a selection
	m_toolInputCommands.selected = m_selectedObject;			//Set selected object
	//do we have a mode
	//are we clicking / dragging /releasing
	//has something changed
		//update Scenegraph

		//add to scenegraph
		//resend scenegraph to Direct X renderer

	m_d3dRenderer.Tick(&m_toolInputCommands);

	if (wire == true)										//If wire is detected (wire button pressed)
	{
		m_toolInputCommands.wireframe = true;				//Wireframe mode
	}
	else m_toolInputCommands.wireframe = false;

}

void ToolMain::UpdateInput(MSG * msg)
{
	switch (msg->message)
	{
		//Global inputs,  mouse position and keys etc
		case WM_KEYDOWN:
			m_keyArray[msg->wParam] = true;
			break;

		case WM_KEYUP:
			m_keyArray[msg->wParam] = false;
			break;
		
		case WM_MOUSEMOVE:										//If mouse is moved
			if (cameraMove == true)								//If Camera move button is pressed
			{
				movedPoint.x = GET_X_LPARAM(msg->lParam);		//Get the positions
				movedPoint.y = GET_Y_LPARAM(msg->lParam);

				if (m_toolInputCommands.leftclicked == true)	//If left clicked
				{
					if (movedPoint.y < clickPoint.y)			//If the moved point y is smaller than the previous point when first clicked
					{
						m_toolInputCommands.movingForward = true;	//Move forward
						m_toolInputCommands.movingBack = false;		//Move back
					}
	
					if (movedPoint.y > clickPoint.y)				//Otherwise
					{
						m_toolInputCommands.movingBack = true;		//Move back
						m_toolInputCommands.movingForward = false;
					}
	
					if (movedPoint.x > clickPoint.x)				//If moved point x position is larger than previous click
					{
						m_toolInputCommands.movingRight = false;	//Move left
						m_toolInputCommands.movingLeft = true;
					}
	
					else if (movedPoint.x < clickPoint.x)			//If moved point x position is smaller than previous click
					{
						m_toolInputCommands.movingLeft = false;		//Move right
						m_toolInputCommands.movingRight = true;
	
					}
				}
			}
			break;
	
		case WM_LBUTTONDOWN:													//If left button of mouse clicked
			if (cameraMove == true)												//If camera button pressed
			{
				m_toolInputCommands.leftclicked = true;							//Left clicked
				m_toolInputCommands.oldMouseX = GET_X_LPARAM(msg->lParam);		//Get positions of mouse at clicked point
				m_toolInputCommands.oldMouseY = GET_Y_LPARAM(msg->lParam);

				clickPoint.x = m_toolInputCommands.oldMouseX;					//Set click point to this mouse position
				clickPoint.y = m_toolInputCommands.oldMouseY;

				if (DragDetect(msg->hwnd, clickPoint))							//If a drag is detected next
				{
					m_toolInputCommands.dragging = true;						//Being dragged
					SetCapture(msg->hwnd);										//Capture mouse at this point
				}
				else m_toolInputCommands.dragging = false;						//Otherwise dragging is not happening
			}
			break;

		case WM_LBUTTONUP:														//Left button unclicked
			if (cameraMove == true)												//If camera button was pressed
			{
				m_toolInputCommands.leftclicked = false;						//No longer left clicked
				ReleaseCapture();												//Release mouse capture
			}
			break;
				
		case WM_MOUSEWHEEL:
		{
			if ((int)msg->wParam > 0)
			{
				m_toolInputCommands.movingUp = true;
				m_toolInputCommands.movingDown = false;
			}
			else if ((int)msg->wParam < 0)
			{
				m_toolInputCommands.movingDown = true;
				m_toolInputCommands.movingUp = false;
			}
				break;
		}
	}
	//here we update all the actual app functionality that we want.  This information will either be used int toolmain, or sent down to the renderer (Camera movement etc
	//WASD movement
	if (m_keyArray['W'])
	{
		m_toolInputCommands.forward = true;					//Move forward with W key
	}
	else m_toolInputCommands.forward = false;
	
	if (m_keyArray['S'])
	{
		m_toolInputCommands.back = true;					//Move back with S key
	}
	else m_toolInputCommands.back = false;
	if (m_keyArray['A'])
	{
		m_toolInputCommands.left = true;					//Move left with A key
	}
	else m_toolInputCommands.left = false;

	if (m_keyArray['D'])
	{
		m_toolInputCommands.right = true;					//Move right with D key
	}
	else m_toolInputCommands.right = false;
	//rotation
	if (m_keyArray['E'])
	{
		m_toolInputCommands.rotRight = true;				//Rotate right with E key
	}
	else m_toolInputCommands.rotRight = false;
	if (m_keyArray['Q'])
	{
		m_toolInputCommands.rotLeft = true;					//Rotate left with Q key
	}
	else m_toolInputCommands.rotLeft = false;

	if (m_keyArray['X'])
	{
		m_toolInputCommands.movingUp = true;				//Moving up with X key
	}
	else m_toolInputCommands.movingUp = false;

	if (m_keyArray['Y'])
	{
		m_toolInputCommands.movingDown = true;				//Moving down with Y key	
	}
	else m_toolInputCommands.movingDown = false;
	
	if (m_keyArray['I'])
	{
		m_toolInputCommands.FocusOnObject = true;			//Focus on object with I key
	}
	else m_toolInputCommands.FocusOnObject = false;

}
