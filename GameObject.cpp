#include "GameObject.h"
#include "Scene.h"

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

GameObject::GameObject(Point3f pos, Vector3f sz, Color4f col)
	: position(pos), size(sz), color(col), offset(pos) 
{

}

GameObject::~GameObject() {

}

void GameObject::Draw() {

}

Point3f GameObject::getPos() {
    return position;
}



Player::Player(Point3f pos, Vector3f sz, Color4f col) : GameObject(pos, sz, col), velocity(1.0f) {
    lastFireTime = std::chrono::high_resolution_clock::now();
}

Player::~Player() {

}

void Player::Update(float deltaTime) {
    if (keyStates['w']) position.y += deltaTime * velocity;
	if (keyStates['s']) position.y -= deltaTime * velocity;
	if (keyStates['a']) position.x -= deltaTime * velocity;
	if (keyStates['d']) position.x += deltaTime * velocity;

    auto currentTime = chrono::high_resolution_clock::now();
    float timeSinceLastFire = chrono::duration<float>(currentTime - lastFireTime).count();

    if (keyStates[KEY_ENTER] && timeSinceLastFire >= fireCooldown) {
        Fire(g_Scene->getBullets());
        lastFireTime = currentTime;
    }

    if (position.x > 1.0f) position.x = 1.0f;
    if (position.x < -1.0f) position.x = -1.0f;
    if (position.y > 1.0f) position.y = 1.0f;
    if (position.y < -1.0f) position.y = -1.0f;
}

void Player::Draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

    const int segments = 32;

    const float radius = 0.01f;
    const float triSize = 0.04f;
    const float offset = 0.01f; 

    // íÜâõÇÃâ~
    glColor4f(color.x, color.y, color.z, color.w);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
    }
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w);

    // è„
    if (hitpoint >= 1) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 2) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 3) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 4) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glPopMatrix();
}

void Player::Fire(vector<Bullet*>& bullets) {
    Vector3f bulletVelocity(0.0f, 1.0f, 0.0f); // è„ï˚å¸
    Bullet* bullet = new Bullet(position, Vector3f(0.1f, 0.1f, 0.0f), Color4f(1.0f, 1.0f, 1.0f, 1.0f), Vector3f(0.0f, 2.0f, 0.0f));
    bullets.push_back(bullet);
}

void Player::TakeDamage(int dmg) {
    hitpoint -= dmg;
}

bool Player::IsDead() const {
    return hitpoint <= 0;
}

void Player::setHitpoint(int hp) {
    hitpoint = hp;
}

float Player::getVelocity() {
    return velocity;
}

void Player::setVelocity(float vel) {
    velocity = vel;
}

float Player::getCooldown() {
    return fireCooldown;
}

void Player::setCooldown(float cd) {
    fireCooldown = cd;
}


Enemy::Enemy(Point3f pos, Vector3f sz, Color4f col, float vel, int hp) : GameObject(pos, sz, col), velocity(vel), hitpoint(hp) {
    lastFireTime = std::chrono::high_resolution_clock::now();
}

Enemy::~Enemy() {

}

void Enemy::Fire(vector<Bullet*>& bullets, Vector3f bullVel) {
    Vector3f bulletVelocity = bullVel;
    Bullet* bullet = new Bullet(position, Vector3f(0.1f, 0.1f, 0.0f), Color4f(0.0f, 0.0f, 0.0f, 1.0f), bulletVelocity);
    bullets.push_back(bullet);
}

void Enemy::TakeDamage(int dmg) {
    hitpoint -= dmg;
}

bool Enemy::IsDead() {
    return hitpoint <= 0;
}



EnemyA::EnemyA(Point3f pos, Vector3f sz, Color4f col, float vel, int hp) : Enemy(pos, sz, col, vel, hp){

}

EnemyA::~EnemyA() {

}

void EnemyA::Update(float deltaTime) {
    auto currentTime = chrono::high_resolution_clock::now();
    float timeSinceLastFire = chrono::duration<float>(currentTime - lastFireTime).count();


    if (timeSinceLastFire >= fireCooldown) {
        const int numDirections = 8;

        for (int i = 0; i < numDirections; ++i) {
            float angle = currentAngle + 2.0f * 3.14159f * i / numDirections;
            Vector3f dir(cosf(angle), sinf(angle), 0.0f);
            Fire(g_Scene->getEnemyBullets(), dir);
        }

        currentAngle += 0.5f; // ñàâÒè≠ÇµÇ∏Ç¬âÒì]
        if (currentAngle > 2.0f * 3.14159f) {
            currentAngle -= 2.0f * 3.14159f;
        }

        lastFireTime = currentTime;
    }

    position.y -= deltaTime * velocity;
}

void EnemyA::Draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

    const int segments = 32;

    const float radius = 0.01f;
    const float triSize = 0.04f;
    const float offset = 0.01f;

    // íÜâõÇÃâ~
    glColor4f(color.x, color.y, color.z, color.w);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
    }
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w);
    // è„
    if (hitpoint >= 1) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 2) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 3) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 4) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glPopMatrix();
}



EnemyB::EnemyB(Point3f pos, Vector3f sz, Color4f col, float vel, int hp) : Enemy(pos, sz, col, vel, hp) {

}

EnemyB::~EnemyB() {

}

void EnemyB::Update(float deltaTime) {
    auto currentTime = chrono::high_resolution_clock::now();
    float timeSinceLastFire = chrono::duration<float>(currentTime - lastFireTime).count();


    if (timeSinceLastFire >= fireCooldown) {
        const int numDirections = 8;

        for (int i = 0; i < numDirections; ++i) {
            float angle = currentAngle + 2.0f * 3.14159f * i / numDirections;
            Vector3f dir(cosf(angle), sinf(angle), 0.0f);
            Fire(g_Scene->getEnemyBullets(), dir);
        }

        currentAngle += 0.5f; // ñàâÒè≠ÇµÇ∏Ç¬âÒì]
        if (currentAngle > 2.0f * 3.14159f) {
            currentAngle -= 2.0f * 3.14159f;
        }

        lastFireTime = currentTime;
    }

    position.y -= deltaTime * velocity;

    if (position.y < 1.0f) {
        if (position.x > 1.0f || position.x < -1.0f) {
            moveSwitch = !moveSwitch;
        }

        if (moveSwitch) {
            position.x -= deltaTime * velocity;
        }
        else {
            position.x += deltaTime * velocity;
        }
    }
}

void EnemyB::Draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

    const int segments = 32;

    const float radius = 0.01f;
    const float triSize = 0.04f;
    const float offset = 0.01f;

    // íÜâõÇÃâ~
    glColor4f(color.x, color.y, color.z, color.w);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
    }
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w);
    // è„
    if (hitpoint >= 1) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 2) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 3) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 4) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glPopMatrix();
}


EnemyC::EnemyC(Point3f pos, Vector3f sz, Color4f col, float vel, int hp) : Enemy(pos, sz, col, vel, hp) {

}

EnemyC::~EnemyC() {

}

void EnemyC::Update(float deltaTime) {
    auto currentTime = chrono::high_resolution_clock::now();
    float timeSinceLastFire = chrono::duration<float>(currentTime - lastFireTime).count();


    if (timeSinceLastFire >= fireCooldown) {
        const int numDirections = 8;

        for (int i = 0; i < numDirections; ++i) {
            float angle = currentAngle + 2.0f * 3.14159f * i / numDirections;
            Vector3f dir(cosf(angle), sinf(angle), 0.0f);
            Fire(g_Scene->getEnemyBullets(), dir);
        }

        currentAngle += 0.5f; // ñàâÒè≠ÇµÇ∏Ç¬âÒì]
        if (currentAngle > 2.0f * 3.14159f) {
            currentAngle -= 2.0f * 3.14159f;
        }

        lastFireTime = currentTime;
    }

    position.y -= deltaTime * velocity;
}

void EnemyC::Draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

    const int segments = 32;

    const float radius = 0.01f;
    const float triSize = 0.04f;
    const float offset = 0.01f;

    // íÜâõÇÃâ~
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
    }
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w);
    // è„
    if (hitpoint >= 1) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 2) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 3) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 4) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glPopMatrix();
}

bool EnemyC::IsDead(){

    if (hitpoint <= 0) {
        genBuff();
    }
    return hitpoint <= 0;
}

void EnemyC::genBuff() {
    g_Scene->getBuffs().push_back(new Heal(position, size, velocity));
}


EnemyD::EnemyD(Point3f pos, Vector3f sz, Color4f col, float vel, int hp) : Enemy(pos, sz, col, vel, hp) {

}

EnemyD::~EnemyD() {

}

void EnemyD::Update(float deltaTime) {
    auto currentTime = chrono::high_resolution_clock::now();
    float timeSinceLastFire = chrono::duration<float>(currentTime - lastFireTime).count();


    if (timeSinceLastFire >= fireCooldown) {
        const int numDirections = 8;

        for (int i = 0; i < numDirections; ++i) {
            float angle = currentAngle + 2.0f * 3.14159f * i / numDirections;
            Vector3f dir(cosf(angle), sinf(angle), 0.0f);
            Fire(g_Scene->getEnemyBullets(), dir);
        }

        currentAngle += 0.5f; // ñàâÒè≠ÇµÇ∏Ç¬âÒì]
        if (currentAngle > 2.0f * 3.14159f) {
            currentAngle -= 2.0f * 3.14159f;
        }

        lastFireTime = currentTime;
    }

    position.y -= deltaTime * velocity;
}

void EnemyD::Draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

    const int segments = 32;

    const float radius = 0.01f;
    const float triSize = 0.04f;
    const float offset = 0.01f;

    // íÜâõÇÃâ~
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
    }
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w);
    // è„
    if (hitpoint >= 1) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 2) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 3) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 4) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glPopMatrix();
}

bool EnemyD::IsDead() {

    if (hitpoint <= 0) {
        genBuff();
    }
    return hitpoint <= 0;
}

void EnemyD::genBuff() {
    g_Scene->getBuffs().push_back(new SpeedUp(position, size, velocity));
}



EnemyE::EnemyE(Point3f pos, Vector3f sz, Color4f col, float vel, int hp) : Enemy(pos, sz, col, vel, hp) {

}

EnemyE::~EnemyE() {

}

void EnemyE::Update(float deltaTime) {
    auto currentTime = chrono::high_resolution_clock::now();
    float timeSinceLastFire = chrono::duration<float>(currentTime - lastFireTime).count();


    if (timeSinceLastFire >= fireCooldown) {
        const int numDirections = 8;

        for (int i = 0; i < numDirections; ++i) {
            float angle = currentAngle + 2.0f * 3.14159f * i / numDirections;
            Vector3f dir(cosf(angle), sinf(angle), 0.0f);
            Fire(g_Scene->getEnemyBullets(), dir);
        }

        currentAngle += 0.5f; // ñàâÒè≠ÇµÇ∏Ç¬âÒì]
        if (currentAngle > 2.0f * 3.14159f) {
            currentAngle -= 2.0f * 3.14159f;
        }

        lastFireTime = currentTime;
    }

    position.y -= deltaTime * velocity;
}

void EnemyE::Draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

    const int segments = 32;

    const float radius = 0.01f;
    const float triSize = 0.04f;
    const float offset = 0.01f;

    // íÜâõÇÃâ~
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
    }
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w);
    // è„
    if (hitpoint >= 1) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 2) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 3) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 4) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glPopMatrix();
}

bool EnemyE::IsDead() {

    if (hitpoint <= 0) {
        genBuff();
    }
    return hitpoint <= 0;
}

void EnemyE::genBuff() {
    g_Scene->getBuffs().push_back(new RateUp(position, size, velocity));
}


Boss::Boss(Point3f pos, Vector3f sz, Color4f col, float vel, int hp) : Enemy(pos, sz, col, vel, hp) {

}

Boss::~Boss() {

}

void Boss::Update(float deltaTime) {
    auto currentTime = chrono::high_resolution_clock::now();
    float timeSinceLastFire = chrono::duration<float>(currentTime - lastFireTime).count();


    if (timeSinceLastFire >= fireCooldown) {
        const int numDirections = 8;

        for (int i = 0; i < numDirections; ++i) {
            float angle = currentAngle + 2.0f * 3.14159f * i / numDirections;
            Vector3f dir(cosf(angle), sinf(angle), 0.0f);
            Fire(g_Scene->getEnemyBullets(), dir);
        }

        currentAngle += 0.5f; // ñàâÒè≠ÇµÇ∏Ç¬âÒì]
        if (currentAngle > 2.0f * 3.14159f) {
            currentAngle -= 2.0f * 3.14159f;
        }

        lastFireTime = currentTime;
    }


    if (position.y < 0.0f) {
        moveSwitch_y = true;
    }

    if (position.y > 1.0f) {
        moveSwitch_y = false;
    }

    if (moveSwitch_y) {
        position.y += deltaTime * velocity;
    }
    else {
        position.y -= deltaTime * velocity;
    }

    if (position.y < 1.0f) {
        if (position.x > 1.0f || position.x < -1.0f) {
            moveSwitch_x = !moveSwitch_x;
        }

        if (moveSwitch_x) {
            position.x -= deltaTime * velocity;
        }
        else {
            position.x += deltaTime * velocity;
        }
    }
}

void Boss::Draw() {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

    const int segments = 32;

    const float radius = 0.01f;
    const float triSize = 0.04f;
    const float offset = 0.01f;

    // íÜâõÇÃâ~
    glColor4f(color.x, color.y, color.z, color.w);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * 3.14159f * i / segments;
        glVertex2f(cosf(angle) * radius, sinf(angle) * radius);
    }
    glEnd();

    glColor4f(color.x, color.y, color.z, color.w);
    // è„
    if (hitpoint >= 1) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 2) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 3) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 4) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);

    // è„
    if (hitpoint >= 5) {
        drawTriangle(0, radius + offset + triSize, -triSize / 2, radius + offset, triSize / 2, radius + offset);
    }
    // â∫
    if (hitpoint >= 6) {
        drawTriangle(0, -radius - offset - triSize, -triSize / 2, -radius - offset, triSize / 2, -radius - offset);
    }
    // ç∂
    if (hitpoint >= 7) {
        drawTriangle(-radius - offset - triSize, 0, -radius - offset, triSize / 2, -radius - offset, -triSize / 2);
    }
    // âE
    if (hitpoint >= 8) {
        drawTriangle(radius + offset + triSize, 0, radius + offset, triSize / 2, radius + offset, -triSize / 2);
    }

    glPopMatrix();
}

bool Boss::IsDead() {
    if (hitpoint <= 0) {
        g_Scene->TransitionTo(GameState::Clear);
    }
    return hitpoint <= 0;
}


Bullet::Bullet(Point3f pos, Vector3f sz, Color4f col, Vector3f vel) : GameObject(pos, sz, col), velocity(vel) {

}

Bullet::~Bullet() {

}

void Bullet::Update(float deltaTime){
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Bullet::Draw(){
    glColor4f(color.x, color.y, color.z, color.w);
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 16; ++i) {
        float angle = 2.0f * 3.14159f * i / 16;
        glVertex2f(cosf(angle) * 0.01f, sinf(angle) * 0.01f);
    }
    glEnd();
    glPopMatrix();
}



Buff::Buff(Point3f pos, Vector3f sz, Color4f col, float vel) : GameObject(pos, sz, col), velocity(vel) {

}

Buff::~Buff() {

}

void Buff::Update(float deltaTime) {
    position.y -= velocity * deltaTime;
}

void Buff::Draw() {
    glColor4f(color.x, color.y, color.z, color.w);
    glPushMatrix();

    // ïΩçsà⁄ìÆ
    glTranslatef(position.x, position.y, 0.0f);

    // ê≥ï˚å`Çï`âÊÅiíÜêSå¥ì_Ç≈ï`Ç≠Åj
    glBegin(GL_QUADS);
    glVertex2f(0.0f, -0.03f);
    glVertex2f(0.03f, 0.0f);
    glVertex2f(0.0f, 0.03f);
    glVertex2f(-0.03f, 0.0f);
    glEnd();

    glPopMatrix();
}

void Buff::buff() {

}

Heal::Heal(Point3f pos, Vector3f sz, float vel) : Buff(pos, sz, Color4f(0.0f, 1.0f, 0.0f, 1.0f), vel){

}

Heal::~Heal() {

}

void Heal::buff() {
    g_Scene->getPlayer()->setHitpoint(4);
}



SpeedUp::SpeedUp(Point3f pos, Vector3f sz, float vel) : Buff(pos, sz, Color4f(0.0f, 0.0f, 1.0f, 1.0f), vel) {

}

SpeedUp::~SpeedUp() {

}

void SpeedUp::buff() {
    g_Scene->getPlayer()->setVelocity(g_Scene->getPlayer()->getVelocity() * 1.2f);
}



RateUp::RateUp(Point3f pos, Vector3f sz, float vel) : Buff(pos, sz, Color4f(1.0f, 0.0f, 0.0f, 1.0f), vel) {

}

RateUp::~RateUp() {

}

void RateUp::buff() {
    g_Scene->getPlayer()->setCooldown(g_Scene->getPlayer()->getCooldown() * 0.6f);
}