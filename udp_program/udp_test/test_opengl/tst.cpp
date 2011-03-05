# include"yo.h"
# include<stdlib.h>

using namespace std;

WORD wVersionRequired = MAKEWORD (2, 2);
WSADATA wd;
int iReturn = ::WSAStartup (wVersionRequired, &wd);
SOCKET sock = ::WSASocket (AF_INET, SOCK_DGRAM, 0, 0, 0, 0);
char szHostName [MAX_PATH];

 HOSTENT* phe = ::gethostbyname (szHostName);
 WSABUF wbRecv [1];
   sockaddr_in sa;
  ULONG NonBlock;

  float xpos = 0, ypos = 0, zpos = 400, xrot = 0, yrot = 0, angle=0.0;
void ReportError (const char* const szErr)
{
  cout << szErr << endl;
}


//angle of rotation


//positions of the cubes
float positionz[10];
float positionx[10];

void cubepositions (void) { //set the positions of the cubes

    for (int i=0;i<10;i++)
    {
    positionz[i] = rand()%5 + 5;
    positionx[i] = rand()%5 + 5;
    }
}

//draw the cube
void cube (void) {

		 // The left face 
glColor3f(1,0,0);

	glBegin(GL_QUADS); //Begin quadrilateral coordinates
    
    
    glVertex3f(-200.0f, -155.0f, -100.0f);
    glVertex3f(-200.0f, 155.0f, -100.0f);
    glVertex3f(-255.0f, 155.0f, 100.0f);
    glVertex3f(-255.0f, -155.0f, 100.0f);
    

    glEnd(); 

	
glColor3f(0,0,1);
		 // The right face 
	glBegin(GL_QUADS); //Begin quadrilateral coordinates
    
    
    glVertex3f(200.0f, -155.0f, -100.0f);
    glVertex3f(200.0f, 155.0f, -100.0f);
    glVertex3f(255.0f, 155.0f, 100.0f);
    glVertex3f(255.0f, -155.0f, 100.0f);
    

    glEnd(); 


glColor3f(0,1,0);
//// The top face
	glBegin(GL_QUADS); //Begin quadrilateral coordinates
    
    
    glVertex3f(200.0f,155.0f, -100.0f);
    glVertex3f(-200.0f,155.0f, -100.0f);
    glVertex3f(-255.0f,155.0f, 100.0f);
    glVertex3f(255.0f,155.0f, 100.0f);
    

    glEnd(); 


glColor3f(1,1,1);//// the bottom face 

	glBegin(GL_QUADS); //Begin quadrilateral coordinates
   
	glVertex3f(200.0f,-155.0f, -100.0f);
    glVertex3f(-200.0f,-155.0f, -100.0f);
    glVertex3f(-255.0f,-155.0f, 100.0f);
    glVertex3f(255.0f,-155.0f, 100.0f);
    
    glEnd(); 


////// End of room code


	
glColor3f(0.4,0.4,0);

glTranslatef(-100,-133,0);
glutWireTeapot(40);

		// Pyramid 

		glColor3f(1,0,0);

		glBegin(GL_QUADS);

		glVertex3f(150,-20,-80);
		glVertex3f(230,-20,-80);
		glVertex3f(230,-20,0);
		glVertex3f(150,-20,0);

		glEnd();

		glColor3f(0,1,0);

		glBegin(GL_TRIANGLES);

		glVertex3f(190,60,-40);
		glVertex3f(150,-20,-80);
		glVertex3f(230,-20,-80);


		glEnd();


		glBegin(GL_TRIANGLES);

		glVertex3f(190,60,-40);
		glVertex3f(230,-20,0);
		glVertex3f(150,-20,0);

		glEnd();


		glColor3f(0,0,1);

		glBegin(GL_TRIANGLES);

		glVertex3f(190,60,-40);
		glVertex3f(230,-20,-80);
		glVertex3f(230,-20,0);

		glVertex3f(190,60,-40);
		glVertex3f(150,-20,-80);
		glVertex3f(150,-20,0);


		glEnd();


}

void init (void) {
cubepositions();
    
}

void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
   // glEnable (GL_LIGHTING); //enable the lighting
   // glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader

}

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void display (void) {
    glClearColor (0.0,0.0,0.0,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();  
    camera();
    enable();
    cube(); //call the cube drawing function

    glutSwapBuffers(); //swap the buffers
    angle++; //increase the angle
  
	
 // Receive the first line of data
  DWORD dwBytesReceived = 0, dwFlags = 0;
  INT nFromLen = sizeof sockaddr_in;


  NonBlock = 1;
     if (ioctlsocket(sock, FIONBIO, &NonBlock) == SOCKET_ERROR)
     {
          printf("ioctlsocket() failed \n");
          return;
     }




  
 FD_SET Reader;

  
 FD_ZERO(&Reader);
 FD_SET(sock, &Reader);

 if(   FD_ISSET(sock, &Reader))
{



  iReturn = ::WSARecvFrom (sock, wbRecv, 1,&dwBytesReceived, &dwFlags, reinterpret_cast <sockaddr*> (&sa), &nFromLen,NULL, NULL);


	  int i=0;
	 
	  while(wbRecv[0].buf[i]!=' ')
		 i++;
            
	  temp= wbRecv[0].buf[++i];
	
	  cout<<temp;

	   float xrotrad, yrotrad;
	   
	 if (temp=='q')
    {
    xrot += 1;
    if (xrot >360) xrot -= 360;
    }

    if (temp=='z')
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (temp=='w')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
    }

    if (temp=='s')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
    }

    if (temp=='d')
    {
    yrot += 1;
    if (yrot >360) yrot -= 360;
    }

    if (temp=='a')
    {
    yrot -= 1;
    if (yrot < -360)yrot += 360;
    }  
	   
	 
	 

      // Reset in - out parameters
      nFromLen = sizeof sockaddr_in;
      dwFlags = 0;
 wbRecv[0].buf[i]=' ';

}
 


    
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport  to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model

}

void keyboard (unsigned char key, int x, int y) {
    if (key=='q')
    {
    xrot += 1;
    if (xrot >360) xrot -= 360;
    }

    if (key=='z')
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (key=='w' ||temp=='w')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
    }

    if (key=='s'||temp=='s')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f); 
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
    }

    if (key=='d')
    {
    yrot += 1;
    if (yrot >360) yrot -= 360;
    }

    if (key=='a')
    {
    yrot -= 1;
    if (yrot < -360)yrot += 360;
    }
    if (key==27)
    {
    exit(0);
    }
}

int main (int argc, char **argv) {

  
	glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth
    glutInitWindowSize (500, 500); //set the window size
    glutInitWindowPosition (100, 100); //set the position of the window
    glutCreateWindow ("A basic OpenGL Window"); //the caption of the window
    init (); //call the init function
	
  // Initialize Windows Sockets

  if (iReturn != 0)
    return ReportError ("WSAStartup failed."), 0;

  // Create the socket
 
  if (sock == INVALID_SOCKET)
    return ReportError ("WSASocket failed."), ::WSACleanup (), 0;

  // Get the name of the local computer
  
  ::gethostname (szHostName, sizeof szHostName);

  // Fill in the sockaddr_in structure for binding

  sa.sin_family = AF_INET;
  ::WSAHtons (sock, 8080, &sa.sin_port);

  // Get the IP address of the local computer name
 
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
  
  char szRecvBuf [1][512];
  wbRecv [0].len = 512;
  wbRecv [0].buf = szRecvBuf [0];
	
	
	
	
	
	
	
	
	

    glutDisplayFunc (display); //use the display function to draw everything
    glutIdleFunc (display); //update any variables in display, display can be changed to anyhing, as long as you move the variables to be updated, in this case, angle++;
    glutReshapeFunc (reshape); //reshape the window accordingly

    glutKeyboardFunc (keyboard); //check the keyboard
    glutMainLoop (); //call the main loop
   


  ::closesocket (sock);
 
  // Uninitialize Windows Sockets
  ::WSACleanup ();

 
	return 0;
}
