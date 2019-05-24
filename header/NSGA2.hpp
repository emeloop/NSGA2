#ifndef _NSGA2_HPP_
#define _NSGA2_HPP_

#include<stdio.h>
#include<math.h>
#include<iostream>
#include<cassert>
#include<algorithm>
#include<vector>
#include<matplotlib-cpp-starter/matplotlibcpp.h>
#include<time.h>
#include<stdlib.h>

class NSGA2 
{
    //メンバ関数
    //初期化
    void Initialization();

    public:
    //メンバ変数crowding_distance_values
    double solution, min_x, max_x;
    int pop_size = 20;
    int max_gen = 921;

    NSGA2();
    //目的関数（２つ）
    double objective_function_1(double x);
    double objective_function_2(double x);
    //crossoverってなんだろう？←これは交叉という意味。一点交叉か二点交叉かはまだわからない。
    double crossover(double a, double b);
    //mutationってなんだろ？←これは突然変異という意味。
    double mutation(double solution);
    //リストのインデックスを見つけるための関数
    int index_of(int a , std::vector<double> list);
    //vector内にある要素が存在するかを検索する関数
    int vector_finder(std::vector<double> vec, int number);
    //ソート用関数
    std::vector<double> sort_by_values(std::vector<double> list, std::vector<double> values);
    //混雑度距離の計算用関数
    std::vector<double> crowding_distance(std::vector<double> values1,std::vector<double> values2,std::vector<std::vector<double>> front);
    //NSGA-Ⅱの高速非優越ソートを実行する関数
    std::vector<std::vector<double>> fast_non_dominated_sort(std::vector<double> values1, std::vector<double> values2);
    //0~1の間でランダムな値を生成する
    double create_random(void);
};

NSGA2::NSGA2()
{
    NSGA2::Initialization();
}
double NSGA2::objective_function_1(double x)
{
    double value;
    value = pow(-x,2);
    return value;
}
double NSGA2::objective_function_2(double x)
{
    double value;
    value = pow(-x-2, 2);
    return value;
}
int NSGA2::index_of(int a, std::vector<double> list)
{
    for(int i = 0; i < list.size();i++)
    {
        if(list[i] = a)
        {
            return i;
        }
        else
        {
            return -1;
        }
    }
}
std::vector<double> NSGA2::sort_by_values(std::vector<double> list, std::vector<double> values)
{
    std::vector<double> sorted_list;
    while(sorted_list.size() != list.size())
    {
        if(vector_finder(list,index_of(*std::min_element(values.begin(),values.end()),values)))
        {
            sorted_list.push_back(index_of(*std::min_element(values.begin(),values.end()),values)));
            values[index_of(*std::min_element(values.begin(),values.end()),values))] = std::numeric_limits<double>::infinity();
        }
        return sorted_list;
    }
}
std::vector<std::vector<double>> NSGA2::fast_non_dominated_sort(std::vector<double> values1, std::vector<double> values2)
{
    std::vector<std::vector<int>> S(values1.size(),std::vector<int>(NULL,0));
    std::vector<std::vector<double>> front;
    std::vector<double> n(values1.size(),0);
    std::vector<double> rank(values1.size(),0);

    for(int p=0;p<values1.size();p++)
    {
        S[p].clear();
        n[p]=0;
        for(int q=0;q<values1.size();q++)
        {
            if((values1[p]>values1[q] && values2[p]>values2[q])|| 
            (values1[p]>=values1[q] && values2[p]>values2[q])||
            (values1[p]>values1[q] && values2[p]>=values2[q]))
            {
                auto which_q_result = std::find(S[p].begin(),S[p].end(),q);
                if(which_q_result != S[q].end())
                {
                    S[p].push_back(q);
                }
                else
                {
                    exit(0);
                }
            }
            else if((values1[q] > values1[p] && values2[q] > values2[p]) ||
                    (values1[p] >= values1[q] && values2[q] > values2[p]) ||
                    (values1[q] > values1[p] && values2[q] >= values2[p]))
            {
                n[p] = n[p] + 1;
            }
            else
            {
                exit(0);
            }
        }
        if(n[p] == 0)
        {
            rank[p] == 0;
            auto which_p_result = std::find(front.begin(),front.end(),p);
            if(which_p_result != front.end())
            {
                front[0].push_back(p);
            }
            else
            {
                exit(0);
            }
        }
    }
    int i = 0;
    while(front[i].empty == false)
    {
        std::vector<int> Q;
        for(int p = 0; p < front[i].size(); p++)
        {
            for(int q = 0; q < S[p].size(); q++)
            {
                n[q] = n[q] - 1;
                if(n[q] == 0)
                {
                    rank[q] = i + 1;
                    auto which_q_result_in_Q = std::find(Q.begin(), Q.end(), q);
                    if(which_q_result_in_Q != Q.end())
                    {
                        Q.push_back(q);
                    }
                    else
                    {
                        exit(0);
                    }
                }
            }
        }
        i = i + 1;
        front[i].push_back(Q);//二重配列に要素として配列を追加したいけどC++でのやり方がわからない。Pythonではfront.append(Q)で書かれている。
    }
    front[front.size()-1].clear;
    return front;
}
std::vector<double> NSGA2::crowding_distance(std::vector<double> values1,std::vector<double> values2,std::vector<std::vector<double>> front)
{
    std::vector<int> distance(front.size(),0);
    std::vector<double> sorted1 = sort_by_values(front, values1);//frontをsort_by_valuesにぶち込めないんですが？

}
double NSGA2::crossover(double a, double b)
{
    double r = create_random();
    if(r > 0.5)
    {
        return mutation((a + b) / 2);
    }
    else
    {
        return mutation((a - b) / 2);
    }
    

}
double NSGA2::mutation(double solution)
{
    double mutation_prob = create_random();
    if(mutation_prob < 1.0)
    {
        solution = min_x + (max_x - min_x)*create_random();
        return solution;
    }
}
void NSGA2::Initialization()
{
    double r;
    srand(time(NULL));
    r = (double)rand()/RAND_MAX;
}
int NSGA2::vector_finder(std::vector<double> vec, int number)
{
  auto itr = std::find(vec.begin(), vec.end(), number);
  size_t index = std::distance( vec.begin(), itr );
  if (index != vec.size()) { // 発見できたとき
    return 1;
  }
  else { // 発見できなかったとき
    return 0;
  }
}
double NSGA2::create_random(void)
{
    double r;
    srand(time(NULL));
    r = (double)rand()/RAND_MAX;
    return r;
}
#endif
