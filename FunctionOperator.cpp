#include "StdAfx.h"
#include "FunctionOperator.h"
#include "Exceptions.h"
#include "Expression.h"

FunctionOperator::FunctionOperator()
{
}

FunctionOperator::~FunctionOperator()
{
}

Expression *FunctionOperator::Group(PartsIterator part)
{
	if(part.IsFirst())
		throw ParseException("No operand on left side of infix operator.");
	if(part.IsLast())
		throw ParseException("No operand on right side of infix operator.");

	PartsIterator prevItr = part.Prev();
	PartsIterator nextItr = part.Next();
	Expression *head = (*prevItr)->Group(prevItr);
	Expression *leaves = (*nextItr)->Group(nextItr);

	leaves->Head(head);
	prevItr.Erase();
	nextItr.Erase();
	delete this;
	*part = leaves;

	return leaves;
}
