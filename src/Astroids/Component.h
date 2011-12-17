#pragma once

class Component
{
public:
	virtual ~Component() { }
};

class NullComponent : public Component
{
public:
	virtual ~NullComponent() { }
};
