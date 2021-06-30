#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "animated.h"
#include "hero.h"
#include "bullet.h"
#include "enemy.h"
#include "gun.h"
#include "bulletenemy.h"
#include "drop.h"

#define path "../debug"

int main()
{
E1:
    //vectors
    std::vector<sf::Sprite> obstacles;
    std::vector<Enemy*> EnemyVector;
    std::vector<Gun*> EnemyGun;
    std::vector<float> enemyBulletSpeed;
    std::vector<float> enemyFireRate;
    std::vector<Bullet*> BulletVector;
    std::vector<sf::Vector2f> bulletDirection;
    std::vector<BulletEnemy*> BulletVector_enemy;
    std::vector<sf::Vector2f> bulletDirection_enemy;
    std::vector<float> EnemyBulletDamage;
    std::vector<Drop*> dropVector;
    std::vector<sf::Sprite> ladder;
    std::vector<sf::Sprite*> aidKit;
    std::vector<sf::Sprite*> armorVest;

    //FONTS*****************************************************************************************************************************************************************
    sf::Font font;
    if (!font.loadFromFile(path "/font/OpenSans-Regular.ttf"))
    {
        std::cerr << "Could not load font :(" << std::endl;
        return 1;
    }

    sf::Text bulletNumberText("", font);
    bulletNumberText.setCharacterSize(18);
    bulletNumberText.setFillColor(sf::Color::Black);

    //SOUNDS*****************************************************************************************************************************************************************
    //machine gun reload
    sf::SoundBuffer machineGunReloadSoundWav;
    if (!machineGunReloadSoundWav.loadFromFile(path "/sounds/machineGunReload.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }
    sf::Sound machineGunReloadSound;
    machineGunReloadSound.setBuffer(machineGunReloadSoundWav);

    //pistol reload
    sf::SoundBuffer pistolReloadSoundWav;
    if (!pistolReloadSoundWav.loadFromFile(path "/sounds/pistolReload.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }
    sf::Sound pistolReloadSound;
    pistolReloadSound.setBuffer(pistolReloadSoundWav);

    //machine gun 2 reload
    sf::SoundBuffer machineGun_v2ReloadSoundWav;
    if (!machineGun_v2ReloadSoundWav.loadFromFile(path "/sounds/machineGun_v2Reload.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }
    sf::Sound machineGun_v2ReloadSound;
    machineGun_v2ReloadSound.setBuffer(machineGun_v2ReloadSoundWav);

    //machine gun
    sf::SoundBuffer shootingMachineGunSoundWav;
    if (!shootingMachineGunSoundWav.loadFromFile(path "/sounds/shootingMachinegun.wav"))
    {
        std::cerr << "../Could not load sound" << std::endl;
        return 1;
    }
    sf::Sound shootingMachineGunSound;
    shootingMachineGunSound.setBuffer(shootingMachineGunSoundWav);

    sf::Sound enemyMachineGunSound;
    enemyMachineGunSound.setBuffer(shootingMachineGunSoundWav);

    //machine gun 2
    sf::SoundBuffer shootingMachineGun_v2SoundWav;
    if (!shootingMachineGun_v2SoundWav.loadFromFile(path "/sounds/shootingMachinegun_v2.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }
    sf::Sound shootingMachineGun_v2Sound;
    shootingMachineGun_v2Sound.setBuffer(shootingMachineGun_v2SoundWav);

    sf::Sound enemyMachineGun_v2Sound;
    enemyMachineGun_v2Sound.setBuffer(shootingMachineGun_v2SoundWav);

    //pistol
    sf::SoundBuffer shootingPistolSoundWav;
    if (!shootingPistolSoundWav.loadFromFile(path "/sounds/shootingPistol.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }
    sf::Sound shootingPistolSound;
    shootingPistolSound.setBuffer(shootingPistolSoundWav);

    sf::Sound enemyPistolSound;
    enemyPistolSound.setBuffer(shootingPistolSoundWav);

    //walking
    sf::SoundBuffer walkingSoundWav;
    if (!walkingSoundWav.loadFromFile(path "/sounds/walking.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }
    sf::Sound walkingSound;
    walkingSound.setBuffer(walkingSoundWav);

    //TEXTURES LOADING*****************************************************************************************************************************************************************
    //floor
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile(path "/textures/floor.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    floorTexture.setRepeated(true);

    //background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(path "/textures/background.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    backgroundTexture.setRepeated(true);

    //HERO
    //pistol
    sf::Texture heroTexturePistol;
    if (!heroTexturePistol.loadFromFile(path "/textures/hero_pistol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //machine gun
    sf::Texture heroTextureMachineGun;
    if (!heroTextureMachineGun.loadFromFile(path "/textures/hero_machinegun.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //machine gun 2
    sf::Texture heroTextureMachineGun_v2;
    if (!heroTextureMachineGun_v2.loadFromFile(path "/textures/hero_machinegun_v2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //lying pistol
    sf::Texture heroTextureLyingPistol;
    if (!heroTextureLyingPistol.loadFromFile(path "/textures/hero_lying_pistol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //lying machine gun
    sf::Texture heroTextureLyingMachineGun;
    if (!heroTextureLyingMachineGun.loadFromFile(path "/textures/hero_lying_machinegun.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //lying machine gun 2
    sf::Texture heroTextureLyingMachineGun_v2;
    if (!heroTextureLyingMachineGun_v2.loadFromFile(path "/textures/hero_lying_machinegun_v2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //ENEMY
    //pistol
    sf::Texture enemyTexturePistol;
    if (!enemyTexturePistol.loadFromFile(path "/textures/enemy_pistol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //machine gun
    sf::Texture enemyTextureMachineGun;
    if (!enemyTextureMachineGun.loadFromFile(path "/textures/enemy_machinegun.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //machine gun 2
    sf::Texture enemyTextureMachineGun_v2;
    if (!enemyTextureMachineGun_v2.loadFromFile(path "/textures/enemy_machinegun_v2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //GUNS
    //pistol
    sf::Texture pistolTexture;
    if (!pistolTexture.loadFromFile(path "/textures/pistol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //machine gun
    sf::Texture machineGunTexture;
    if (!machineGunTexture.loadFromFile(path "/textures/machinegun.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //machine gun 2
    sf::Texture machineGun_v2Texture;
    if (!machineGun_v2Texture.loadFromFile(path "/textures/machinegun_v2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //ladder
    sf::Texture ladderTexture;
    if (!ladderTexture.loadFromFile(path "/textures/ladder.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    ladderTexture.setRepeated(true);

    //aid kit
    sf::Texture adiKitTexture;
    if (!adiKitTexture.loadFromFile(path "/textures/aid_kit.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //vest
    sf::Texture armorVestTexture;
    if (!armorVestTexture.loadFromFile(path "/textures/armor.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //box
    sf::Texture boxTexture;
    if (!boxTexture.loadFromFile(path "/textures/box.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    boxTexture.setRepeated(true);

    //locker
    sf::Texture lockerTexture;
    if (!lockerTexture.loadFromFile(path "/textures/locker.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //OBJECTS*****************************************************************************************************************************************************************
    //background
    sf::Sprite backgruond;
    backgruond.setTexture(backgroundTexture);
    backgruond.setPosition(-2000, -3000);
    backgruond.setScale(5, 5);
    backgruond.setTextureRect(sf::IntRect(0, 0, 20000, 5400));

    //floor
    sf::Sprite floor;
    floor.setTexture(floorTexture);
    floor.setPosition(-2000, 1500);
    floor.setScale(7, 7);
    floor.setTextureRect(sf::IntRect(0, 0, 40000, 1080));
    obstacles.emplace_back(floor);

    //obstacles
    sf::Sprite wall1;
    wall1.setTexture(floorTexture);
    wall1.setPosition(-500, -1000);
    wall1.setTextureRect(sf::IntRect(0, 0, 20, 357));
    wall1.setScale(7, 7);
    obstacles.emplace_back(wall1);

    sf::Sprite floor2;
    floor2.setTexture(floorTexture);
    floor2.setPosition(1500, 800);
    floor2.setTextureRect(sf::IntRect(0, 0, 150, 15));
    floor2.setScale(7, 7);
    obstacles.emplace_back(floor2);

    sf::Sprite box1;
    box1.setTexture(boxTexture);
    box1.setPosition(2400, 525);
    box1.setScale(3, 3);
    box1.setTextureRect(sf::IntRect(0, 0, 41, 92));
    obstacles.emplace_back(box1);

    sf::Sprite box2;
    box2.setTexture(boxTexture);
    box2.setPosition(3500, 1155);
    box2.setScale(3, 3);
    box2.setTextureRect(sf::IntRect(0, 0, 41, 115));
    obstacles.emplace_back(box2);

    sf::Sprite box3;
    box3.setTexture(boxTexture);
    box3.setPosition(3623, 1293);
    box3.setScale(3, 3);
    box3.setTextureRect(sf::IntRect(0, 0, 41, 69));
    obstacles.emplace_back(box3);

    sf::Sprite floor3;
    floor3.setTexture(floorTexture);
    floor3.setPosition(3000, 500);
    floor3.setTextureRect(sf::IntRect(0, 0, 246, 15));
    floor3.setScale(7, 7);
    obstacles.emplace_back(floor3);

    sf::Sprite box4;
    box4.setTexture(boxTexture);
    box4.setPosition(1000, 1431);
    box4.setScale(3, 3);
    box4.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box4);

    sf::Sprite floor4;
    floor4.setTexture(floorTexture);
    floor4.setPosition(5000, 500);
    floor4.setTextureRect(sf::IntRect(0, 0, 70, 15));
    floor4.setScale(7, 7);
    obstacles.emplace_back(floor4);

    sf::Sprite locker1;
    locker1.setTexture(lockerTexture);
    locker1.setPosition(5370, 293);
    locker1.setScale(3, 3);
    obstacles.emplace_back(locker1);

    sf::Sprite box5;
    box5.setTexture(boxTexture);
    box5.setPosition(7150, 931);
    box5.setScale(3, 3);
    box5.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box5);

    sf::Sprite locker2;
    locker2.setTexture(lockerTexture);
    locker2.setPosition(5800, 1293);
    locker2.setScale(3, 3);
    obstacles.emplace_back(locker2);

    sf::Sprite wall2;
    wall2.setTexture(floorTexture);
    wall2.setPosition(6750, 1000);
    wall2.setTextureRect(sf::IntRect(0, 0, 286, 72));
    wall2.setScale(7, 7);
    obstacles.emplace_back(wall2);

    sf::Sprite box6;
    box6.setTexture(boxTexture);
    box6.setPosition(5550, 1431);
    box6.setScale(3, 3);
    box6.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box6);

    sf::Sprite floor5;
    floor5.setTexture(floorTexture);
    floor5.setPosition(8950, 900);
    floor5.setTextureRect(sf::IntRect(0, 0, 72, 17));
    floor5.setScale(7, 7);
    obstacles.emplace_back(floor5);

    sf::Sprite locker3;
    locker3.setTexture(lockerTexture);
    locker3.setPosition(9950, 1293);
    locker3.setScale(3, 3);
    obstacles.emplace_back(locker3);

    sf::Sprite box7;
    box7.setTexture(boxTexture);
    box7.setPosition(9700, 1431);
    box7.setScale(3, 3);
    box7.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box7);

    sf::Sprite floor6;
    floor6.setTexture(floorTexture);
    floor6.setPosition(10500, 500);
    floor6.setTextureRect(sf::IntRect(0, 0, 72, 17));
    floor6.setScale(7, 7);
    obstacles.emplace_back(floor6);

    sf::Sprite box8;
    box8.setTexture(boxTexture);
    box8.setPosition(11000, 1362);
    box8.setScale(3, 3);
    box8.setTextureRect(sf::IntRect(0, 0, 41, 46));
    obstacles.emplace_back(box8);

    sf::Sprite box9;
    box9.setTexture(boxTexture);
    box9.setPosition(11250, 1224);
    box9.setScale(3, 3);
    box9.setTextureRect(sf::IntRect(0, 0, 41, 92));
    obstacles.emplace_back(box9);

    sf::Sprite wall3;
    wall3.setTexture(floorTexture);
    wall3.setPosition(12500, 500);
    wall3.setTextureRect(sf::IntRect(0, 0, 20, 142));
    wall3.setScale(7, 7);
    obstacles.emplace_back(wall3);

    sf::Sprite floor7;
    floor7.setTexture(floorTexture);
    floor7.setPosition(10500, -100);
    floor7.setTextureRect(sf::IntRect(0, 0, 285, 17));
    floor7.setScale(7, 7);
    obstacles.emplace_back(floor7);

    sf::Sprite box10;
    box10.setTexture(boxTexture);
    box10.setPosition(11000, -238);
    box10.setScale(3, 3);
    box10.setTextureRect(sf::IntRect(0, 0, 41, 46));
    obstacles.emplace_back(box10);

    sf::Sprite box11;
    box11.setTexture(boxTexture);
    box11.setPosition(11123, -169);
    box11.setScale(3, 3);
    box11.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box11);

    sf::Sprite box12;
    box12.setTexture(boxTexture);
    box12.setPosition(11373, 1362);
    box12.setScale(3, 3);
    box12.setTextureRect(sf::IntRect(0, 0, 41, 46));
    obstacles.emplace_back(box12);

    sf::Sprite floor8;
    floor8.setTexture(floorTexture);
    floor8.setPosition(12640, 1000);
    floor8.setTextureRect(sf::IntRect(0, 0, 114, 17));
    floor8.setScale(7, 7);
    obstacles.emplace_back(floor8);

    sf::Sprite locker4;
    locker4.setTexture(lockerTexture);
    locker4.setPosition(16000, 1293);
    locker4.setScale(3, 3);
    obstacles.emplace_back(locker4);

    sf::Sprite box13;
    box13.setTexture(boxTexture);
    box13.setPosition(16108, 1385);
    box13.setScale(3, 5);
    box13.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box13);

    sf::Sprite box14;
    box14.setTexture(boxTexture);
    box14.setPosition(15200, 1362);
    box14.setScale(3, 3);
    box14.setTextureRect(sf::IntRect(0, 0, 41, 46));
    obstacles.emplace_back(box14);

    sf::Sprite floor9;
    floor9.setTexture(floorTexture);
    floor9.setPosition(14500, 900);
    floor9.setTextureRect(sf::IntRect(0, 0, 71, 17));
    floor9.setScale(7, 7);
    obstacles.emplace_back(floor9);

    sf::Sprite box15;
    box15.setTexture(boxTexture);
    box15.setPosition(15480, 1155);
    box15.setScale(3, 3);
    box15.setTextureRect(sf::IntRect(0, 0, 41, 115));
    obstacles.emplace_back(box15);

    sf::Sprite box16;
    box16.setTexture(boxTexture);
    box16.setPosition(15770, 1431);
    box16.setScale(3, 3);
    box16.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box16);

    sf::Sprite floor10;
    floor10.setTexture(floorTexture);
    floor10.setPosition(16500, 700);
    floor10.setTextureRect(sf::IntRect(0, 0, 100, 17));
    floor10.setScale(7, 7);
    obstacles.emplace_back(floor10);

    sf::Sprite floor11;
    floor11.setTexture(floorTexture);
    floor11.setPosition(17460, 700);
    floor11.setTextureRect(sf::IntRect(0, 0, 214, 17));
    floor11.setScale(7, 7);
    obstacles.emplace_back(floor11);

    sf::Sprite locker5;
    locker5.setTexture(lockerTexture);
    locker5.setPosition(17800, 1293);
    locker5.setScale(3, 3);
    obstacles.emplace_back(locker5);

    sf::Sprite locker6;
    locker6.setTexture(lockerTexture);
    locker6.setPosition(16500, 493);
    locker6.setScale(3, 3);
    obstacles.emplace_back(locker6);

    sf::Sprite box17;
    box17.setTexture(boxTexture);
    box17.setPosition(20000, 1362);
    box17.setScale(3, 3);
    box17.setTextureRect(sf::IntRect(0, 0, 41, 46));
    obstacles.emplace_back(box17);

    sf::Sprite wall4;
    wall4.setTexture(floorTexture);
    wall4.setPosition(20600, 600);
    wall4.setTextureRect(sf::IntRect(0, 0, 114, 129));
    wall4.setScale(7, 7);
    obstacles.emplace_back(wall4);

    sf::Sprite floor12;
    floor12.setTexture(floorTexture);
    floor12.setPosition(24000, 1000);
    floor12.setTextureRect(sf::IntRect(0, 0, 43, 7));
    floor12.setScale(7, 7);
    obstacles.emplace_back(floor12);

    sf::Sprite floor13;
    floor13.setTexture(floorTexture);
    floor13.setPosition(24000, 500);
    floor13.setTextureRect(sf::IntRect(0, 0, 43, 7));
    floor13.setScale(7, 7);
    obstacles.emplace_back(floor13);

    sf::Sprite floor14;
    floor14.setTexture(floorTexture);
    floor14.setPosition(26000, 1000);
    floor14.setTextureRect(sf::IntRect(0, 0, 43, 7));
    floor14.setScale(7, 7);
    obstacles.emplace_back(floor14);

    sf::Sprite floor15;
    floor15.setTexture(floorTexture);
    floor15.setPosition(26000, 500);
    floor15.setTextureRect(sf::IntRect(0, 0, 43, 7));
    floor15.setScale(7, 7);
    obstacles.emplace_back(floor15);

    sf::Sprite box18;
    box18.setTexture(boxTexture);
    box18.setPosition(24177, 931);
    box18.setScale(3, 3);
    box18.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box18);

    sf::Sprite box19;
    box19.setTexture(boxTexture);
    box19.setPosition(24177, 431);
    box19.setScale(3, 3);
    box19.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box19);

    sf::Sprite box20;
    box20.setTexture(boxTexture);
    box20.setPosition(26000, 931);
    box20.setScale(3, 3);
    box20.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box20);

    sf::Sprite box21;
    box21.setTexture(boxTexture);
    box21.setPosition(26000, 431);
    box21.setScale(3, 3);
    box21.setTextureRect(sf::IntRect(0, 0, 41, 23));
    obstacles.emplace_back(box21);

    //ladder
    sf::Sprite ladder_1;
    ladder_1.setTexture(ladderTexture);
    ladder_1.setPosition(1440, 800);
    ladder_1.setTextureRect(sf::IntRect(0, 0, 20, 175));
    ladder_1.setScale(3, 4);
    ladder.emplace_back(ladder_1);

    sf::Sprite ladder_2;
    ladder_2.setTexture(ladderTexture);
    ladder_2.setPosition(2940, 500);
    ladder_2.setScale(3, 4);
    ladder_2.setTextureRect(sf::IntRect(0, 0, 20, 250));
    ladder.emplace_back(ladder_2);

    sf::Sprite ladder_3;
    ladder_3.setTexture(ladderTexture);
    ladder_3.setPosition(4722, 500);
    ladder_3.setScale(3, 4);
    ladder_3.setTextureRect(sf::IntRect(0, 0, 20, 250));
    ladder.emplace_back(ladder_3);

    sf::Sprite ladder_4;
    ladder_4.setTexture(ladderTexture);
    ladder_4.setPosition(6690, 1000);
    ladder_4.setScale(3, 4);
    ladder_4.setTextureRect(sf::IntRect(0, 0, 20, 125));
    ladder.emplace_back(ladder_4);

    sf::Sprite ladder_5;
    ladder_5.setTexture(ladderTexture);
    ladder_5.setPosition(11004, 500);
    ladder_5.setScale(3, 4);
    ladder_5.setTextureRect(sf::IntRect(0, 0, 20, 170));
    ladder.emplace_back(ladder_5);

    sf::Sprite ladder_6;
    ladder_6.setTexture(ladderTexture);
    ladder_6.setPosition(10440, -100);
    ladder_6.setScale(3, 4);
    ladder_6.setTextureRect(sf::IntRect(0, 0, 20, 150));
    ladder.emplace_back(ladder_6);

    sf::Sprite ladder_7;
    ladder_7.setTexture(ladderTexture);
    ladder_7.setPosition(14997, 900);
    ladder_7.setScale(3, 4);
    ladder_7.setTextureRect(sf::IntRect(0, 0, 20, 80));
    ladder.emplace_back(ladder_7);

    sf::Sprite ladder_8;
    ladder_8.setTexture(ladderTexture);
    ladder_8.setPosition(17200, 700);
    ladder_8.setScale(3, 4);
    ladder_8.setTextureRect(sf::IntRect(0, 0, 20, 200));
    ladder.emplace_back(ladder_8);

    sf::Sprite ladder_9;
    ladder_9.setTexture(ladderTexture);
    ladder_9.setPosition(20540, 600);
    ladder_9.setScale(3, 4);
    ladder_9.setTextureRect(sf::IntRect(0, 0, 20, 225));
    ladder.emplace_back(ladder_9);

    sf::Sprite ladder_10;
    ladder_10.setTexture(ladderTexture);
    ladder_10.setPosition(23940, 500);
    ladder_10.setScale(3, 4);
    ladder_10.setTextureRect(sf::IntRect(0, 0, 20, 250));
    ladder.emplace_back(ladder_10);

    sf::Sprite ladder_11;
    ladder_11.setTexture(ladderTexture);
    ladder_11.setPosition(26301, 500);
    ladder_11.setScale(3, 4);
    ladder_11.setTextureRect(sf::IntRect(0, 0, 20, 250));
    ladder.emplace_back(ladder_11);

    //aid kit
    sf::Sprite *aidKit_1 = new sf::Sprite;
    aidKit_1->setTexture(adiKitTexture);
    aidKit_1->setPosition(5270, 460);
    aidKit_1->setScale(4.5, 4.5);
    aidKit.emplace_back(aidKit_1);

    sf::Sprite *aidKit_2 = new sf::Sprite;
    aidKit_2->setTexture(adiKitTexture);
    aidKit_2->setPosition(10100, 1460);
    aidKit_2->setScale(4.5, 4.5);
    aidKit.emplace_back(aidKit_2);

    sf::Sprite *aidKit_3 = new sf::Sprite;
    aidKit_3->setTexture(adiKitTexture);
    aidKit_3->setPosition(12700, 1460);
    aidKit_3->setScale(4.5, 4.5);
    aidKit.emplace_back(aidKit_3);

    sf::Sprite *aidKit_4 = new sf::Sprite;
    aidKit_4->setTexture(adiKitTexture);
    aidKit_4->setPosition(16670, 660);
    aidKit_4->setScale(4.5, 4.5);
    aidKit.emplace_back(aidKit_4);

    sf::Sprite *aidKit_5 = new sf::Sprite;
    aidKit_5->setTexture(adiKitTexture);
    aidKit_5->setPosition(20750, 560);
    aidKit_5->setScale(4.5, 4.5);
    aidKit.emplace_back(aidKit_5);

    //armor vest
    sf::Sprite *armorVest_1 = new sf::Sprite;
    armorVest_1->setTexture(armorVestTexture);
    armorVest_1->setPosition(2300, 700);
    armorVest_1->setScale(3, 3);
    armorVest.emplace_back(armorVest_1);

    sf::Sprite *armorVest_2 = new sf::Sprite;
    armorVest_2->setTexture(armorVestTexture);
    armorVest_2->setPosition(8830, 1400);
    armorVest_2->setScale(3, 3);
    armorVest.emplace_back(armorVest_2);

    sf::Sprite *armorVest_3 = new sf::Sprite;
    armorVest_3->setTexture(armorVestTexture);
    armorVest_3->setPosition(13200, 900);
    armorVest_3->setScale(3, 3);
    armorVest.emplace_back(armorVest_3);

    sf::Sprite *armorVest_4 = new sf::Sprite;
    armorVest_4->setTexture(armorVestTexture);
    armorVest_4->setPosition(21000, 500);
    armorVest_4->setScale(3, 3);
    armorVest.emplace_back(armorVest_4);


    //interface
    //health
    sf::RectangleShape healthBar(sf::Vector2f(200, 10));
    healthBar.setFillColor(sf::Color::Red);

    sf::RectangleShape healthBarTopBound(sf::Vector2f(204, 2));
    healthBarTopBound.setFillColor(sf::Color::Black);

    sf::RectangleShape healthBarBottomBound(sf::Vector2f(204, 2));
    healthBarBottomBound.setFillColor(sf::Color::Black);

    sf::RectangleShape healthBarLeftBound(sf::Vector2f(2, 10));
    healthBarLeftBound.setFillColor(sf::Color::Black);

    sf::RectangleShape healthBarRightBound(sf::Vector2f(2, 10));
    healthBarRightBound.setFillColor(sf::Color::Black);

    //armor
    sf::RectangleShape armorBar(sf::Vector2f(0, 10));
    armorBar.setFillColor(sf::Color::Blue);

    sf::RectangleShape armorBarTopBound(sf::Vector2f(204, 2));
    armorBarTopBound.setFillColor(sf::Color::Black);

    sf::RectangleShape armorBarBottomBound(sf::Vector2f(204, 2));
    armorBarBottomBound.setFillColor(sf::Color::Black);

    sf::RectangleShape armorBarLeftBound(sf::Vector2f(2, 10));
    armorBarLeftBound.setFillColor(sf::Color::Black);

    sf::RectangleShape armorBarRightBound(sf::Vector2f(2, 10));
    armorBarRightBound.setFillColor(sf::Color::Black);

    sf::RectangleShape bulletNumberBackGround(sf::Vector2f(90, 38));
    bulletNumberBackGround.setFillColor(sf::Color::Black);

    //boss health
    sf::RectangleShape bossHealthBar(sf::Vector2f(1520, 20));
    bossHealthBar.setFillColor(sf::Color::Red);

    sf::RectangleShape bossHealthBarTopBound(sf::Vector2f(1524, 2));
    bossHealthBarTopBound.setFillColor(sf::Color::Black);

    sf::RectangleShape bossHealthBarBottomBound(sf::Vector2f(1524, 2));
    bossHealthBarBottomBound.setFillColor(sf::Color::Black);

    sf::RectangleShape bossHealthBarLeftBound(sf::Vector2f(2, 20));
    bossHealthBarLeftBound.setFillColor(sf::Color::Black);

    sf::RectangleShape bossHealthBarRightBound(sf::Vector2f(2, 20));
    bossHealthBarRightBound.setFillColor(sf::Color::Black);

    //GUNS*****************************************************************************************************************************************************************
    //guns parameters
    //pistol
    const int PistolGunType = 1;
    const float PistolFireRate = 35;
    const float PistolBulletSpeed = 30;
    const float PistolDamage = 20;
    const float EnemyPistolDamage = 3;
    const float PistolReloadingTime = 60;
    const int PistolMagazineCapasity = 7;
    const int PistolBulletNumber = 14;
    const int EnemyPistolBulletNumber = 7;
    const bool PistolFullauto = false;

    //machine gun
    const int MachineGunGunType = 2;
    const float MachineGunFireRate = 8;
    const float MachineGunBulletSpeed = 50;
    const float MachineGunDamage = 12;
    const float EnemyMachineGunlDamage = 4;
    const float MachineGunReloadingTime = 160;
    const int MachineGunMagazineCapasity = 30;
    const int MachineGunBulletNumber = 30;
    const int EnemyMachineGunBulletNumber = 15;
    const bool MachineGunFullauto = true;

    //machine gun 2
    const int MachineGun_v2GunType = 3;
    const float MachineGun_v2FireRate = 12;
    const float MachineGun_v2BulletSpeed = 65;
    const float MachineGun_v2Damage = 20;
    const float EnemyMachineGun_v2Damage = 6;
    const float MachineGun_v2ReloadingTime = 300;
    const int MachineGun_v2MagazineCapasity = 36;
    const int MachineGun_v2BulletNumber = 36;
    const int EnemyMachineGun_v2BulletNumber = 18;
    const bool MachineGun_v2Fullauto = true;

    //hero's guns
    //pistol
    Gun heroPistol(PistolGunType, PistolFireRate, PistolBulletSpeed, PistolDamage, PistolReloadingTime, PistolMagazineCapasity, PistolBulletNumber, PistolFullauto);
    heroPistol.setTexture(pistolTexture);
    heroPistol.setScale(4, 4);

    //machine gun
    Gun heroMachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, MachineGunDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, MachineGunBulletNumber, MachineGunFullauto);
    heroMachineGun.setTexture(machineGunTexture);
    heroMachineGun.setScale(6, 6);

    //machine gun 2
    Gun heroMachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, MachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, MachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    heroMachineGun_v2.setTexture(machineGun_v2Texture);
    heroMachineGun_v2.setScale(6, 6);

    //enemy's guns
    //enemy_1
    Gun enemy_1Pistol(PistolGunType, PistolFireRate, PistolBulletSpeed, EnemyPistolDamage, PistolReloadingTime, PistolMagazineCapasity, EnemyPistolBulletNumber, PistolFullauto);
    enemy_1Pistol.setTexture(pistolTexture);
    enemy_1Pistol.setScale(4, 4);

    //enemy_2
    Gun enemy_2Pistol(PistolGunType, PistolFireRate, PistolBulletSpeed, EnemyPistolDamage, PistolReloadingTime, PistolMagazineCapasity, EnemyPistolBulletNumber, PistolFullauto);
    enemy_2Pistol.setTexture(pistolTexture);
    enemy_2Pistol.setScale(4, 4);

    //enemy_3
    Gun enemy_3MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, EnemyMachineGunBulletNumber, MachineGunFullauto);
    enemy_3MachineGun.setTexture(machineGunTexture);
    enemy_3MachineGun.setScale(6, 6);

    //enemy_4
    Gun enemy_4MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, EnemyMachineGunBulletNumber, MachineGunFullauto);
    enemy_4MachineGun.setTexture(machineGunTexture);
    enemy_4MachineGun.setScale(6, 6);

    //enemy_5
    Gun enemy_5MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, EnemyMachineGunBulletNumber, MachineGunFullauto);
    enemy_5MachineGun.setTexture(machineGunTexture);
    enemy_5MachineGun.setScale(6, 6);

    //enemy_6
    Gun enemy_6Pistol(PistolGunType, PistolFireRate, PistolBulletSpeed, EnemyPistolDamage, PistolReloadingTime, PistolMagazineCapasity, EnemyPistolBulletNumber, PistolFullauto);
    enemy_6Pistol.setTexture(pistolTexture);
    enemy_6Pistol.setScale(4, 4);

    //enemy_7
    Gun enemy_7MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, EnemyMachineGunBulletNumber, MachineGunFullauto);
    enemy_7MachineGun.setTexture(machineGunTexture);
    enemy_7MachineGun.setScale(6, 6);

    //enemy_8
    Gun enemy_8Pistol(PistolGunType, PistolFireRate, PistolBulletSpeed, EnemyPistolDamage, PistolReloadingTime, PistolMagazineCapasity, EnemyPistolBulletNumber, PistolFullauto);
    enemy_8Pistol.setTexture(pistolTexture);
    enemy_8Pistol.setScale(4, 4);

    //enemy_9
    Gun enemy_9MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, EnemyMachineGunBulletNumber, MachineGunFullauto);
    enemy_9MachineGun.setTexture(machineGunTexture);
    enemy_9MachineGun.setScale(6, 6);

    //enemy_10
    Gun enemy_10MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_10MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_10MachineGun_v2.setScale(6, 6);

    //enemy_11
    Gun enemy_11MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_11MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_11MachineGun_v2.setScale(6, 6);

    //enemy_12
    Gun enemy_12Pistol(PistolGunType, PistolFireRate, PistolBulletSpeed, EnemyPistolDamage, PistolReloadingTime, PistolMagazineCapasity, EnemyPistolBulletNumber, PistolFullauto);
    enemy_12Pistol.setTexture(pistolTexture);
    enemy_12Pistol.setScale(4, 4);

    //enemy_13
    Gun enemy_13MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, EnemyMachineGunBulletNumber, MachineGunFullauto);
    enemy_13MachineGun.setTexture(machineGunTexture);
    enemy_13MachineGun.setScale(6, 6);

    //enemy_14
    Gun enemy_14MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_14MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_14MachineGun_v2.setScale(6, 6);

    //enemy_15
    Gun enemy_15MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, EnemyMachineGunBulletNumber, MachineGunFullauto);
    enemy_15MachineGun.setTexture(machineGunTexture);
    enemy_15MachineGun.setScale(6, 6);

    //enemy_16
    Gun enemy_16MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_16MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_16MachineGun_v2.setScale(6, 6);

    //enemy_17
    Gun enemy_17Pistol(PistolGunType, PistolFireRate, PistolBulletSpeed, EnemyPistolDamage, PistolReloadingTime, PistolMagazineCapasity, EnemyPistolBulletNumber, PistolFullauto);
    enemy_17Pistol.setTexture(pistolTexture);
    enemy_17Pistol.setScale(4, 4);

    //enemy_18
    Gun enemy_18MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_18MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_18MachineGun_v2.setScale(6, 6);

    //enemy_19
    Gun enemy_19MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_19MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_19MachineGun_v2.setScale(6, 6);

    //enemy_20
    Gun enemy_20MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_20MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_20MachineGun_v2.setScale(6, 6);

    //enemy_21
    Gun enemy_21MachineGun_v2(MachineGun_v2GunType, MachineGun_v2FireRate, MachineGun_v2BulletSpeed, EnemyMachineGun_v2Damage, MachineGun_v2ReloadingTime, MachineGun_v2MagazineCapasity, EnemyMachineGun_v2BulletNumber, MachineGun_v2Fullauto);
    enemy_21MachineGun_v2.setTexture(machineGun_v2Texture);
    enemy_21MachineGun_v2.setScale(6, 6);

    //CHARAKTERS*****************************************************************************************************************************************************************
    const sf::Vector2i textureLayout(7, 4);
    const sf::Vector2i textureSize(45 ,70);

    //hero start parameters
    const sf::Vector2f heroStartPosition(0, 1400);

    //hero
    Hero hero(heroStartPosition, heroTexturePistol, textureLayout, textureSize);
    hero.setScale(3, 3);
    Gun *gun;
    gun = &heroPistol;

    //aid kit and vest patameters
    float addedHealth = 50;
    float addedArmor = 50;

    //LEVEL
    float enemyHealthMultipler = 1;
    float enemyDamageMultipler = 1;
    float damageMultipler = 1;
    std::fstream lvl;
    lvl.open(path "/config/level_of_difficulty.txt", std::ios::in);
    std::string level;
    std::string line;
    int lineCounter = 1;
    while (std::getline(lvl, line))
    {
        switch (lineCounter)
        {
        case 3:
            level = line;
            break;
        }
        lineCounter++;
    }
    lvl.close();

    if (level == "easy")
    {
        hero.setMaxHealth(hero.getMaxHealth() * 1.2);
        hero.setMaxArmor(hero.getMaxArmor() * 1.2);
        hero.setArmor(hero.getMaxArmor() * 0.3);
        enemyHealthMultipler = 0.8;
        enemyDamageMultipler = 0.8;
        damageMultipler = 1.2;
        addedHealth *= 1.2;
        addedArmor *= 1.2;
    }
    else if (level == "hard")
    {
        hero.setMaxHealth(hero.getMaxHealth() * 0.8);
        hero.setMaxArmor(hero.getMaxArmor() * 0.8);
        enemyHealthMultipler = 1.2;
        enemyDamageMultipler = 1.2;
        damageMultipler = 0.8;
        addedHealth *= 0.5;
        addedArmor *= 0.5;
    }

    //enemies
    //enemy_1 start parameters
    const sf::Vector2f enemy_1StartPosition(1200, 1200);
    const bool enemy_1_is_walking = false;
    const bool enemy_1_orientated_right = false;
    const float enemy_1Speed = 200;
    const float enemy_1Health = 100 * enemyHealthMultipler;
    const int enemy_1GunType = 1;
    const float enemy_1DetectedDistanceX = 600;
    const float enemy_1DetectedDistanceY = 300;

    //enemy_1
    Enemy *enemy_1 = new Enemy(enemy_1StartPosition, enemyTexturePistol, textureLayout, textureSize, enemy_1_is_walking, enemy_1_orientated_right,
                               enemy_1Speed, enemy_1Health, enemy_1GunType, enemy_1DetectedDistanceX, enemy_1DetectedDistanceY, obstacles);
    enemy_1->setScale(3, 3);
    EnemyVector.push_back(enemy_1);
    Gun *enemy1Gun;
    enemy1Gun = &enemy_1Pistol;
    EnemyGun.push_back(enemy1Gun);
    enemyFireRate.push_back(1);

    //enemy_2 start parameters
    const sf::Vector2f enemy_2StartPosition(1600, 590);
    const bool enemy_2_is_walking = true;
    const bool enemy_2_orientated_right = true;
    const float enemy_2Speed = 200;
    const float enemy_2Health = 100 * enemyHealthMultipler;
    const int enemy_2GunType = 1;
    const float enemy_2DetectedDistanceX = 400;
    const float enemy_2DetectedDistanceY = 200;

    //enemy_2
    Enemy *enemy_2 = new Enemy(enemy_2StartPosition, enemyTexturePistol, textureLayout, textureSize, enemy_2_is_walking, enemy_2_orientated_right,
                               enemy_2Speed, enemy_2Health, enemy_2GunType, enemy_2DetectedDistanceX, enemy_2DetectedDistanceY, obstacles);
    enemy_2->setScale(3, 3);
    EnemyVector.push_back(enemy_2);
    Gun *enemy2Gun;
    enemy2Gun = &enemy_2Pistol;
    EnemyGun.push_back(enemy2Gun);
    enemyFireRate.push_back(1);

    //enemy_3 start parameters
    const sf::Vector2f enemy_3StartPosition(3800, 290);
    const bool enemy_3_is_walking = true;
    const bool enemy_3_orientated_right = false;
    const float enemy_3Speed = 200;
    const float enemy_3Health = 100 * enemyHealthMultipler;
    const int enemy_3GunType = 2;
    const float enemy_3DetectedDistanceX = 800;
    const float enemy_3DetectedDistanceY = 300;

    //enemy_3
    Enemy *enemy_3 = new Enemy(enemy_3StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_3_is_walking, enemy_3_orientated_right,
                               enemy_3Speed, enemy_3Health, enemy_3GunType, enemy_3DetectedDistanceX, enemy_3DetectedDistanceY, obstacles);
    enemy_3->setScale(3, 3);
    EnemyVector.push_back(enemy_3);
    Gun *enemy3Gun;
    enemy3Gun = &enemy_3MachineGun;
    EnemyGun.push_back(enemy3Gun);
    enemyFireRate.push_back(1);

    //enemy_4 start parameters
    const sf::Vector2f enemy_4StartPosition(4500, 1490);
    const bool enemy_4_is_walking = false;
    const bool enemy_4_orientated_right = false;
    const float enemy_4Speed = 200;
    const float enemy_4Health = 100 * enemyHealthMultipler;
    const int enemy_4GunType = 2;
    const float enemy_4DetectedDistanceX = 3000;
    const float enemy_4DetectedDistanceY = 3000;

    //enemy_4
    Enemy *enemy_4 = new Enemy(enemy_4StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_4_is_walking, enemy_4_orientated_right,
                               enemy_4Speed, enemy_4Health, enemy_4GunType, enemy_4DetectedDistanceX, enemy_4DetectedDistanceY, obstacles);
    enemy_4->setScale(3, 3);
    EnemyVector.push_back(enemy_4);
    Gun *enemy4Gun;
    enemy4Gun = &enemy_4MachineGun;
    EnemyGun.push_back(enemy4Gun);
    enemyFireRate.push_back(1);

    //enemy_5 start parameters
    const sf::Vector2f enemy_5StartPosition(6000, 1490);
    const bool enemy_5_is_walking = true;
    const bool enemy_5_orientated_right = false;
    const float enemy_5Speed = 200;
    const float enemy_5Health = 100 * enemyHealthMultipler;
    const int enemy_5GunType = 2;
    const float enemy_5DetectedDistanceX = 600;
    const float enemy_5DetectedDistanceY = 600;

    //enemy_5
    Enemy *enemy_5  = new Enemy(enemy_5StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_5_is_walking, enemy_5_orientated_right,
                               enemy_5Speed, enemy_5Health, enemy_5GunType, enemy_5DetectedDistanceX, enemy_5DetectedDistanceY, obstacles);
    enemy_5->setScale(3, 3);
    EnemyVector.push_back(enemy_5);
    Gun *enemy5Gun;
    enemy5Gun = &enemy_5MachineGun;
    EnemyGun.push_back(enemy5Gun);
    enemyFireRate.push_back(1);

    //enemy_6 start parameters
    const sf::Vector2f enemy_6StartPosition(7200, 1010);
    const bool enemy_6_is_walking = false;
    const bool enemy_6_orientated_right = false;
    const float enemy_6Speed = 200;
    const float enemy_6Health = 100 * enemyHealthMultipler;
    const int enemy_6GunType = 1;
    const float enemy_6DetectedDistanceX = 2000;
    const float enemy_6DetectedDistanceY = 800;

    //enemy_6
    Enemy *enemy_6 = new Enemy(enemy_6StartPosition, enemyTexturePistol, textureLayout, textureSize, enemy_6_is_walking, enemy_6_orientated_right,
                               enemy_6Speed, enemy_6Health, enemy_6GunType, enemy_6DetectedDistanceX, enemy_6DetectedDistanceY, obstacles);
    enemy_6->setScale(3, 3);
    EnemyVector.push_back(enemy_6);
    Gun *enemy6Gun;
    enemy6Gun = &enemy_6Pistol;
    EnemyGun.push_back(enemy6Gun);
    enemyFireRate.push_back(1);

    //enemy_7 start parameters
    const sf::Vector2f enemy_7StartPosition(9500, 1490);
    const bool enemy_7_is_walking = false;
    const bool enemy_7_orientated_right = false;
    const float enemy_7Speed = 200;
    const float enemy_7Health = 100 * enemyHealthMultipler;
    const int enemy_7GunType = 2;
    const float enemy_7DetectedDistanceX = 1000;
    const float enemy_7DetectedDistanceY = 200;

    //enemy_7
    Enemy *enemy_7  = new Enemy(enemy_7StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_7_is_walking, enemy_7_orientated_right,
                               enemy_7Speed, enemy_7Health, enemy_7GunType, enemy_7DetectedDistanceX, enemy_7DetectedDistanceY, obstacles);
    enemy_7->setScale(3, 3);
    EnemyVector.push_back(enemy_7);
    Gun *enemy7Gun;
    enemy7Gun = &enemy_7MachineGun;
    EnemyGun.push_back(enemy7Gun);
    enemyFireRate.push_back(1);

    //enemy_8 start parameters
    const sf::Vector2f enemy_8StartPosition(11875, 1490);
    const bool enemy_8_is_walking = true;
    const bool enemy_8_orientated_right = false;
    const float enemy_8Speed = 200;
    const float enemy_8Health = 100 * enemyHealthMultipler;
    const int enemy_8GunType = 1;
    const float enemy_8DetectedDistanceX = 600;
    const float enemy_8DetectedDistanceY = 100;

    //enemy_8
    Enemy *enemy_8 = new Enemy(enemy_8StartPosition, enemyTexturePistol, textureLayout, textureSize, enemy_8_is_walking, enemy_8_orientated_right,
                               enemy_8Speed, enemy_8Health, enemy_8GunType, enemy_8DetectedDistanceX, enemy_8DetectedDistanceY, obstacles);
    enemy_8->setScale(3, 3);
    EnemyVector.push_back(enemy_8);
    Gun *enemy8Gun;
    enemy8Gun = &enemy_8Pistol;
    EnemyGun.push_back(enemy8Gun);
    enemyFireRate.push_back(1);

    //enemy_9 start parameters
    const sf::Vector2f enemy_9StartPosition(10700, 520);
    const bool enemy_9_is_walking = false;
    const bool enemy_9_orientated_right = true;
    const float enemy_9Speed = 200;
    const float enemy_9Health = 100 * enemyHealthMultipler;
    const int enemy_9GunType = 2;
    const float enemy_9DetectedDistanceX = 1000;
    const float enemy_9DetectedDistanceY = 700;

    //enemy_9
    Enemy *enemy_9  = new Enemy(enemy_9StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_9_is_walking, enemy_9_orientated_right,
                               enemy_9Speed, enemy_9Health, enemy_9GunType, enemy_9DetectedDistanceX, enemy_9DetectedDistanceY, obstacles);
    enemy_9->setScale(3, 3);
    EnemyVector.push_back(enemy_9);
    Gun *enemy9Gun;
    enemy9Gun = &enemy_9MachineGun;
    EnemyGun.push_back(enemy9Gun);
    enemyFireRate.push_back(1);

    //enemy_10 start parameters
    const sf::Vector2f enemy_10StartPosition(11500, -200);
    const bool enemy_10_is_walking = false;
    const bool enemy_10_orientated_right = false;
    const float enemy_10Speed = 200;
    const float enemy_10Health = 100 * enemyHealthMultipler;
    const int enemy_10GunType = 3;
    const float enemy_10DetectedDistanceX = 1000;
    const float enemy_10DetectedDistanceY = 800;

    //enemy_10
    Enemy *enemy_10  = new Enemy(enemy_10StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_10_is_walking, enemy_10_orientated_right,
                               enemy_10Speed, enemy_10Health, enemy_10GunType, enemy_10DetectedDistanceX, enemy_10DetectedDistanceY, obstacles);
    enemy_10->setScale(3, 3);
    EnemyVector.push_back(enemy_10);
    Gun *enemy10Gun;
    enemy10Gun = &enemy_10MachineGun_v2;
    EnemyGun.push_back(enemy10Gun);
    enemyFireRate.push_back(1);

    //enemy_11 start parameters
    const sf::Vector2f enemy_11StartPosition(12750, 400);
    const bool enemy_11_is_walking = false;
    const bool enemy_11_orientated_right = false;
    const float enemy_11Speed = 200;
    const float enemy_11Health = 100 * enemyHealthMultipler;
    const int enemy_11GunType = 3;
    const float enemy_11DetectedDistanceX = 1000;
    const float enemy_11DetectedDistanceY = 800;

    //enemy_11
    Enemy *enemy_11  = new Enemy(enemy_11StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_11_is_walking, enemy_11_orientated_right,
                               enemy_11Speed, enemy_11Health, enemy_11GunType, enemy_11DetectedDistanceX, enemy_11DetectedDistanceY, obstacles);
    enemy_11->setScale(3, 3);
    EnemyVector.push_back(enemy_11);
    Gun *enemy11Gun;
    enemy11Gun = &enemy_11MachineGun_v2;
    EnemyGun.push_back(enemy11Gun);
    enemyFireRate.push_back(1);

    //enemy_12 start parameters
    const sf::Vector2f enemy_12StartPosition(13750, 1490);
    const bool enemy_12_is_walking = true;
    const bool enemy_12_orientated_right = true;
    const float enemy_12Speed = 200;
    const float enemy_12Health = 100 * enemyHealthMultipler;
    const int enemy_12GunType = 1;
    const float enemy_12DetectedDistanceX = 800;
    const float enemy_12DetectedDistanceY = 800;

    //enemy_12
    Enemy *enemy_12 = new Enemy(enemy_12StartPosition, enemyTexturePistol, textureLayout, textureSize, enemy_12_is_walking, enemy_12_orientated_right,
                               enemy_12Speed, enemy_12Health, enemy_12GunType, enemy_12DetectedDistanceX, enemy_12DetectedDistanceY, obstacles);
    enemy_12->setScale(3, 3);
    EnemyVector.push_back(enemy_12);
    Gun *enemy12Gun;
    enemy12Gun = &enemy_12Pistol;
    EnemyGun.push_back(enemy12Gun);
    enemyFireRate.push_back(1);

    //enemy_13 start parameters
    const sf::Vector2f enemy_13StartPosition(15000, 1490);
    const bool enemy_13_is_walking = false;
    const bool enemy_13_orientated_right = false;
    const float enemy_13Speed = 200;
    const float enemy_13Health = 100 * enemyHealthMultipler;
    const int enemy_13GunType = 2;
    const float enemy_13DetectedDistanceX = 1500;
    const float enemy_13DetectedDistanceY = 700;

    //enemy_13
    Enemy *enemy_13  = new Enemy(enemy_13StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_13_is_walking, enemy_13_orientated_right,
                               enemy_13Speed, enemy_13Health, enemy_13GunType, enemy_13DetectedDistanceX, enemy_13DetectedDistanceY, obstacles);
    enemy_13->setScale(3, 3);
    EnemyVector.push_back(enemy_13);
    Gun *enemy13Gun;
    enemy13Gun = &enemy_13MachineGun;
    EnemyGun.push_back(enemy13Gun);
    enemyFireRate.push_back(1);

    //enemy_14 start parameters
    const sf::Vector2f enemy_14StartPosition(16108, 1400);
    const bool enemy_14_is_walking = false;
    const bool enemy_14_orientated_right = false;
    const float enemy_14Speed = 0;
    const float enemy_14Health = 100 * enemyHealthMultipler;
    const int enemy_14GunType = 3;
    const float enemy_14DetectedDistanceX = 3000;
    const float enemy_14DetectedDistanceY = 800;

    //enemy_14
    Enemy *enemy_14  = new Enemy(enemy_14StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_14_is_walking, enemy_14_orientated_right,
                               enemy_14Speed, enemy_14Health, enemy_14GunType, enemy_14DetectedDistanceX, enemy_14DetectedDistanceY, obstacles);
    enemy_14->setScale(3, 3);
    EnemyVector.push_back(enemy_14);
    Gun *enemy14Gun;
    enemy14Gun = &enemy_14MachineGun_v2;
    EnemyGun.push_back(enemy14Gun);
    enemyFireRate.push_back(1);

    //enemy_15 start parameters
    const sf::Vector2f enemy_15StartPosition(16700, 600);
    const bool enemy_15_is_walking = false;
    const bool enemy_15_orientated_right = true;
    const float enemy_15Speed = 200;
    const float enemy_15Health = 100 * enemyHealthMultipler;
    const int enemy_15GunType = 2;
    const float enemy_15DetectedDistanceX = 900;
    const float enemy_15DetectedDistanceY = 400;

    //enemy_15
    Enemy *enemy_15  = new Enemy(enemy_15StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_15_is_walking, enemy_15_orientated_right,
                               enemy_15Speed, enemy_15Health, enemy_15GunType, enemy_15DetectedDistanceX, enemy_15DetectedDistanceY, obstacles);
    enemy_15->setScale(3, 3);
    EnemyVector.push_back(enemy_15);
    Gun *enemy15Gun;
    enemy15Gun = &enemy_15MachineGun;
    EnemyGun.push_back(enemy15Gun);
    enemyFireRate.push_back(1);

    //enemy_16 start parameters
    const sf::Vector2f enemy_16StartPosition(17300, 600);
    const bool enemy_16_is_walking = true;
    const bool enemy_16_orientated_right = true;
    const float enemy_16Speed = 200;
    const float enemy_16Health = 100 * enemyHealthMultipler;
    const int enemy_16GunType = 3;
    const float enemy_16DetectedDistanceX = 900;
    const float enemy_16DetectedDistanceY = 400;

    //enemy_16
    Enemy *enemy_16  = new Enemy(enemy_16StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_16_is_walking, enemy_16_orientated_right,
                               enemy_16Speed, enemy_16Health, enemy_16GunType, enemy_16DetectedDistanceX, enemy_16DetectedDistanceY, obstacles);
    enemy_16->setScale(3, 3);
    EnemyVector.push_back(enemy_16);
    Gun *enemy16Gun;
    enemy16Gun = &enemy_16MachineGun_v2;
    EnemyGun.push_back(enemy16Gun);
    enemyFireRate.push_back(1);

    //enemy_17 start parameters
    const sf::Vector2f enemy_17StartPosition(17280, 1490);
    const bool enemy_17_is_walking = false;
    const bool enemy_17_orientated_right = true;
    const float enemy_17Speed = 200;
    const float enemy_17Health = 100 * enemyHealthMultipler;
    const int enemy_17GunType = 1;
    const float enemy_17DetectedDistanceX = 800;
    const float enemy_17DetectedDistanceY = 800;

    //enemy_17
    Enemy *enemy_17 = new Enemy(enemy_17StartPosition, enemyTexturePistol, textureLayout, textureSize, enemy_17_is_walking, enemy_17_orientated_right,
                               enemy_17Speed, enemy_17Health, enemy_17GunType, enemy_17DetectedDistanceX, enemy_17DetectedDistanceY, obstacles);
    enemy_17->setScale(3, 3);
    EnemyVector.push_back(enemy_17);
    Gun *enemy17Gun;
    enemy17Gun = &enemy_17Pistol;
    EnemyGun.push_back(enemy17Gun);
    enemyFireRate.push_back(1);

    //enemy_18 start parameters
    const sf::Vector2f enemy_18StartPosition(20000, 1490);
    const bool enemy_18_is_walking = true;
    const bool enemy_18_orientated_right = false;
    const float enemy_18Speed = 200;
    const float enemy_18Health = 100 * enemyHealthMultipler;
    const int enemy_18GunType = 3;
    const float enemy_18DetectedDistanceX = 1000;
    const float enemy_18DetectedDistanceY = 300;

    //enemy_18
    Enemy *enemy_18  = new Enemy(enemy_18StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_18_is_walking, enemy_18_orientated_right,
                               enemy_18Speed, enemy_18Health, enemy_18GunType, enemy_18DetectedDistanceX, enemy_18DetectedDistanceY, obstacles);
    enemy_18->setScale(3, 3);
    EnemyVector.push_back(enemy_18);
    Gun *enemy18Gun;
    enemy18Gun = &enemy_18MachineGun_v2;
    EnemyGun.push_back(enemy18Gun);
    enemyFireRate.push_back(1);

    //enemy_19 start parameters
    const sf::Vector2f enemy_19StartPosition(19400, 1490);
    const bool enemy_19_is_walking = true;
    const bool enemy_19_orientated_right = true;
    const float enemy_19Speed = 200;
    const float enemy_19Health = 100 * enemyHealthMultipler;
    const int enemy_19GunType = 3;
    const float enemy_19DetectedDistanceX = 1000;
    const float enemy_19DetectedDistanceY = 300;

    //enemy_19
    Enemy *enemy_19  = new Enemy(enemy_19StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_19_is_walking, enemy_19_orientated_right,
                               enemy_19Speed, enemy_19Health, enemy_19GunType, enemy_19DetectedDistanceX, enemy_19DetectedDistanceY, obstacles);
    enemy_19->setScale(3, 3);
    EnemyVector.push_back(enemy_19);
    Gun *enemy19Gun;
    enemy19Gun = &enemy_19MachineGun_v2;
    EnemyGun.push_back(enemy19Gun);
    enemyFireRate.push_back(1);

    //enemy_20 start parameters
    const sf::Vector2f enemy_20StartPosition(20900, 500);
    const bool enemy_20_is_walking = false;
    const bool enemy_20_orientated_right = false;
    const float enemy_20Speed = 200;
    const float enemy_20Health = 100 * enemyHealthMultipler;
    const int enemy_20GunType = 3;
    const float enemy_20DetectedDistanceX = 700;
    const float enemy_20DetectedDistanceY = 400;

    //enemy_20
    Enemy *enemy_20  = new Enemy(enemy_20StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_20_is_walking, enemy_20_orientated_right,
                               enemy_20Speed, enemy_20Health, enemy_20GunType, enemy_20DetectedDistanceX, enemy_20DetectedDistanceY, obstacles);
    enemy_20->setScale(3, 3);
    EnemyVector.push_back(enemy_20);
    Gun *enemy20Gun;
    enemy20Gun = &enemy_20MachineGun_v2;
    EnemyGun.push_back(enemy20Gun);
    enemyFireRate.push_back(1);

    //enemy_21 start parameters
    const sf::Vector2f enemy_21StartPosition(25000, 1400);
    const bool enemy_21_is_walking = false;
    const bool enemy_21_orientated_right = false;
    const float enemy_21Speed = 250;
    const float enemy_21Health = 2000 * enemyHealthMultipler;
    const int enemy_21GunType = 3;
    const float enemy_21DetectedDistanceX = 2000;
    const float enemy_21DetectedDistanceY = 2000;

    //enemy_21
    Enemy *enemy_21  = new Enemy(enemy_21StartPosition, enemyTextureMachineGun_v2, textureLayout, textureSize, enemy_21_is_walking, enemy_21_orientated_right,
                               enemy_21Speed, enemy_21Health, enemy_21GunType, enemy_21DetectedDistanceX, enemy_21DetectedDistanceY, obstacles);
    enemy_21->setScale(6, 6);
    EnemyVector.push_back(enemy_21);
    Gun *enemy21Gun;
    enemy21Gun = &enemy_21MachineGun_v2;
    EnemyGun.push_back(enemy21Gun);
    enemyFireRate.push_back(1);

    //drop
    Drop *drop;

    //clock
    sf::Clock clock;

    //needed varibles
    bool machineGun_enable = false;
    bool machineGun_v2_enable = false;
    bool heroReload = false;
    bool lying_flag = true;
    bool dead = false;
    bool boss_fight = false;
    bool one = true;
    int downTime = 1;
    int frameAdd = 0;
    int frameOffset = 0;
    float fireRate = 1;

    //LOADING CONFIG DATA*****************************************************************************************************************************************************************
    std::fstream config;
    config.open(path "/config/config.txt", std::ios::in);
    lineCounter = 1;
    while (std::getline(config, line))
    {
        switch (lineCounter)
        {
        case 3:
            hero.setMaxHealth(std::stof(line));
            break;
        case 5:
            hero.setArmor(std::stof(line));
            break;
        case 7:
            heroPistol.setBulletNumber(std::stoi(line));
            break;
        case 9:
            if (line == "yes")
            {
                machineGun_enable = true;
                machineGun_v2_enable = true;
            }
            break;
        case 11:
            addedHealth = std::stof(line);
            break;
        case 13:
            addedArmor = std::stof(line);
            break;
        case 15:
            hero.setMaxSpeed(std::stof(line));
            break;
        case 17:
            hero.setFloorOffset(std::stoi(line));
            break;
        }
        lineCounter++;
    }
    config.close();

    //start health points
    hero.setHealth(hero.getMaxHealth());

    //MENU*****************************************************************************************************************************************************************
    sf::RectangleShape button_1(sf::Vector2f(200, 67));
    button_1.setPosition(100, 270);
    button_1.setFillColor(sf::Color::Red);

    sf::RectangleShape button_2(sf::Vector2f(200, 67));
    button_2.setPosition(100, 400);
    button_2.setFillColor(sf::Color::Red);

    sf::Text startText("START", font);
    startText.setCharacterSize(28);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(160, 287);

    sf::Text quitText("QUIT", font);
    quitText.setCharacterSize(28);
    quitText.setFillColor(sf::Color::Black);
    quitText.setPosition(165, 417);

    sf::Text titleText("EPIC FINAL ULTIMATE SHOOTER", font);
    titleText.setCharacterSize(40);
    titleText.setFillColor(sf::Color::Black);
    titleText.setPosition(175, 50);


    //menu window
    int menuWidth = 960;
    int menuHeight = 540;
    sf::RenderWindow menu(sf::VideoMode(menuWidth, menuHeight), "Epic Final Ultimate Shooter");
    menu.setFramerateLimit(60);

    bool pressed = false;

    while (menu.isOpen())
    {
        //EVENTS
        sf::Event event;

        while(menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                menu.close();
                exit(0);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                pressed = true;
            }

            //LOGIC
            if(button_1.getGlobalBounds().contains(sf::Mouse::getPosition(menu).x, sf::Mouse::getPosition(menu).y) && pressed)
            {
                    menu.close();
            }
            if(button_2.getGlobalBounds().contains(sf::Mouse::getPosition(menu).x, sf::Mouse::getPosition(menu).y) && pressed)
            {
                    menu.close();
                    exit(0);
            }
            pressed = false;

            //DISPLAY
            menu.clear(sf::Color::Yellow);

            menu.draw(titleText);
            menu.draw(button_1);
            menu.draw(button_2);
            menu.draw(startText);
            menu.draw(quitText);

            menu.display();
        }
    }

    //main window
    int windowWidth = 1920;
    int windowHeight = 1080;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Epic Final Ultimate Shooter", sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    //camera
    sf::View camera;
    camera.setSize(windowWidth, windowHeight);

    //frame limit
    window.setFramerateLimit(60);

    //MAIN LOOP###################################################################################################################################################################
    while (window.isOpen())
    {
        //EVENTS###################################################################################################################################################################

        sf::Event event;

        while(window.pollEvent(event))
        {
            //ESC
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            //SPACE
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (hero.is_on_floor_ == true))
            {
                hero.setSpeedUp(-720);
                hero.move_up = true;
            }
            //D
            if (!hero.lying && !hero.rise_up)
            {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                hero.move_forward = true;
                hero.move_backward = false;
                hero.oriented_right = true;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                hero.move_forward = false;
                hero.oriented_right = true;
                hero.setSpeed(0);
                hero.setTextureRect(hero.frames[0]);
            }
            //A
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                hero.move_backward = true;
                hero.move_forward = false;
                hero.oriented_right = false;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::A && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                hero.move_backward = false;
                hero.oriented_right = false;
                hero.setSpeed(0);
                hero.setTextureRect(hero.frames[7]);
            }
            //W
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                hero.move_forward = false;
                hero.move_backward = false;
                hero.is_climbing_up = true;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::W && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                hero.is_climbing_up = false;
            }
            //S
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                hero.move_forward = false;
                hero.move_backward = false;
                hero.is_climbing_down = true;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S && !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                hero.is_climbing_down = false;
            }
            }
            //R
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            {
                if (gun->getLeftInMagazine() != gun->getMagazineCapasity() && gun->getBulletNumber() > 0)
                {
                    if (gun == &heroPistol)
                    {
                        pistolReloadSound.play();
                    }
                    if (gun == &heroMachineGun)
                    {
                        machineGunReloadSound.play();
                    }
                    if (gun == &heroMachineGun_v2)
                    {
                        machineGun_v2ReloadSound.play();
                    }
                }
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
            {
                if (gun->getBulletNumber() + gun->getLeftInMagazine() >= gun->getMagazineCapasity())
                {
                    gun->setBulletNumber(gun->getBulletNumber() - (gun->getMagazineCapasity() - gun->getLeftInMagazine()));
                    gun->setLeftInMagazine(gun->getMagazineCapasity());
                }
                else
                {
                    gun->setLeftInMagazine(gun->getBulletNumber() + gun->getLeftInMagazine());
                    gun->setBulletNumber(0);
                }
                hero.is_shooting = false;
                heroReload = true;
            }
            if (gun->getCurretnReloadingTime() == 0)
            {
                //1
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                {
                    gun = &heroPistol;
                    heroPistol.setCurrettReloadingTime(0);
                    hero.is_shooting = false;
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTexturePistol, textureLayout, textureSize);
                }
                //2
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && machineGun_enable)
                {
                    gun = &heroMachineGun;
                    heroMachineGun.setCurrettReloadingTime(0);
                    hero.is_shooting = false;
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTextureMachineGun, textureLayout, textureSize);
                }
                //3
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && machineGun_v2_enable)
                {
                    gun = &heroMachineGun_v2;
                    heroMachineGun_v2.setCurrettReloadingTime(0);
                    hero.is_shooting = false;
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTextureMachineGun_v2, textureLayout, textureSize);
                }
            }
            //LSHIFT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !hero.lying && hero.is_on_floor_)
            {
                if (gun == &heroPistol)
                {
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTextureLyingPistol, sf::Vector2i(5, 2), sf::Vector2i(72, 70));
                }
                if (gun == &heroMachineGun)
                {
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTextureLyingMachineGun, sf::Vector2i(5, 2), sf::Vector2i(72, 70));
                }
                if (gun == &heroMachineGun_v2)
                {
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTextureLyingMachineGun_v2, sf::Vector2i(5, 2), sf::Vector2i(72, 70));
                }
                hero.lying = true;
                hero.rise_up = false;
                hero.move_backward = false;
                hero.move_forward = false;
                hero.frame_ = 0;
                if (hero.oriented_right)
                {
                    frameAdd = 0;
                    frameOffset = 0;
                }
                if (!hero.oriented_right)
                {
                    frameAdd = 5;
                    frameOffset = 70;
                }
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LShift)
            {
                hero.rise_up = true;
                hero.frame_ = 2;
            }
        }
        //LMB
        if(gun->getFullauto())
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                hero.is_shooting = true;
            }
        }
        else
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && gun->shooting_flag)
            {
                hero.is_shooting = true;
                gun->shooting_flag = false;
            }
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left/*sf::Mouse::isButtonPressed(sf::Mouse::Left)*/)
            {
                gun->shooting_flag = true;
            }
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            shootingMachineGunSound.stop();
            shootingMachineGun_v2Sound.stop();
        }

        //LOGIC###################################################################################################################################################################

        //one frame time
        sf::Time elapsed = clock.restart();
        hero.getTime(elapsed.asSeconds());
        enemy_1->getTime(elapsed.asSeconds());

        //OPTIMIZATION*****************************************************************************************************************************************************************
        if (hero.getPosition().x > 12500)
        {
            for (size_t i = 0; i < EnemyVector.size(); i++)
            {
                if (EnemyVector[i]->getPosition().x < 12000)
                {
                    auto it_0 = EnemyVector.begin() + i;
                    EnemyVector.erase(it_0);
                    auto it_1 = EnemyGun.begin() + i;
                    EnemyGun.erase(it_1);
                    auto it_2 = enemyFireRate.begin() + i;
                    enemyFireRate.erase(it_2);
                }
            }
        }
        if (hero.getPosition().x > 23000)
        {
            for (size_t i = 0; i < EnemyVector.size(); i++)
            {
                if (EnemyVector[i]->getPosition().x < 23000)
                {
                    auto it_0 = EnemyVector.begin() + i;
                    EnemyVector.erase(it_0);
                    auto it_1 = EnemyGun.begin() + i;
                    EnemyGun.erase(it_1);
                    auto it_2 = enemyFireRate.begin() + i;
                    enemyFireRate.erase(it_2);
                }
            }
        }

        //LADDERS*****************************************************************************************************************************************************************
        hero.using_ladder = false;
        for (auto &it : ladder)
        {
            if (it.getGlobalBounds().left > hero.getGlobalBounds().left &&
                    it.getGlobalBounds().left + it.getGlobalBounds().width < hero.getGlobalBounds().left + hero.getGlobalBounds().width &&
                    hero.getGlobalBounds().top + hero.getGlobalBounds().height < it.getGlobalBounds().top + it.getGlobalBounds().height +20 &&
                    hero.getGlobalBounds().top > it.getGlobalBounds().top - 200)
            {
                if (hero.is_climbing_up)
                {
                    hero.move(0, -150 * elapsed.asSeconds());
                }
                if (hero.is_climbing_down)
                {
                    hero.move(0, 150 * elapsed.asSeconds());
                }
                hero.using_ladder = true;
                hero.move_up = false;
            }
        }

        //HERO*****************************************************************************************************************************************************************
        for (auto &it : obstacles)
        {
            if (it.getGlobalBounds().intersects(hero.getGlobalBounds()))
            {
                hero.isColliding(obstacles);
            }
        }

        if (hero.lying && !hero.rise_up)
        {
            hero.setTextureRect(hero.frames[hero.frame_ + frameAdd]);
            downTime--;
            if (downTime == 0)
            {
                downTime = 20;
                if (hero.frame_ < 2)
                {
                    hero.frame_++;
                }
            }
            if (hero.frame_ == 2)
            {
                hero.setTextureRect(sf::IntRect(144, 40 + frameOffset, 72, 30));
                if (lying_flag)
                {
                    hero.setPosition(sf::Vector2f(hero.getPosition().x, hero.getPosition().y + 100));
                    lying_flag = false;
                }
            }
        }
        if (hero.lying && hero.rise_up)
        {
            hero.setTextureRect(hero.frames[hero.frame_ + frameAdd]);
            downTime--;
            if (downTime == 0)
            {
                downTime = 20;
                if(hero.frame_ < 5)
                {
                    hero.frame_++;
                }
            }

            if (hero.frame_ == 4)
            {
                if (gun == &heroPistol)
                {
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTexturePistol, textureLayout, textureSize);
                }
                if (gun == &heroMachineGun)
                {
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTextureMachineGun, textureLayout, textureSize);
                }
                if (gun == &heroMachineGun_v2)
                {
                    hero.frames.clear();
                    hero.loadTexture(hero.getPosition(), heroTextureMachineGun_v2, textureLayout, textureSize);
                }
                hero.lying = false;
                hero.rise_up = false;
                lying_flag = true;
                if (hero.oriented_right)
                {
                    hero.frame_ = 0;
                }
                if (!hero.oriented_right)
                {
                    hero.frame_ = 14;
                }
                downTime = 1;
            }
        }
        if (!hero.lying && !hero.rise_up)
        {
            hero.control();
            if ((hero.move_backward || hero.move_forward) && hero.is_on_floor_)
            {
                if(walkingSound.getStatus() != sf::Sound::Playing)
                {
                    walkingSound.play();
                }
            }
            hero.setTextureRect(hero.frames[hero.frame_]);
        }
        hero.gravity(obstacles);
        if(heroReload)
        {
            gun->setCurrettReloadingTime(gun->getReloadingTime());
            heroReload = false;
        }
        if(gun->getCurretnReloadingTime() > 0)
        {
            gun->setCurrettReloadingTime(gun->getCurretnReloadingTime() - 1);
        }
        if (hero.is_shooting && gun->getCurretnReloadingTime() <= 0)
        {
            if ((hero.oriented_right && sf::Mouse::getPosition().x > 960) ||
                    (!hero.oriented_right && sf::Mouse::getPosition().x < 960))
            {
                fireRate--;
                if (hero.is_shooting && fireRate <= 0 && gun->getLeftInMagazine() > 0)
                {
                    Bullet *bullet = new Bullet(sf::Vector2f(10, 4));
                    bullet->setOrigin(sf::Vector2f(10, 2));
                    if (hero.oriented_right)
                    {
                        if (gun->getGunType() == 1)
                        {
                            bullet->setPosition(sf::Vector2f(hero.getPosition().x + 150, hero.getPosition().y + 70));
                        }
                        if (gun->getGunType() == 2)
                        {
                            bullet->setPosition(sf::Vector2f(hero.getPosition().x + 140, hero.getPosition().y + 90));
                        }
                        if (gun->getGunType() == 3)
                        {
                            bullet->setPosition(sf::Vector2f(hero.getPosition().x + 140, hero.getPosition().y + 90));
                        }
                    }
                    else
                    {
                        if (gun->getGunType() == 1)
                        {
                            bullet->setPosition(sf::Vector2f(hero.getPosition().x, hero.getPosition().y + 70));
                        }
                        if (gun->getGunType() == 2)
                        {
                            bullet->setPosition(sf::Vector2f(hero.getPosition().x + 10, hero.getPosition().y + 90));
                        }
                        if (gun->getGunType() == 3)
                        {
                            bullet->setPosition(sf::Vector2f(hero.getPosition().x + 10, hero.getPosition().y + 90));
                        }
                    }
                    BulletVector.push_back(bullet);
                    bulletDirection.push_back(bullet->shootingDirection(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)));
                    hero.is_shooting = false;
                    fireRate = gun->getFireRate();
                    gun->setLeftInMagazine(gun->getLeftInMagazine() - 1);
                    if(shootingMachineGunSound.getStatus() != sf::Sound::Playing && shootingPistolSound.getStatus() != sf::Sound::Playing)
                    {
                        if (gun->getGunType() == 1)
                        {
                            shootingPistolSound.play();
                        }
                        if (gun->getGunType() == 2)
                        {
                            shootingMachineGunSound.play();
                        }
                        if (gun->getGunType() == 3)
                        {
                            shootingMachineGun_v2Sound.play();
                        }
                    }
                }
            }
            else
            {
                hero.is_shooting = false;
            }
        }
        hero.hit(BulletVector_enemy, EnemyBulletDamage);

        int cameraOffset = 150;

        if (!hero.lying && !hero.rise_up)
        {
            camera.setCenter(hero.getPosition().x + hero.getGlobalBounds().width / 2, hero.getPosition().y + hero.getGlobalBounds().height / 2 - cameraOffset);
        }

        if (hero.getHealth() <= 0)
        {
            dead = true;
            break;
        }

        window.setView(camera);

        //ENEMY*****************************************************************************************************************************************************************
        bool reload = false;
        for (size_t i = 0; i < EnemyVector.size(); i++)
        {
            if (std::abs(EnemyVector[i]->getPosition().x - hero.getPosition().x) < 2000 || one)
            {
                EnemyVector[i]->gravity(obstacles);
                EnemyVector[i]->control();
                EnemyVector[i]->standby(hero.getPosition(), EnemyVector[i]->isColliding(obstacles));
                EnemyVector[i]->isColliding(obstacles);
                if (EnemyVector[i]->getMaxSpeed() != 0)
                {
                    EnemyVector[i]->setTextureRect(enemy_1->frames[EnemyVector[i]->frame_]);
                }
                else if (EnemyVector[i]->getOrientation())
                {
                    EnemyVector[i]->setTextureRect(enemy_1->frames[0]);
                }
                else
                {
                    EnemyVector[i]->setTextureRect(enemy_1->frames[7]);
                }
                if(EnemyVector[i]->hit(BulletVector, gun, damageMultipler))
                {
                    if (EnemyGun[i]->getGunType() == 1)
                    {
                        drop = new Drop(1, EnemyGun[i]->getBulletNumber());
                        drop->setTexture(pistolTexture);
                        drop->setScale(3, 3);
                        drop->setPosition(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y + 150);
                        dropVector.emplace_back(drop);
                    }
                    if (EnemyGun[i]->getGunType() == 2)
                    {
                        drop = new Drop(2, EnemyGun[i]->getBulletNumber());
                        drop->setTexture(machineGunTexture);
                        drop->setScale(4, 4);
                        drop->setPosition(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y + 150);
                        dropVector.emplace_back(drop);
                    }
                    if (EnemyGun[i]->getGunType() == 3)
                    {
                        drop = new Drop(3, EnemyGun[i]->getBulletNumber());
                        drop->setTexture(machineGun_v2Texture);
                        drop->setScale(4, 4);
                        drop->setPosition(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y + 150);
                        dropVector.emplace_back(drop);
                    }
                    auto it_0 = EnemyVector.begin() + i;
                    EnemyVector.erase(it_0);
                    auto it_1 = EnemyGun.begin() + i;
                    EnemyGun.erase(it_1);
                    auto it_2 = enemyFireRate.begin() + i;
                    enemyFireRate.erase(it_2);
                    break;

                }
                if (EnemyVector[i]->clear_shoot && std::abs(EnemyVector[i]->getPosition().x - hero.getPosition().x) < 1000)
                {
                    enemyFireRate[i] = enemyFireRate[i] - 1;
                    EnemyVector[i]->clear_shoot = false;
                    if (enemyFireRate[i] <= 0)
                    {
                        if(EnemyGun[i]->getLeftInMagazine() == 0)
                        {
                            EnemyGun[i]->setCurrettReloadingTime(EnemyGun[i]->getCurretnReloadingTime() - 1);
                            reload = true;
                        }
                        if(EnemyGun[i]->getCurretnReloadingTime() == 0)
                        {
                            reload = false;
                            EnemyGun[i]->setCurrettReloadingTime(EnemyGun[i]->getReloadingTime());
                            EnemyGun[i]->setLeftInMagazine(EnemyGun[i]->getMagazineCapasity());
                        }
                        if(!reload)
                        {
                            BulletEnemy *bullet_enemy = new BulletEnemy(sf::Vector2f(10, 4));
                            bullet_enemy->setOrigin(sf::Vector2f(15, 3));
                            if (EnemyVector[i]->getOrientation())
                            {
                                if (EnemyGun[i]->getGunType() == 1)
                                {
                                    bullet_enemy->setPosition(sf::Vector2f(EnemyVector[i]->getPosition().x + 150, EnemyVector[i]->getPosition().y + 70));
                                }
                                if (EnemyGun[i]->getGunType() == 2)
                                {
                                    bullet_enemy->setPosition(sf::Vector2f(EnemyVector[i]->getPosition().x + 140, EnemyVector[i]->getPosition().y + 90));
                                }
                                if (EnemyGun[i]->getGunType() == 3)
                                {
                                    bullet_enemy->setPosition(sf::Vector2f(EnemyVector[i]->getPosition().x + 140, EnemyVector[i]->getPosition().y + 90));
                                }
                            }
                            else
                            {
                                if (EnemyGun[i]->getGunType() == 1)
                                {
                                    bullet_enemy->setPosition(sf::Vector2f(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y + 70));
                                }
                                if (EnemyGun[i]->getGunType() == 2)
                                {
                                    bullet_enemy->setPosition(sf::Vector2f(EnemyVector[i]->getPosition().x + 10, EnemyVector[i]->getPosition().y + 90));
                                }
                                if (EnemyGun[i]->getGunType() == 3)
                                {
                                    bullet_enemy->setPosition(sf::Vector2f(EnemyVector[i]->getPosition().x + 10, EnemyVector[i]->getPosition().y + 90));
                                }
                            }
                            BulletVector_enemy.push_back(bullet_enemy);
                            bulletDirection_enemy.push_back(bullet_enemy->shootingDirection(sf::Vector2f(hero.getPosition().x, hero.getPosition().y), sf::Vector2f(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y)));
                            enemyFireRate[i] = EnemyGun[i]->getFireRate();
                            enemyBulletSpeed.push_back(EnemyGun[i]->getBulletSpeed());
                            EnemyBulletDamage.push_back(EnemyGun[i]->getDamage() * enemyDamageMultipler);
                            EnemyGun[i]->setLeftInMagazine(EnemyGun[i]->getLeftInMagazine() - 1);
                            if(enemyMachineGunSound.getStatus() != sf::Sound::Playing && enemyPistolSound.getStatus() != sf::Sound::Playing)
                            {
                                if (EnemyGun[i]->getGunType() == 1)
                                {
                                    enemyPistolSound.play();
                                }
                                if (EnemyGun[i]->getGunType() == 2)
                                {
                                    enemyMachineGunSound.play();
                                }
                                if (EnemyGun[i]->getGunType() == 3)
                                {
                                    enemyMachineGun_v2Sound.play();
                                }
                            }
                        }
                    }
                }
            }
        }
        one = false;

        //BULLET*****************************************************************************************************************************************************************
        //hero
        for (size_t i = 0; i < BulletVector.size(); i++)
        {
            BulletVector[i]->fire(gun->getBulletSpeed(), bulletDirection[i]);
            for (auto &it : obstacles)
            {
                if (it.getGlobalBounds().intersects(BulletVector[i]->getGlobalBounds()))
                {
                    delete BulletVector[i];
                    auto it_0 = BulletVector.begin() + i;
                    BulletVector.erase(it_0);
                    auto it_1 = bulletDirection.begin() + i;
                    bulletDirection.erase(it_1);
                }
            }
            if (std::abs(BulletVector[i]->getBulletPosition().x - hero.getPosition().x) > 5000)
            {
                delete BulletVector[i];
                auto it_0 = BulletVector.begin() + i;
                BulletVector.erase(it_0);
                auto it_1 = bulletDirection.begin() + i;
                bulletDirection.erase(it_1);
            }
        }

        //enemy
        for (size_t i = 0; i < BulletVector_enemy.size(); i++)
        {
            BulletVector_enemy[i]->fire(enemyBulletSpeed[i], bulletDirection_enemy[i]);
            for (auto &it : obstacles)
            {
                if (it.getGlobalBounds().intersects(BulletVector_enemy[i]->getGlobalBounds()))
                {
                    delete BulletVector_enemy[i];
                    auto it_0 = BulletVector_enemy.begin() + i;
                    BulletVector_enemy.erase(it_0);
                    auto it_1 = bulletDirection_enemy.begin() + i;
                    bulletDirection_enemy.erase(it_1);
                    auto it_2 = EnemyBulletDamage.begin() + i;
                    EnemyBulletDamage.erase(it_2);
                    auto it_3 = enemyBulletSpeed.begin() + i;
                    enemyBulletSpeed.erase(it_3);
                }
            }
            if (std::abs(BulletVector_enemy[i]->getBulletPosition().x - hero.getPosition().x) > 5000)
            {
                delete BulletVector_enemy[i];
                auto it_0 = BulletVector_enemy.begin() + i;
                BulletVector_enemy.erase(it_0);
                auto it_1 = bulletDirection_enemy.begin() + i;
                bulletDirection_enemy.erase(it_1);
                auto it_2 = EnemyBulletDamage.begin() + i;
                EnemyBulletDamage.erase(it_2);
                auto it_3 = enemyBulletSpeed.begin() + i;
                enemyBulletSpeed.erase(it_3);
            }
        }

        //DROP*****************************************************************************************************************************************************************
        //guns
        for (size_t i = 0; i < dropVector.size(); i++)
        {
            if (dropVector[i]->getGlobalBounds().intersects(hero.getGlobalBounds()))
            {
                if (dropVector[i]->getGunType() == 1)
                {
                    heroPistol.setBulletNumber(heroPistol.getBulletNumber() + dropVector[i]->getBulletNumber());
                }
                if (dropVector[i]->getGunType() == 2)
                {
                    machineGun_enable = true;
                    heroMachineGun.setBulletNumber(heroMachineGun.getBulletNumber() + dropVector[i]->getBulletNumber());
                }
                if (dropVector[i]->getGunType() == 3)
                {
                    machineGun_v2_enable = true;
                    heroMachineGun_v2.setBulletNumber(heroMachineGun_v2.getBulletNumber() + dropVector[i]->getBulletNumber());
                }
                delete dropVector[i];
                auto it = dropVector.begin() + i;
                dropVector.erase(it);
            }
        }

        //health
        for (size_t i = 0; i < aidKit.size(); i++)
        {
            if (aidKit[i]->getGlobalBounds().intersects(hero.getGlobalBounds()))
            {
                if (hero.getHealth() < hero.getMaxHealth() - addedHealth)
                {
                    hero.setHealth(hero.getHealth() + addedHealth);
                }
                else if (hero.getHealth() >= hero.getMaxHealth() - addedHealth)
                {
                    hero.setHealth(hero.getMaxHealth());
                }
                delete aidKit[i];
                auto it = aidKit.begin() + i;
                aidKit.erase(it);
                break;
            }
        }

        //armor
        for (size_t i = 0; i < armorVest.size(); i++)
        {
            if (armorVest[i]->getGlobalBounds().intersects(hero.getGlobalBounds()))
            {
                if (hero.getArmor() < hero.getMaxArmor() - addedArmor)
                {
                    hero.setArmor(hero.getArmor() + addedArmor);
                }
                else if (hero.getArmor() >= hero.getMaxArmor() - addedArmor)
                {
                    hero.setArmor(hero.getMaxArmor());
                }
                delete armorVest[i];
                auto it = armorVest.begin() + i;
                armorVest.erase(it);
                break;
            }
        }

        //INTERFACE*****************************************************************************************************************************************************************
        //gun view
        if (!hero.lying && !hero.rise_up)
        {
            gun->setPosition(hero.getPosition().x - 850, hero.getPosition().y + 400);
        }

        //health bar
        if (!hero.lying && !hero.rise_up)
        {
            healthBar.setPosition(hero.getPosition().x - 850, hero.getPosition().y + 350);
        }
        healthBar.setSize(sf::Vector2f(hero.getHealth() / (hero.getMaxHealth() / 100) * 2, 10));
        healthBarTopBound.setPosition(healthBar.getPosition().x - 2, healthBar.getPosition().y - 2);
        healthBarBottomBound.setPosition(healthBar.getPosition().x - 2, healthBar.getPosition().y + 10);
        healthBarLeftBound.setPosition(healthBar.getPosition().x - 2, healthBar.getPosition().y);
        healthBarRightBound.setPosition(healthBar.getPosition().x + 200, healthBar.getPosition().y);

        //armor bar
        if (!hero.lying && !hero.rise_up)
        {
            armorBar.setPosition(hero.getPosition().x - 850, hero.getPosition().y + 320);
        }
        armorBar.setSize(sf::Vector2f(hero.getArmor() / (hero.getMaxArmor() / 100) * 2, 10));
        if (hero.getArmor() < 0)
        {
            hero.setArmor(0);
        }
        armorBarTopBound.setPosition(armorBar.getPosition().x - 2, armorBar.getPosition().y - 2);
        armorBarBottomBound.setPosition(armorBar.getPosition().x - 2, armorBar.getPosition().y + 10);
        armorBarLeftBound.setPosition(armorBar.getPosition().x - 2, armorBar.getPosition().y);
        armorBarRightBound.setPosition(armorBar.getPosition().x + 200, armorBar.getPosition().y);

        //bullet number
        std::string bulletNumber = std::to_string(gun->getBulletNumber()) + "/" + std::to_string(gun->getLeftInMagazine());
        bulletNumberText.setString(bulletNumber);
        bulletNumberText.setCharacterSize(26);
        bulletNumberText.setFillColor(sf::Color::White);
        if (!hero.lying && !hero.rise_up)
        {
            bulletNumberText.setPosition(hero.getPosition().x - 750, hero.getPosition().y + 430);
            bulletNumberBackGround.setPosition(bulletNumberText.getPosition());
        }
        bulletNumberBackGround.setSize(sf::Vector2f(bulletNumberText.getGlobalBounds().width + 12, bulletNumberText.getGlobalBounds().height + 18));

        //boss
        if (hero.getPosition().x > 23000)
        {
            boss_fight = true;
        }

        if (boss_fight)
        {
            if (!hero.lying && !hero.rise_up)
            {
                bossHealthBar.setPosition(hero.getPosition().x - 760, hero.getPosition().y - 480);
            }
            bossHealthBar.setSize(sf::Vector2f(1520 * (enemy_21->getHealth() / enemy_21Health), 20));
            bossHealthBarTopBound.setPosition(bossHealthBar.getPosition().x - 2, bossHealthBar.getPosition().y - 2);
            bossHealthBarBottomBound.setPosition(bossHealthBar.getPosition().x - 2, bossHealthBar.getPosition().y + 20);
            bossHealthBarLeftBound.setPosition(bossHealthBar.getPosition().x - 2, bossHealthBar.getPosition().y);
            bossHealthBarRightBound.setPosition(bossHealthBar.getPosition().x + 1520, bossHealthBar.getPosition().y);
        }

        if (enemy_21->getHealth() <= 0)
        {
            break;
        }

        //DISPLAY###################################################################################################################################################################

        window.clear(sf::Color::Black);

        window.draw(backgruond);

        for (auto &it : dropVector)
        {
            window.draw(*it);
        }

        for (auto &it : ladder)
        {
            window.draw(it);
        }

        window.draw(hero);

        for (auto &it : EnemyVector)
        {
            window.draw(*it);
        }

        for(auto &it : obstacles)
        {
            window.draw(it);
        }

        for (size_t i = 0; i < BulletVector.size(); i++)
        {  
            BulletVector[i]->draw(window);
        }

        for (size_t i = 0; i < BulletVector_enemy.size(); i++)
        {
            BulletVector_enemy[i]->draw(window);
        }

        for(auto &it : aidKit)
        {
            window.draw(*it);
        }

        for(auto &it : armorVest)
        {
            window.draw(*it);
        }

        window.draw(healthBarTopBound);
        window.draw(healthBarBottomBound);
        window.draw(healthBarLeftBound);
        window.draw(healthBarRightBound);
        window.draw(healthBar);

        window.draw(armorBarTopBound);
        window.draw(armorBarBottomBound);
        window.draw(armorBarLeftBound);
        window.draw(armorBarRightBound);
        window.draw(armorBar);

        if (boss_fight)
        {
            window.draw(bossHealthBarTopBound);
            window.draw(bossHealthBarBottomBound);
            window.draw(bossHealthBarLeftBound);
            window.draw(bossHealthBarRightBound);
            window.draw(bossHealthBar);
        }

        window.draw(bulletNumberBackGround);
        window.draw(bulletNumberText);

        window.draw(*gun);

        window.display();
    }
    window.close();

    //END WINDOW
    if (dead || enemy_21->getHealth() <= 0)
    {
        sf::RectangleShape button_3(sf::Vector2f(200, 67));
        button_3.setPosition(100, 270);
        button_3.setFillColor(sf::Color::Red);

        sf::RectangleShape button_4(sf::Vector2f(200, 67));
        button_4.setPosition(100, 400);
        button_4.setFillColor(sf::Color::Red);

        sf::Text againText("PLAY AGAIN", font);
        againText.setCharacterSize(28);
        againText.setFillColor(sf::Color::Black);
        againText.setPosition(120, 287);

        sf::Text quitText_1("QUIT", font);
        quitText_1.setCharacterSize(28);
        quitText_1.setFillColor(sf::Color::Black);
        quitText_1.setPosition(165, 417);

        sf::Text messageText("YOU WIN!", font);
        messageText.setCharacterSize(40);
        messageText.setFillColor(sf::Color::Black);
        messageText.setPosition(330, 50);

        int endWidth = 960;
        int endHeight = 540;
        sf::RenderWindow end(sf::VideoMode(endWidth, endHeight), "Epic Final Ultimate Shooter");
        end.setFramerateLimit(60);

        bool pressedEnd = false;

        while (end.isOpen())
        {
            //EVENTS
            sf::Event event;

            while(end.pollEvent(event))
            {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    end.close();
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    pressedEnd = true;
                }
            }
            //LOGIC
            if(button_3.getGlobalBounds().contains(sf::Mouse::getPosition(end).x, sf::Mouse::getPosition(end).y) && pressedEnd)
            {
                end.close();
                goto E1;
            }
            if(button_4.getGlobalBounds().contains(sf::Mouse::getPosition(end).x, sf::Mouse::getPosition(end).y) && pressedEnd)
            {
                end.close();
                exit(0);
            }
            pressedEnd = false;

            if (hero.getHealth() <= 0)
            {
                messageText.setString("YOU LOOSE!");
            }

            //DISPLAY
            end.clear(sf::Color::Yellow);

            end.draw(messageText);
            end.draw(button_3);
            end.draw(button_4);
            end.draw(againText);
            end.draw(quitText_1);

            end.display();
        }
    }

    return 0;
}
