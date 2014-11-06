#include "BoundingBoxClass.h"

BoundingBoxClass::BoundingBoxClass(String theInstance)
{
	//Initialize variables
	mesh = nullptr;
	centroid = vector3(0.0f,0.0f,0.0f);
	color = MEWHITE;
	modelToWorld = matrix4(1.0f);
	visible = false;

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
	//Crete a new Sphere and initialize it using the member variables
	mesh = new PrimitiveWireClass();
	mesh->GenerateCube(5, MEWHITE);
	mesh->SetModelMatrix(glm::translate(modelToWorld, centroid));
}
BoundingBoxClass::BoundingBoxClass(BoundingBoxClass const& other)
{
	//Initialize the Sphere using other instance of it
	instance = other.instance;
	visible = other.visible;
	centroid = other.centroid;
	modelToWorld = other.modelToWorld;
	modelManager = other.modelManager;

	mesh = new PrimitiveWireClass();
	mesh->GenerateCube(5, MEWHITE);
	mesh->SetModelMatrix(glm::translate(modelToWorld, centroid));
}

BoundingBoxClass::~BoundingBoxClass(void)
{
}
