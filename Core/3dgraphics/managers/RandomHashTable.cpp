#ifdef _3D

#include "RandomHashTable.h"
#include "foundation/PSPHeap.h"

BaseRandomHashTable::BaseRandomHashTable(){
	m_currentIndex=0;
	m_N[0]=11;
	m_N[1]=13;
	m_N[2]=16;
	m_N[3]=17;
	m_N[4]=19;
	m_Nj=16;
	m_M=5;														//5 permutations, m_N[0-4]
	m_permSize=m_N[0]+m_N[1]+m_N[2]+m_N[3]+m_N[4];
	m_size=4096;												//the perioud is 739,024 , but this is too big for our needs here
	Create();
}

void BaseRandomHashTable::Permute(unsigned int index, unsigned int num){
	for (unsigned int i=0;i<num-1;i++){
		int j = i + (rand() % (num - i));
		std::swap(m_pPerm[index+i],m_pPerm[index+j]);
	}
}

int BaseRandomHashTable::Hash(unsigned int x){
	unsigned int S=0;
	unsigned int index=0;
	for (unsigned j=0;j<m_M;j++){
		S+=m_pPerm[index+x%m_N[j]];
		index+=m_N[j];
	}
	return S%m_Nj;
}

void BaseRandomHashTable::CreatePerlin(){
	m_pPerm=new unsigned int [m_permSize];
	unsigned int index=0;
	for (unsigned int j=0;j<m_M;j++){
		for (unsigned int i=0;i<m_N[j];i++){
			m_pPerm[index+i]=i;
		}
		index+=m_N[j];
	}
	index=0;
	for (unsigned int j=0;j<m_M;j++){
		Permute(index,m_N[j]);
		index+=m_N[j];
	}
	for (unsigned int x=0;x<m_size;x++){
		float y=(float)Hash(x)/255.0f;
		m_hashTable.insert(std::pair<int,float>(x,y));
	}
}

void BaseRandomHashTable::Create(){
	//for (unsigned int x=0;x<m_size;x++){
	//	m_hashTable.insert(pair<int,float>(x,(float)(rand()%1001)/1000.0f));
	//}

#ifdef _SPSP
	sceSfmt11213InitGenRand(&m_ctx, 1000000);

#endif

}

#endif