#include "Networks.h"
#include "DeliveryManager.h"

Delivery* DeliveryManager::WriteSequenceNumber(OutputMemoryStream& packet)
{
	packet << nextSeqNum;

	Delivery* delivery = new Delivery;
	delivery->delegate = new DeliveryDelegate;

	delivery->dispatchTime = Time.time;
	delivery->sequenceNumber = nextSeqNum;
	nextSeqNum++;

	pendingDeliveries.push_back(delivery);

	return delivery;
}

bool DeliveryManager::ProcessSequenceNumber(const InputMemoryStream& packet)
{
	bool ret = false;

	uint32 currSeqNum; packet >> currSeqNum;

	if (currSeqNum >= nextSeqNumExpected)
	{
		pendingNumSeqList.push_back(currSeqNum);
		nextSeqNumExpected = currSeqNum + 1;
		ret = true;
	}

	return ret;
}

bool DeliveryManager::HasSequenceNumbersPendingAck() const
{
	return !pendingNumSeqList.empty();
}

void DeliveryManager::WriteSequenceNumbersPendingAck(OutputMemoryStream& packet)
{
	packet << pendingNumSeqList.size();
	for (std::list<uint32>::const_iterator it = pendingNumSeqList.begin(); it != pendingNumSeqList.end(); ++it)
	{
		packet << *it;
	}
	pendingNumSeqList.clear();
}

void DeliveryManager::ProcessAckdSequenceNumbers(const InputMemoryStream& packet)
{
	int size; packet >> size;

	for (int it = 0; it < size; ++it)
	{
		uint32 seqNum; packet >> seqNum;

		for (auto delivery : pendingDeliveries)
		{
			if (delivery->sequenceNumber == seqNum)
			{
				delivery->delegate->OnDeliverySuccess(this);
				pendingDeliveries.remove(delivery);
				delete delivery->delegate;
				delete delivery;
				break;
			}
		}
	}
}

void DeliveryManager::ProcessTimedOutPackets()
{
	std::list<std::list<Delivery*>::iterator> toDelete;

	for (std::list<Delivery*>::iterator it = pendingDeliveries.begin(); it != pendingDeliveries.end(); ++it)
	{
		if (Time.time - (*it)->dispatchTime >= PACKET_DELIVERY_TIMEOUT_SECONDS)
		{
			(*it)->delegate->OnDeliveryFailure(this);
			toDelete.push_back(it);
			delete (*it)->delegate;
			delete* it;
		}
	}

	for (auto mode : toDelete)
	{
		pendingDeliveries.erase(mode);
	}
}

void DeliveryManager::Clear()
{
	for (auto delivery : pendingDeliveries)
	{
		delete delivery->delegate;
		delete delivery;
	}
	pendingDeliveries.clear();
	pendingNumSeqList.clear();
}


//---------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------DELIVERY DELEGATE-----------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

void DeliveryDelegate::OnDeliverySuccess(DeliveryManager* deliveryManager)
{
	//
}

void DeliveryDelegate::OnDeliveryFailure(DeliveryManager* deliveryManager)
{
	//
}
