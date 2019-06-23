#include "ListenerComponent.h"
#include "Actor.h"

namespace rah
{
	ListenerComponent::ListenerComponent()
	{
	}


	ListenerComponent::~ListenerComponent()
	{
	}
	void ListenerComponent::init(Actor * _owner, void * /*_data*/)
	{
		m_owner = _owner;
		m_lastOwnerPosition = m_owner->m_transform.m_position;
	}
	void ListenerComponent::update(float _deltaTime)
	{
		Vector3D velocity;
		velocity.x = (m_owner->m_transform.m_position.x - m_lastOwnerPosition.x) / _deltaTime;
		velocity.y = (m_owner->m_transform.m_position.y - m_lastOwnerPosition.y) / _deltaTime;
		velocity.z = (m_owner->m_transform.m_position.z - m_lastOwnerPosition.z) / _deltaTime;

		m_listener.UpdateListener(m_owner->m_transform.m_position, velocity, m_listener.m_forward ,m_listener.m_up);

		m_lastOwnerPosition = m_owner->m_transform.m_position;
	}
	void ListenerComponent::render()
	{
		if (m_rendereable)
		{
			RenderManager::GetInstance().renderShape(AABB(m_lastOwnerPosition, Vector4D(-1.f, -1.f, -1.f), Vector4D(1.f, 1.f, 1.f)), Color::red);
		}
	}
	void ListenerComponent::SetFowardUp(Vector3D _foward, Vector3D _up)
	{
		m_listener.m_forward = _foward;
		m_listener.m_up = _up;
	}
	void ListenerComponent::SetFoward(Vector3D _foward)
	{
		m_listener.m_forward = _foward;
	}
	void ListenerComponent::SetUp(Vector3D _up)
	{
		m_listener.m_up = _up;
	}
}