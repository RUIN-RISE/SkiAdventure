
#ifndef __FRAME_H__
#define __FRAME_H__

typedef std::function<void(uint32_t)>  PropertyNotification;

class PropertyTrigger {
public:
	PropertyTrigger() noexcept {}
	PropertyTrigger(const PropertyTrigger&) = delete;
	~PropertyTrigger() noexcept {}

	PropertyTrigger& operator=(const PropertyTrigger&) = delete;

	void clear_notifications() noexcept {
		m_vec_nf.clear();
	}

	uintptr_t add_notification(PropertyNotification&& pn);

	void remove_notification(uintptr_t cookie) noexcept;

protected:
	void fire(uint32_t id);

private:
	std::vector<PropertyNotification> m_vec_nf;
};

#endif
