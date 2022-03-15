#version 400

in vec3 o_normal;
in vec3 o_color;
in vec2 o_uv;

uniform sampler2D u_texture;
uniform bool u_lighting_enabled;

const vec3 light_dir = normalize(vec3(1,-.5,1));

const vec3 ambient = vec3(0.05, 0.05, 0.05);
const vec3 diffuse = vec3(.5,.5,.5);

const vec3 specular = vec3(0.5, 0.5, 0.5);

out vec4 finalColor;

void main(void)
{

	finalColor = texture(u_texture,o_uv);
	
	if (u_lighting_enabled)
	{
		vec3 diffuse_color = diffuse * max(dot(-light_dir, o_normal),0);
		vec3 lit_color = ambient + diffuse_color;

		finalColor = vec4(lit_color * vec3(finalColor),1.0);
	}
}
