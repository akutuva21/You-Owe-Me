#include <algorithm>
#include "List.h"
#pragma once

using namespace std;

int minIndex(vector<double> arr);
int maxIndex(vector<double> arr);
void calculateAmount();
void minCashFlowRec(AdjList& list, vector<double> amount);
void minCashFlow(AdjList& list);