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

// �������
vec3 position = vec3(0, 0, 5);
// ����� �������
vec3 ObjectCenter = vec3(0, 0, 5);

// �������������� ����
float horizontalAngle = 3.14f;
// ������������ ����
float verticalAngle = 0.0f;
// ���� ������
float initialFoV = 45.0f;

float speed = 3.0f; // 3 ����� / ������
float mouseSpeed = 0.5f;

float radius = 1.0;
float time = 3.0;
float height = 1.0;

void computeMatricesFromInputs() {

	static double lastTime = glfwGetTime(); // ������� ����� ����

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// �������� ������� ����
	double xpos, ypos;
	glfwGetCursorPos(window , &xpos, &ypos);

	
	
	//�������� ������� ���� ��� ���������� �����
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);


	// ��������� ����
	horizontalAngle += mouseSpeed * deltaTime * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * deltaTime * float(768 / 2 - ypos);


	// �����������
	vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// ������, ����������� ����������� ������ �� ������
	vec3 right = vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// ������, ����������� ����������� ����� ������������ ������
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


	// �������� ������
	if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}
	// �������� �����
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}
	// ������ ������
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position += right * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}
	// ������ �����
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
		//position = ObjectCenter + (radius * cos(time), height, radius * sin(time));
	}

	float FoV = initialFoV; //-5 * glfwGetMouseWheel(); ������-�� �� ��������, � � ����� ���(

	// ������������ �������: ���� ������ = FoV, ��������� ������ 4 � 3, ��������� ��������� 0.1 � 100 ������
	ProjectionMatrix = perspective(radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// ������� ������
	ViewMatrix = glm::lookAt(
		position,           // ������� ������
		position + direction, // ����������� ������
		up                  // ������ "�����" ������
	);

	lastTime = currentTime;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	initialFoV = yoffset;
}