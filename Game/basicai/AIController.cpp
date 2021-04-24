#include "AIController.h"

//-------------------------------------

AIController::AIController() :
	m_AIType(0),
	mp_impl(NULL) {
}

//--------------------------------------

AIController::~AIController()
{
	if(mp_impl)
	{
		delete mp_impl;
	}
}

//--------------------------------------

void AIController::SetImpl(AI_ImplementationIF* impl) { 
	mp_impl = impl; 
	if (mp_impl)
	{
		mp_impl->Init();
		mp_impl->setAgentType(m_AIType);
	}
}

//--------------------------------------

void AIController::Update(float frameTime) {
	if(mp_ship && mp_impl)
	{
		mp_impl->Update(mp_ship);
	}
}

//--------------------------------------

void AIController::setAgentType(int AIType) {
	m_AIType = AIType;
	if (mp_impl)
		mp_impl->setAgentType(AIType);
}

//--------------------------------------

void AIController::Init() {
	if (mp_impl)
		mp_impl->Init();
}

//--------------------------------------

void AIController::Cleanup() {
	if (mp_impl)
		mp_impl->Cleanup();
}
