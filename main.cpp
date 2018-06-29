/*
 main.cpp
 Knapsack
 
 Copyright � 2018  Dominik Witczak
 
 This program is free software : you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.If not, see <https://www.gnu.org/licenses/>.
 */

#include <initializer_list>
#include <list>
#include <iostream>

/*
Knapsack is a class for representing a Knapsack problem instantion:
#Member Variables:
#-------------------------------------------------------------------
int		m_size		(private):
	the capacity of Knapsack
int		m_elems		(private):
	number of elements we can choose from while packing
int*	m_weights	(private):
	pointer to a dynamic table, representing the size of an element
int*	m_values	(private):
	pointer to a dynamic table, representing the value of an element	
#Methods:
#-------------------------------------------------------------------
expect for constructor and destructor there are no other methods
*/

class Knapsack {
friend class KnapsackSolver;
public:
	Knapsack(int size, int n, std::initializer_list<int> weights, std::initializer_list<int> values) {
		m_size = size;
		m_elems = n;
		m_weights = new int[n];
		int idx = 0;
		for (auto elem : weights)
			m_weights[idx++] = elem;
		m_values = new int[n];
		idx = 0;
		for (auto elem : values)
			m_values[idx++] = elem;
	}
	~Knapsack() {
		delete m_weights;
		delete m_values;
	}

protected:
private:
	int m_size;
	int m_elems;
	int *m_weights;
	int *m_values;
};

/*
KnapsackSolver is a class for solving a Knapsack problem instantion, it's a friend of Knapsack class:
#Member Variables:
#-------------------------------------------------------------------
	NONE	
#Methods:
#-------------------------------------------------------------------
STATIC VOID solve(Knapsack* const sack):
	solves problem dynamically for given Knapsack (passed by pointer, assuring given Knapsack will not be modified),
	then prints solution
*/

class KnapsackSolver {
public:
	static void solve(Knapsack const *sack) {
		//Create a dynamic table of pointers that will be our workfield
		int ** workfield = new int*[sack->m_elems + 1];
		//Create a list for our solution
		std::list<int> sol;
		//Expand to a 2d table of ints
		for (int i = 0; i < sack->m_elems + 1; i++) {
			workfield[i] = new int[sack->m_size + 1];
		}
		//Initialize the left and top border with 0's
		for (int i = 0; i < sack->m_size + 1; i++) 
			workfield[0][i] = 0;
		for (int i = 0; i < sack->m_elems + 1; i++)
			workfield[i][0] = 0;
		
		//Solve problem dynamically
		for (int i = 1; i < sack->m_elems + 1; i++) {//solve evry verse, evry verse stand for an i-th element
			for (int j = 1; j < sack->m_size + 1; j++) {//solve evry column, evry column stand for a Knapsack with capacity=j
				//if the element doesn't fits
				if (j < sack->m_weights[i - 1]) { 
					workfield[i][j] = workfield[i - 1][j]; //rewrite from top
				}
				//if the element fit
				else { 
					int a = workfield[i-1][j];
					int b = workfield[i-1][j - sack->m_weights[i - 1]] + sack->m_values[i - 1]; 
					workfield[i][j] = a > b ? a : b;//look what's better rewrite from top, or fit our element
				}
			}
		}



		//Write the solution
		int i = sack->m_elems;
		int j = sack->m_size;
		while (j>0 && i > 0) {
			if (workfield[i - 1][j] != workfield[i][j]) {
			//Write to solution

				sol.push_back(i);

			//Move left
				i--;
				j -= sack->m_weights[i];

			}
			else {
			//Move up
				i--;
			}
		}

		//Write solution
		std::cout << "\n\nsol = { ";
		for (auto elem : sol)
			std::cout << elem << ", ";
		
		std::cout << " }\n";

		//Write the total sum
		std::cout << "sum = " << workfield[sack->m_elems]sack->m_size];

		delete workfield;
	}
protected:
private:
};

int main()
{
	Knapsack sack(6, 5, { 1,4,3,2,1 }, { 2,10,5,6,1 });

	std::cout << "\n\n\n";

	KnapsackSolver::solve(&sack);

	return 0;
}

