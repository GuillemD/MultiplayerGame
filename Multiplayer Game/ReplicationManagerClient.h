#pragma once
class ModuleNetworkingClient;
class ReplicationManagerClient
{
public:
	void Read(const InputMemoryStream& packet, ModuleNetworkingClient* client);
};