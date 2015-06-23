///
/// This merely tests the UnixSignalHandlers.
///
#include "UnixSignalHandlers.h"

#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

/// SIGPIPE forcing code snipped from https://www.cs.utah.edu/~swalton/listings/sockets/programs/part2/chap10/sigpipe-client.c
/* sigpipe-client.c
 *
 * Copyright (c) 2000 Sean Walton and Macmillan Publishers.  Use may be in
 * whole or in part in accordance to the General Public License (GPL).
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
*/

inline void runBadSocketTest() {
  struct sockaddr_in addr;
  int sd;

  if ( (sd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
  {
    cerr << "Socket" << endl;
    abort();
  }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9999);
  if ( inet_aton("127.0.0.1", &addr.sin_addr) == 0 )
  {
    cerr << "127.0.0.1" << endl;
    abort();
  }
  if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
  {
    cerr << "Failed to connect to server. Make sure to run an echo server (e.g. echoserver.python)" << endl;
    abort();
  }
  if ( send(sd, "this is a test", 17, 0) < 0 ) {
    cerr << "send" << endl;
  }

  auto count = 0;
  while(true) {
    sleep(1);
    if ( send(sd, "this is a test", 17, 0) < 0 ) {
      // there was an error
      cerr << "Error sending data" << endl;
    }
    cout << "Counting up: " << count << endl;
    count += 1;
  }
}

/// Run our code.
int main(int argc, char const *argv[])
{
  cout << "Installing signal handler" << endl;
  /// Whenever the OS sends a SIGPIPE, call handleSigPipe.
  installUnixSignalHandlers();

  cout << "Running bad socket test" << endl;
  runBadSocketTest();

  std::cout << "Exiting program normally" << std::endl;
  return 0;
}
