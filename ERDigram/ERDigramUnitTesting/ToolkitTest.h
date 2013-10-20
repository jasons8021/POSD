#ifndef TOOLKITTEST_H_
#define TOOLKITTEST_H_

#include "gtest/gtest.h"
#include "Toolkit.h"

using namespace std;

class ToolkitTest : public :: testing :: Test
{
protected:
	Toolkit toolkit;
};

#endif