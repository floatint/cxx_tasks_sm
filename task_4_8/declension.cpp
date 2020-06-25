#include "declension.h"

QString declensionToString(Declension d) {
	switch (d)
	{
	case Declension::Nominative:
		return "именительный";
	case Declension::Genetive:
		return "родительный";
	case Declension::Dative:
		return "дательный";
	case Declension::Accusative:
		return "винительный";
	case Declension::Instrumental:
		return "творительный";
	case Declension::Prepositional:
		return "предложный";
	default:
		return "Unsupported declension";
	}
}