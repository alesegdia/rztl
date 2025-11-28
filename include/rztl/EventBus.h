#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <algorithm>

namespace rztl {

class EventBus
{
public:
	using HandlerID = uint32_t;

	template<typename T>
	HandlerID SubscribeToEvent(std::function<void(const T&)> handler)
	{
		auto& vec = handlers[typeid(T)];
		HandlerID id = ++lastID;
		vec.push_back(HandlerWrapper{ id, [handler] (const void* ev) { handler(*static_cast<const T*>(ev)); }
		});
		return id;
	}

	template<typename T>
	void UnsubscribeFromEvent(HandlerID id)
	{
		auto it = handlers.find(typeid(T));
		if(it == handlers.end()) return;

		auto& vec = it->second;

		vec.erase( std::remove_if(vec.begin(), vec.end(), [&] (auto& hw) { return hw.id == id; }), vec.end());
	}

	template<typename T>
	void FireEvent(const T& ev)
	{
		auto it = handlers.find(typeid(T));
		if(it == handlers.end()) return;

		for(auto& hw : it->second)
			hw.fn(&ev);
	}

private:
	struct HandlerWrapper
	{
		HandlerID id;
		std::function<void(const void*)> fn;
	};

	std::unordered_map<std::type_index, std::vector<HandlerWrapper>> handlers;
	HandlerID lastID = 0;

};

} // namespace aether::core