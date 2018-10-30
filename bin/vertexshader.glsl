#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoords;

void main() {

    vec4 worldPos = model * vec4(Position, 1.0);
    gl_Position = proj * view * worldPos;
    fPosition = vec3(worldPos);
    fNormal = mat3(transpose(inverse(model))) * Normal;
    fTexCoords = TexCoords;
}
