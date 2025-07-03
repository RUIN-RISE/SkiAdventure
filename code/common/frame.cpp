#include "frame.h"

uintptr_t PropertyTrigger::add_notification(PropertyNotification&& pn) {
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

void PropertyTrigger::remove_notification(uintptr_t cookie) noexcept {
	assert( cookie > 0 && cookie <= m_vec_nf.size() );
	m_vec_nf[cookie - 1] = nullptr;
}

void PropertyTrigger::fire(uint32_t id) {
	// std::cerr << "fire" << std::endl;
	for (auto& fn : m_vec_nf) {
		if (fn != nullptr)
			fn(id);
	}
}
