#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const char* vertexShaderSource = "#version 330 core\n" // the source code for Vertex shader stored in a string literal which will be constant throughout the program
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 fragColor; \n"
"void main()\n"
"{\n"
"fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//this is the color of the fragment wher first threee values are RGB and the last one is alpha(opacity)
"}\0"; // the source code for Fragment shader stored in a string literal which will be constant throughout the program


int main() 
{
	
	//Initiale glfw
	glfwInit();
	//glfwWindowHint sets hints for the next call to windowscreate function
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl Learning", NULL, NULL);
	if (window == NULL)
	{
		cout << "Windows can't be created" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	unsigned int VAO; // Create a variable VAO in CPU.
	glGenVertexArrays(1, &VAO); //Store the unique buffer ID in VAO that we later going to bind

	glBindVertexArray(VAO); // Binds the VAO to the target buffer type(GL_ARRAY_BUFFER)

	float Vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VBO; // Create a variable VBO in CPU.
	glGenBuffers(1, &VBO); //Store the unique buffer ID in VBO that we later going to bind 

	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Binds the VBO to the target buffer type(GL_ARRAY_BUFFER)

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW); //This is where actual storing of data happens in GPU

	glBindVertexArray(VAO); // Bind the VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // This function tells OpenGL how to interpret the vertex data
	glEnableVertexAttribArray(0); // Enable the vertex attribute array at index 0

	unsigned int vertexShader; //Declare a variable to hold Shader ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // GL_VERTEXT_SHADER returns the ID and stores it in vertexShader

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // Attach the shader source code to the shader object
	glCompileShader(vertexShader); // Compile the shader

	//check for compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex shader compilation failed:\n" << infoLog << std::endl;
	}


	unsigned int fragmentShader; //Declare a variable to hold Shader ID
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); // Create a program object

	glAttachShader(shaderProgram, vertexShader); // Attach the vertex shader to the program
	glAttachShader(shaderProgram, fragmentShader); // Attach the fragment shader to the program
	glLinkProgram(shaderProgram); // Link the program

	

	glDeleteShader(vertexShader); // Delete the vertex shader as it's linked to the program and no longer needed
	glDeleteShader(fragmentShader); // Delete the fragment shader as it's linked to the program and no longer needed

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear color
		glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

		glUseProgram(shaderProgram); // Use the program
		//glBindVertexArray(VAO); // Bind the VAO
		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
	
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0, 0, width, height);
}