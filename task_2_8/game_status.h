#pragma once


enum class GameStatus {
	//�������� ���, ������ ������
	Ok,
	//������ ���� �����
	MoleKilled,
	//������� ����
	MoleBorn,
	//��� ����� ������ - ������
	AllMolesDead,
	//���� ������ ������ - ���������
	FieldIsEmpty
};