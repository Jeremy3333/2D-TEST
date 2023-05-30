#pragma once

class Neural
{
private:
    float HiddenLayerBias[2][4];
    float HiddenLayerResult[2][4];
    float WeightsIL_HL1[4][2];
    float WeightsHL1_HL2[4][4];
    float WeightsHL2_OL[2][4];
public:
    Neural();
    Neural(const Neural &Heredity);
    ~Neural();
    void Solve(float Input[2], float Output[2]);
};