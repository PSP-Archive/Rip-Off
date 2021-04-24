#pragma once

#ifdef _3D


#include <cstdlib>
#include <map>
#include "foundation/Singleton.h"
#ifdef _SPSP
	#include <libsfmt11213.h>
#endif

//this class is building a hash table with random numbers; 
//it is used instead of rand() function

//The purpose of the class is yielding a random real number
//in the interval [0,1] whenever Random() method is called

class BaseRandomHashTable{
private:


#ifdef _SPSP
	SceSfmt11213Context m_ctx;	//context for random number sequence
		
#endif

	unsigned int m_currentIndex, m_size;
	unsigned int m_N[5], m_M, m_Nj, *m_pPerm, m_permSize;
	std::map<int, float> m_hashTable;
	
	//generates an integer random number between [0,upperLimit]
	//it uses the random() function, and it is used only for creating the hash table
	int SlowRandom(int upperLimit){
		return rand()%(upperLimit+1);	
	}
	
	BaseRandomHashTable(const BaseRandomHashTable& rhs){}
	BaseRandomHashTable& operator = (const BaseRandomHashTable& rhs){ return *this; }
	
	int Hash(unsigned int x);
	void Permute(unsigned int index, unsigned int num);

	//it creates a one-dimensional long-period hash function, as it
	//is defined by Ares Lagae & Philip Dutre in the paper:
	//www.cs.kuleuven.be/~ares/publications/LD06LPHFPT/LD06LPHFPT.pdf
	void CreatePerlin();
	void Create();

public:

	BaseRandomHashTable();

	//returns a random number in the interval [0,1]
	float randomf(){
		if (m_currentIndex>=m_size) m_currentIndex=0;
		return m_hashTable[m_currentIndex++];
	}
	//return a random number in the interval [minValue,maxValue]
	float randomMinMaxf(float minVal, float maxVal){
		#ifndef _SPSP
			return minVal+(maxVal-minVal)*((float)(rand()%1001)/1000.0f);
		#else
			SceUInt32 val=sceSfmt11213GenRand32(&m_ctx);
			
			float x=((float)(val%1001)/1000.0f);
			if (x<0) x=0.0f;
			else if (x>1) x=1.0f;
			x=minVal+(maxVal-minVal)*x;
			if (x<minVal) x=minVal;
			else if (x>maxVal) x=maxVal;
			return x;
		#endif

	}
	float randomMinMaxfTrue(float minVal, float maxVal){
		if (m_currentIndex>=m_size) m_currentIndex=0;
		float x=m_hashTable[m_currentIndex++];
		
		return (maxVal-minVal)*x+minVal;
	}
};

typedef Singleton<BaseRandomHashTable> RandomHashTable;


#endif