#pragma once

#ifndef __BOUNDINGBOXMANAGER_H_
#define __BOUNDINGBOXMANAGER_H_

#include "BoundingBoxClass.h"

using namespace MyEngine;

class BoundingBoxManager
{
	int numBox;
	std::vector<BoundingBoxClass*> boundingBox;
	std::vector<BoundingBoxClass*> aaboundingBox;
	ModelManagerClass* bModelMngr;
	std::vector<String> bCollidingNames;
public:
	static BoundingBoxManager* GetInstance();
	void ReleaseInstance(void);
	int GetNumberOfBoxes(void);
	void AddBox(String bInstanceName);
	/*Remove a sphere from the List in the manager
	Arguments:
		a_sInstanceName name of the instance to remove from the List */
	void RemoveBox(String bInstanceName = "ALL");
	/*Sets the visibility of the specified Instance
	Arguments:
		a_bVisible sets whether the shape will be drawn or not
		a_sInstanceName identify the shape if ALL is provided then it applies to all shapes*/
	void SetOBBVisible(bool bVisible, String bInstanceName = "ALL");
	void SetAABBVisible(bool bVisible, String bInstanceName = "ALL");
	/*Sets the Color of the specified Instance
	Arguments:
		a_v3Color sets the color of the shape to be drawn
		a_sInstanceName identify the shape if ALL is provided then it applies to all shapes*/
	void SetColor(vector3 bv3Color, vector3 cv3Color, String bInstanceName = "ALL");
	/*Sets the Model matrix to the object and the shape
	Arguments:
		a_mModelMatrix matrix4 that contains the space provided
		a_sInstanceName identify the shape if ALL is provided then it applies to all shapes*/
	void SetModelMatrix(matrix4 bModelMatrix, String bInstanceName = "ALL");
	void SetaaModelMatrix(matrix4 bModelMatrix, String bInstanceName = "ALL");

	/*Render the specified shape
	Arguments:
		a_sInstanceName identify the shape if ALL is provided then it applies to all shapes*/
	void Render(String bInstanceName = "ALL");
	/*Initializes the list of names and check collision and collision resolution*/
	void Update(void);

private:
	/*Constructor*/
	BoundingBoxManager(void);
	/*Copy Constructor*/
	BoundingBoxManager(BoundingBoxManager const& other);
	/*Copy Assignment operator*/
	BoundingBoxManager& operator=(BoundingBoxManager const& other);
	/*Destructor*/
	~BoundingBoxManager(void);
	/*Releases the allocated memory*/
	void Release(void);
	/*Initializes the manager*/
	void Init(void);

	static BoundingBoxManager* bInstance; // Singleton
	/*Check the collision within all spheres*/
	void CollisionCheck(void);
	/*Response to the collision test*/
	void CollisionResponse(void);
	/*Checks whether a name is the List of collisions
	Arguments
		a_sName checks this specific name*/
	bool CheckForNameInList(String bName);
};

#endif