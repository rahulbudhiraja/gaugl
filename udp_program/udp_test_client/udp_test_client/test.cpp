#undef UNICODE and #undef _UNICODE


#include <iostream>
#include <Winsock2.h>
#include <stdio.h>

using namespace std;


void ReportError (const char* const szErr)
{
  cout << szErr << endl;
}

int main (void)
{
  // Initialize Windows Sockets
  WORD wVersionRequired = MAKEWORD (2, 2);
  WSADATA wd;
  int iReturn = ::WSAStartup (wVersionRequired, &wd);
  if (iReturn != 0)
    return ReportError ("WSAStartup failed."), 0;

  // Create the socket
  SOCKET sock = ::WSASocket (AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
  if (sock == INVALID_SOCKET)
    return ReportError ("WSASocket failed."), ::WSACleanup (), 0;

  // Fill in the sockaddr_in structure for sending
  sockaddr_in sa;
  sa.sin_family = AF_INET;
  ::WSAHtons (sock, 8080, &sa.sin_port);

  // Fill in the IP address of the machine where the 
  // server resides
  sa.sin_addr.S_un.S_addr = ::inet_addr ("172.20.130.112");
  // Substitute "xxx.xxx.xxx.xxx" with a valid IP

  // Pad with zeros
  ZeroMemory (sa.sin_zero, sizeof sa.sin_zero);

  // Prepare receive buffer(s)
  WSABUF wbSend [1];
  char szSendBuf [1][512];
  wbSend [0].len = 512;
  wbSend [0].buf = szSendBuf [0];

  // Receive the first line of data
  DWORD dwBytesSent = 0;
  INT nToLen = sizeof sockaddr_in;

  cout << ">" << flush;
  char szGet [402];
  gets (szGet);

  DWORD dwTickCount = GetTickCount ();
  wsprintf (wbSend [0].buf, "%lu %s", dwTickCount, szGet);

  if ((iReturn = ::WSASendTo (sock, wbSend, 1, 
    &dwBytesSent, NULL, 
    reinterpret_cast <sockaddr*> (&sa), 
    nToLen, NULL, NULL)) == 0)
  {
    // Output Sent data till an 'Exit' is typed
    do
    {
      cout << "Data: " << wbSend [0].buf << ", Sent: " 
        << dwBytesSent << endl;
 /*  string abc;
	   
	abc.copy(wbSend[0].buf,0,4);*/

	      cout << ">" << flush;
      gets (szGet);

      dwTickCount = GetTickCount ();
      wsprintf (wbSend [0].buf, "%lu %s", dwTickCount, szGet);

      // Reset in - out parameters
      nToLen = sizeof sockaddr_in;
      dwBytesSent = 0;
    }
    while (lstrcmpi (szGet, "Exit") != 0
      && ::WSASendTo (sock, wbSend, 1, 
      &dwBytesSent, NULL, 
      reinterpret_cast <sockaddr*> (&sa), 
      nToLen, NULL, NULL) == 0);
  }
  else
  {
    // Report Recv errors
    char szError [256];
    wsprintf (szError, 
      "WSASendTo failed and returned: %d. "
      "WSAGetLastError: %d", iReturn, 
    WSAGetLastError ());
    ReportError (szError);
  }

  // Close the socket
  ::closesocket (sock);

  // Uninitialize Windows Sockets
  ::WSACleanup ();

  return 0;
}