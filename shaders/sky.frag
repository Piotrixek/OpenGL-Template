#version 330 core
out vec4 FragColor;

in vec3 v_worldPos;

uniform vec3 u_sunDirection;

void main()
{
    vec3 viewDir = normalize(v_worldPos);

    float t = pow(max(0.0, viewDir.y), 0.5);
    vec3 skyColor = mix(vec3(0.1, 0.2, 0.4), vec3(0.4, 0.7, 1.0), t);

    float dotProduct = dot(viewDir, normalize(u_sunDirection));
    float sunDisc = smoothstep(0.999, 1.0, dotProduct);
    float sunGlow = smoothstep(0.95, 1.0, dotProduct);

    vec3 sunColor = vec3(1.0, 0.9, 0.7) * sunDisc + vec3(1.0, 0.7, 0.3) * pow(sunGlow, 10.0);

    FragColor = vec4(skyColor + sunColor, 1.0);
}
