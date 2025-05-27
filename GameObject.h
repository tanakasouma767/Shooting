#pragma once

#include "App.h"

#include <GL/glut.h>
#include <GL/gl.h>

#include <Vector3.h>
#include <Point3.h>
#include <Matrix3.h>
#include <Matrix4.h>
#include <Color3.h>
#include <Color4.h>

#include <vector>
#include <chrono>

using namespace std;

class GameObject
{
protected:
    Point3f position; // 2D��Ԃł̈ʒu
    Vector3f size;     // �T�C�Y�i���E�����j
    Color4f color;    // RGBA�F���
    Point3f offset;   // �����ʒu


public:
    GameObject(Point3f pos, Vector3f sz, Color4f col);
    virtual ~GameObject();

    virtual void Update(float deltaTime) {}
    virtual void Draw();

    Point3f getPos();
};

class Bullet : public GameObject {
private:
    Vector3f velocity;

public:
    Bullet(Point3f pos, Vector3f sz, Color4f col, Vector3f vel);
    ~Bullet();
    void Update(float deltaTime) override;
    void Draw() override;
};

class Buff : public GameObject {
private:
    float velocity;

public:
    Buff(Point3f pos, Vector3f sz, Color4f col, float vel);
    ~Buff();
    void Update(float deltaTime) override;
    void Draw() override;
    virtual void buff();
};

class Heal : public Buff {
public:
    Heal(Point3f pos, Vector3f sz, float vel);
    ~Heal();
    void buff() override;
};

class SpeedUp : public Buff {
public:
    SpeedUp(Point3f pos, Vector3f sz, float vel);
    ~SpeedUp();
    void buff() override;
};

class RateUp : public Buff {
public:
    RateUp(Point3f pos, Vector3f sz, float vel);
    ~RateUp();
    void buff() override;
};

class Player : public GameObject {
private:
    float velocity;
    chrono::time_point<chrono::high_resolution_clock> lastFireTime;
    float fireCooldown = 0.3f;
    int hitpoint = 4; // 4

public:
    Player(Point3f pos, Vector3f sz, Color4f col);
    ~Player();
    void Update(float deltaTime) override;
    void Draw() override;
    void Fire(vector<Bullet*>& bullets);
    void TakeDamage(int dmg);
    void setHitpoint(int hp);
    float getVelocity();
    void setVelocity(float vel);
    float getCooldown();
    void setCooldown(float cd);
    bool IsDead() const;
};

class Enemy : public GameObject {
protected:
    int hitpoint;
    float velocity;
    chrono::time_point<chrono::high_resolution_clock> lastFireTime;
    float fireCooldown = 0.4f;

public:
    Enemy(Point3f pos, Vector3f sz, Color4f col, float vel, int hp);
    ~Enemy();
    void Fire(vector<Bullet*>& bullets, Vector3f bullVel);
    void TakeDamage(int dmg);
    virtual bool IsDead();
};

class EnemyA : public Enemy { // �ʏ�
private :
    float currentAngle = 0.0f;

public:
    EnemyA(Point3f pos, Vector3f sz, Color4f col, float vel, int hp);
    ~EnemyA();
    void Update(float deltaTime) override;
    void Draw() override;
};

class EnemyB : public Enemy { // �ړ�
private:
    float currentAngle = 0.0f;
    bool moveSwitch = false;
public:
    EnemyB(Point3f pos, Vector3f sz, Color4f col, float vel, int hp);
    ~EnemyB();
    void Update(float deltaTime) override;
    void Draw() override;
};

class EnemyC : public Enemy { // �񕜃o�t
private:
    float currentAngle = 0.0f;

public:
    EnemyC(Point3f pos, Vector3f sz, Color4f col, float vel, int hp);
    ~EnemyC();
    void Update(float deltaTime) override;
    void Draw() override;
    bool IsDead();
    void genBuff();
};

class EnemyD : public Enemy { // ���x�o�t
private:
    float currentAngle = 0.0f;

public:
    EnemyD(Point3f pos, Vector3f sz, Color4f col, float vel, int hp);
    ~EnemyD();
    void Update(float deltaTime) override;
    void Draw() override;
    bool IsDead();
    void genBuff();
};

class EnemyE : public Enemy { // �U���o�t
private:
    float currentAngle = 0.0f;

public:
    EnemyE(Point3f pos, Vector3f sz, Color4f col, float vel, int hp);
    ~EnemyE();
    void Update(float deltaTime) override;
    void Draw() override;
    bool IsDead();
    void genBuff();
};

class Boss: public Enemy { // �U���o�t
private:
    float currentAngle = 0.0f;
    bool moveSwitch_x = false;
    bool moveSwitch_y = false;

public:
    Boss(Point3f pos, Vector3f sz, Color4f col, float vel, int hp);
    ~Boss();
    void Update(float deltaTime) override;
    void Draw() override;
    bool IsDead();
};