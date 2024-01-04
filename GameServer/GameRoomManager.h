#pragma once


class Room;

class GameRoomManager
{
public:
	Atomic<uint64> m_RoomKeyGenerator = 1;
	static GameRoomManager& Instance()
	{
		static GameRoomManager instance;
		return instance;
	}

	ptr<Room> GetDefaultEnterRoom() { return m_RoomMap[1]; }

	void Update(uint64 deltaTick);

	void CreateRoom();
	void EraseRoom(uint64 roomKey);

	void EnterRoom(uint64 roomKey, const PlayerPtr& player);
	void LeaveRoom(uint64 roomKey, const PlayerPtr& player);


private:
	GameRoomManager();

	HashMap<uint64, ptr<Room>> m_RoomMap;
};
