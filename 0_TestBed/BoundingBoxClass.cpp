#include "BoundingBoxClass.h"

BoundingBoxClass::BoundingBoxClass(String theInstance)
{
	//Initialize variables
	mesh = nullptr;
	centroidOBB = vector3(0.0f,0.0f,0.0f);
	colorOBB = MEWHITE;
	modelToWorld = matrix4(1.0f);
	visibleOBB = false;

	//Get the singleton instance of the Model Manager
	modelManager = ModelManagerClass::GetInstance();
	instance = theInstance;
	//Identify the instance from the list inside of the Model Manager
	int nInstance = modelManager->IdentifyInstance(instance);
	//If there is no instance with that name the Identify Instance will return -1
	//In which case there is nothing to do here so we just return without allocating memory
	if(nInstance == -1)
		return;

	//Construct a box with the dimensions of the instance, they will be allocated in the
	//corresponding member variables inside the method
	CalculateBox(instance);
	//Get the Model to World matrix associated with the Instance
	modelToWorld = modelManager->GetModelMatrix(instance);
	//Crete a new Box and initialize it using the member variables
	mesh = new PrimitiveWireClass();
	mesh->GenerateCube(5, MEWHITE);
	mesh->SetModelMatrix(glm::translate(modelToWorld, centroidOBB));
}
BoundingBoxClass::BoundingBoxClass(BoundingBoxClass const& other)
{
	//Initialize the Box using other instance of it
	instance = other.instance;
	visibleOBB = other.visibleOBB;
	centroidOBB = other.centroidOBB;
	modelToWorld = other.modelToWorld;
	modelManager = other.modelManager;

	mesh = new PrimitiveWireClass();
	mesh->GenerateCube(5, MEWHITE);
	mesh->SetModelMatrix(glm::translate(modelToWorld, centroidOBB));
}
BoundingBoxClass& BoundingBoxClass::operator=(BoundingBoxClass const& other)
{
	//If the incoming instance is the same as the current there is nothing to do here
	if(this != &other)
	{
		//Release the existing object
		Release();
		//Construct the object as in the copy constructor
		instance = other.instance;
		visibleOBB = other.visibleOBB;
		centroidOBB = other.centroidOBB;
		modelToWorld = other.modelToWorld;
		modelManager = other.modelManager;
		
		mesh = new PrimitiveWireClass();
		mesh->GenerateCube(5, MEWHITE);
		mesh->SetModelMatrix(glm::translate(modelToWorld, centroidOBB));
	}
	return *this;
}
BoundingBoxClass::~BoundingBoxClass(void)
{
	//Destroying the object requires releasing all the allocated memory first
	Release();
}
void BoundingBoxClass::Release(void)
{
	//If the mesh exists release it
	if(mesh != nullptr)
	{
		delete mesh;
		mesh = nullptr;
	}

	//The job of releasing the Model Manager Instance is going to be the work
	//of another method, we can't assume that this class is the last class
	//that uses this singleton, so we do not release it, we just make the pointer
	//point at nothing.
	modelManager = nullptr;
}
//Accessors
vector3 BoundingBoxClass::GetOBBCentroid(void){ return centroidOBB; }
//vector3 BoundingBoxClass::GetAABBCentroid(void){ return centroidAABB; }
vector3 BoundingBoxClass::GetOBBColor(void){ return colorOBB; }
void BoundingBoxClass::SetOBBColor(vector3 theColor){ colorOBB = theColor; }
//vector3 BoundingBoxClass::GetAABBColor(void){ return colorAABB; }
//void BoundingBoxClass::SetAABBColor(vector3 theColor){ colorAABB = theColor; }
matrix4 BoundingBoxClass::GetModelMatrix(void){ return modelToWorld; }
void BoundingBoxClass::SetModelMatrix(matrix4 theModelMatrix)
{
	//Sets the model matrix of the Box
	modelToWorld = theModelMatrix;
	//Sets the Model Matrix of the actual Box shape
	//(which is translated m_v3Centrod away from the origin of our Box)
	mesh->SetModelMatrix(glm::translate(theModelMatrix, centroidOBB));
}
bool BoundingBoxClass::GetOBBVisible(void) { return visibleOBB; }
void BoundingBoxClass::SetOBBVisible(bool imVisible) { visibleOBB = imVisible; }
String BoundingBoxClass::GetInstanceName(void){ return instance; }
void BoundingBoxClass::CalculateBox(String theInstance)
{
	return;
}
void BoundingBoxClass::Render( vector3 otherColor )
{
	//If the shape is visible render it
	//otherwise just return
	if(visibleOBB)
		return;
	//Calculate the color we want the shape to be
	vector3 vColor;
	//if the argument was MEDEFAULT just use the color variable in our class
	if(otherColor == MEDEFAULT)
		vColor = colorOBB;
	else //Otherwise use the argument
		vColor = otherColor;

	//render the shape using a special case of the Shape Render method which uses the Color Shader.
	mesh->Render( matrix4(1.0f), vColor );
	
}