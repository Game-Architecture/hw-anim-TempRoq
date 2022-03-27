#include "graphics/ga_animation.h"
#include "graphics/ga_node.h"
#include<iostream>

float lerp(float v1, float v2, float t)
{
	// TODO: Homework 6.
	// implement LERP for single float and 2,3, and 4 dimensional vectors
	return v1;
}

ga_vec2f lerp(ga_vec2f v1, ga_vec2f v2, float t)
{
	ga_vec2f ret;
	ret.x = v1.x + ((v2.x - v1.x) / t);
	ret.y = v1.y + ((v2.y - v1.y) / t);
	return ret;
}
ga_vec3f lerp(ga_vec3f v1, ga_vec3f v2, float t)
{
	ga_vec3f ret;
	ret.x = v1.x + ((v2.x - v1.x) / t);
	ret.y = v1.y + ((v2.y - v1.y) / t);
	ret.z = v1.z + ((v2.z - v1.z) / t);
	return ret;
}
ga_vec4f lerp(ga_vec4f v1, ga_vec4f v2, float t)
{
	ga_vec4f ret;
	ret.x = v1.x + ((v2.x - v1.x) / t);
	ret.y = v1.y + ((v2.y - v1.y) / t);
	ret.z = v1.z + ((v2.z - v1.z) / t);
	ret.w = v1.w + ((v2.w - v1.w) / t);
	return ret;
}

ga_quatf slerp(ga_quatf q1, ga_quatf q2, float t)
{
	
	ga_quatf qm;
	double cosHalfTheta = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	if (abs(cosHalfTheta) >= 1.0) {
		qm.w = q1.w; qm.x = q1.x; qm.y = q1.y; qm.z = q1.z;
		return qm;
	}
	double halfTheta = acos(cosHalfTheta);
	double sinHalfTheta = sqrt(1.0 - cosHalfTheta * cosHalfTheta);

	if (fabs(sinHalfTheta) < 0.001) { 
		qm.w = (q1.w * 0.5 + q2.w * 0.5);
		qm.x = (q1.x * 0.5 + q2.x * 0.5);
		qm.y = (q1.y * 0.5 + q2.y * 0.5);
		qm.z = (q1.z * 0.5 + q2.z * 0.5);
		return qm;
	}
	double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
	double ratioB = sin(t * halfTheta) / sinHalfTheta;
	qm.w = (q1.w * ratioA + q2.w * ratioB);
	qm.x = (q1.x * ratioA + q2.x * ratioB);
	qm.y = (q1.y * ratioA + q2.y * ratioB);
	qm.z = (q1.z * ratioA + q2.z * ratioB);
	return qm;
}

ga_quatf nlerp(ga_quatf q1, ga_quatf q2, float t)
{
	ga_quatf yuh = slerp(q1, q2, t);
	yuh.normalize();
	return yuh;
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
	return _elapsed_time * _current_clip->_fps;
}
void ga_animation_player::update(float dt)
{
	
	if (!_playing) {
		return;
	}

	
	_elapsed_time += dt;
	float newFrame = get_current_frame();

	if (newFrame > _current_clip->_duration) {
		_elapsed_time = 0;
		newFrame = 0;	
	}


	for (int i = 0; i < _current_clip->_channels.size(); i++) {

		int keyNum = -1;

		for (int j = 0; j < _current_clip->_channels[i]->_keys.size(); j++) {

			if (_current_clip->_channels[i]->_keys[j]._time > newFrame) {
				keyNum = j;
				break;
			}

		}

		//std::cout << "Key in " << i << ": nextKey is " << keyNum << std::endl;
		
		if (keyNum == -1) {

			std::cout << "There are no more keys in " << i << " at frame: " << newFrame << std::endl;
			continue;
			
		}

			
			ga_animkey key1 = _current_clip->_channels[i]->_keys[keyNum - 1];
			ga_animkey key2 = _current_clip->_channels[i]->_keys[keyNum];

			float time = (newFrame - key1._time) / (key2._time - key1._time);





			ga_vec3f newTranslate = lerp(key1._translation, key2._translation, time);
			ga_quatf newRotate = slerp(key1._rotation, key2._rotation, time);
			ga_vec3f newScale = lerp(key1._scale, key2._scale, time);

			ga_mat4f newMat;
			newMat.make_identity();
			newMat.rotate(newRotate);
			newMat.translate(newTranslate);

			_current_clip->_channels[i]->_node->_transform = newMat;


		
		
	}
	/*
	for (int i = 0; i < _current_clip->_channels.size(); i++) { //for each channel
		
		ga_animkey key1;
		ga_animkey key2;
		
		int keyNum = -1;
		for (int j = 0; j < _current_clip->_channels[i]->_keys.size(); j++) {
			if (_current_clip->_channels[i]->_keys[j]._time > newFrame) {
				keyNum = j;
				break;
			}
		}
		if (keyNum == -1) {
			_elapsed_time = 0;
			newFrame = 0;
			key1 = _current_clip->_channels[i]->_keys[0];
			key2 = _current_clip->_channels[i]->_keys[1];
		}
		else {
			key2 = _current_clip->_channels[i]->_keys[keyNum];
			key1 = _current_clip->_channels[i]->_keys[int(keyNum) - 1];
		}


		float time = ( newFrame - key1._time) / (key2._time - key1._time);
		ga_vec3f newTranslate = lerp(key1._translation, key2._translation, time);
		ga_quatf newRotate = slerp(key1._rotation, key2._rotation, time);
		ga_vec3f newScale = lerp(key1._scale, key2._scale, time);

		ga_mat4f newMat;
		newMat.make_identity();
		newMat.rotate(newRotate);
		newMat.translate(newTranslate);
		//newMat.scale(newScale);

		_current_clip->_channels[i]->_node->_transform = newMat;

	}
	*/
	
	

}
