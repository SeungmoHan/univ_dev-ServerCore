#include "pch.h"
#include "Structs.h"

Vector2D Vector2D::operator+(const Vector2D other)
{
	return { _x += other._x ,_y += other._y };
}
Vector2D Vector2D::operator-(const Vector2D other)
{
	return 	{ _x -= other._x, _y -= other._y };;
}

Vector2D Vector2D::operator+=(const Vector2D other)
{
	*this = *this + other;
	return *this;
}

Vector2D Vector2D::operator-=(const Vector2D other)
{
	*this = *this - other;
	return *this;
}


void Location::init()
{
	_curPos._x = rand() % 6400;
	_curPos._y = rand() % 6400;
	_sectorX = -1;
	_sectorY = -1;
	set_direction(Protocol::MoveDirection::PLAYER_MOVE_DIR_NONE);
	do_clear();
}

void Location::set_direction(const Protocol::MoveDirection dir)
{
	m_MoveDirection = dir;
}

void Location::update(const int64 sectorSize)
{
#pragma region Vector<Vector2D>locVec
	//	PLAYER_MOVE_DIR_NONE = 0,
	//	PLAYER_MOVE_DIR_LEFT = 1,
	//	PLAYER_MOVE_DIR_RIGHT = 2,
	//	PLAYER_MOVE_DIR_UP = 3,
	//	PLAYER_MOVE_DIR_DOWN = 4,
	static const Vector<Vector2D> locVec{ Vector2D{0,0},
		Vector2D{-1,0}, Vector2D{1,0}, Vector2D{0,1}, Vector2D{0,-1} };
#pragma endregion

	const auto& curMove = locVec[m_MoveDirection];

	_curPos += curMove;

	const int64 calcSectorX = _curPos._x / sectorSize;
	const int64 calcSectorY = _curPos._y / sectorSize;

	if(calcSectorX != _sectorX || calcSectorY != _sectorY)
	{
		_sectorX = calcSectorX;
		_sectorY = calcSectorY;

		do_dirty();
	}

}
