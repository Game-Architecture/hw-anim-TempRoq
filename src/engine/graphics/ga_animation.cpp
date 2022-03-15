#include "graphics/ga_animation.h"
#include "graphics/ga_node.h"

float lerp(float v1, float v2, float t)
{
	// TODO: Homework 6.
	// implement LERP for single float and 2,3, and 4 dimensional vectors
	return v1;
}

ga_vec2f lerp(ga_vec2f v1, ga_vec2f v2, float t)
{
	// TODO: Homework 6.
	return v1;
}
ga_vec3f lerp(ga_vec3f v1, ga_vec3f v2, float t)
{
	// TODO: Homework 6.
	return v1;
}
ga_vec4f lerp(ga_vec4f v1, ga_vec4f v2, float t)
{
	// TODO: Homework 6.
	return v1;
}

ga_quatf slerp(ga_quatf q1, ga_quatf q2, float t)
{
	// TODO: Homework 6.
	// implement SLERP for quaternions

	return q1;
}

ga_quatf nlerp(ga_quatf q1, ga_quatf q2, float t)
{
	// TODO: Homework 6.
	// implement NLERP for quaternions
	return q1;
}

ga_animation_player::ga_animation_player()
{
	_current_clip = nullptr;
	_playing = false;
	_elapsed_time = 0;

}
ga_animation_player::~ga_animation_player()
{

}

void ga_animation_player::add_clip(ga_animclip* clip)
{
	_clips.push_back(clip);
}

void ga_animation_player::play(ga_animclip* clip)
{
	_current_clip = clip;
	_playing = true;
	_elapsed_time = 0;
}

void ga_animation_player::play(int clip_idx)
{
	if (clip_idx < _clips.size())
	{
		_current_clip = _clips[clip_idx];
		_playing = true;
		_elapsed_time = 0;
	}
}
void ga_animation_player::play()
{
	_playing = true;
}
void ga_animation_player::pause()
{
	_playing = false;
}
bool ga_animation_player::is_playing()
{
	return _playing;
}
ga_animclip* ga_animation_player::get_current_clip()
{
	return _current_clip;
}
float ga_animation_player::get_time()
{
	return _elapsed_time;
}
float ga_animation_player::get_current_frame()
{
	// TODO: Homework 6.
	// convert seconds to frames:
	// return the current frame number based on the player's elapsed time

	return 0;
}
void ga_animation_player::update(float dt)
{
	// TODO: Homework 6.
	// If an animation is playing, update local time and determine the current frame.
	// Using the pose of the current frame, you must calculate each node's new world
	// and skinning matrices.

}
