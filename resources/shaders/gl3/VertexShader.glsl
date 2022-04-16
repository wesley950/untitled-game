#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 vColor;

uniform mat4 uProjectionView;

void main() {
    gl_Position = uProjectionView * vec4(aPosition, 1);

    vColor = aColor;
}
