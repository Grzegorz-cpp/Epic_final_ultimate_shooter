#include "gun.h"

Gun::Gun(int gunType, float fireRate, float bulletSpeed, float damage, float reloadingTime, int magazineCapasity, int bulletNumber, bool fullauto)
{
    fireRate_ = fireRate;
    bulletSpeed_ = bulletSpeed;
    damage_ = damage;
    reloadingTime_ = reloadingTime;
    magazineCapasity_ = magazineCapasity;
    fullauto_ = fullauto;
    leftInMagazine_ = magazineCapasity_;
    currentReloadingTime_ = reloadingTime_;
    bulletNumber_ = bulletNumber;
    gunType_ = gunType;
}

float Gun::getFireRate()
{
    return fireRate_;
}
float Gun::getBulletSpeed()
{
    return bulletSpeed_;
}
float Gun::getDamage()
{
    return damage_;
}
float Gun::getReloadingTime()
{
    return reloadingTime_;
}
int Gun::getMagazineCapasity()
{
    return magazineCapasity_;
}
int Gun::getLeftInMagazine()
{
    return leftInMagazine_;
}
bool Gun::getFullauto()
{
    return fullauto_;
}
void Gun::setLeftInMagazine(int leftInMagazine)
{
    leftInMagazine_ = leftInMagazine;
}
void Gun::setFireRate(float fireRate)
{
    fireRate_ = fireRate;
}
void Gun::setCurrettReloadingTime(float currentReloadingTime)
{
    currentReloadingTime_ = currentReloadingTime;
}
float Gun::getCurretnReloadingTime()
{
    return currentReloadingTime_;
}
void Gun::setBulletNumber(int bulletNumber)
{
    bulletNumber_ = bulletNumber;
}
int Gun::getBulletNumber()
{
    return bulletNumber_;
}

int Gun::getGunType()
{
    return gunType_;
}

























