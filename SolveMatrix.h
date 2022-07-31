#include <algorithm>
#include "Matrix.h"
#pragma once

using namespace std;

int minIndex(vector<double> arr);
int maxIndex(vector<double> arr);
void minCashFlowRec(AdjMatrix& matrix, vector<double> amount);
void minCashFlow(AdjMatrix& matrix);