#pragma once

#pragma region LOCATION_STRUCT
#pragma region Vector2D
struct Vector2D
{
	Vector2D(const int64 x, const int64 y ) : _x(x), _y(y){}

	Vector2D operator+(Vector2D other);
	Vector2D operator-(Vector2D other);
	Vector2D operator+=(Vector2D other);
	Vector2D operator-=(Vector2D other);

	int64 _x;
	int64 _y;
};
#pragma endregion //Vector2D

#pragma region Sector
class Location
{
public:
	void init();

	void set_direction(const Protocol::MoveDirection dir);
	void update(const int64 sectorSize);

	bool is_dirty() const { return _dirtyFlag; }

	Vector2D get_curpos() const { return _curPos; }
	pair<int64, int64> get_cur_sector() const { return make_pair(_sectorX, _sectorY); }
private:
	void do_dirty() { _dirtyFlag = true; }
	void do_clear() { _dirtyFlag = false; _oldSectorX = -1; _oldSectorY = -1; }

	Vector2D _curPos{ -1,-1 };
	int64 _sectorX{};
	int64 _sectorY{};

	int64 _oldSectorX{};
	int64 _oldSectorY{};
	Protocol::MoveDirection m_MoveDirection = Protocol::PLAYER_MOVE_DIR_NONE;
	// sector 변경되었는지 플래그
	bool _dirtyFlag = false;
};
#pragma endregion //Sector
#pragma endregion //LOCATION_STRUCT