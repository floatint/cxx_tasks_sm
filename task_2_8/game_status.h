#pragma once


enum class GameStatus {
	//Ќовостей нет, играем дальше
	Ok,
	//фермер убил крота
	MoleKilled,
	//родилс€ крот
	MoleBorn,
	//все кроты мертвы - победа
	AllMolesDead,
	//весь урожай съеден - поражение
	FieldIsEmpty
};