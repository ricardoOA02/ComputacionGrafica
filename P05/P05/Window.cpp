#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	articulacion7 = 0.0f;
	movimiento = 0.0f;
	articulacion9 = 0.0f;
	cofre = 0.0f;
	c1 = 5.0f;
	c2 = 5.0f;
	c3 = 5.0f;
	c4 = 5.0f;
	c5 = 5.0f;
	c6 = 5.0f;
	c7 = 5.0f;
	c8 = 5.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica 05: Optimizacion y carga de modelos", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	bool flag1 = false;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}
	//Cabeza
	if (key == GLFW_KEY_F)
	{	
		if (theWindow->articulacion1 >= 20.0f) {
			theWindow->c1 = -5.0f;
		}
		else if (theWindow->articulacion1 <= -20.0f)
		{
			theWindow->c1 = 5.0f;
		}
		theWindow->articulacion1 += theWindow->c1;
	}
	//Mandibula
	if (key == GLFW_KEY_G)
	{
		if (theWindow->articulacion2 >= 10.0f) {
			theWindow->c2 = -5.0f;
		}
		else if (theWindow->articulacion2 <= -30.0f)
		{
			theWindow->c2 = 5.0f;
		}
		theWindow->articulacion2 += theWindow->c2;
	}
	//Pata delantera derecha
	if (key == GLFW_KEY_H)
	{
		if (theWindow->articulacion3 >= 45.0f) {
			theWindow->c3 = -5.0f;
		}
		else if (theWindow->articulacion3 <= -45.0f)
		{
			theWindow->c3 = 5.0f;
		}
		theWindow->articulacion3 += theWindow->c3;
	}
	//Pata delantera izquierda
	if (key == GLFW_KEY_J)
	{
		if (theWindow->articulacion4 >= 45.0f) {
			theWindow->c4 = -5.0f;
		}
		else if (theWindow->articulacion4 <= -45.0f)
		{
			theWindow->c4 = 5.0f;
		}
		theWindow->articulacion4 += theWindow->c4;
	}
	//Pata trasera derecha
	if (key == GLFW_KEY_K)
	{
		if (theWindow->articulacion5 >= 45.0f) {
			theWindow->c5 = -5.0f;
		}
		else if (theWindow->articulacion5 <= -45.0f)
		{
			theWindow->c5 = 5.0f;
		}
		theWindow->articulacion5 += theWindow->c5;
	}
	//Pata trasera izquierda
	if (key == GLFW_KEY_L)
	{
		if (theWindow->articulacion6 >= 45.0f) {
			theWindow->c6 = -5.0f;
		}
		else if (theWindow->articulacion6 <= -45.0f)
		{
			theWindow->c6 = 5.0f;
		}
		theWindow->articulacion6 += theWindow->c6;
	}
	if (key == GLFW_KEY_V)
	{
		if (theWindow->articulacion7 >= 45.0f) {
			theWindow->c7 = -5.0f;
		}
		else if (theWindow->articulacion7 <= -45.0f)
		{
			theWindow->c7 = 5.0f;
		}
		theWindow->articulacion7 += theWindow->c7;
	}
	// Carro hacia adelante
	if (key == GLFW_KEY_B)
	{
		theWindow->movimiento += 5.0;
		theWindow->articulacion9 += 5.0f;

	}
	// Carro hacia atras
	if (key == GLFW_KEY_N)
	{
		theWindow->movimiento -= 5.0;
		theWindow->articulacion9 -= 5.0f;
	}
	// Cofre
	if (key == GLFW_KEY_C)
	{
		if (theWindow->cofre >= 0.0f) {
			theWindow->c8 = -5.0f;
		}
		else if (theWindow->cofre <= -45.0f)
		{
			theWindow->c8 = 5.0f;
		}
		theWindow->cofre += theWindow->c8;
	}

	// Llantas hacia adelante
	if (key == GLFW_KEY_X)
	{
		theWindow->articulacion9 += 5.0f;
	}
	// Llantas hacia atras
	if (key == GLFW_KEY_Z)
	{
		theWindow->articulacion9 -= 5.0f;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
