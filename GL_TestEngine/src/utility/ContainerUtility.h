#pragma once

#include <vector>
#include <algorithm>
#include <unordered_set>

namespace utility {
	class ContainerUtility {
	public:
		static ContainerUtility* getInstance();

		// This is slow!
		template<typename T>
		bool isVectorEqual(std::vector<T>& lhs, std::vector<T>& rhs) {
			// Before sorting check if both vectors have the same Size
			if (lhs.size() != rhs.size())
				return false;

			// Sort Vectors before checking for equality
			std::sort(rhs.begin(), rhs.end());
			std::sort(lhs.begin(), lhs.end());

			return rhs == lhs;
		}

	private:
		ContainerUtility();
		ContainerUtility(const ContainerUtility& other);
	};
}