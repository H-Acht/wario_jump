#include "DxLib.h"
#include "game.h"
#include "car.h"


namespace
{
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	//東の速度
	constexpr float kSpeed = -24.0f;

	//キャラクターのサイズ
	constexpr float kSizeX = 128.0f;
	constexpr float kSizeY = 128.0f;
	//ジャンプ力
	constexpr float kJumpAcc = -30.0f;
	//重力
	constexpr float kGravity = 0.8f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_moveType = kMoveTypeNormal();
	m_waitFrame = 0;
	m_countTimer = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	//動きのバリエーション選択
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum <  38 +30)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 38 + 30 + 30)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}
	//デバッグ用に挙動を決める
	m_moveType = kMoveTypeJump;
	//動き始めるまでの時間を設定　一秒から三秒待つ　60フレームから180フレーム
	m_waitFrame = GetRand(kWaitFrameMax - kWaitFrameMin) + kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFrame);
}

void Car::updateNormal()
{
	m_pos += m_vec;
}

void Car::updateStop()
{
	m_pos += m_vec;
	if (m_pos.x == Game::kScreenWidth / 2)
	{
		m_vec.x = 0;

		m_countTimer++;
		if (m_countTimer > 20)
		{
			m_vec.x = kSpeed;
		}
	}
}

void Car::updateJump()
{
	bool isField = false;
	m_pos += m_vec;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}


	// キー入力処理
	//int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//if (padState & PAD_INPUT_1)
	
	if(m_pos.x == Game::kScreenWidth /2)
	{
		if (isField)
		{
			m_vec.y = kJumpAcc; //ジャンプ開始
		}
	}
	m_vec.y += kGravity;
}

void Car::updateReturn()
{
	m_pos += m_vec;
	if (m_pos.x <= Game::kScreenWidth - 150)
	{
		m_vec.x++;
	}
}