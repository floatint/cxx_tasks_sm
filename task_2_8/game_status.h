#pragma once

//Статус игры


enum class GameStatus {
	//Игра еще не запущена
	NotStared,
	//Игра продолжается
	Play,
	//фермер убил крота
	MoleKilled,
	//родился крот
	//MoleBorn,
	//все кроты мертвы - победа
	AllMolesDead,
	//весь урожай съеден - поражение
	FieldIsEmpty
};