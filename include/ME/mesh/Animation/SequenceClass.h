/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __SEQUENCECLASS_H_
#define __SEQUENCECLASS_H_

#include "ME\system\SystemClass.h"

namespace MyEngine
{

class MyEngineDLL SequenceClass
{
	int m_nID;				//Secuence Identifier
	String m_sName;			//Secuence Name
	int m_nFirstFrame;		//First frame of the secuence;
	int m_nLastFrame;		//Last frame of the secuence;
	bool m_bDirectAnimation;//Secuence going from a low to a high frame number?
	int m_nFrameRate;		//How many frames a secuence is playing
	void Swap(SequenceClass& other);
public:
	SequenceClass();	//Constructor
	SequenceClass(String a_sName, int a_nID, int a_nFirstFrame, int a_nLastFrame, int a_nFrameRate);
	SequenceClass(const SequenceClass& other);
	SequenceClass& operator=(const SequenceClass& other);;
	~SequenceClass();	//Destructor

	void Init();		//Initialices variable values
	void Release();		//Releases the memory and deallocate space.
	
	void SetID(int a_nID);
	int getID(void);
	__declspec(property(put = SetID, get = GetID)) int ID;

	void SetName(String a_sName);
	String GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	void SetFirstFrame(int a_nFirstFrame);
	int GetFirstFrame(void);
	__declspec(property(put = SetFirstFrame, get = GetFirstFrame)) int FirstFrame;

	void SetLastFrame(int a_nLastFrame);
	int GetLastFrame(void);
	__declspec(property(put = SetLastFrame, get = GetLastFrame)) int LastFrame;

	void SetDirectAnimation(bool a_bDirectAnimation);
	bool IsDirectAnimation(void);
	__declspec(property(put = SetDirectAnimation, get = IsDirectAnimation)) bool DirectAnimation;

	void setFrameRate(int a_nFrameRate);
	int GetFrameRate(void);
	__declspec(property(put = SetFrameRate, get = GetFrameRate)) int FrameRate;
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<SequenceClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<SequenceClass*>;

}
#endif //__SEQUENCECLASS_H__