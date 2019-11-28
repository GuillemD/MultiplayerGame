#pragma once

class DeliveryManager;

class DeliveryDelegate
{
public:
	virtual void OnDeliverySuccess(DeliveryManager* deliveryManager) = 0;
	virtual void OnDeliveryFailure(DeliveryManager* deliveryManager) = 0;

};

struct Delivery
{
	uint32 sequenceNumber = 0;
	double dispatchTime = 0.0;
	DeliveryDelegate* delegate = nullptr;

	void CleanUp();
};



class DeliveryManager
{
public:

	// For senders to write a new seq. numbers into a packet 
	Delivery* writeSequenceNumber(OutputMemoryStream &packet, DeliveryDelegate &delegate);

	// For receivers to process the seq. number from an incoming packet 
	bool ProcessSequenceNumber(const InputMemoryStream& packet);

	// For receivers to write ack'ed seq. numbers into a packet 
	bool HasSequenceNumbersPendingAck() const;
	void WritesequenceNumbersPendingAck(OutputMemoryStream& packet);

	// For senders to process ack'ed seq. numbers from a packet
	void ProcessAckdSequenceNumbers(const InputMemoryStream& packet);
	void ProcessTimedOutPackets();

	void Clear();

private:

	// Private members (sender side)
	// - The next outgoing sequence number 
	// - A list of pending deliveries

	uint32 nextSequenceNumber = 0;
	std::vector<Delivery> pendingDeliveries;

	// Private members (receiver side)
	// - The next expected sequence number
	// - A list of sequence numbers pending ack

	uint32 expectedSequenceNumber = 0;
	std::vector<uint32> pendingAcknowledgedDeliveries;
};