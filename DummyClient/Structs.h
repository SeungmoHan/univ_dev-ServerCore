#pragma once

#pragma region LOCATION_STRUCT
#pragma region Vector2D
struct Vector2D
{
	int64 _x;
	int64 _y;
};
#pragma endregion //Vector2D

#pragma region Sector
class Location
{
public:
	Vector2D _curPos{ -1,-1 };
	int64 _sectorX{};
	int64 _sectorY{};
};
#pragma endregion //Sector
#pragma endregion //LOCATION_STRUCT