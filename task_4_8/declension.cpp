#include "declension.h"

QString declensionToString(Declension d) {
	switch (d)
	{
	case Declension::Nominative:
		return QString::fromUtf8(u8"именительный");
	case Declension::Genetive:
		return QString::fromUtf8(u8"родительный");
	case Declension::Dative:
		return QString::fromUtf8(u8"дательный");
	case Declension::Accusative:
		return QString::fromUtf8(u8"винительный");
	case Declension::Instrumental:
		return QString::fromUtf8(u8"творительный");
	case Declension::Prepositional:
		return QString::fromUtf8(u8"предложный");
	default:
		return QString::fromUtf8(u8"Unsupported declension");
	}
}