#include "declension.h"

QString declensionToString(Declension d) {
	switch (d)
	{
	case Declension::Nominative:
		return QString::fromUtf8(u8"������������");
	case Declension::Genetive:
		return QString::fromUtf8(u8"�����������");
	case Declension::Dative:
		return QString::fromUtf8(u8"���������");
	case Declension::Accusative:
		return QString::fromUtf8(u8"�����������");
	case Declension::Instrumental:
		return QString::fromUtf8(u8"������������");
	case Declension::Prepositional:
		return QString::fromUtf8(u8"����������");
	default:
		return QString::fromUtf8(u8"Unsupported declension");
	}
}