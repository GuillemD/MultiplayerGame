#include "Networks.h"

Delivery* DeliveryManager::WriteSequenceNumber(OutputMemoryStream& packet)
{
	return nullptr;
}

bool DeliveryManager::ProcessSequenceNumber(const InputMemoryStream& packet)
{
	return false;
}

bool DeliveryManager::HasSequenceNumbersPendingAck() const
{
	return false;
}

void DeliveryManager::WritesequenceNumbersPendingAck(OutputMemoryStream& packet)
{
}

void DeliveryManager::ProcessAckdSequenceNumbers(const InputMemoryStream& packet)
{
}

void DeliveryManager::ProcessTimedOutPackets()
{
}

void DeliveryManager::Clear()
{
}