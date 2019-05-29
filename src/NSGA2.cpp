#include<NSGA2.hpp>

namespace plt = matplotlibcpp;

int main()
{
    NSGA2 NSGA2;

    std::vector<double> solution; 
    
    for(int i=0; i<NSGA2.pop_size;i++)
    {
        solution.push_back(NSGA2.min_x + (NSGA2.max_x - NSGA2.min_x) * NSGA2.create_random());
    }
    int gen_no=0;
    std::vector<double> function1_values;
    std::vector<double> function2_values;

    while(gen_no < NSGA2.max_gen)
    {
        for(int i=0;i<NSGA2.pop_size;i++)
        {
            function1_values.push_back(NSGA2.objective_function_1(solution[i]));
        }    
        for(int i=0;i<NSGA2.pop_size;i++)
        {
            function2_values.push_back(NSGA2.objective_function_2(solution[i]));
        }
        std::vector<std::vector<double>> non_dominated_sorted_solution = NSGA2.fast_non_dominated_sort(function1_values,function2_values);
        std::cout << "the best front for generation number " << gen_no << " is" <<std::endl;
        

        std::vector<double> crowding_distance_values;
        for(int i=0;i<non_dominated_sorted_solution.size();i++)
        {
            crowding_distance_values.push_back(NSGA2.crowding_distance(function1_values,function2_values,non_dominated_sorted_solution));
        }
        std::vector<double> solution2 = solution;
        while(solution2.size() != 2*NSGA2.pop_size)
        {
            double a1 = NSGA2.create_random();
            double b1 = NSGA2.create_random();
            solution2.push_back(NSGA2.crossover(solution[a1],solution[b1]));
        }
        std::vector<double> function1_values2;
        std::vector<double> function2_values2;
        for(int i; i<2*NSGA2.pop_size;i++)
        {
            function1_values2.push_back(NSGA2.objective_function_1(solution2[i]));
        }
        for(int i; i<2*NSGA2.pop_size;i++)
        {
            function2_values2.push_back(NSGA2.objective_function_2(solution2[i]));
        }
        std::vector<std::vector<double>> non_dominated_sorted_solution2 = NSGA2.fast_non_dominated_sort(function1_values2,function2_values2);
        std::vector<double> crowding_distance_values2;
        for(int i=0;i<non_dominated_sorted_solution2.size();i++)
        {
            crowding_distance_values2.push_back(NSGA2.crowding_distance(function1_values2,function2_values2,non_dominated_sorted_solution2));
        }
        std::vector<double> new_solution;
        for(int i=0;i<non_dominated_sorted_solution2.size();i++)
        {
            std::vector<double> non_dominated_sorted_solution2_1;
            for(int j=0;j<non_dominated_sorted_solution2[i].size();i++)
            {
                non_dominated_sorted_solution2_1.push_back(NSGA2.index_of(non_dominated_sorted_solution2[i][j],non_dominated_sorted_solution2[i]));
            }

            front22 = NSGA2.sort_by_values(non_dominated_sorted_solution2_1,crowding_distance_values2[i]);
            for(int j=0;j<non_dominated_sorted_solution2[i].size();j++)
            {
                front = non_dominated_sorted_solution2[i][front22[j]];
            }
            std::reverse(front.begin(),front.end());
            for(int k=0; k<NSGA2.pop_size;k++)
            {
                new_solution.push_back(front[k]);
                if(new_solution.size() == NSGA2.pop_size)
                {
                    break;
                }
            }
            if(new_solution.size() == NSGA2.pop_size)
            {
                break;
            }
        }
        for(int i=0;i<new_solution.size();i++)
        {
            solution.push_back(solution2[i])
        }
        gen_no = gen_no + 1;

    }

    //plot the final front
    for(int i=0;i<function1_values[i]; i++)
    {
        std::vector<double> function1;
        function1.push_back(i * -1);
    }
    for(int i=0;i<function1_values[i]; i++)
    {
        std::vector<double> function1;
        function1.push_back(i * -1);
    }
    plt::xlabel("Function 1");
    plt::ylabel("Function 2");

    plt::scatter(function1,function2);
    plt::show();
}

