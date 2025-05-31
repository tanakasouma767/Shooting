#pragma once
#include <vector>
#include "GameObject.h"
#include <chrono>
using namespace std;

enum class GameState
{
	InitialScreen,
	Gameplay,
	Clear,
	GameOver
};

class Scene
{
private:
	GameState currentState; // �V�[���̏��
	Player* player; // �v���C���[
	vector<Bullet*> bullets; // �e
	vector<Enemy*> enemys; // �G
	vector<Bullet*> enemyBullets; // �G�̒e
	vector<Buff*> buffs; // �o�t�A�C�e��
	chrono::time_point<chrono::high_resolution_clock> previousTime; // �O��擾��������

public:
	Scene();
	~Scene();
	bool Init(); // ������
	void Update(); // �X�V����
	void Draw(); // �`�揈��
	void TransitionTo(GameState newState); // �V�[���̏�ԑJ��
	GameState getState(); // ��Ԃ̎擾
	vector<Bullet*>& getBullets();
	vector<Bullet*>& getEnemyBullets();
	Player* getPlayer();
	vector<Buff*>& getBuffs();
	void deleteMember();
};

extern Scene* g_Scene;