#include "Solver.h"
#include <fstream>

void GenericSolver::solve(data_input * input, data_input * target, vector<int> selectedIndexes)
{
	std::ofstream fout("submission.csv");
	fout << "UserId:ItemId,Prediction"<< std::endl;

	for (int i = 0; i < target->length; i++)
	{
		data_node node = target->data[i];
		node.value = predict(input, node.userId, node.itemId);
		fout << node.userId <<":"<< node.itemId<< ","<< node.value << std::endl;
	}
	fout.close();
}

ConstantOutputSolver::ConstantOutputSolver(){}

float ConstantOutputSolver::predict(data_input * input, string targetUser, string targetItem)
{
	return 5.5f;
}

UserAveragesSolver::UserAveragesSolver(){}

float UserAveragesSolver::predict(data_input * input, string targetUser, string targetItem)
{
	auto userIterator = input->userInfo.find(targetUser);
	if (userIterator == input->userInfo.end())
	{
		//o usu�rio n�o tem notas, o chute escolhido ser� a m�dia do item
		auto itemIterator = input->userInfo.find(targetUser);
		if (itemIterator == input->userInfo.end())
		{
			//n�o tem nem o usu�rio nem o item no treino, o chute ser� a m�dia geral
			return input->generalAverage;
		}
		return itemIterator->second->getAverage();
	}
	return userIterator->second->getAverage();
}