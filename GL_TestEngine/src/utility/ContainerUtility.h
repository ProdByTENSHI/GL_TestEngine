#pragma once

#include <vector>
#include <algorithm>
#include <unordered_set>

#include <iostream>

namespace engine {
	class ContainerUtility {
	public:
		static ContainerUtility* getInstance();

		template<typename T>
		bool isVectorEqual(std::vector<T>& lhs, std::vector<T>& rhs) {
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

		// TODO: Fix this
		template<typename T>
		const int getArraySize(const T array[]) {
			return sizeof(array) / sizeof(array[0]);
		}

	private:
		ContainerUtility();
		ContainerUtility(const ContainerUtility& other);
	};
}