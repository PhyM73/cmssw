#ifndef POPCON_EXCEPTION_H
#define POPCON_EXCEPTION_H
#include "FWCore/Utilities/interface/Exception.h"
#include <string>

namespace popcon {
  class Exception : public cms::Exception {
  public:
    explicit Exception(const std::string& message) : cms::Exception("PopCon", message) {}
    Exception(const std::string& category, const std::string& message) : cms::Exception(category, message) {}
    ~Exception() throw() override {}
  };
}  // namespace popcon
#endif
