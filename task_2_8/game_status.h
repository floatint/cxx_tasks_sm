#pragma once

//������ ����


enum class GameStatus {
	//���� ��� �� ��������
	NotStared,
	//���� ������������
	Play,
	//������ ���� �����
	MoleKilled,
	//������� ����
	//MoleBorn,
	//��� ����� ������ - ������
	AllMolesDead,
	//���� ������ ������ - ���������
	FieldIsEmpty
};