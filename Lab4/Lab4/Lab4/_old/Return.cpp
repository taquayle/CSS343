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

