#include "api.hpp"

const double sensitivity = 1.0;

extern "C" Variant _input_plane(Object event, Node3D plane, Vector2 input_mouse_speed) {
	if (is_editor_hint()) {
		return Nil;
	}

	Vector2 rel = event("get_relative").v2();
	Vector2 mouse_speed = input_mouse_speed.lerp(rel / Vector2(1000, 1000), sensitivity);
	plane.call("rotate_object_local", Vector3(1, 0, 0), mouse_speed.y);
	plane.call("rotate_object_local", Vector3(0, 0, 1), mouse_speed.x);

	return Nil;
}
