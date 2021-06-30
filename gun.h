#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Gun : public sf::Sprite
{
public:
    Gun(int gunType, float fireRate, float bulletSpeed, float damage, float reloadingTime, int magazineCapasity, int bulletNumber, bool fullauto);
    float getFireRate();
    float getBulletSpeed();
    float getDamage();
    float getReloadingTime();
    float getCurretnReloadingTime();
    int getMagazineCapasity();
    int getLeftInMagazine();
    int getBulletNumber();
    int getGunType();
    bool getFullauto();
    void setLeftInMagazine(int leftInMagazine);
    void setFireRate(float fireRate);
    void setCurrettReloadingTime(float currentReloadingTime);
    void setBulletNumber(int bulletNumber);
    sf::SoundBuffer getReloadSound();

    bool shooting_flag = true;

private:
    bool fullauto_;
    float fireRate_;
    float bulletSpeed_;
    float damage_;
    float reloadingTime_;
    float currentReloadingTime_ = 0;
    int bulletNumber_;
    int gunType_;
    int magazineCapasity_;
    int leftInMagazine_;
};
