#pragma once

#include <vector>
#include <algorithm>
#include <unordered_set>

#include <iostream>

namespace utility {
	class ContainerUtility {
	public:
		static ContainerUtility* getInstance();

		template<typename T>
		bool isVectorEqual(std::vector<T>& lhs, std::vector<T>& rhs) {
			// Before sorting check if both vectors have the same Size
			if (lhs.size() != rhs.size())
				return false;

			for (const auto& lItem : lhs) {
				for (unsigned int i = 0; i < lhs.size(); i++) {
					if (*lItem != *rhs[i])
						return false;
				}
			}

			return true;
		}

	private:
		ContainerUtility();
		ContainerUtility(const ContainerUtility& other);
	};
}