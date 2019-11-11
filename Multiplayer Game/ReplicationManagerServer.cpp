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

