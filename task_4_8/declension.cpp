#include "declension.h"

QString declensionToString(Declension d) {
	switch (d)
	{
	case Declension::Nominative:
		return "������������";
	case Declension::Genetive:
		return "�����������";
	case Declension::Dative:
		return "���������";
	case Declension::Accusative:
		return "�����������";
	case Declension::Instrumental:
		return "������������";
	case Declension::Prepositional:
		return "����������";
	default:
		return "Unsupported declension";
	}
}