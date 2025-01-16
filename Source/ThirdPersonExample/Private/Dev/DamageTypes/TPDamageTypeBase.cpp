// Project Untitled Game by JDNLY. All Rights Reserved.


#include "Dev/DamageTypes/TPDamageTypeBase.h"

UTPDamageTypeBase::UTPDamageTypeBase()
{
	DamageType = ETPDamageType::None;
}

UTPDamageTypeHeavy::UTPDamageTypeHeavy()
{
	DamageType = ETPDamageType::None;
}

UTPDamageTypeLeft::UTPDamageTypeLeft()
{
	DamageType = ETPDamageType::Left;
}

UTPDamageTypeRight::UTPDamageTypeRight()
{
	DamageType = ETPDamageType::Right;
}

UTPDamageTypeBack::UTPDamageTypeBack()
{
	DamageType = ETPDamageType::Back;
}

UTPDamageTypeFront::UTPDamageTypeFront()
{
	DamageType = ETPDamageType::Front;
}
