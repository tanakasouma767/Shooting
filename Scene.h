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
	GameState currentState; // シーンの状態
	Player* player; // プレイヤー
	vector<Bullet*> bullets; // 弾
	vector<Enemy*> enemys; // 敵
	vector<Bullet*> enemyBullets;
	vector<Buff*> buffs;
	chrono::time_point<chrono::high_resolution_clock> previousTime; // 前回取得した時刻

public:
	Scene() : currentState(GameState::InitialScreen) {}
	bool Init(); // 初期化
	void Update(); // 更新処理
	void Draw(); // 描画処理
	void TransitionTo(GameState newState); // シーンの状態遷移
	GameState getState(); // 状態の取得
	vector<Bullet*>& getBullets();
	vector<Bullet*>& getEnemyBullets();
	Player* getPlayer();
	vector<Buff*>& getBuffs();
	void deleteMember();
};

extern Scene* g_Scene;