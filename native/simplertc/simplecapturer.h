#ifndef _SIMPLECAPTURER_H_
#define _SIMPLECAPTURER_H_

#include <string>
#include <vector>

#include "talk/base/stream.h"
#include "talk/base/stringutils.h"
#include "talk/media/base/videocapturer.h"


// Simulated video capturer that periodically reads frames from a file.
class SimpleCapturer : public cricket::VideoCapturer {
 public:
  SimpleCapturer();
  virtual ~SimpleCapturer();

  // Override virtual methods of parent class VideoCapturer.
  virtual cricket::CaptureState Start(const cricket::VideoFormat& capture_format);
  virtual void Stop();
  virtual bool IsRunning();
  virtual bool IsScreencast() const { return false; }

 protected:
  virtual bool GetPreferredFourccs(std::vector<uint32>* fourccs);

  DISALLOW_COPY_AND_ASSIGN(SimpleCapturer);
};

#endif