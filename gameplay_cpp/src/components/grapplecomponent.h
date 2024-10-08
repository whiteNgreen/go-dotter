#pragma once

#include <core/nodecomponent.hpp>

#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>

using namespace godot;

struct GrappleEvent;

class GrappleComponent : public NodeComponent {
	GDCLASS(GrappleComponent, NodeComponent)
public:
	Area3D* m_area = nullptr;
	CollisionShape3D* m_shape = nullptr;

	bool anchored = false;
	float m_pull_strength = 0.f;
	float m_mass = 10.f;

public:
	enum LaunchType {
		BOTH_ANCHOR,
		BOTH_NON_ANCHOR,
		INSTIGATOR_ANCHOR,
		SUBJECT_ANCHOR,
	};
	struct LaunchContext {
		Vector3 impulse;
		LaunchType type;
	};

public:
	LaunchContext launch(GrappleComponent* subject);

protected:
	LaunchType _determine_launch_type(const GrappleComponent* subject);
	Vector3 _determine_launch_direction_atob(const GrappleComponent* a, const GrappleComponent* b);
	Vector3 _impulse_owner(const Vector3& direction, float impulse_strength);

public:
	static void _bind_methods();

	void _enter_tree() override;
	void _exit_tree() override;

	RID get_rid() const;

	void set_is_anchor(bool val);
	bool get_is_anchor() const;
	void set_pull_strength(float val);
	float get_pull_strength() const;
	void set_mass(float val);
	float get_mass() const;

	template <typename T>
	T* get_child_node_of_type(const godot::Node* node) {
		TypedArray<godot::Node> children = node->get_children();
		for (int i = 0; i < children.size(); ++i) {
			if (T* child = cast_to<T>(children[i])) { return child; }
		}
		return nullptr;
	}
};
