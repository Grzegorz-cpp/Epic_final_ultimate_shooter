#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Gun : public sf::Sprite
{
public:
    Gun(float fireRate, float bulletSpeed, float damage, float reloadingTime, int magazineCapasity, int bulletNumber, bool fullauto);
    float getFireRate();
    float getBulletSpeed();
    float getDamage();
    float getReloadingTime();
    int getMagazineCapasity();
    int getLeftInMagazine();
    bool getFullauto();
    void setLeftInMagazine(int leftInMagazine);
    void setFireRate(float fireRate);
    void setCurrettReloadingTime(float currentReloadingTime);
    float getCurretnReloadingTime();
    void setBulletNumber(int bulletNumber);
    int getBulletNumber();
    sf::SoundBuffer getReloadSound();

    bool shooting_flag = true;

private:
    float fireRate_;
    float bulletSpeed_;
    float damage_;
    float reloadingTime_;
    int magazineCapasity_;
    int leftInMagazine_;
    bool fullauto_;
    float currentReloadingTime_;
    int bulletNumber_;
};
