#include "BoundingBoxManager.h"

BoundingBoxManager* BoundingBoxManager::bInstance = nullptr;

BoundingBoxManager* BoundingBoxManager::GetInstance()
{
	if(bInstance == nullptr)
	{
		bInstance = new BoundingBoxManager();
	}
	return bInstance;
}

void BoundingBoxManager::ReleaseInstance()
{
	if(bInstance != nullptr)
	{
		delete bInstance;
		bInstance = nullptr;
	}
}

void BoundingBoxManager::Init(void)
{
	bModelMngr = ModelManagerClass::GetInstance();
	bCollidingNames.clear();
	numBox = 0;
}

void BoundingBoxManager::Release(void)
{
	RemoveBox("ALL");
	return;
}

//The big 3
BoundingBoxManager::BoundingBoxManager(){Init();}
BoundingBoxManager::BoundingBoxManager(BoundingBoxManager const& other){ }
BoundingBoxManager& BoundingBoxManager::operator=(BoundingBoxManager const& other) { return *this; }
BoundingBoxManager::~BoundingBoxManager(){Release();};
//Accessors
int BoundingBoxManager::GetNumberOfBoxes(void){ return numBox; }
//--- Non Standard Singleton Methods

void BoundingBoxManager::SetVisible(bool a_bVisible, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxs = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxs; nBox++)
		{
			boundingBox[nBox]->SetOBBVisible(a_bVisible);
			aaboundingBox[nBox]->SetOBBVisible(a_bVisible);
		}
	}
	else
	{
		int box = bModelMngr->IdentifyInstance(a_sInstance);
		if(box < 0 || box < numBox)
		{
			boundingBox[box]->SetOBBVisible(a_bVisible);
			aaboundingBox[box]->SetOBBVisible(a_bVisible);
		}
	}
}
void BoundingBoxManager::SetColor(vector3 a_v3Color, vector3 b_v3Color, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxs = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxs; nBox++)
		{
			boundingBox[nBox]->SetOBBColor(a_v3Color);
			aaboundingBox[nBox]->SetOBBColor(b_v3Color);
		}
	}
	else
	{
		int nBox = bModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < numBox)
		{
			boundingBox[nBox]->SetOBBColor(a_v3Color);
			aaboundingBox[nBox]->SetOBBColor(b_v3Color);
		}
	}
}
void BoundingBoxManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxs = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxs; nBox++)
		{
			boundingBox[nBox]->SetModelMatrix(a_mModelMatrix);
		}
	}
	else
	{
		int nBox = bModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < numBox)
		{
			boundingBox[nBox]->SetModelMatrix(a_mModelMatrix);
		}
	}
}

void BoundingBoxManager::SetaaModelMatrix(matrix4 a_mModelMatrix, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxs = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxs; nBox++)
		{
			std::vector<vector3> verts = boundingBox[nBox]->getVertices();
			aaboundingBox[nBox]->SetAAModelMatrix(a_mModelMatrix, verts);
		}
	}
	else
	{
		int nBox = bModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < numBox)
		{
			std::vector<vector3> verts = boundingBox[nBox]->getVertices();
			aaboundingBox[nBox]->SetAAModelMatrix(a_mModelMatrix, verts);
		}
	}
}

void BoundingBoxManager::Render(String a_sInstance)
{
	
	if(a_sInstance == "ALL")
	{
		int nBoxs = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxs; nBox++)
		{
			boundingBox[nBox]->Render(MEDEFAULT);
			aaboundingBox[nBox]->Render(MEDEFAULT);
		}
	}
	else
	{
		int nBox = bModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < numBox)
		{
			boundingBox[nBox]->Render(MEDEFAULT);
			aaboundingBox[nBox]->Render(MEDEFAULT);
		}
	}
}
void BoundingBoxManager::AddBox(String a_sInstanceName)
{
	BoundingBoxClass* oBox = new BoundingBoxClass(a_sInstanceName);
	BoundingBoxClass* aaBox = new BoundingBoxClass(oBox->getVertices(), a_sInstanceName);
	boundingBox.push_back(oBox);
	aaboundingBox.push_back(aaBox);

	numBox ++;
}
void BoundingBoxManager::RemoveBox(String a_sInstanceName)
{
	if(a_sInstanceName == "ALL")
	{
		//Clear the vector's element first otherwise there is a memory leak
		for(int nBox = 0; nBox < numBox; nBox++)
		{
			BoundingBoxClass* pBB = boundingBox[nBox];
			BoundingBoxClass* aapBB = aaboundingBox[nBox];
			delete pBB;
			delete aapBB;
		}
		boundingBox.clear();
		aaboundingBox.clear();
		numBox = 0;
		return;
	}
	std::vector<BoundingBoxClass*> vTemp;
	std::vector<BoundingBoxClass*> aaTemp;
	int nBox = bModelMngr->IdentifyInstance(a_sInstanceName);
	if(nBox < 0 || nBox < numBox)
	{
		for(int nBox = 0; nBox < numBox; nBox++)
		{
			if(nBox != nBox)
			{
				vTemp.push_back(boundingBox[nBox]);
				aaTemp.push_back(aaboundingBox[nBox]);
			}
			else
			{
				BoundingBoxClass* pBB = boundingBox[nBox];
				BoundingBoxClass* aapBB = aaboundingBox[nBox];
				delete pBB;
				delete aapBB;
			}
		}
	}
	boundingBox = vTemp;
	aaboundingBox = aaTemp;
	numBox++;
}
void BoundingBoxManager::Update(void)
{
	bCollidingNames.clear();
	for(int nBox = 0; nBox < numBox; nBox++)
	{
		boundingBox[nBox]->SetOBBColor(MEWHITE);
		aaboundingBox[nBox]->SetOBBColor(MEGREEN);
	}
	CollisionCheck();
	CollisionResponse();
}
void BoundingBoxManager::CollisionCheck(void)
{
	for(int i = 0; i < numBox; i++)
	{
		for(int j = 0; j < numBox; j++)
		{
			if(i != j)
			{
				matrix4  mat1 = aaboundingBox[i]->GetModelMatrix();
				vector3 maximum1 = aaboundingBox[i]->GetMaximum();
				vector3 minimum1 = aaboundingBox[i]->GetMinimum();
				vector3 newmax1 = static_cast<vector3>(glm::translate(mat1,maximum1) * vector4(0.0f,0.0f,0.0f, 1.0f));
				vector3 newmin1 = static_cast<vector3>(glm::translate(mat1,minimum1) * vector4(0.0f,0.0f,0.0f, 1.0f));

				matrix4  mat2 = aaboundingBox[j]->GetModelMatrix();
				vector3 maximum2 = aaboundingBox[j]->GetMaximum();
				vector3 minimum2 = aaboundingBox[j]->GetMinimum();
				vector3 newmax2 = static_cast<vector3>(glm::translate(mat2,maximum2) * vector4(0.0f,0.0f,0.0f, 1.0f));
				vector3 newmin2 = static_cast<vector3>(glm::translate(mat2,minimum2) * vector4(0.0f,0.0f,0.0f, 1.0f));
				/*std::cout<< boundingBox[i]->GetInstanceName() << " Min1: " << newmin1.x << std::endl;
				std::cout<< boundingBox[i]->GetInstanceName() << " Max1: " << newmax1.x << std::endl;
				std::cout<< boundingBox[j]->GetInstanceName() << " Min2: " << newmin2.x << std::endl;
				std::cout<< boundingBox[j]->GetInstanceName() << " Max2: " << newmax2.x << std::endl;*/
				if((newmax1.y > newmin2.y && newmin1.y < newmax2.y) && (newmax1.z > newmin2.z && newmin1.z < newmax2.z) && (newmax1.x > newmin2.x && newmin1.x < newmax2.x))
				{
					bCollidingNames.push_back(aaboundingBox[i]->GetInstanceName());
					bCollidingNames.push_back(aaboundingBox[j]->GetInstanceName());
				}
			}
		}
	}

}
bool BoundingBoxManager::CheckForNameInList(String a_sName)
{
	int nNames = static_cast<int>(bCollidingNames.size());
	for(int nName = 0; nName < nNames; nName++)
	{
		if(bCollidingNames[nName] == a_sName)
			return true;
	}
	return false;
}
void BoundingBoxManager::CollisionResponse(void)
{
	for(int nBox = 0; nBox < numBox; nBox++)
	{
		if(CheckForNameInList(boundingBox[nBox]->GetInstanceName()))
		{
			boundingBox[nBox]->SetOBBColor(MERED);
		}
		if(CheckForNameInList(aaboundingBox[nBox]->GetInstanceName()))
		{
			aaboundingBox[nBox]->SetOBBColor(MEBLUE);
		}
	}
}
