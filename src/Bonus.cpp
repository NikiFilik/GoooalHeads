#include "Bonus.hpp"

namespace nf {
	void Bonus::setBonusType(nf::BonusType bonusType) { mBonusType = bonusType; }

	nf::BonusType Bonus::getBonusType() { return mBonusType; }
}