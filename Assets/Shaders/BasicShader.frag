#version 410 core

in vec3 world_position;
in vec3 world_normal;
in vec2 tex_coord;

uniform vec3 point_light_positions[9];
uniform vec3 point_light_colors[9];
uniform vec3 eye_position;
uniform vec3 material_ka;
uniform vec3 material_kd;
uniform vec3 material_ks;
uniform int material_shininess;
uniform sampler2D u_texture;

layout(location = 0) out vec4 out_color;

vec3 PhongIllumination(vec3 light_position, vec3 light_color)
{
    // diffuse
    vec3 L = normalize(light_position - world_position);
    vec3 N = normalize(world_normal);
    vec3 diffuse_component = material_kd * light_color * max(dot(N, L), 0);

    // specular
    int receiveLight = dot(N, L) > 0 ? 1 : 0;
    vec3 R = reflect(-L, N);
    vec3 V = normalize(eye_position - world_position);
    vec3 specular_component = material_ks * light_color * receiveLight * pow(max(dot(V, R), 0), material_shininess);

    vec3 illumination = diffuse_component + specular_component;

    return illumination;
}

float DistanceAttenuation(vec3 light_position, vec3 point_position)
{
    return 1.0f / (pow(distance(light_position, point_position), 2) + 1);
}

vec3 PointLightSourcesIllumination()
{
    vec3 lights_illumination = vec3(0);

    for (int i = 0; i < 9; i++) {
        vec3 light_position = point_light_positions[i];
        vec3 light_color = point_light_colors[i];

        vec3 light_illumination = PhongIllumination(light_position, light_color);
        float illumination_attenuation = DistanceAttenuation(light_position, world_position);
        lights_illumination += light_illumination * illumination_attenuation;
    }

    return lights_illumination;
}

vec3 AmbientComponent()
{
    vec3 global_ambient_color = vec3(0.25f);

    // ambient
    vec3 ambient_component = material_ka * global_ambient_color;

    return ambient_component;
}

void main()
{
    vec3 illumination = PointLightSourcesIllumination() + AmbientComponent();
    vec4 textureColor = texture(u_texture, tex_coord);
    out_color = vec4 ((textureColor.rgb * illumination), 1);
}
