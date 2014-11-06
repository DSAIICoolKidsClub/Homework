#ifndef __BOUNDINGBOXCLASS_H_
#define __BOUNDINGBOXCLASS_H_

#include "ME\Mesh\shape\PrimitiveWireClass.h"
#include "ME\Mesh\shape\ModelManagerClass.h"
using namespace MyEngine;

class BoundingBoxClass
{
	String instance;
	bool visible;
	vector3 centroid;
	vector3 color;
	matrix4 modelToWorld;
	PrimitiveWireClass* mesh;
	ModelManagerClass* modelManager;
public:
	BoundingBoxClass(String theInstance);
	BoundingBoxClass(BoundingBoxClass const& other);
	BoundingBoxClass& operator=(BoundingBoxClass const& other);
	~BoundingBoxClass(void);

	bool GetVisible(void);
	void SetVisible(bool a_bVisible);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetVisible, put = SetVisible)) bool Visible;

	/* Gets the name of the model associated with this bounding box from model manager */
	String GetInstanceName(void);
	/* Property:
	GetInstanceName()*/
	__declspec(property(get = GetInstanceName)) String InstanceName;

	/* Gets the centroid the bounding box */
	vector3 GetCentroid(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCentroid)) vector3 Centroid;

	/* Gets the "ModelToWorld" matrix associated with the bounding box */
	matrix4 GetModelMatrix(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding box */
	void SetModelMatrix(matrix4 a_ModelMatrix);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	/* Gets the color vector of this bounding box (the default color in which is going to be rendered) */
	vector3 GetColor(void);
	/* Sets the color vector of this bounding box (the default color in which is going to be rendered) */
	void SetColor(vector3 a_v3Color);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetColor, put = SetColor)) vector3 Color;

	/* Renders the bounding box
		Args:
			a_vColor -> determinate the color of the sphere to be rendered, if MEDEFAULT
			it will render the shape in the constructed color (white) */
	void Render( vector3 a_vColor = MEDEFAULT);

private:
	/* Released Memory and objects allocated. */
	void Release(void);
	/* Calculates the sphere from the instance
	Args:
		a_sInstance: The name of the instance for which the bounding sphere is going to be calculated */
	void CalculateBox(String theInstance);
};

#endif