//////////////////////////////////////////////////////////////////////////////////////////////
/// \file CommonTools.hpp
/// \brief A header-only helper file with a few common tools.
/// \details Implements a basic timer tool.

/// \author Sean Anderson, ASRL
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OPTIMUS_COMMON_TOOLS_HPP
#define OPTIMUS_COMMON_TOOLS_HPP

// system timer
#include <sys/time.h>
#include <iostream>

namespace lgmath {
namespace common {

//////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Simple wall timer class to get approximate timings of functions
//////////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
 public:
  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Default constructor
  //////////////////////////////////////////////////////////////////////////////////////////////
  Timer() {
    reset();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Reset timer
  //////////////////////////////////////////////////////////////////////////////////////////////
  void reset() {
    beg_ = this->get_wall_time();
  }

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Get seconds since last reset
  //////////////////////////////////////////////////////////////////////////////////////////////
  double seconds() const {
    return this->get_wall_time() - beg_;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Get milliseconds since last reset
  //////////////////////////////////////////////////////////////////////////////////////////////
  double milliseconds() const {
    return 1000.0*(this->get_wall_time() - beg_);
  }

 private:

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Get current wall time
  //////////////////////////////////////////////////////////////////////////////////////////////
  double get_wall_time() const {
    struct timeval time;
    if (gettimeofday(&time,NULL)){
      //  Handle error
      return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////
  /// \brief Wall time at reset
  //////////////////////////////////////////////////////////////////////////////////////////////
  double beg_;

};

} // common
} // lgmath

#endif // OPTIMUS_COMMON_TOOLS_HPP
