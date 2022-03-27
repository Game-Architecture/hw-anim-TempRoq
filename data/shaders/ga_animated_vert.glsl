#version 400

uniform mat4 u_mvp;
uniform mat4[75] u_skin;

//****

// TODO: Homework 6.
// First, create a mat4 array to hold the skinning matrices of the skeleton.
// Refer to ga_animated_material::bind for clues on how to define this array.



uniform bool u_hasweights;
uniform bool u_lighting_enabled;


// Next, create the additional input variables for vertex attributes of the bar model.


//****
layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;
layout(location = 3) in vec2 in_texcoord;

layout(location = 4) in uvec4 joints;
layout(location = 5) in vec4 joint_weights;
layout(location = 6) in uint influencers;

//****

out vec3 o_normal;
out vec3 o_color;
out vec2 o_uv;

void main(void)
{
	if (u_hasweights){
		vec3 ret = vec3(0.0f, 0.0f, 0.0f);
		vec3 ret2 = vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < influencers; i++){	
			ret = ret + (vec4(in_vertex, 1.0f) * u_skin[joints[i]] * joint_weights[i]).xyz; 
			ret2 = ret2 + (vec4(in_normal, 1.0f) * u_skin[joints[i]] * joint_weights[i]).xyz;
		}
		gl_Position = u_mvp * vec4(ret, 1.0);
		o_normal = (u_mvp * vec4(ret2, 0.0)).xyz;
	}

	else{	
		gl_Position = u_mvp * vec4(in_vertex,1.0);
		o_normal = (u_mvp * vec4(in_normal, 0.0)).xyz;	
	}

	
	o_color = vec3(1.0, 1.0, 1.0);
	o_uv = in_texcoord;
}