#version 330

const uint MAX_TEXTURES = 5u;

float getDiffuseScaling(vec3 normal, vec3 lightDirection) {
    normal = normalize(normal);
    lightDirection = normalize(lightDirection);

    return max(dot(normal, lightDirection), 0.0);
}

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoords;

out vec4 OutColor;

struct Material {
    sampler2D diffuse[MAX_TEXTURES];
    sampler2D specular[MAX_TEXTURES];
};

uniform Material material;
uniform uint diffuseSize;
uniform uint specularSize;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightIntensity;

void main() {

    vec4 objColor = texture2D(material.diffuse[0], fTexCoords);
    vec3 fff = objColor.xyz;

    vec3 ambient = vec3(0.1, 0.1, 0.1);
    vec3 diffuse = getDiffuseScaling(fNormal, lightPosition - fPosition) * lightColor * lightIntensity;

    vec3 result = (diffuse + ambient) * fff;

    if (result == vec3(0.0, 0.0, 0.0)) {
        OutColor = vec4(result, 0.0);
    }
    else {
        OutColor = vec4(result, objColor.a);
    }
    /*
    if (OutColor == vec4(0.0, 0.0, 0.0, 1.0)) {
        OutColor = vec4(0.0, 0.0, 0.0, 0.0);
    }
    */
    //OutColor = vec4(1, 0, 0, 1);
}

