#ifndef _PROBER_H_
#define _PROBER_H_

#include <vector>
#include <map>
#include "talk/base/thread.h"
#include "talk/base/messagequeue.h"

class Peer;
class SimpleCapturer;
class SimpleVideoRenderer;

class RtcStream;
namespace webrtc {
    class PeerConnectionFactoryInterface;
    class SimpleAudioDevice; 
}

class SimpleRTC : public sigslot::has_slots<>, public talk_base::MessageHandler {  
public:
    SimpleRTC(const std::string& myName, bool isCaller);
    ~SimpleRTC();
    
    virtual void OnMessage(talk_base::Message *msg);
    void Login(const std::string &server, 
               const unsigned short port);
    void Run();

protected:
    // call back from peer
    void onOnLine(bool isOk);
    void onOffline();
    void onRemoteOnline(const std::string& name, const std::string& role);
    void onRemoteOffline(const std::string&);
    void onRemoteMessage(const std::string&, const std::vector<std::string>& );
    void onPrintString(const std::string& );

private:
    void OnLocalDescription(RtcStream* stream, const std::string& desc);
    void OnLocalCandidate(RtcStream* stream, const std::string& cand);
    void makeCall(); 
    void answerCall();

private:
    // thread resource
    talk_base::Thread *signal_thread_;

    // info resource
    std::string myName_;
    bool isCaller_;
    Peer *peer_;

    webrtc::SimpleAudioDevice* adm_;
    SimpleCapturer* capturer_;
    SimpleVideoRenderer* renderer_;
    RtcStream* stream_;
    talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> factory_;
};

#endif
