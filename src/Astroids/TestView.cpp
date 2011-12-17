#include <limits.h>
#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "View.h"

using namespace std;
using namespace Entity;

TEST(ViewTest,Create)
{
	View foo;
	for(int eid: foo)
	{
		cout << "neat " << eid << endl;
	}
/*
	cout << "Hi" << endl;
	view->update(0);	
	view->update(1);	
	view->update(2);	
	
	view->add(0);
	view->remove(0);

	for(int eid: view)
	{
		cout << eid << endl;
	}
*/
}
