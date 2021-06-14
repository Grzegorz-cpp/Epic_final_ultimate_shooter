#include <iostream>
#include <vector>
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

int main()
{
    //window
    int windowWidth = 1920;
    int windowHeight = 1080;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Epic Final Ultimate Shooter", sf::Style::Fullscreen);
    window.setPosition(sf::Vector2i(0, 0));

    //camera
    sf::View camera;
    camera.setSize(windowWidth, windowHeight);

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

    //FONT*****************************************************************************************************************************************************************
    sf::Font font;
    font.loadFromFile("debug/font/OpenSans-Regular.ttf");

    sf::Text bulletNumberText("", font);
    bulletNumberText.setCharacterSize(18);
    bulletNumberText.setFillColor(sf::Color::Black);

    //SOUNDS*****************************************************************************************************************************************************************
    sf::SoundBuffer machineGunReloadSoundWav;
    if (!machineGunReloadSoundWav.loadFromFile("debug/sounds/machineGunReload.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }

    sf::Sound machineGunReloadSound;
    machineGunReloadSound.setBuffer(machineGunReloadSoundWav);

    sf::SoundBuffer pistolReloadSoundWav;
    if (!pistolReloadSoundWav.loadFromFile("debug/sounds/pistolReload.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }

    sf::Sound pistolReloadSound;
    pistolReloadSound.setBuffer(pistolReloadSoundWav);

    sf::SoundBuffer shootingMachineGunSoundWav;
    if (!shootingMachineGunSoundWav.loadFromFile("debug/sounds/shootingMachinegun.wav"))
    {
        std::cerr << "../Could not load sound" << std::endl;
        return 1;
    }

    sf::Sound shootingMachineGunSound;
    shootingMachineGunSound.setBuffer(shootingMachineGunSoundWav);

    sf::SoundBuffer shootingPistolSoundWav;
    if (!shootingPistolSoundWav.loadFromFile("debug/sounds/shootingPistol.wav"))
    {
        std::cerr << "Could not load sound" << std::endl;
        return 1;
    }

    sf::Sound shootingPistolSound;
    shootingPistolSound.setBuffer(shootingPistolSoundWav);

    sf::Sound enemyPistolSound;
    enemyPistolSound.setBuffer(shootingPistolSoundWav);

    sf::Sound enemyMachineGunSound;
    enemyMachineGunSound.setBuffer(shootingMachineGunSoundWav);

    //TEXTURE LOADING*****************************************************************************************************************************************************************
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile("debug/textures/floor.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    floorTexture.setRepeated(true);

    sf::Texture skyTexture;
    if (!skyTexture.loadFromFile("debug/textures/sky.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    skyTexture.setRepeated(true);

    sf::Texture heroTexturePistol;
    if (!heroTexturePistol.loadFromFile("debug/textures/hero_pistol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture heroTextureMachineGun;
    if (!heroTextureMachineGun.loadFromFile("debug/textures/hero_machinegun.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture enemyTexturePistol;
    if (!enemyTexturePistol.loadFromFile("debug/textures/enemy_pistol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture enemyTextureMachineGun;
    if (!enemyTextureMachineGun.loadFromFile("debug/textures/enemy_machinegun.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture pistolTexture;
    if (!pistolTexture.loadFromFile("debug/textures/pistol.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture machineGunTexture;
    if (!machineGunTexture.loadFromFile("debug/textures/machinegun.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    //OBJECTS*****************************************************************************************************************************************************************
    //background
    sf::Sprite sky;
    sky.setTexture(skyTexture);
    sky.setPosition(0, 0);
    sky.setScale(0.2, 0.2);
    sky.setTextureRect(sf::IntRect(0, 0, 20000, 5400));

    //floor
    sf::Sprite floor;
    floor.setTexture(floorTexture);
    floor.setPosition(0, 1000);
    floor.setScale(0.1, 0.1);
    floor.setTextureRect(sf::IntRect(0, 0, 40000, 10800));
    obstacles.emplace_back(floor);

    //obstacles
    sf::Sprite box1;
    box1.setTexture(floorTexture);
    box1.setPosition(500, 600);
    box1.setScale(1, 1);
    box1.setTextureRect(sf::IntRect(0, 0, 200, 200));
    obstacles.emplace_back(box1);

    sf::Sprite box2;
    box2.setTexture(floorTexture);
    box2.setPosition(1000, 650);
    box2.setScale(1, 1);
    box2.setTextureRect(sf::IntRect(0, 0, 200, 200));
    obstacles.emplace_back(box2);

    sf::Sprite box3;
    box3.setTexture(floorTexture);
    box3.setPosition(2200, 750);
    box3.setScale(1, 1);
    box3.setTextureRect(sf::IntRect(0, 0, 200, 200));
    obstacles.emplace_back(box3);

    //ladder
    sf::Sprite ladder_1;
    ladder_1.setTexture(floorTexture);
    ladder_1.setPosition(3500, 600);
    ladder_1.setScale(1, 1);
    ladder_1.setTextureRect(sf::IntRect(0, 0, 20, 400));
    ladder.emplace_back(ladder_1);

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

    //GUNS*****************************************************************************************************************************************************************
    //guns parameters
    //pistol
    int PistolGunType = 1;
    float PistolFireRate = 35;
    float PistolBulletSpeed = 30;
    float PistolDamage = 20;
    float EnemyPistolDamage = 7;
    float PistolReloadingTime = 60;
    int PistolMagazineCapasity = 7;
    int PistolBulletNumber = 100;
    bool PistolFullauto = false;

    //machine gun
    int MachineGunGunType = 2;
    float MachineGunFireRate = 8;
    float MachineGunBulletSpeed = 50;
    float MachineGunDamage = 15;
    float EnemyMachineGunlDamage = 4;
    float MachineGunReloadingTime = 160;
    int MachineGunMagazineCapasity = 30;
    int MachineGunBulletNumber = 100;
    bool MachineGunFullauto = true;

    Gun heroPistol(PistolGunType, PistolFireRate, PistolBulletSpeed, PistolDamage, PistolReloadingTime, PistolMagazineCapasity, PistolBulletNumber, PistolFullauto);
    heroPistol.setTexture(pistolTexture);
    heroPistol.setScale(4, 4);

    Gun heroMachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, MachineGunDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, MachineGunBulletNumber, MachineGunFullauto);
    heroMachineGun.setTexture(machineGunTexture);
    heroMachineGun.setScale(6, 6);

    Gun enemy_1Pistol(PistolGunType, PistolFireRate, PistolBulletSpeed, EnemyPistolDamage, PistolReloadingTime, PistolMagazineCapasity, PistolBulletNumber, PistolFullauto);
    enemy_1Pistol.setTexture(pistolTexture);
    enemy_1Pistol.setScale(4, 4);

    Gun enemy_2MachineGun(MachineGunGunType, MachineGunFireRate, MachineGunBulletSpeed, EnemyMachineGunlDamage, MachineGunReloadingTime, MachineGunMagazineCapasity, MachineGunBulletNumber, MachineGunFullauto);
    enemy_2MachineGun.setTexture(machineGunTexture);
    enemy_2MachineGun.setScale(6, 6);

    //CHARAKTERS*****************************************************************************************************************************************************************
    const sf::Vector2i textureLayout(7, 4);
    const sf::Vector2i textureSize(45 ,70);

    //hero start parameters
    const sf::Vector2f heroStartPosition(2000, 200);

    //hero
    Hero hero(heroStartPosition, heroTexturePistol, textureLayout, textureSize);
    hero.setScale(3, 3);
    Gun *gun;
    gun = &heroPistol;

    //enemies
    //enemy_1 start parameters
    const sf::Vector2f enemy_1StartPosition(1000, 200);
    bool enemy_1_is_walking = false;
    bool enemy_1_orientated_right = true;
    float enemy_1Speed = 100;
    float enemy_1Health = 100;
    int enemy_1GunType = 1;
    float enemy_1DetectedDistanceX = 300;
    float enemy_1DetectedDistanceY = 300;

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
    const sf::Vector2f enemy_2StartPosition(3000, 200);
    bool enemy_2_is_walking = false;
    bool enemy_2_orientated_right = true;
    float enemy_2Speed = 100;
    float enemy_2Health = 100;
    int enemy_2GunType = 1;
    float enemy_2DetectedDistanceX = 300;
    float enemy_2DetectedDistanceY = 300;

    //enemy_2
    Enemy *enemy_2 = new Enemy(enemy_2StartPosition, enemyTextureMachineGun, textureLayout, textureSize, enemy_2_is_walking, enemy_2_orientated_right,
                               enemy_2Speed, enemy_2Health, enemy_2GunType, enemy_2DetectedDistanceX, enemy_2DetectedDistanceY, obstacles);
    enemy_2->setScale(3, 3);
    EnemyVector.push_back(enemy_2);
    Gun *enemy2Gun;
    enemy2Gun = &enemy_2MachineGun;
    EnemyGun.push_back(enemy2Gun);
    enemyFireRate.push_back(1);

    Drop *drop;

    sf::Clock clock;

    float fireRate = 1;
    bool debug = false;
    bool machineGun_enable = false;
    bool heroReload = false;

    //frame limit
    window.setFramerateLimit(60);

    //MAIN LOOP###################################################################################################################################################################
    while (window.isOpen())
    {
        //EVENTS###################################################################################################################################################################

        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
            //SPACE
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (hero.is_on_floor_ == true))
            {
                hero.setSpeedUp(-700);
                hero.move_up = true;
            }
            //D
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
            //R
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            {
                if (gun->getLeftInMagazine() != gun->getMagazineCapasity() && gun->getBulletNumber() > 0)
                {
                    if (gun == &heroMachineGun)
                    {
                        machineGunReloadSound.play();
                    }
                    if (gun == &heroPistol)
                    {
                        pistolReloadSound.play();
                    }
                }
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
            {
                if (gun->getBulletNumber() + gun->getLeftInMagazine() >= 30)
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
            //1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                gun = &heroPistol;
                hero.is_shooting = false;
                hero.loadTexture(hero.getPosition(), heroTexturePistol, textureLayout, textureSize);
                //magazineCapasity = gun->getMagazineCapasity();
            }
            //2
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)/* && machineGun_enable*/)
            {
                gun = &heroMachineGun;
                hero.is_shooting = false;
                hero.loadTexture(hero.getPosition(), heroTextureMachineGun, textureLayout, textureSize);
                //magazineCapasity = gun->getMagazineCapasity();
            }
            //L
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            {
                debug = true;
            }
        }
        //LPM
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

        //LOGIC###################################################################################################################################################################

        sf::Time elapsed = clock.restart();
        hero.getTime(elapsed.asSeconds());
        enemy_1->getTime(elapsed.asSeconds());

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
        hero.control();

        hero.setTextureRect(hero.frames[hero.frame_]);

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

        camera.setCenter(hero.getPosition().x + hero.getGlobalBounds().width / 2, hero.getPosition().y + hero.getGlobalBounds().height / 2 - cameraOffset);

        window.setView(camera);

        //ENEMY*****************************************************************************************************************************************************************
        bool reload = false;
        for (size_t i = 0; i < EnemyVector.size(); i++)
        {
            EnemyVector[i]->gravity(obstacles);
            EnemyVector[i]->control();
            EnemyVector[i]->standby(hero.getPosition(), EnemyVector[i]->isColliding(obstacles));
            EnemyVector[i]->isColliding(obstacles);
            EnemyVector[i]->setTextureRect(enemy_1->frames[EnemyVector[i]->frame_]);
            if(EnemyVector[i]->hit(BulletVector, gun))
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

                EnemyVector[i]->setPosition(10000000, 10000000);
            }

            if(debug)
            {
                hero.move_up = false;
            }

            if (EnemyVector[i]->clear_shoot)
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
                        }
                        BulletVector_enemy.push_back(bullet_enemy);
                        bulletDirection_enemy.push_back(bullet_enemy->shootingDirection(sf::Vector2f(hero.getPosition().x, hero.getPosition().y), sf::Vector2f(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y)));
                        enemyFireRate[i] = EnemyGun[i]->getFireRate();
                        enemyBulletSpeed.push_back(EnemyGun[i]->getBulletSpeed());
                        EnemyBulletDamage.push_back(EnemyGun[i]->getDamage());
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
                        }
                    }
                }
            }
        }

        //BULLET*****************************************************************************************************************************************************************
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
        }
        for (size_t i = 0; i < BulletVector_enemy.size(); i++)
        {
            BulletVector_enemy[i]->fire(enemyBulletSpeed[i], bulletDirection_enemy[i]);
            for (auto &it : obstacles)
            {
                if (it.getGlobalBounds().intersects(BulletVector_enemy[i]->getGlobalBounds()))
                {
                    BulletVector_enemy[i]->deleteBullet();
                }
            }
        }

        //DROP*****************************************************************************************************************************************************************
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
                delete dropVector[i];
                auto it = dropVector.begin() + i;
                dropVector.erase(it);
            }
        }

        //INTERFACE*****************************************************************************************************************************************************************
        gun->setPosition(hero.getPosition().x - 850, hero.getPosition().y + 400);

        healthBar.setPosition(hero.getPosition().x - 850, hero.getPosition().y + 350);
        healthBar.setSize(sf::Vector2f(hero.getHealth() * 2, 10));
        healthBarTopBound.setPosition(healthBar.getPosition().x - 2, healthBar.getPosition().y - 2);
        healthBarBottomBound.setPosition(healthBar.getPosition().x - 2, healthBar.getPosition().y + 10);
        healthBarLeftBound.setPosition(healthBar.getPosition().x - 2, healthBar.getPosition().y);
        healthBarRightBound.setPosition(healthBar.getPosition().x + 200, healthBar.getPosition().y);

        armorBar.setPosition(hero.getPosition().x - 850, hero.getPosition().y + 320);
        armorBar.setSize(sf::Vector2f(hero.getArmor() * 2, 10));
        armorBarTopBound.setPosition(armorBar.getPosition().x - 2, armorBar.getPosition().y - 2);
        armorBarBottomBound.setPosition(armorBar.getPosition().x - 2, armorBar.getPosition().y + 10);
        armorBarLeftBound.setPosition(armorBar.getPosition().x - 2, armorBar.getPosition().y);
        armorBarRightBound.setPosition(armorBar.getPosition().x + 200, armorBar.getPosition().y);

        std::string bulletNumber = std::to_string(gun->getBulletNumber()) + "/" + std::to_string(gun->getLeftInMagazine());
        bulletNumberText.setString(bulletNumber);
        bulletNumberText.setCharacterSize(26);
        bulletNumberText.setFillColor(sf::Color::White);
        bulletNumberText.setPosition(hero.getPosition().x - 750, hero.getPosition().y + 430);
        bulletNumberBackGround.setPosition(bulletNumberText.getPosition());
        bulletNumberBackGround.setSize(sf::Vector2f(bulletNumberText.getGlobalBounds().width + 12, bulletNumberText.getGlobalBounds().height + 18));

        //DISPLAY###################################################################################################################################################################

        window.clear(sf::Color::Black);

        window.draw(sky);

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

        window.draw(bulletNumberBackGround);
        window.draw(bulletNumberText);

        window.draw(*gun);

        window.display();
    }
    return 0;
}
