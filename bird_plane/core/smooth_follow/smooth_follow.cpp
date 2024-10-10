#include "api.hpp"

static float smoothness = 1.0f;

SANDBOXED_PROPERTIES(1, {
	.name = "smoothness",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return smoothness; },
	.setter = [](Variant value) -> Variant { smoothness = value; return smoothness; },
	.default_value = 1.0f,
});

static Transform3D last_transform = Transform3D::identity();

extern "C" Variant _process_parent_child(double delta, Node3D parent, Node3D child) {
	if (Engine::is_editor_hint()) {
		return Nil;
	}

	Transform3D parent_transform = parent.get_transform();
	last_transform = last_transform.interpolate_with(parent_transform, smoothness);
	last_transform.set_basis(parent_transform.get_basis().slerp(last_transform.get_basis(), smoothness / 2));
	child.set_transform(last_transform);

	return Nil; //3452
}
