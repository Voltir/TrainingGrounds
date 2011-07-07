#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "EntitySystem.h"

using namespace std;

struct CompPos3D : public Component
{
	static const ComponentId componentId;

	CompPos3D() : x(0), y(0), z(0) {}
	double x,y,z;
};

struct CompBar : public Component
{
	static const ComponentId componentId;

	CompBar(std::string inp) : bar(inp) {}

	std::string bar;
};

const ComponentId CompPos3D::componentId = 1;
const ComponentId CompBar::componentId = 2;

TEST(EntitySystemTest,Foo)
{
	EntitySystem foo_entities(10);

	for(int i=0; i<foo_entities.size(); ++i)
	{
		cout << i << endl;

		if(i < 5)
			foo_entities[i]->add(new CompBar("Bar!"));
			
		if(i % 2 == 0)
			foo_entities[i]->add(new CompPos3D());
	
	}
	
	EntitySystemView pos_entities = foo_entities.getWith<CompPos3D>();
	cout << "Pos entities: " << pos_entities.size() << endl;
	
	EntitySystemView bar_and_pos_entities = pos_entities.getWith<CompBar>();
	cout << "BarPos entities: " << bar_and_pos_entities.size() << endl;
}
