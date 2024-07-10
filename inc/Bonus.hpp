#pragma once

#include "Object.hpp"

namespace nf {
	class Bonus : public Object {
	protected:
		nf::BonusType mBonusType;
	public:
		void setBonusType(nf::BonusType bonusType);

		nf::BonusType getBonusType();
	};
}