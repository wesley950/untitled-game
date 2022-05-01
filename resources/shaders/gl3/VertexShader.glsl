#version 330 core

layout (location = 0) in vec3   aPosition;
layout (location = 1) in vec4   aColor;
layout (location = 2) in vec2   aTextureCoordinates;
layout (location = 3) in float  aTextureSlot;

out vec4    vColor;
out vec2    vTextureCoordinates;
out float   vTextureSlot;

uniform mat4 uProjectionView;

void main() {
    gl_Position = uProjectionView * vec4(aPosition, 1);

    vColor = aColor;
    vTextureCoordinates = aTextureCoordinates;
    vTextureSlot = aTextureSlot;
}
