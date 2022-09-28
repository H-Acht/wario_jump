#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	constexpr int kWaitFrameMin = 60;
	constexpr int kWaitFrameMax = 180;

	//東の速度
	constexpr float kSpeed = -24.0f;
}

Car::Car()
{
	
	m_handle = -1;
	m_fieldY = 0.0f;
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

	m_vec.x = -16.0f;
	m_vec.y = 0.0f;

	//動き始めるまでの時間を設定　一秒から三秒待つ　60フレームから180フレーム
	m_waitFrame = GetRand(120) + 60;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}
	m_pos += m_vec;
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawFormatString(0, 0, GetColor(255, 255, 255), "wait:%d", m_waitFrame);
}