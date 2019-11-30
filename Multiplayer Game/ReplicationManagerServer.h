#pragma once
#include <list>


enum class ReplicationAction
{
	None,
	Create,
	Update,
	Destroy,
	Notification
};

struct ReplicationCommand
{
	ReplicationCommand(ReplicationAction action, uint32 networkId, uint32 data = 0u) : action(action), networkId(networkId), data(data) {}

	ReplicationAction action = ReplicationAction::None;
	uint32 networkId = 0u;

	uint32 data = 0u;
};

class ReplicationManagerServer
{
public:
	void create(uint32 networkId);
	void update(uint32 networkId);
	void destroy(uint32 networkId);
	void notification(uint32 networkId, uint32 data);

	void write(OutputMemoryStream& packet);
	// More members... 

public:
	std::list<ReplicationCommand*> commandList;
};
