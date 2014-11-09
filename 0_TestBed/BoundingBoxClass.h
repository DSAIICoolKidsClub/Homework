#ifndef __BOUNDINGBOXCLASS_H_
#define __BOUNDINGBOXCLASS_H_

#include "ME\Mesh\shape\PrimitiveWireClass.h"
#include "ME\Mesh\shape\ModelManagerClass.h"
using namespace MyEngine;

class BoundingBoxClass
{
	String instance;
	bool visibleOBB;
	vector3 centroidOBB;
	vector3 colorOBB;
	bool visibleAABB;
	vector3 centroidAABB;
	vector3 colorAABB;
	matrix4 modelToWorld;
	PrimitiveWireClass* mesh;
	ModelManagerClass* modelManager;
	vector3 maximum;
	vector3 minimum;
	std::vector<vector3> vertices;

public:
	BoundingBoxClass(String theInstance);
	BoundingBoxClass(BoundingBoxClass const& other);
	BoundingBoxClass& operator=(BoundingBoxClass const& other);
	std::vector<vector3> getVertices();
	~BoundingBoxClass(void);

	bool GetOBBVisible(void);
	void SetOBBVisible(bool imVisible);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetOBBVisible, put = SetOBBVisible)) bool OBBVisible;

	bool GetAABBVisible(void);
	void SetAABBVisible(bool imVisible);
	/* Property:
	GetVisible() or GetVisible()*/
	__declspec(property(get = GetAABBVisible, put = SetAABBVisible)) bool AABBVisible;

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
	vector3 GetOBBCentroid(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetOBBCentroid)) vector3 OBBCentroid;

	/* Gets the centroid the bounding box */
	vector3 GetAABBCentroid(void);
	/* Property:
	GetCentroid()*/
	__declspec(property(get = GetAABBCentroid)) vector3 AABBCentroid;

	/* Gets the "ModelToWorld" matrix associated with the bounding box */
	matrix4 GetModelMatrix(void);
	/* Sets the "ModelToWorld" matrix associated with the bounding box */
	void SetModelMatrix(matrix4 theModelMatrix);
	/* "ModelToWorld"
	GetModelMatrix() or SetModelMatrix() */
	__declspec(property(get = GetModelMatrix, put = SetModelMatrix)) matrix4 ModelMatrix;

	/* Gets the color vector of this bounding box (the default color in which is going to be rendered) */
	vector3 GetOBBColor(void);
	/* Sets the color vector of this bounding box (the default color in which is going to be rendered) */
	void SetOBBColor(vector3 theColor);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetOBBColor, put = SetOBBColor)) vector3 OBBColor;

	/* Gets the color vector of this bounding box (the default color in which is going to be rendered) */
	vector3 GetAABBColor(void);
	/* Sets the color vector of this bounding box (the default color in which is going to be rendered) */
	void SetAABBColor(vector3 theColor);
	/* Property:
	GetColor() or SetColor() */
	__declspec(property(get = GetAABBColor, put = SetAABBColor)) vector3 AABBColor;
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