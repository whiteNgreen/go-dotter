#include "projectile.h"

static constexpr float LIFETIME = 2.f;

void Projectile::_bind_methods() {
	DEFAULT_PROPERTY(Projectile)
	//
}

void Projectile::_enter_tree() {
	RETURN_IF_EDITOR
	//

	m_timer = memnew(Timer);

	ASSERT_NOTNULL(m_timer)

	add_child(m_timer);
	m_timer->connect("timeout", callable_mp(this, &Projectile::onTimeout));
	m_timer->start(LIFETIME);
}

void Projectile::_physics_process(double delta) {}

void Projectile::onTimeout() { queue_free(); }
