#pragma once

#include <gmock/gmock.h>
#include <aasdk/Messenger/IMessenger.hpp>


namespace aasdk
{
namespace messenger
{
namespace ut
{

class MessengerMock: public IMessenger
{
public:
    MOCK_METHOD2(enqueueReceive, void(ChannelId channelId, ReceivePromise::Pointer promise));
    MOCK_METHOD2(enqueueSend, void(Message::Pointer message, SendPromise::Pointer promise));
    MOCK_METHOD0(stop, void());

    // a plain value, not a mock: strict mocks need no expectation for it
    void setProtocolVersion(ProtocolVersion version) override { protocolVersion = version; }
    ProtocolVersion getProtocolVersion() const override { return protocolVersion; }
    ProtocolVersion protocolVersion;
};

}
}
}
