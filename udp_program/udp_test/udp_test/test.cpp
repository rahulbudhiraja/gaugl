#include"test.h";


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

  // Get the name of the local computer
  char szHostName [MAX_PATH];
  ::gethostname (szHostName, sizeof szHostName);

  // Fill in the sockaddr_in structure for binding
  sockaddr_in sa;
  sa.sin_family = AF_INET;
  ::WSAHtons (sock, 8080, &sa.sin_port);

  // Get the IP address of the local computer name
  HOSTENT* phe = ::gethostbyname (szHostName);
  memcpy (&sa.sin_addr, phe->h_addr_list [0], phe->h_length);

  // Pad with zeros
  ZeroMemory (sa.sin_zero, sizeof sa.sin_zero);

  // Bind to a port
  iReturn = ::bind (sock, reinterpret_cast <sockaddr*> (&sa), 
    sizeof sockaddr_in);
  if (iReturn == SOCKET_ERROR)
    return ReportError ("bind failed."), ::closesocket (sock), 
    ::WSACleanup (), 0;

  // Prepare receive buffer(s)
  WSABUF wbRecv [1];

  char szRecvBuf [1][512];
  wbRecv [0].len = 512;
  wbRecv [0].buf = szRecvBuf [0];
 
  // Receive the first line of data
  DWORD dwBytesReceived = 0, dwFlags = 0;
  INT nFromLen = sizeof sockaddr_in;
  if ((iReturn = ::WSARecvFrom (sock, wbRecv, 1, 
    &dwBytesReceived, &dwFlags, 
    reinterpret_cast <sockaddr*> (&sa), &nFromLen, 
    NULL, NULL)) == 0)
  {
    // Output Received data till a 'Close' is received.
    do
    {
      cout << "Data: " << wbRecv [0].buf << ", Read: " 
        << dwBytesReceived << " bytes" <<
        ", From IP: " << ::inet_ntoa (sa.sin_addr) << endl;

	  int i=0;
	 
	  while(wbRecv[0].buf[i]!=' ')
		 i++;
            
	  temp= wbRecv[0].buf[++i];
	   cout<<temp;
 

      // Reset in - out parameters
      nFromLen = sizeof sockaddr_in;
      dwFlags = 0;
    }
    while (lstrcmpi (wbRecv [0].buf, "Close") != 0
      && ::WSARecvFrom (sock, wbRecv, 1, 
      &dwBytesReceived, &dwFlags, 
      reinterpret_cast <sockaddr*> (&sa), &nFromLen, 
      NULL, NULL) == 0);
  }
  else
  {
    // Report Recv errors
    char szError [512];
    wsprintf (szError, 
      "WSARecvFrom failed and returned: %d. "
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