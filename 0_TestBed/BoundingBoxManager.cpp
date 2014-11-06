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
		int numBox = GetNumberOfBoxes();
		for(int nBox = 0; nBox < numBox; nBox++)
		{
			boundingBox[nBox]->SetVisible(a_bVisible);
		}
	}
	else
	{
		int box = bModelMngr->IdentifyInstance(a_sInstance);
		if(box < 0 || box < numBox)
			boundingBox[box]->SetVisible(a_bVisible);
	}
}
void BoundingBoxManager::SetColor(vector3 a_v3Color, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxs = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxs; nBox++)
		{
			boundingBox[nBox]->SetColor(a_v3Color);
		}
	}
	else
	{
		int nBox = bModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < numBox)
			boundingBox[nBox]->SetColor(a_v3Color);
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
			boundingBox[nBox]->SetModelMatrix(a_mModelMatrix);
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
		}
	}
	else
	{
		int nBox = bModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < numBox)
			boundingBox[nBox]->Render(MEDEFAULT);
	}
}
void BoundingBoxManager::AddBox(String a_sInstanceName)
{
	BoundingBoxClass* oBox = new BoundingBoxClass(a_sInstanceName);
	boundingBox.push_back(oBox);
	numBox ++;
}
void BoundingBoxManager::RemoveBox(String a_sInstanceName)
{
	if(a_sInstanceName == "ALL")
	{
		//Clear the vector's element first otherwise there is a memory leak
		for(int nBox = 0; nBox < numBox; nBox++)
		{
			BoundingBoxClass* pBS = boundingBox[nBox];
			delete pBS;
		}
		boundingBox.clear();
		numBox = 0;
		return;
	}
	std::vector<BoundingBoxClass*> vTemp;
	int nBox = bModelMngr->IdentifyInstance(a_sInstanceName);
	if(nBox < 0 || nBox < numBox)
	{
		for(int nBox = 0; nBox < numBox; nBox++)
		{
			if(nBox != nBox)
			{
				vTemp.push_back(boundingBox[nBox]);
			}
			else
			{
				BoundingBoxClass* pBS = boundingBox[nBox];
				delete pBS;
			}
		}
	}
	boundingBox = vTemp;
	numBox++;
}
void BoundingBoxManager::Update(void)
{
	bCollidingNames.clear();
	for(int nBox = 0; nBox < numBox; nBox++)
	{
		boundingBox[nBox]->SetColor(MEWHITE);
	}
	CollisionCheck();
	CollisionResponse();
}
void BoundingBoxManager::CollisionCheck(void)
{
	
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
			boundingBox[nBox]->SetColor(MERED);
	}
}
