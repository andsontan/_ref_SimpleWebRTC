#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "simpleaudiodevice.h"
#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"                                                                                        
#include "webrtc/system_wrappers/interface/trace.h"

namespace webrtc {

enum { kAdmMaxIdleTimeProcess = 1000 };

SimpleAudioDevice::SimpleAudioDevice() :
        critSect_(*CriticalSectionWrapper::CreateCriticalSection()),
        ptrCbAudioDeviceObserver_(NULL),
        ptrCbAudioTransport_(NULL) {
    
}

SimpleAudioDevice::~SimpleAudioDevice() {
    
}

int32_t SimpleAudioDevice::TimeUntilNextProcess() {
    return kAdmMaxIdleTimeProcess;
}

int32_t SimpleAudioDevice::Process() {
    return 0;
}

int32_t SimpleAudioDevice::RegisterEventObserver(AudioDeviceObserver* eventCallback) {
    CriticalSectionScoped lock(&critSect_);
    ptrCbAudioDeviceObserver_ = eventCallback;
}

int32_t SimpleAudioDevice::RegisterAudioCallback(AudioTransport* audioCallback) {
    CriticalSectionScoped lock(&critSect_);
    ptrCbAudioTransport_ = audioCallback;
}

void SimpleAudioDevice::Test() {
    static unsigned char buffer[40960];
    uint32_t samples = 0;
    uint32_t micLevel;
    if ( ptrCbAudioTransport_ != NULL) {
        int ret = ptrCbAudioTransport_->NeedMorePlayData(
                80,
                2,
                1,
                16000,
                buffer,
                samples);

        ret = ptrCbAudioTransport_->RecordedDataIsAvailable(
                buffer,
                160,
                2,
                1,
                16000,
                0,
                0,
                0,
                100,
                micLevel);
    }    
    
    static FILE* fp = NULL;
    if ( fp == NULL) {
        fp = fopen("./test.pcm", "wb");
    }
    fwrite(buffer, samples*2, 1, fp);
}

}  // namespace webrtc
