#include <GLFW/glfw3.h>
extern GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "HeaderControls.h"


using namespace glm;

mat4 ProjectionMatrix;
mat4 ViewMatrix;

mat4 getProjectionMatrix() {
	return ProjectionMatrix;
};

mat4 getViewMatrix() {
	return ViewMatrix;
};

// позиция
vec3 position = vec3(0, 0, 5);
// центр объекта
vec3 ObjectCenter = vec3(0, 0, 5);

// горизонтальный угол
float horizontalAngle = 3.14f;
// вертикальный угол
float verticalAngle = 0.0f;
// поле обзора
float initialFoV = 45.0f;

float speed = 3.0f; // 3 юнита / сеукнд
float mouseSpeed = 0.5f;

float radius = 1.0;
float time = 3.0;
float height = 1.0;

void computeMatricesFromInputs() {

	static double lastTime = glfwGetTime(); // текущее время типо

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Получить позицию мыши
	double xpos, ypos;
	glfwGetCursorPos(window , &xpos, &ypos);

	
	
	//сбросить позицию мыши для следующего кадра
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);


	// Вычисляем углы
	horizontalAngle += mouseSpeed * deltaTime * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(768 / 2 - ypos);


	// Направление
	vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Вектор, указывающий направление вправо от камеры
	vec3 right = vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Вектор, указывающий направление вверх относительно камеры
	vec3 up = cross(right, direction);

	//glfwSetScrollCallback(window, scroll_callback);

	//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
	//	radius = radius + 0.1;
	//	position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	//}

	//if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
	//	time = time + 0.1;
	//	position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	//}

	//if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
	//	height = height + 0.1;
	//	position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	//}
	//


	// Движение вперед
	if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}
	// Движение назад
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}
	// Стрэйф вправо
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}
	// Стрэйф влево
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}

	float FoV = initialFoV; //-5 * glfwGetMouseWheel(); почему-то не работает, а я хотел зум(

	// Проекционная матрица: Поле обзора = FoV, отношение сторон 4 к 3, плоскости отсечения 0.1 и 100 юнитов
	ProjectionMatrix = perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Матрица камеры
	ViewMatrix = glm::lookAt(
		position,           // Позиция камеры
		position + direction, // Направление камеры
		up                  // Вектор "Вверх" камеры
	);

	lastTime = currentTime;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	initialFoV = yoffset;
}