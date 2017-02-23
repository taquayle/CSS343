/****************************************************************************/
/*	PROJECT: LAB4															*/
/*	TEAM: Assignment4 19													*/
/*	MEMBERS: Tyler Quayle, Gytautas Jankauskas								*/
/****************************************************************************/
/*	FILE:		Return.cpp													*/
/*	PARENT:		Command														*/
/*	CHILDREN:	ReturnDrama, ReturnClassic, ReturnComedy					*/
/****************************************************************************/
#include "Return.h"

Return::Return()
{
}

Return::Return(int accNum, std::string medType, std::string movType) : Command(accNum, medType, movType)
{
}

Return::~Return()
{
}

