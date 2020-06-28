/*
 * LRUCache.cc
 *
 *  Created on: Jul 7, 2019
 *      Author: gongw
 */
#include <unordered_map>
#include <list>

class LRUCache {
	int m_capacity;
	std::unordered_map<int, std::pair<int, int>::iterator> m_map;
	std::list<std::pair<int, int>> m_list;
public:
	LRUCache(int capacity): m_capacity(capacity) {}

	int get(int key) {
		auto found_iter = m_map.find(key);
		if (found_iter == m_map.end())
			return -1;
		m_list.splice(m_list.begin(), m_list, found_iter->second);
		return found_iter->second->second;
	}

	void set(int key, int value) {
		auto found_iter = m_map.find(key);
		if (found_iter != m_map.end()) {
			// key existed
			m_list.splice(m_list.begin(), m_list, found_iter->second);
			found_iter->second->second = value;
		}

		if (m_map.size() == m_capacity) {
			int key_to_del = m_list.back().first;
			m_list.pop_back();
			m_map.erase(key_to_del);
		}
		m_list.emplace_front(key, value);
		m_map[key] = m_list.begin();
	}
};


