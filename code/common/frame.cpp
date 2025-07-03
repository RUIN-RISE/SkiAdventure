
#include "frame.h"

uintptr_t PropertyTrigger::add_notification(PropertyNotification&& pn)
{
	uintptr_t index = 0;
	for (auto& fn : m_vec_nf) {
		if (fn == nullptr) {
			fn = std::move(pn);
			return index + 1;
		}
		index ++;
	}
	m_vec_nf.push_back(std::move(pn));
	return index + 1;
}

void PropertyTrigger::fire(uint32_t id)
{
	for (auto& fn : m_vec_nf) {
		if (fn != nullptr)
			fn(id);
	}
}
