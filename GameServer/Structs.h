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
	Location() = default;
	~Location() = default;
	void init();

	void set_direction(const Protocol::MoveDirection dir);
	void update(const int64 sectorSize);

	bool is_dirty_position() const { return _positionDirty; }
	bool is_dirty_sector() const { return _sectorDirty; }
	Vector2D get_curpos() const { return _curPos; }
	void set_curpos(const Vector2D& pos) { _curPos = pos; }
	pair<int64, int64> get_cur_sector() const { return make_pair(_sectorX, _sectorY); }
	void set_sector(const int64 x, const int64 y);
private:
	void do_dirty_position() { _positionDirty = true; }
	void do_clear_position() { _positionDirty = false; _oldSectorX = -1; _oldSectorY = -1; }

	void do_dirty_sector() { _sectorDirty = true; }
	void do_clear_sector() { _sectorDirty = false; _oldSectorX = _oldSectorY = 0; }

	// ���� ��ǥ,,, Sync���� ���� ���� + Update���� ���氡��
	Vector2D _curPos = { -1,-1 };
	// ��ġ�� ����Ǿ����� �÷���(���� �Ǿ����� sector�� ������ calc�������)
	volatile bool _positionDirty = false;
	// ����� ��Ŷ���� ���� ������,,, ���� ��Ŷ���� ���� �������� �ٲ�� ������
	Vector2D _dirtyPos = { -1,-1 };

	// ���ʹ� ������ update ������ ���氡��
	int64 _sectorX{};
	int64 _sectorY{};
	int64 _oldSectorX{};
	int64 _oldSectorY{};
	volatile bool _sectorDirty = false;


	

	// �����̴� ������ ������ ��Ŷ���θ� ���氡��
	Protocol::MoveDirection m_MoveDirection = Protocol::PLAYER_MOVE_DIR_NONE;
};
#pragma endregion //Sector
#pragma endregion //LOCATION_STRUCT