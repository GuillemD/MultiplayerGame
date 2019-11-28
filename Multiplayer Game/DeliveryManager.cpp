#include "Networks.h"
#include "DeliveryManager.h"

Delivery * DeliveryManager::writeSequenceNumber(OutputMemoryStream & packet, DeliveryDelegate& _delegate)
{
	packet << nextSequenceNumber;

	Delivery delivery;
	delivery.dispatchTime = Time.time;
	delivery.sequenceNumber = nextSequenceNumber++;
	delivery.delegate = &_delegate;

	pendingDeliveries.push_back(delivery);

	return &delivery;
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