#include "drop.h"

Drop::Drop(int gunType, int bulletNumber)
{
    gunType_ = gunType;
    bulletNumber_ = bulletNumber;
}

int Drop::getBulletNumber()
{
    return bulletNumber_;
}

int Drop::getGunType()
{
    return gunType_;
}
