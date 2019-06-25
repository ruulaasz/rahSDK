#include "ComponentFactory.h"
#include "rahEngine.h"

namespace rah
{
	size_t ComponentFactory::m_autoID = 0;

	ComponentFactory::ComponentFactory()
	{

	}

	ComponentFactory::~ComponentFactory()
	{

	}

	RahResult ComponentFactory::Initialize(void * _init)
	{
		_init;
		return RahResult();
	}

	void ComponentFactory::Release()
	{

	}

	Component * ComponentFactory::createEmptyComponent(Actor * _owner, ComponentTypes _ct, std::string _id, void* _data)
	{
		if (_owner != NULL)
		{
			switch (_ct)
			{
			case rah::CT_NONE:
				break;

			case rah::CT_MODEL:
			{
				ModelComponent* mc = new ModelComponent();

				mc->init(_owner, _data);

				setID(mc, "model", _id);
				return mc;
			}
			case rah::CT_BOX:
			{
				BoxComponent* bc = new BoxComponent();

				bc->init(_owner, _data);

				setID(bc, "box", _id);
				return bc;
			}
			case rah::CT_LISTENER:
			{
				ListenerComponent* lc = new ListenerComponent();

				lc->init(_owner);
				setID(lc, "listener", _id);

				return lc;
			}
			case rah::CT_AUDIO:
			{
				AudioComponent* ac = new AudioComponent();

				ac->init(_owner, _data);
				setID(ac, "audio", _id);

				return ac;
			}
			case rah::CT_TOTAL:
				break;

			default:
				break;
			}
		}
		else
		{
			RAH_LOG("owner invalid");
			GetLastError() = RahResult::RAH_ERROR;
			return NULL;
		}

		return NULL;
	}

	void ComponentFactory::setID(Component* _component, std::string _ct, std::string _id)
	{
		if (_id.empty())
		{
			_component->m_id = _ct + std::to_string(m_autoID);
			m_autoID++;
		}
		else
		{
			//buscar repetido en actor
			Component* c = _component->m_owner->getComponent(_id);

			if (c != NULL)
			{
				_component->m_id = _ct + std::to_string(m_autoID);
				m_autoID++;
			}
			else
			{
				_component->m_id = _id;
			}
		}
	}
}