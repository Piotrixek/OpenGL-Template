#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 v_worldPos;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
    v_worldPos = aPos;
    mat4 viewNoTranslation = mat4(mat3(u_view)); 
    vec4 clipPos = u_projection * viewNoTranslation * vec4(v_worldPos, 1.0);
    gl_Position = clipPos.xyww; 
}
