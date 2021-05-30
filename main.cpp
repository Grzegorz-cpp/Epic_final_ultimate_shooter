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

//bool is_shooting = false;
//float fireRate = 1;
//float fireRate_enemy = 1;
//float bulletSpeed = 70;
//float magazineCapasity = 30;



//void shooting(sf::Vector2f shooterPosition, sf::Vector2f targetPosition)
//{
//    Bullet *bullet = new Bullet(sf::Vector2f(30, 6));
//    bullet->setOrigin(sf::Vector2f(15, 3));
//    bullet->setPosition(shooterPosition);
//    BulletVector.push_back(bullet);
//    bulletDirection.push_back(bullet->shootingDirection(targetPosition));
//    is_shooting = false;
//    fireRate = 7;
//}

//void shootingenemy(sf::Vector2f shooterPosition, sf::Vector2f targetPosition)
//{
//    BulletEnemy *bullet_enemy = new BulletEnemy(sf::Vector2f(30, 6));
//    bullet_enemy->setOrigin(sf::Vector2f(15, 3));
//    bullet_enemy->setPosition(shooterPosition);
//    BulletVector_enemy.push_back(bullet_enemy);
//    bulletDirection_enemy.push_back(bullet_enemy->shootingDirection(targetPosition, shooterPosition));
//    //is_shooting = false;
//    fireRate_enemy = 7;
//}

int main()
{
    //window
    int windowWidth = 1920;
    int windowHeight = 1080;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Epic Final Ultimate Shooter");
    window.setPosition(sf::Vector2i(0, 0));

    //camera
    sf::View camera;
    camera.setSize(windowWidth, windowHeight);

    //vectors
    std::vector<sf::RectangleShape> obstacles;

    std::vector<Enemy*> EnemyVector;
    std::vector<Gun*> EnemyGun;
    std::vector<float> enemyBulletSpeed;
    std::vector<float> enemyFireRate;

    std::vector<Bullet*> BulletVector;
    std::vector<sf::Vector2f> bulletDirection;

    std::vector<BulletEnemy*> BulletVector_enemy;
    std::vector<sf::Vector2f> bulletDirection_enemy;

    std::vector<sf::RectangleShape> ladder;

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

    sf::Texture heroTexture;
    if (!heroTexture.loadFromFile("debug/textures/hero_v2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("debug/textures/hero_v2.png"))
    {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Texture pistolTexture;
    if (!pistolTexture.loadFromFile("debug/textures/pistol_v1.png"))
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

//    sf::Sprite floor;
//    floor.setTexture(floorTexture);
//    floor.setPosition(0, 1000);
//    floor.setScale(0.1, 0.1);
//    floor.setTextureRect(sf::IntRect(0, 0, 40000, 10800));
//    obstacles.emplace_back(floor);

    //OBJECTS*****************************************************************************************************************************************************************
    sf::RectangleShape floor(sf::Vector2f(4000, 4000));
    floor.setPosition(0, 1000);
    floor.setFillColor(sf::Color::Green);
    obstacles.emplace_back(floor);

    sf::Sprite sky;
    sky.setTexture(skyTexture);
    sky.setPosition(0, 0);
    sky.setScale(0.2, 0.2);
    sky.setTextureRect(sf::IntRect(0, 0, 20000, 5400));

    sf::RectangleShape box1(sf::Vector2f(2000, 10));
    box1.setPosition(500, 600);
    box1.setFillColor(sf::Color::Red);
    obstacles.emplace_back(box1);

    sf::RectangleShape box2(sf::Vector2f(50, 250));
    box2.setPosition(1000, 650);
    box2.setFillColor(sf::Color::Red);
    obstacles.emplace_back(box2);

    sf::RectangleShape box3(sf::Vector2f(50, 250));
    box3.setPosition(3500, 750);
    box3.setFillColor(sf::Color::Red);
    //obstacles.emplace_back(box3);
    ladder.emplace_back(box3);

    sf::RectangleShape box4(sf::Vector2f(200, 200));
    box4.setPosition(2200, 750);
    box4.setFillColor(sf::Color::Red);
    obstacles.emplace_back(box4);

    sf::RectangleShape healthBar(sf::Vector2f(200, 10));
    healthBar.setFillColor(sf::Color::Red);

    sf::RectangleShape armorBar(sf::Vector2f(0, 10));
    armorBar.setFillColor(sf::Color::Blue);

    //GUNS*****************************************************************************************************************************************************************
    Gun pistol(50, 5, 5, 180, 7, 100, false);
    pistol.setTexture(pistolTexture);
    pistol.setScale(0.2, 0.2);

    Gun pistol1(50, 5, 5, 180, 7, 100, false);
    pistol1.setTexture(pistolTexture);
    pistol1.setScale(0.2, 0.2);

    Gun machineGun(8, 50, 10, 180, 30, 100, true);
    machineGun.setTexture(machineGunTexture);
    machineGun.setScale(0.2, 0.2);
    machineGun.setOrigin(100, 100);

    Gun machineGun1(8, 50, 10, 180, 30, 100, true);
    machineGun1.setTexture(machineGunTexture);
    machineGun1.setScale(0.2, 0.2);
    machineGun1.setOrigin(100, 100);

    //CHARAKTERS*****************************************************************************************************************************************************************
    //start parameters
    const sf::Vector2f heroStartPosition(2000, 200);
    const sf::Vector2f enemyStartPosition(1000, 300);
    const sf::Vector2f enemyStartPosition1(3000, 700);
    const sf::Vector2i textureLayout(7, 4);
    const sf::Vector2i textureSize(40 ,70);

    //hero
    Hero hero(heroStartPosition, heroTexture, textureLayout, textureSize);
    hero.setScale(3, 3);
    Gun *gun;
    gun = &pistol1;

    //enemies
    Enemy *enemy = new Enemy(enemyStartPosition, enemyTexture, textureLayout, textureSize, false, false, 100, 100, 1, 1000, 1000,obstacles);
    enemy->setScale(3, 3);
    EnemyVector.push_back(enemy);
    Gun *enemy1Gun;
    enemy1Gun = &pistol;
    EnemyGun.push_back(enemy1Gun);
    enemyFireRate.push_back(1);

    Enemy *enemy1 = new Enemy(enemyStartPosition1, enemyTexture, textureLayout, textureSize, true, false, 100, 100, 1, 1000, 1000, obstacles);
    enemy1->setScale(3, 3);
    EnemyVector.push_back(enemy1);
    Gun *enemy2Gun;
    enemy2Gun = &machineGun;
    EnemyGun.push_back(enemy2Gun);
    enemyFireRate.push_back(1);

    //frame limit
    window.setFramerateLimit(60);

    //one frame time
    sf::Clock clock;

    //float fireRate = 1;
    //float fireRate_enemy = 1;
   // float bulletSpeed_enemy;
    //gun->setLeftInMagazine(gun->getMagazineCapasity());
    float fireRate = 1;
    //float fireRate_enemy = 1;
    //float bulletSpeed;
            bool debug = false;

    //MAIN LOOP###################################################################################################################################################################
    while (window.isOpen())
    {
        //EVENTS###################################################################################################################################################################

        sf::Event event;

        while(window.pollEvent(event))//;
        {
        if (event.type == sf::Event::Closed) window.close();
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
        //R
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
        {
            if (gun == &machineGun1)
            {
                machineGunReloadSound.play();
            }
            if (gun == &pistol1)
            {
                pistolReloadSound.play();
            }
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
        {
            gun->setBulletNumber(gun->getBulletNumber() - (gun->getMagazineCapasity() - gun->getLeftInMagazine()));
            gun->setLeftInMagazine(gun->getMagazineCapasity());
            hero.is_shooting = false;
        }
        //1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        {
            gun = &pistol1;
            hero.is_shooting = false;
            //magazineCapasity = gun->getMagazineCapasity();
        }
        //2
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        {
            gun = &machineGun1;
            hero.is_shooting = false;
            //magazineCapasity = gun->getMagazineCapasity();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            debug = true;
        }
        }

        //LOGIC###################################################################################################################################################################

        sf::Time elapsed = clock.restart();
        hero.getTime(elapsed.asSeconds());
        enemy->getTime(elapsed.asSeconds());

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

        //float fireRate_enemy = 1;
        //bulletSpeed = gun->getBulletSpeed();

        if (hero.is_shooting)
        {
            if ((hero.oriented_right && sf::Mouse::getPosition().x > 960) ||
                    (!hero.oriented_right && sf::Mouse::getPosition().x < 960))
            {
                fireRate--;
                if (hero.is_shooting && fireRate <= 0 && gun->getLeftInMagazine() > 0)
                {
                    //shooting(sf::Vector2f(hero.getPosition().x + 150, hero.getPosition().y + 120), sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
                    Bullet *bullet = new Bullet(sf::Vector2f(20, 4));
                    bullet->setOrigin(sf::Vector2f(10, 2));
                    bullet->setPosition(sf::Vector2f(hero.getPosition().x + 150, hero.getPosition().y + 120));
                    BulletVector.push_back(bullet);
                    bulletDirection.push_back(bullet->shootingDirection(sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)));
                    hero.is_shooting = false;
                    fireRate = gun->getFireRate();
                    //magazineCapasity--;
                    gun->setLeftInMagazine(gun->getLeftInMagazine() - 1);
                }
            }
            else
            {
                hero.is_shooting = false;
            }
        }

        hero.hit(BulletVector_enemy);

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
            EnemyVector[i]->setTextureRect(enemy->frames[EnemyVector[i]->frame_]);
            EnemyVector[i]->hit(BulletVector);

            if(debug)
            {
                hero.move_up = false;
            }
            //bulletSpeed_enemy = EnemyGun[i]->getBulletSpeed();
            if (EnemyVector[i]->clear_shoot)
            {
                //fireRate_enemy--;
                //EnemyGun[i]->setFireRate(EnemyGun[i]->getFireRate() - 1);
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
                        //shootingenemy(sf::Vector2f(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y), sf::Vector2f(hero.getPosition().x, hero.getPosition().y));
                        BulletEnemy *bullet_enemy = new BulletEnemy(sf::Vector2f(30, 6));
                        bullet_enemy->setOrigin(sf::Vector2f(15, 3));
                        bullet_enemy->setPosition(sf::Vector2f(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y));
                        BulletVector_enemy.push_back(bullet_enemy);
                        bulletDirection_enemy.push_back(bullet_enemy->shootingDirection(sf::Vector2f(hero.getPosition().x, hero.getPosition().y), sf::Vector2f(EnemyVector[i]->getPosition().x, EnemyVector[i]->getPosition().y)));
                        enemyFireRate[i] = EnemyGun[i]->getFireRate();
                        enemyBulletSpeed.push_back(EnemyGun[i]->getBulletSpeed());
                        std::cout<<"strzelam"<<std::endl;
                        EnemyGun[i]->setLeftInMagazine(EnemyGun[i]->getLeftInMagazine() - 1);
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
                if (it.getGlobalBounds().intersects(BulletVector[i]->getGlobalBoungs()))
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
                if (it.getGlobalBounds().intersects(BulletVector_enemy[i]->getGlobalBoungs()))
                {
                    BulletVector_enemy[i]->deleteBullet();
                }
            }
        }

        //INTERFACE*****************************************************************************************************************************************************************
        gun->setPosition(hero.getPosition().x - 900, hero.getPosition().y + 400);

        healthBar.setPosition(hero.getPosition().x - 850, hero.getPosition().y + 300);
        healthBar.setSize(sf::Vector2f(hero.getHealth() * 2, 10));

        armorBar.setPosition(hero.getPosition().x - 850, hero.getPosition().y + 270);
        armorBar.setSize(sf::Vector2f(hero.getArmor() * 2, 10));

        std::string bulletNumber = std::to_string(gun->getBulletNumber()) + "/" + std::to_string(gun->getLeftInMagazine());
        bulletNumberText.setString(bulletNumber);
        bulletNumberText.setPosition(hero.getPosition().x - 850, hero.getPosition().y + 230);

        //DISPLAY###################################################################################################################################################################

        window.clear(sf::Color::Black);

        window.draw(sky);

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

        window.draw(healthBar);

        window.draw(armorBar);

        window.draw(bulletNumberText);

        window.draw(*gun);

        window.display();
    }
    return 0;
}
