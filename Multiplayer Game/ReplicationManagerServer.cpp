#include "Networks.h"
#include "ReplicationManagerServer.h"

void ReplicationManagerServer::create(uint32 networkId)
{
	RepCommand createCommand;
	createCommand.action = RepAction::Create;
	createCommand.networkId = networkId;

	commands.push_back(createCommand);
}

void ReplicationManagerServer::update(uint32 networkId)
{
	RepCommand updateCommand;
	updateCommand.action = RepAction::Update;
	updateCommand.networkId = networkId;

	commands.push_back(updateCommand);
}

void ReplicationManagerServer::destroy(uint32 networkId)
{
	RepCommand destroyCommand;
	destroyCommand.action = RepAction::Destroy;
	destroyCommand.networkId = networkId;

	commands.push_back(destroyCommand);
}

void ReplicationManagerServer::write(OutputMemoryStream & packet)
{
	for (int i = 0; i < commands.size(); ++i)
	{

		if (commands[i].action == RepAction::Create)
		{
			GameObject* object = nullptr;
			object = App->modLinkingContext->getNetworkGameObject(commands[i].networkId);

			if (object)
			{
				packet << commands[i].networkId;
				packet << commands[i].action;

				packet << object->position.x;
				packet << object->position.y;
				packet << object->angle;
				packet << object->size.x;
				packet << object->size.y;

				std::string texture(object->texture->filename);
				packet << texture;
			}
		}
		else if (commands[i].action == RepAction::Update)
		{
			GameObject* object = nullptr;
			object = App->modLinkingContext->getNetworkGameObject(commands[i].networkId);

			if (object)
			{
				packet << commands[i].networkId;
				packet << commands[i].action;
				packet << object->position.x;
				packet << object->position.y;
				packet << object->angle;
			}
		}
		else if(commands[i].action == RepAction::Destroy)
		{
			
			packet << commands[i].networkId;
			packet << commands[i].action;
			
		}
	}

	commands.clear();
}


void ReplicationManagerServer::AppendLostCommands(std::unordered_map<uint32, ReplicationAction>* repCommands)
{
	for (auto it : *repCommands) {
		if (replicationCommands.find(it.first) == replicationCommands.end()) {
			replicationCommands[it.first] = it.second;
		}
		else {
			if (replicationCommands[it.first] == ReplicationAction::Update) {//only override if the new replication command (not the not send) is in action update
				replicationCommands[it.first] = it.second;
			}
		}
	}
}


ReplicationDeliveryDelegate::ReplicationDeliveryDelegate(std::unordered_map<uint32, ReplicationAction>& map, ReplicationManagerServer* server)
{
	storedReplicationCommands = map;
	serverReplicationManager = server;
}

void ReplicationDeliveryDelegate::OnDeliverySuccess(DeliveryManager * deliveryManager)
{
	//succesfully delivered replication delivery

}

void ReplicationDeliveryDelegate::OnDeliveryFailure(DeliveryManager * deliveryManager)
{
	//resend packet
	serverReplicationManager->AppendLostCommands(&storedReplicationCommands);

}
