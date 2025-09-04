#include <iostream>
#include <vector>
#include <random>

int GenInt(int a, int b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(a, b);
	return dis(gen);
}

double GenDouble(double a, double b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(a, b);
	return dis(gen);
}

struct cargo
{
	int weight;
	double cost;
};

void swap(int* a, int* b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

void SortShell(double* A, int* Ind, int n)
{
	int i, j, h;
	for (h = 1; h <= n / 9; h = h * 3 + 1);
	while (h >= 1)
	{
		for (i = h; i < n; i++)
			for (j = i - h; (j >= 0) && (A[Ind[j]] < A[Ind[j + h]]); j -= h)
				swap(&Ind[j], &Ind[j + h]);
		h = (h - 1) / 3;
	}
}

double greedy(std::vector<cargo>& cargoes, int W)
{
	double* ratio = new double[cargoes.size()];
	int* Ind = new int[cargoes.size()];
	for (int i = 0; i < cargoes.size(); i++)
	{
		ratio[i] = cargoes[i].cost / (double)(cargoes[i].weight);
		Ind[i] = i;
	}

	SortShell(ratio, Ind, cargoes.size());

	double max_cost = 0.0;
	int current_weight = 0;
	int k = 0;
	while ((current_weight < W) && (k < cargoes.size()))
	{
		if ((current_weight + cargoes[Ind[k]].weight) < W)
		{
			current_weight += cargoes[Ind[k]].weight;
			max_cost += cargoes[Ind[k]].cost;
		}
		k++;
	}
	return max_cost;
}

void backtracking(std::vector<cargo>& cargoes, int W, std::vector<bool>& use, int current_weight, double max_cost, double& best_cost)
{
	if (current_weight > W) 
	{
		return;
	}

	best_cost = std::max(max_cost, best_cost);

	for (int i = 0; i < cargoes.size(); i++)
	{
		if (!use[i] && current_weight + cargoes[i].weight <= W)
		{
			use[i] = true;
			backtracking(cargoes, W, use, current_weight + cargoes[i].weight, max_cost + cargoes[i].cost, best_cost);
			use[i] = false; 
		}
	}
}

double dynamic_programming(std::vector<cargo>& cargoes, int W)
{
	std::vector<std::vector<double>> A(cargoes.size() + 1, std::vector<double>(W + 1, 0));

	for (int k = 1; k <= cargoes.size(); k++)
	{
		for (int w = 1; w <= W; w++)
		{
			if (w >= cargoes[k - 1].weight)
			{
				A[k][w] = std::max(A[k - 1][w], A[k - 1][w - cargoes[k - 1].weight] + cargoes[k - 1].cost);
			}
			else
			{
				A[k][w] = A[k - 1][w];
			}
		}
	}
	
	//std::cout << "\n";
	//for (int k = 0; k <= cargoes.size(); k++)
	//{
	//	for (int w = 0; w <= W; w++)
	//	{
	//		printf("%6.2f ", A[k][w]);
	//	}
	//	std::cout << "\n";
	//}

	return A[cargoes.size()][W];
}

void main()
{
	setlocale(LC_ALL, "rus");
	int n;
	std::cout << "Введите n: ";
	std::cin >> n;

	std::vector<cargo> cargoes(n);

	//initialization start values
	int W = 0;

	for (int i = 0; i < n; i++)
	{
		//std::cin >> cargoes[i].weight >> cargoes[i].cost;
		cargoes[i].weight = GenInt(1, 10);
		cargoes[i].cost = GenDouble(5, 25);
		W += cargoes[i].weight;
	}

	W /= 2;

	//all cargoes
	for (int i = 0; i < n; i++)
	{
		std::cout << "weight = " << cargoes[i].weight << "; cost = " << cargoes[i].cost << ";\n";
	}
	std::cout << "W = " << W << ";\n";

	//greedy algorithm
	double greedy_max_cost = greedy(cargoes, W);
	std::cout << "\ngreedy_max_cost = " << greedy_max_cost << "\n";

	//backtracking algorithm
	if (n < 15)
	{
		std::vector<bool> use(n);
		for (int i = 0; i < n; i++)
		{
			use[i] = false;
		}
		int current_weight = 0;
		double max_cost = 0.0;
		double best_cost = 0.0;
		backtracking(cargoes, W, use, current_weight, max_cost, best_cost);
		std::cout << "\nbacktracking_max_cost = " << best_cost << "\n";
	}

	//dynamic programming algorithm
	double dynamic_programming_max_cost = dynamic_programming(cargoes, W);
	std::cout << "\ndynamic_programming_max_cost = " << dynamic_programming_max_cost << "\n";
}