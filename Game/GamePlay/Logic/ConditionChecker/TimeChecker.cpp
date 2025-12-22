#include "TimeChecker.h"

TimeChecker::TimeChecker(int value, float clearTime)
	: BaseChecker(value)
	, m_clearTime{ clearTime }
{
}

bool TimeChecker::IsSatisfied()
{
	return (m_clearTime <= m_value);
}
