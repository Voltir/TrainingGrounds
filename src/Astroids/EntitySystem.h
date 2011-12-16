
class EntitySystem;
class EntityView;

class EntitySystem
{

friend class EntityView;

public:
	EntitySystem() : m_count(0) {}
	void newEntity();
	EntityView view() const;

private:
	int m_count;
};

class EntityView
{
public:
	EntityView(const EntitySystem& es) : m_es(es) {}
	int size() { return m_es.m_count; } 

private:
	const EntitySystem& m_es;
};

EntityView
EntitySystem::view() const
{
	//EntityView result(*this);
	//return std::move<EntityView>(result);
	return EntityView(*this);
};

void
EntitySystem::newEntity()
{
	m_count += 1;
}
