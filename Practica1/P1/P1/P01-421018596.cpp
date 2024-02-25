#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <random>
#include <time.h>
#include <Windows.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;
float rojo, verde, azul = 0.0f;
//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,0.0f,0.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = {
		//x,y,z
		//R
		//Triangulo 1
		-0.9f,0.4f,0.0f, // C
		-0.8f,0.4f,0.0f, // D
		-0.9f,-0.4f,0.0f, // A
		//Triangulo 2
		-0.8f,0.4f,0.0f, // D
		-0.9f,-0.4f,0.0f, // A
		-0.8f,-0.4f,0.0f, // B
		//T3
		-0.8f,0.4f,0.0f, // D
		-0.8f,0.3f,0.0f, // G
		-0.5f,0.4f,0.0f, // E
		//T4
		-0.5f,0.4f,0.0f, // E
		-0.8f,0.3f,0.0f, // G
		-0.5f,0.3f,0.0f, // F
		//T5
		-0.8f,0.2f,0.0f, // H
		-0.8f,0.1f,0.0f, // I
		-0.5f,0.2f,0.0f, // J
		//T6
		-0.8f,0.1f,0.0f, // I
		-0.5f,0.2f,0.0f, // J
		-0.5f,0.1f,0.0f, // K
		//T7
		-0.5f,0.4f,0.0f, // E
		-0.5f,0.1f,0.0f, // K
		-0.4f,0.4f,0.0f, // L
		//T8
		-0.5f,0.1f,0.0f, // K
		-0.4f,0.4f,0.0f, // L
		-0.4f,0.1f,0.0f, // M
		//PALITO
		//T9
		-0.8f,0.1f,0.0f, // I
		-0.7f,0.1f,0.0f, // P1
		-0.7f,-0.05f,0.0f, // Q1
		//T10
		-0.7f,0.1f,0.0f, // P1
		-0.7f,-0.05f,0.0f, // Q1
		-0.6f,-0.05f,0.0f, // R1
		//T11
		-0.7f,-0.05f,0.0f, // Q1
		-0.6f,-0.05f,0.0f, // R1
		-0.6f,-0.2f,0.0f, // S1
		//T12
		-0.6f,-0.05f,0.0f, // R1
		-0.6f,-0.2f,0.0f, // S1
		-0.5f,-0.2f,0.0f, // T1
		//T13
		-0.6f,-0.2f,0.0f, // S1
		-0.5f,-0.2f,0.0f, // T1
		-0.5f,-0.35f,0.0f, // U1
		//T14
		-0.5f,-0.2f,0.0f, // T1
		-0.5f,-0.35f,0.0f, // U1
		-0.4f,-0.35f,0.0f, // V1
		//T15
		-0.5f,-0.35f,0.0f, // U1
		-0.4f,-0.35f,0.0f, // V1
		-0.4f,-0.4f,0.0f, // W1
		//T16
		-0.5f,-0.35f,0.0f, // U1
		-0.4f,-0.4f,0.0f, // W1
		-0.5f,-0.4f,0.0f, // Z1

		//O
		//T1
		-0.2f,0.3f,0.0f, // N
		-0.2f,-0.3f,0.0f, // Q
		-0.1f,0.3f,0.0f, // J1
		//Otro T
		-0.1f,0.3f,0.0f, // J1
		-0.2f,0.3f,0.0f, // N
		-0.1f,0.4f,0.0f, // J1

		//T2
		-0.2f,-0.3f,0.0f, // Q
		-0.1f,0.4f,0.0f, // J1
		-0.1f,-0.3f,0.0f, // K1
		//Otro T mas
		-0.1f,-0.3f,0.0f, // K1
		-0.2f,-0.3f,0.0f, // Q
		-0.1f,-0.4f,0.0f, // K1

		//T3
		-0.1f,0.4f,0.0f, // J1
		-0.1f,0.3f,0.0f, // R
		0.1f,0.4f,0.0f, // L1
		//T4
		-0.1f,0.3f,0.0f, // R
		0.1f,0.4f,0.0f, // L1
		0.1f,0.3f,0.0f, // S
		//T5
		-0.1f,-0.4f,0.0f, // K1
		-0.1f,-0.3f,0.0f, // U
		0.1f,-0.3f,0.0f, // T
		//T6
		-0.1f,-0.4f,0.0f, // K1
		0.1f,-0.3f,0.0f, // T
		0.1f,-0.4f,0.0f, // M1

		//T7
		0.1f,0.3f,0.0f, // L1
		0.1f,-0.3f,0.0f, // M1
		0.2f,0.3f,0.0f, // O
		//Uno mas
		0.2f, 0.3f, 0.0f, // O
		0.1f, 0.3f, 0.0f, // L1
		0.1f, 0.4f, 0.0f, 

		//T8
		0.1f,-0.3f,0.0f, // M1
		0.2f,0.3f,0.0f, // O
		0.2f,-0.3f,0.0f, // P
		//
		0.2f, -0.3f, 0.0f, // P
		0.1f, -0.3f, 0.0f, // M1
		0.1f, -0.4f, 0.0f, // O

		//A
		//T1
		0.4f,0.3f,0.0f, // E1
		0.4f,-0.4f,0.0f, // V
		0.55f,0.3f,0.0f, // N1
		// Otro T
		0.55f, 0.3f, 0.0f, // N1
		0.4f, 0.3f, 0.0f, // E1
		0.55f, 0.4f, 0.0f, // N1
		//T2
		0.4f,-0.4f,0.0f, // V
		0.55f,0.3f,0.0f, // N1
		0.55f,-0.4f,0.0f, // W
		//T3
		0.55f,0.4f,0.0f, // N1
		0.55f,0.3f,0.0f, // F1
		0.7f,0.4f,0.0f, // O1
		//T4
		0.55f,0.3f,0.0f, // F1
		0.7f,0.4f,0.0f, // O1
		0.7f,0.3f,0.0f, // G1
		//T5
		0.55f,0.1f,0.0f, // I1
		0.55f,0.0f,0.0f, // Z
		0.7f,0.1f,0.0f, // H1
		//T6
		0.55f,0.0f,0.0f, // Z
		0.7f,0.1f,0.0f, // H1
		0.7f,0.0f,0.0f, // A1
		//T7
		0.7f,0.3f,0.0f, // O1
		0.85f,0.3f,0.0f, // D1
		0.7f,-0.4f,0.0f, // B1
		// T
		0.7f, 0.3f, 0.0f, // O1
		0.85f, 0.3f, 0.0f, // D1
		0.7f, 0.4f, 0.0f, // O1
		//T8
		0.85f,0.3f,0.0f, // D1
		0.7f,-0.4f,0.0f, // B1
		0.85f,-0.4f,0.0f // B1

	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
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
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Crear tríangulo
	CrearTriangulo();
	CompileShaders();


	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		rojo = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // Asignar valores a las variables de color
		verde = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		azul = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		Sleep(2000);
		//Limpiar la ventana
		glClearColor(rojo,verde,azul,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,114);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);

	}


	return 0;
}