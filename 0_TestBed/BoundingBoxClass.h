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
	vector3 maximum;
	vector3 minimum;
	std::vector<vector3> vertices;

public:
	BoundingBoxClass(String theInstance);
	BoundingBoxClass(BoundingBoxClass const& other);
	BoundingBoxClass(std::vector<vector3> other, String theInstance);
	BoundingBoxClass& operator=(BoundingBoxClass const& other);
	std::vector<vector3> getVertices();
	~BoundingBoxClass(void);

	bool GetVisible(void);
	void SetVisible(bool imVisible);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetVisible, put = SetVisible)) bool Visible;

	/* Gets the name of the model associated with this bounding box from model manager */
	String GetInstanceName(void);
	/* Property:
	GetInstanceName()*/
	__declspec(property(get = GetInstanceName)) String InstanceName;
	// gets the minimum points of the box
	vector3 GetMinimum(void);
	// get the maximum points of box
	vector3 GetMaximum(void);

	/* Gets the centroid the bounding box */
	vector3 GetCentroid(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetCentroid)) vector3 Centroid;

	/* Gets the "ModelToWorld" matrix associated with the bounding box */
	matrix4 GetModelMatrix(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding box */
	void SetModelMatrix(matrix4 theModelMatrix);
	void SetAAModelMatrix(matrix4 theModelMatrix, std::vector<vector3> other);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	/* Gets the color vector of this bounding box (the default color in which is going to be rendered) */
	vector3 GetColor(void);
	/* Sets the color vector of this bounding box (the default color in which is going to be rendered) */
	void SetColor(vector3 theColor);
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
	void CalculateaaBox(std::vector<vector3> other);
};

#endif