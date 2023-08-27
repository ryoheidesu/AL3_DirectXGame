#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <Enemy.h>
#include <EnemyBullet.h>
#include <Player.h>
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}

	delete debugCamera_;
	delete skydome_;
	delete modelSkydome_;
	delete railCamera_;
	delete ui_;
}

void GameScene::Initialize() {

	worldTransform_.Initialize();
	viewProjection_.Initialize();

	// レティクルのテクスチャ
	TextureManager::Load("target.png");
	// タイトルのテクスチャ
	TextureManager::Load("title.png");
	// 自キャラの生成
	player_ = new Player();
	Vector3 playerPosition{0, 0, 50};
	// 自キャラの初期化
	textureHandleP_ = TextureManager::Load("Player.png");
	// 敵キャラの生成
	Enemy* newEnemy = new Enemy();

	// 敵キャラの初期化
	textureHandleE_ = TextureManager::Load("Enemy.png");
	// 天球の生成
	skydome_ = new Skydome();
	// レールカメラの生成
	railCamera_ = new RailCamera();
	ui_ = new Ui();
	LoadEnemyPopData();

	// 読み込み
	// モデル生成
	model_ = Model::Create();
	player_->Initialize(model_, textureHandleP_, playerPosition);
	player_->SetParent(&railCamera_->GetWorldTransform());
	ui_->Initialize();

	newEnemy->Initialize(model_, textureHandleE_);
	newEnemy->SetPlayer(player_);
	// newEnemy->Initialize(model_, textureHandleE_);
	// 敵キャラにゲームシーンを渡す
	newEnemy->SetGameScene(this);
	enemys_.push_back(newEnemy);

	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	// 　天球の初期化
	skydome_->Initialize(modelSkydome_);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	AxisIndicator::GetInstance()->SetVisible(true);

	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	/*viewProjection_.farZ = 10.0f;
	viewProjection_.Initialize();*/
	// レールカメラ初期化
	railCamera_->Initialize(worldTransform_.translation_, worldTransform_.rotation_);
}

void GameScene::Update() {
	///
	/// シーン処理
	///
	switch (scene) {
	// タイトル
	case GameScene::Scene::Title:

		if (input_->TriggerKey(DIK_SPACE)) {
			scene = Scene::GamePlay;
		}
		break;

	// ゲームプレイ
	case GameScene::Scene::GamePlay:
		// 自キャラの更新
		player_->Update(viewProjection_);
		// 敵キャラの更新
		for (Enemy* enemy : enemys_) {
			enemy->Update();
		}

		UpdateEnemyPopCommands();

		CheckAllCollisions();
		railCamera_->Update();
#ifdef _DEBUG
		// デバックカメラキー
		if (input_->TriggerKey(DIK_RETURN)) {
			isDebugCameraActive_ = true;
		}

#endif // DEBUG

		if (isDebugCameraActive_) {
			debugCamera_->Update();

			/*viewProjection_.matView = debugCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;*/

		} else {
			viewProjection_.matView = railCamera_->GetViewProjection().matView;
			viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
			// viewProjection_.UpdateMatrix();
			viewProjection_.TransferMatrix();
		}

		enemys_.remove_if([](Enemy* enemy) {
			if (enemy->IsDead()) {
				delete enemy;
				return true;
			}
			return false;
		});

		enemyBullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
			return false;
		});

		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Update();
		}

		break;

		// リザルト
	case GameScene::Scene::Result:
		// スペースでタイトルへ
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = Scene::Title;
		}
		break;

	default:

		break;
	}
}

void GameScene::AddEnemy(Enemy* enemy) { enemys_.push_back(enemy); }

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	switch (scene) {
	case GameScene::Scene::Title:
		break;
	case GameScene::Scene::GamePlay:
		// 自キャラの描画
		player_->Draw(viewProjection_);
		// 敵キャラの描画
		for (Enemy* enemy : enemys_) {
			enemy->Draw(viewProjection_);
		}
		// 天球の描画
		skydome_->Draw(viewProjection_);
		// 敵弾の描画
		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Draw(viewProjection_);
		}
		break;
	case GameScene::Scene::Result:
		break;
	default:
		break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	switch (scene) {
	case GameScene::Scene::Title:
		ui_->Draw();
		break;
	case GameScene::Scene::GamePlay:
		player_->DrawUI();
		break;
	case GameScene::Scene::Result:
		break;
	default:
		break;
	}
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// ファイル読み込み
void GameScene::LoadEnemyPopData() {

	std::ifstream file;
	file.open("./Resources/enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::AddEnemy(Vector3 pos) {
	Enemy* enemy = new Enemy();
	enemy->Initialize(model_, textureHandleE_, pos);
	enemy->SetPlayer(player_);
	enemy->SetGameScene(this);
	enemys_.push_back(enemy);
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	const std::list<EnemyBullet*>& enemyBullets = enemyBullets_;

// 自キャラと敵弾の当たり判定
#pragma region
	posA = player_->GetWorldPosition();

	for (EnemyBullet* bullet_ : enemyBullets) {
		posB = bullet_->GetWorldPosition();
		float dist = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
		             (posB.z - posA.z) * (posB.z - posA.z);

		if (dist < (player_->GetRadius() + bullet_->GetRadius())) {
			player_->OnCollision();

			bullet_->OnCollision();

			scene = Scene::Result;
			
		}
	}

#pragma endregion

// 自弾と敵キャラの当たり判定
#pragma region
	for (Enemy* enemy : enemys_) {
		posA = enemy->GetWorldPosition();

		for (PlayerBullet* bullet_ : playerBullets) {
			posB = bullet_->GetWorldPosition();
			float dist = (posB.x - posA.x) * (posB.x - posA.x) +
			             (posB.y - posA.y) * (posB.y - posA.y) +
			             (posB.z - posA.z) * (posB.z - posA.z);

			if (dist < (bullet_->GetRadius() + enemy->GetRadius())) {
				enemy->OnCollision();

				bullet_->OnCollision();
			}
		}
	}
#pragma endregion

// 自弾と敵弾の当たり判定
#pragma region

	for (PlayerBullet* playerbullet_ : playerBullets) {
		for (EnemyBullet* enemybullet_ : enemyBullets) {
			posA = enemybullet_->GetWorldPosition();
			posB = playerbullet_->GetWorldPosition();
			float dist = (posB.x - posA.x) * (posB.x - posA.x) +
			             (posB.y - posA.y) * (posB.y - posA.y) +
			             (posB.z - posA.z) * (posB.z - posA.z);

			if (dist < (playerbullet_->GetRadius() + enemybullet_->GetRadius())) {
				enemybullet_->OnCollision();
				playerbullet_->OnCollision();
			}
		}
	}
#pragma endregion
}

void GameScene::UpdateEnemyPopCommands() {

	if (waitFlag) {
		waitTimer--;
		if (waitTimer <= 0) {
			waitFlag = false;
		}
		return;
	}

	std::string line;
	while (getline(enemyPopCommands, line)) {
		std::istringstream line_stream(line);

		std::string word;

		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}

		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			AddEnemy(Vector3(x, y, z));
		} else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			int32_t waitTime = atoi(word.c_str());

			waitFlag = true;
			waitTimer = waitTime;

			break;
		}
	}
}