#pragma once
#include "Utils.hpp"

class Neural
{
private:
    float HiddenLayerBias[BRAIN_HIDDEN_LAYERS][BRAIN_HIDDEN_LAYER_SIZE];
    float HiddenLayerResult[BRAIN_HIDDEN_LAYERS][BRAIN_HIDDEN_LAYER_SIZE];
    float WeightsIL_HL1[BRAIN_HIDDEN_LAYER_SIZE][BRAIN_INPUTS];
    float WeightsHL1_HL2[BRAIN_HIDDEN_LAYER_SIZE][BRAIN_HIDDEN_LAYER_SIZE];
    float WeightsHL2_OL[BRAIN_OUTPUTS][BRAIN_HIDDEN_LAYER_SIZE];

public:
    Neural();
    Neural(const Neural &Heredity);
    ~Neural();
    void Solve(float Input[BRAIN_INPUTS], float Output[BRAIN_OUTPUTS]);
};