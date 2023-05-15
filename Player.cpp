#include "Player.h"
#include"Input.h"
#include<cassert>
#include"ImGuiManager.h"
#include"MathUtility.h"

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}


void Player::Attack() {
	/*if (bullet_) {
		delete bullet_;
		bullet_ = nullptr;
	}*/

	if (input_->TriggerKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		//速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity,worldTransform_.matWorld_);

		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_,worldTransform_.translation_, velocity);

		//bullet_ = newBullet;
		bullets_.push_back(newBullet);
	}
}


void Player::Initialize(Model*model,uint32_t textureHandle) {
	//nullポインタチェック
	assert(model);
	model_ = model;
	worldTransform_.Initialize();

	textureHandle_ = textureHandle;
	input_ = Input::GetInstance();
}

void Player::Update() {

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	Vector3 move = {0, 0, 0};

	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	worldTransform_.TransferMatrix();

	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y += kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;

	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	Attack();

	/*if (bullet_) {
		bullet_->Update();
	}*/

	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	worldTransform_.matWorld_ = MakeAffineMatrix(
	worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


	const float kMoveLimitX = 10.0f;
	const float kMoveLimitY = 10.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	//行列転送
	worldTransform_.TransferMatrix();

	ImGui::Begin("player");
	float sliderValue[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,worldTransform_.translation_.z};
	ImGui::SliderFloat3("position", sliderValue, -20.0f, 20.0f);
	worldTransform_.translation_ = {sliderValue[0], sliderValue[1], sliderValue[2]};
	ImGui::End();


}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	/*if (bullet_) {
		bullet_->Draw(viewProjection);
	}*/
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}
