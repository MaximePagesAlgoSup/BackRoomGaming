#include "include/glad.h"
#include "include/glfw3.h"
#include <iostream>

#define BLACK 0.0f, 0.0f, 0.0f, 0.0f
#define BACKGROUND 0.2f, 0.3f, 0.3f, 1.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // force the 16/9 aspect ratio
    if (width / 16 != height / 9)
    {
        if (width / 16 > height / 9)
        {
			width = height * 16 / 9;
		}
        else
        {
			height = width * 9 / 16;
		}
		glfwSetWindowSize(window, width, height);
	}

    glViewport(0, 0, width, height);
    glScissor(0, 0, width, height);
}


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1600, 900, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1600, 900);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    float vertices[] = {
         -0.1f, -0.1f, 0.0f,
         0.1f, -0.1f, 0.0f,
         0.0f,  0.1f, 0.0f
    };

    while (!glfwWindowShouldClose(window))
    {

    unsigned int VBO;
    
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // ..:: Initialization code (done once (unless your object frequently changes)) :: ..
    // 1. bind Vertex Array Object
    glBindVertexArray(VAO);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. then set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glClearColor(BACKGROUND);
    //Main Game Loop
        //Handle Inputs event
        
        //Handle Game Logic Events

        //Handle Physics

        //Update positions

        //Draw Frame

        if (glfwGetKey(window, GLFW_KEY_LEFT))
             for (int i = 0; i < 9; i++)
                if(i!=1 && i!=4 && i!=7)
                    vertices[i] -= 0.02f;
        if (glfwGetKey(window, GLFW_KEY_RIGHT))
            for (int i = 0; i < 9; i++)
                if (i != 1 && i != 4 && i != 7)
                    vertices[i] += 0.02f;
        if(glfwGetKey(window, GLFW_KEY_UP))
			for (int i = 0; i < 9; i++)
				if (i != 0 && i != 3 && i != 6)
					vertices[i] += 0.02f;
        if (glfwGetKey(window, GLFW_KEY_DOWN))
            for (int i = 0; i < 9; i++)
                if (i != 0 && i != 3 && i != 6)
					vertices[i] -= 0.02f;



        // 4. draw the object
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //display generated frame
        glfwSwapBuffers(window);
        //getevents such as input that happened during the frame to prepare for the next one
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(BLACK);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(BACKGROUND);
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

    }

    glfwTerminate();

    return 0;
}

