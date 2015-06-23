/*
 * Copyright (c) 2015 David Wicks, sansumbrella.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <signal.h>

#if defined(USE_CUSTOM_UNIX_SIGNAL_HANDLERS)
  // User must provide handleBrokenPipeSignal and handleTerminateSignal functions.
#elif defined(CINDER_CINDER)
  #include "cinder/app/App.h"
  #include "cinder/Log.h"
  /// Graceful ignoring of SIGPIPE.
  void handleBrokenPipeSignal(int signum)
  {
    CI_LOG_W("Ignoring SIGPIPE signal.");
  }
  /// Graceful handler for terminate signal
  void handleTerminateSignal(int signum)
  {
    CI_LOG_I("Received terminate signal (SIGTERM)");
    ci::app::shutdown();
  }
#else // Not Cinder and not user-defined
  #include <iostream>
  /// Graceful ignoring of SIGPIPE.
  void handleBrokenPipeSignal(int signum)
  {
    std::cout << "Ignoring SIGPIPE signal." << std::endl;
  }

  /// Graceful handler for terminate signal
  void handleTerminateSignal(int signum)
  {
    std::cout << "Received terminate signal (SIGTERM). Exiting." << std::endl;
    exit(0);
  }
#endif

/// Installs more graphics-application-friendly defaults for unix signals.
/// Default handlers log the signals
/// Ignore broken pipes to prevent crashing on network errors. Logs the signal.
/// Exit more gracefully when terminate signal is received. Log
inline void installUnixSignalHandlers() {
  signal(SIGPIPE, &handleBrokenPipeSignal);
  signal(SIGTERM, &handleTerminateSignal);
}
