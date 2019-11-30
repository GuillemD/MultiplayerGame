#pragma once

#include <list>
class DeliveryManager;

class DeliveryDelegate
{
public:
	void OnDeliverySuccess(DeliveryManager* deliveryManager);
	void OnDeliveryFailure(DeliveryManager* deliveryManager);

};
struct Delivery
{
	uint32 sequenceNumber = 0;
	double dispatchTime = 0.0;
	DeliveryDelegate* delegate = nullptr;
};



class DeliveryManager
{
public:
	// For senders to write a new seq. numbers into a packet 
	Delivery* WriteSequenceNumber(OutputMemoryStream& packet);

	// For receivers to process the seq. number from an incoming packet 
	bool ProcessSequenceNumber(const InputMemoryStream& packet);

	// For receivers to write ack'ed seq. numbers into a packet 
	bool HasSequenceNumbersPendingAck() const;
	void WriteSequenceNumbersPendingAck(OutputMemoryStream& packet);

	// For senders to process ack'ed seq. numbers from a packet
	void ProcessAckdSequenceNumbers(const InputMemoryStream& packet);
	void ProcessTimedOutPackets();

	void Clear();

private:


	// Private members (receiver side)
	// - The next expected sequence number
	uint32 nextSeqNumExpected = 0u;

	// - A list of sequence numbers pending ack
	std::list<uint32> pendingNumSeqList;

	// Private members (sender side)
	// - The next outgoing sequence number
	uint32 nextSeqNum = 0u;
public:
	// - A list of pending deliveries
	std::list<Delivery*> pendingDeliveries;
};
