#pragma once

#include "Vec2.h"
#include "car.h"

class Player
{
public:
	Player();
	virtual ~Player() {}

	// グラフィックデータの設定	内部でサイズも取得する
	void setGraphic(int handle);

	// 初期設定	地面の高さを与える
	void setup( float fieldY );

	// 更新
	void update();
	// 描画
	void draw();

	// 車との衝突判定
	bool isCol(Car& car);

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getGraphSize() const { return m_graphSize; }
	Vec2 getColSize() const { return m_colSize; }

	// 死亡設定
	void setDead(bool isDead) { m_isDead = isDead; }

private:
	// グラフィックハンドル
	int m_handle;
	// グラフィックの幅と高さ
	Vec2 m_graphSize;
	// 当たり判定の幅と高さ
	Vec2 m_colSize;

	// 位置
	Vec2 m_pos;
	// ベクトル
	Vec2 m_vec;
	// 地面の高さ
	float m_fieldY;

	bool m_isDead;
};