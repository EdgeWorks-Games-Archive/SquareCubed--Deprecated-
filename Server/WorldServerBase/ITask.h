#pragma once

namespace Server {
	namespace Units {
		namespace AI {
			class ITask {
			public:
				virtual ~ITask();
				virtual void Update(const float delta);
			};
		}
	}
}