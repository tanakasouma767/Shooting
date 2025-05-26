#include "Scene.h"
Scene* g_Scene;


void DrawText(const std::string& text, float x, float y, void* font = GLUT_BITMAP_HELVETICA_18) {
	glRasterPos2f(x, y); // 描画位置（-1.0〜1.0の範囲）
	for (char c : text) {
		glutBitmapCharacter(font, c);
	}
}

bool Scene::Init()
{
	auto currentTime = chrono::high_resolution_clock::now();
	previousTime = currentTime;

	// プレイヤーの生成
	Point3f position(0.0f, 0.0f, 0.0f);
	Vector3f size(1.0f, 1.0f, 1.0f);
	Color4f color(1.0f, 1.0f, 1.0f, 1.0f);
	player = new Player(position, size, color);

	// 敵1
	Point3f enemy1_position(0.5f, 1.2f, 0.0f);
	Vector3f enemy1_size(1.0f, 1.0f, 1.0f);
	Color4f enemy1_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy1_velocity = 0.1f;
	float enemy1_hp = 4;
	EnemyA* enemy1 = new EnemyA(enemy1_position, enemy1_size, enemy1_color, enemy1_velocity, enemy1_hp);
	enemys.push_back(enemy1);

	// 敵2
	Point3f enemy2_position(-0.5f, 1.2f, 0.0f);
	Vector3f enemy2_size(1.0f, 1.0f, 1.0f);
	Color4f enemy2_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy2_velocity = 0.1f;
	float enemy2_hp = 4;
	EnemyA* enemy2 = new EnemyA(enemy2_position, enemy2_size, enemy2_color, enemy2_velocity, enemy2_hp);
	enemys.push_back(enemy2);

	// 敵3
	Point3f enemy3_position(1.0f, 2.0f, 0.0f);
	Vector3f enemy3_size(1.0f, 1.0f, 1.0f);
	Color4f enemy3_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy3_velocity = 0.1f;
	float enemy3_hp = 4;
	EnemyB* enemy3 = new EnemyB(enemy3_position, enemy3_size, enemy3_color, enemy3_velocity, enemy3_hp);
	enemys.push_back(enemy3);

	// 敵4
	Point3f enemy4_position(-1.0f, 2.0f, 0.0f);
	Vector3f enemy4_size(1.0f, 1.0f, 1.0f);
	Color4f enemy4_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy4_velocity = 0.1f;
	float enemy4_hp = 4;
	EnemyB* enemy4 = new EnemyB(enemy4_position, enemy4_size, enemy4_color, enemy4_velocity, enemy4_hp);
	enemys.push_back(enemy4);

	// 敵5 回復バフ
	Point3f enemy5_position(0.0f, 2.5f, 0.0f);
	Vector3f enemy5_size(1.0f, 1.0f, 1.0f);
	Color4f enemy5_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy5_velocity = 0.1f;
	float enemy5_hp = 4;
	EnemyC* enemy5 = new EnemyC(enemy5_position, enemy5_size, enemy5_color, enemy5_velocity, enemy5_hp);
	enemys.push_back(enemy5);

	// 敵6 速度バフ
	Point3f enemy6_position(0.5f, 3.5f, 0.0f);
	Vector3f enemy6_size(1.0f, 1.0f, 1.0f);
	Color4f enemy6_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy6_velocity = 0.1f;
	float enemy6_hp = 4;
	EnemyD* enemy6 = new EnemyD(enemy6_position, enemy6_size, enemy6_color, enemy6_velocity, enemy6_hp);
	enemys.push_back(enemy6);

	// 敵7 発射レートバフ
	Point3f enemy7_position(-0.5f, 3.5f, 0.0f);
	Vector3f enemy7_size(1.0f, 1.0f, 1.0f);
	Color4f enemy7_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy7_velocity = 0.1f;
	float enemy7_hp = 4;
	EnemyE* enemy7 = new EnemyE(enemy7_position, enemy7_size, enemy7_color, enemy7_velocity, enemy7_hp);
	enemys.push_back(enemy7);

	// 敵8
	Point3f enemy8_position(0.0f, 4.5f, 0.0f);
	Vector3f enemy8_size(1.0f, 1.0f, 1.0f);
	Color4f enemy8_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy8_velocity = 0.1f;
	float enemy8_hp = 4;
	EnemyA* enemy8 = new EnemyA(enemy8_position, enemy8_size, enemy8_color, enemy8_velocity, enemy8_hp);
	enemys.push_back(enemy8);

	// 敵9
	Point3f enemy9_position(1.0f, 4.5f, 0.0f);
	Vector3f enemy9_size(1.0f, 1.0f, 1.0f);
	Color4f enemy9_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy9_velocity = 0.1f;
	float enemy9_hp = 4;
	EnemyB* enemy9 = new EnemyB(enemy9_position, enemy9_size, enemy9_color, enemy9_velocity, enemy9_hp);
	enemys.push_back(enemy9);

	// 敵10
	Point3f enemy10_position(-1.0f, 4.5f, 0.0f);
	Vector3f enemy10_size(1.0f, 1.0f, 1.0f);
	Color4f enemy10_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy10_velocity = 0.1f;
	float enemy10_hp = 4;
	EnemyB* enemy10 = new EnemyB(enemy10_position, enemy10_size, enemy10_color, enemy10_velocity, enemy10_hp);
	enemys.push_back(enemy10);

	// 敵11 回復バフ
	Point3f enemy11_position(0.0f, 5.5f, 0.0f);
	Vector3f enemy11_size(1.0f, 1.0f, 1.0f);
	Color4f enemy11_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy11_velocity = 0.1f;
	float enemy11_hp = 4;
	EnemyC* enemy11 = new EnemyC(enemy11_position, enemy11_size, enemy11_color, enemy11_velocity, enemy11_hp);
	enemys.push_back(enemy11);

	// 敵12 速度バフ
	Point3f enemy12_position(0.5f, 5.5f, 0.0f);
	Vector3f enemy12_size(1.0f, 1.0f, 1.0f);
	Color4f enemy12_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy12_velocity = 0.1f;
	float enemy12_hp = 4;
	EnemyD* enemy12 = new EnemyD(enemy12_position, enemy12_size, enemy12_color, enemy12_velocity, enemy12_hp);
	enemys.push_back(enemy12);

	// 敵13 発射レートバフ
	Point3f enemy13_position(-0.5f, 5.5f, 0.0f);
	Vector3f enemy13_size(1.0f, 1.0f, 1.0f);
	Color4f enemy13_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy13_velocity = 0.1f;
	float enemy13_hp = 4;
	EnemyE* enemy13 = new EnemyE(enemy13_position, enemy13_size, enemy13_color, enemy13_velocity, enemy13_hp);
	enemys.push_back(enemy13);

	// 敵14
	Point3f enemy14_position(0.5f, 6.5f, 0.0f);
	Vector3f enemy14_size(1.0f, 1.0f, 1.0f);
	Color4f enemy14_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy14_velocity = 0.1f;
	float enemy14_hp = 4;
	EnemyA* enemy14 = new EnemyA(enemy14_position, enemy14_size, enemy14_color, enemy14_velocity, enemy14_hp);
	enemys.push_back(enemy14);

	// 敵15
	Point3f enemy15_position(-0.5f, 6.5f, 0.0f);
	Vector3f enemy15_size(1.0f, 1.0f, 1.0f);
	Color4f enemy15_color(0.0f, 0.0f, 0.0f, 0.0f);
	float enemy15_velocity = 0.1f;
	float enemy15_hp = 4;
	EnemyA* enemy15 = new EnemyA(enemy15_position, enemy15_size, enemy15_color, enemy15_velocity, enemy15_hp);
	enemys.push_back(enemy15);

	// 敵13 発射レートバフ
	Point3f boss_position(0.0f, 18.0f, 0.0f);
	Vector3f boss_size(1.0f, 1.0f, 1.0f);
	Color4f boss_color(0.0f, 0.0f, 0.0f, 0.0f);
	float boss_velocity = 0.3f;
	float boss_hp = 8;
	Boss* boss = new Boss(boss_position, boss_size, boss_color, boss_velocity, boss_hp);
	enemys.push_back(boss);

	return true;
}


void Scene::Update()
{
	// 初期画面
	if (currentState == GameState::InitialScreen) {
		auto currentTime = chrono::high_resolution_clock::now();
		previousTime = currentTime;

		if (keyStates['r']) {
			TransitionTo(GameState::Gameplay); // Rでゲーム開始
		}
		return;
	}

	// ゲームプレイメイン画面
	if (currentState == GameState::Gameplay) {
		auto currentTime = chrono::high_resolution_clock::now();
		float deltaTime = chrono::duration<float>(currentTime - previousTime).count();
		previousTime = currentTime;

		// プレイヤーの更新
		player->Update(deltaTime);

		// 弾の更新
		for (Bullet* bullet : bullets)
		{
			bullet->Update(deltaTime);
		}

		// 画面外に行った弾の削除
		for (auto it = bullets.begin(); it != bullets.end(); )
		{
			if ((*it)->getPos().x > 1.0f || (*it)->getPos().x < -1.0f || (*it)->getPos().y > 1.0f || (*it)->getPos().y < -1.0f) {
				delete* it;
				it = bullets.erase(it);
			}
			else {
				++it;
			}
		}

		// 敵の更新
		for (Enemy* enemy : enemys) {
			enemy->Update(deltaTime);
		}
		// 弾の更新
		for (Bullet* enemyBullet : enemyBullets)
		{
			enemyBullet->Update(deltaTime);
		}
		// 画面外に行った弾の削除
		for (auto it = enemyBullets.begin(); it != enemyBullets.end(); )
		{
			if ((*it)->getPos().x > 1.0f || (*it)->getPos().x < -1.0f || (*it)->getPos().y > 1.0f || (*it)->getPos().y < -1.0f) {
				delete* it;
				it = enemyBullets.erase(it);
			}
			else {
				++it;
			}
		}

		// バフアイテムの更新
		for (Buff* buff : buffs)
		{
			buff->Update(deltaTime);
		}
		// 画面外に行ったバフアイテムの削除
		for (auto it = buffs.begin(); it != buffs.end(); )
		{
			if ((*it)->getPos().x > 1.0f || (*it)->getPos().x < -1.0f || (*it)->getPos().y > 1.0f || (*it)->getPos().y < -1.0f) {
				delete* it;
				it = buffs.erase(it);
			}
			else {
				++it;
			}
		}

		// バフアイテムとプレイヤーの衝突判定
		for (auto it = buffs.begin(); it != buffs.end(); ) {
			Buff* buff = *it;

			float dx = buff->getPos().x - player->getPos().x;
			float dy = buff->getPos().y - player->getPos().y;
			float distance = sqrtf(dx * dx + dy * dy);

			if (distance < 0.05f) { // サイズに応じて調整
				buff->buff();
				delete buff;
				it = buffs.erase(it);
			}
			else {
				++it;
			}
		}

		// プレイヤーの弾と敵の衝突判定
		for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
			Bullet* bullet = *bulletIt;
			bool bulletHit = false;

			for (auto enemyIt = enemys.begin(); enemyIt != enemys.end(); ) {
				Enemy* enemy = *enemyIt;

				// 簡易的な衝突判定（距離が一定以下）
				float dx = bullet->getPos().x - enemy->getPos().x;
				float dy = bullet->getPos().y - enemy->getPos().y;
				float distance = sqrtf(dx * dx + dy * dy);

				if (distance < 0.05f) { // ←サイズに応じて調整
					enemy->TakeDamage(1);
					bulletHit = true;

					// 敵が死んだら削除
					if (enemy->IsDead()) {
						delete enemy;
						enemyIt = enemys.erase(enemyIt);
					}
					else {
						++enemyIt;
					}
				}
				else {
					++enemyIt;
				}
			}

			if (bulletHit) {
				delete bullet;
				bulletIt = bullets.erase(bulletIt);
			}
			else {
				++bulletIt;
			}
		}

		// 敵弾とプレイヤーの衝突判定
		for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
			Bullet* bullet = *it;

			float dx = bullet->getPos().x - player->getPos().x;
			float dy = bullet->getPos().y - player->getPos().y;
			float distance = sqrtf(dx * dx + dy * dy);

			if (distance < 0.05f) { // サイズに応じて調整
				player->TakeDamage(1);
				delete bullet;
				it = enemyBullets.erase(it);

				// プレイヤー死亡時の処理（例：シーン遷移）
				if (player->IsDead()) {
					delete player;
					player = nullptr;
					TransitionTo(GameState::GameOver);
					break;
				}
			}
			else {
				++it;
			}
		}
	}

	// クリア画面
	if (currentState == GameState::Clear) {
		if (keyStates['r']) {
			printf("Game Restarted\n");
			deleteMember();
			Init();
			TransitionTo(GameState::InitialScreen); // Rで初期画面に戻る
		}
	}

	// 失敗画面
	if (currentState == GameState::GameOver) {
		if (keyStates['r']) {
			printf("Game Restarted\n");
			deleteMember();
			Init();
			TransitionTo(GameState::InitialScreen); // Rで初期画面に戻る
		}
	}
}


void Scene::Draw()
{
	// 初期画面
	if (currentState == GameState::InitialScreen) {
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawText("move:WASD", -0.2f, 0.0f);
		DrawText("shot:Enter", -0.2f, -0.1f);
		DrawText("start:R", -0.2f, -0.3f);
	}

	// ゲームプレイ画面
	if (currentState == GameState::Gameplay) {
		// プレイヤーの描画
		player->Draw();
		// 弾の描画
		for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Draw();
		}

		// 敵の描画
		for (size_t i = 0; i < enemys.size(); i++)
		{
			enemys[i]->Draw();
		}
		// 弾の描画
		for (size_t i = 0; i < enemyBullets.size(); i++)
		{
			enemyBullets[i]->Draw();
		}

		// バフアイテムの描画
		for (size_t i = 0; i < buffs.size(); i++)
		{
			buffs[i]->Draw();
		}
	}

	// クリア表示
	if (currentState == GameState::Clear) {
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawText("Clear", -0.2f, 0.0f);
		DrawText("restart:R", -0.2f, -0.3f);
	}

	// 失敗表示
	if (currentState == GameState::GameOver) {
		glColor3f(0.0f, 0.0f, 0.0f);
		DrawText("GameOver", -0.2f, 0.0f);
		DrawText("restart:R", -0.2f, -0.3f);
	}
}

void Scene::TransitionTo(GameState newState)
{
	currentState = newState;

	if (currentState == GameState::Gameplay) {
		printf("Gameplay started\n");
	}
	else if (currentState == GameState::Clear) {
		printf("Clear screen displayed\n");
	}
}

GameState Scene::getState() {
	return currentState;
}

vector<Bullet*>& Scene::getBullets() {
	return bullets;
}

vector<Bullet*>& Scene::getEnemyBullets() {
	return enemyBullets;
}

Player* Scene::getPlayer() {
	return player;
}

vector<Buff*>& Scene::getBuffs() {
	return buffs;
}

void Scene::deleteMember()
{
	// プレイヤーの解放
	delete player;

	// 弾の解放
	for (Bullet* bullet : bullets)
	{
		delete bullet;
	}
	bullets.clear();

	// 敵の解放
	for (Enemy* enemy : enemys) {
		delete enemy;
	}
	enemys.clear();

	// 敵の弾の解放
	for (Bullet* bullet : enemyBullets)
	{
		delete bullet;
	}
	enemyBullets.clear();

	// バフアイテムの解放
	for (Buff* buff : buffs)
	{
		delete buff;
	}
	buffs.clear();
}